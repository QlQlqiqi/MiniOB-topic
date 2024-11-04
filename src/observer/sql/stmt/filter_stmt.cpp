/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2022/5/22.
//

#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "common/rc.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include <sql/parser/expression_binder.h>

FilterStmt::~FilterStmt() = default;

RC FilterStmt::create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *table_map,
    const Expression *conditions, FilterStmt *&stmt)
{
  free(stmt);
  
  RC rc = RC::SUCCESS;

  FilterStmt *tmp_stmt    = new FilterStmt();
  BinderContext binder_context;

    // tmp_stmt->set_expr(conditions->Clone());
    // auto condition_expr = tmp_stmt->expr_.get();
  for (auto [table_name, table]:(*table_map)) {
    binder_context.add_table(table);
    rc = binder_context.add_alias(table_name, table); //这里传进来的table_map 可能存在别名,所以需要加入映射
    if (OB_FAIL(rc)) { return rc; }
  }
  // collect query fields in `select` statement
  vector<unique_ptr<Expression>> bound_expressions;
  ExpressionBinder               expression_binder(binder_context);

  if (conditions) {
    vector<unique_ptr<Expression>> filter_expressions;
    filter_expressions.reserve(1);
    auto l  = conditions->Clone();

    RC   rc = expression_binder.bind_expression(l, filter_expressions, false, default_table);
    if (OB_FAIL(rc)) {
      LOG_INFO("bind expression failed. rc=%s", strrc(rc));
      return rc;
    }

    ASSERT(filter_expressions.size() == 1, "the number of bounded expr should be one");

    auto prepare_subquery = [db, table_map](Expression* expr) {
      RC rc = RC::SUCCESS;
      if (expr->type() == ExprType::SUBQUERY) {
        auto  subquery_expr = static_cast<SubQueryExpr *>(expr);
        Stmt *select_stmt   = nullptr;
        if (RC rc = SelectStmt::create(db, *subquery_expr->sql_node(), select_stmt, *table_map); RC::SUCCESS != rc)
        {
          return rc;
        }
        if (select_stmt->type() != StmtType::SELECT) { return RC::INVALID_ARGUMENT; }
        subquery_expr->set_select_stmt(static_cast<SelectStmt *>(select_stmt));
      }
      return rc;
    };

    if (OB_FAIL(filter_expressions[0]->traverse(prepare_subquery)))
    {
      LOG_WARN("zyq: filter expr traverse failed");
      return RC::INTERNAL;
    };
    tmp_stmt->set_expr(std::move(filter_expressions[0]));
  }

  stmt = tmp_stmt;
  return rc;
}


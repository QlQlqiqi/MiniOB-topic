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
#include "common/lang/string.h"
#include "common/log/log.h"
#include "common/rc.h"
#include "storage/db/db.h"
#include "storage/table/table.h"

FilterStmt::~FilterStmt() = default;

RC FilterStmt::create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const Expression *conditions, FilterStmt *&stmt)
{
  RC rc = RC::SUCCESS;
  stmt  = nullptr;

  FilterStmt *tmp_stmt    = new FilterStmt();
  // FilterUnit *filter_unit = nullptr;

  if (conditions) {
    // 使用 expr
    tmp_stmt->set_expr(conditions->Clone());
  }

  stmt = tmp_stmt;
  return rc;
}

RC FilterStmt::create_filter_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const Expression *condition, FilterUnit *&filter_unit)
{
  RC rc = RC::SUCCESS;

  // 这里 condition 应该是 ComparisonExpr
  if(condition->type() != ExprType::COMPARISON) {
    LOG_WARN("condition should be ComparisonExpr, but now is: ", condition->type());
    return RC::UNSUPPORTED;
  }

  auto expr = static_cast<const ComparisonExpr*>(condition);

  CompOp comp = expr->comp();
  if (comp < EQUAL_TO || comp >= NO_OP) {
    LOG_WARN("invalid compare operator : %d", comp);
    return RC::INVALID_ARGUMENT;
  }

  filter_unit = new FilterUnit;
  filter_unit->set_comp(comp);
  filter_unit->set_left(expr->left_con()->Clone());
  filter_unit->set_right(expr->right_con()->Clone());

  // 检查两个类型是否能够比较
  return rc;
}

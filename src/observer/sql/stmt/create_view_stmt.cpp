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
// Created by Wangyunlai on 2023/6/13.
//

#include "common/log/log.h"
#include "common/types.h"
#include "sql/stmt/create_view_stmt.h"
#include "event/sql_debug.h"

RC CreateViewStmt::create(Db *db, const CreateViewSqlNode &create_view, Stmt *&stmt)
{
  std::unique_ptr<SelectStmt> select_stmt_ptr = nullptr;
  Stmt* select_stmt = nullptr;
  ASSERT(create_view.select_stmt != nullptr, "select_stmt is null");
  ASSERT(create_view.select_stmt->flag == SCF_SELECT, "select_stmt is not select");
  RC rc = Stmt::create_stmt(db, *create_view.select_stmt, select_stmt);
  if (rc != RC::SUCCESS)
    return rc;

  select_stmt_ptr.reset(static_cast<SelectStmt *>(select_stmt));

  if(!create_view.attr_ids.empty()){
    if(create_view.attr_ids.size() != select_stmt_ptr->query_expressions().size()){
      LOG_WARN("column num not match");
      return RC::INVALID_ARGUMENT;
    }
    /*Todo set alias*/
    // for(auto& query_expr: select_stmt_ptr->query_expressions()){
      // query_expr->set_alias(query_expr->field_name());
    // }
  }
  auto *create_view_stmt = new CreateViewStmt(create_view.view_name, create_view.attr_ids, std::move(select_stmt_ptr), create_view.select_sql);
  create_view_stmt->view_name_ = create_view.view_name;
  stmt = create_view_stmt;
  return RC::SUCCESS;
}


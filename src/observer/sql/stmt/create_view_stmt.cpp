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
#include "sql/expr/expression.h"
#include "storage/db/db.h"
#include "event/sql_debug.h"

RC CreateViewStmt::create(Db *db, const CreateViewSqlNode &create_view, Stmt *&stmt)
{
  std::unique_ptr<SelectStmt> select_stmt_ptr = nullptr;
  Stmt* select_stmt = nullptr;
  std::string view_name = create_view.view_name;
  ASSERT(create_view.select_stmt != nullptr, "select_stmt is null");
  ASSERT(create_view.select_stmt->flag == SCF_SELECT, "select_stmt is not select");
  RC rc = Stmt::create_stmt(db, *create_view.select_stmt, select_stmt);

  if (rc != RC::SUCCESS)
    return rc;

  if (view_name.empty()) {
      LOG_WARN("invalid argument. view name is null");
      return RC::INVALID_ARGUMENT;
  }

  if (db->find_table(view_name.c_str()) != nullptr) {
      LOG_WARN("view exists.");
      return RC::INVALID_ARGUMENT;
  }

  select_stmt_ptr.reset(static_cast<SelectStmt *>(select_stmt));

  auto &attr_expressions = select_stmt_ptr->query_expressions();
  std::vector<FieldMeta> field_metas;

  if(!create_view.attr_ids.empty()){
    if(create_view.attr_ids.size() != attr_expressions.size()){
      LOG_WARN("column num not match");
      return RC::INVALID_ARGUMENT;
    }
    /*Todo set alias*/
    // for(auto& query_expr: select_stmt_ptr->query_expressions()){
      // query_expr->set_alias(query_expr->field_name());
    // }
  }

  bool has_exprssion = false;
  bool is_single_table = select_stmt_ptr->tables().size() == 1;
  int offset = 0;
  
  auto *create_view_stmt = new CreateViewStmt(create_view.view_name, create_view.attr_ids, std::move(select_stmt_ptr), create_view.select_sql);

  std::vector<std::unique_ptr<Field>>& origin_fields = create_view_stmt->origin_fields_;
  for(auto &expr : attr_expressions){
    AttrInfoSqlNode attr_info;
    Expression* expression = expr.get();

    attr_info.type = expression->value_type();
    attr_info.name = create_view.attr_ids.empty() ? expression->name() : create_view.attr_ids[offset];
    attr_info.nullable = expression->value_nullable();       
    //如果为nullable ，应该多一个字节，标识是否为空 
    attr_info.length = attr_info.nullable ? expression->value_length() + 1: expression->value_length();

    switch(expr->type()){
      case ExprType::ARITHMETIC:
      case ExprType::COMPARISON:
      case ExprType::SUBQUERY:
      case ExprType::AGGREGATION:{
        has_exprssion = true;
        origin_fields.push_back(nullptr);
      } break;
      case ExprType::FIELD:{
        FieldExpr * field_expr = static_cast<FieldExpr*>(expression);
        origin_fields.push_back(std::make_unique<Field>(field_expr->field()));
      } break;
      case ExprType::VALUE:{
        origin_fields.push_back(nullptr);
      } break;
      default:{
        LOG_WARN("invalid argument. expression type is not supported");
        return RC::INVALID_ARGUMENT;
      }
    }

    // auto field_meta = FieldMeta(attr_info.name.c_str(), attr_info.type, offset++, attr_info.length,true, field_id++, attr_info.nullable);
    create_view_stmt->attr_infos_.emplace_back(attr_info);
  }
  
  create_view_stmt->is_insertable_ = !has_exprssion && is_single_table;
  create_view_stmt->is_updateable_ = !has_exprssion && is_single_table;
  stmt = create_view_stmt;
  return RC::SUCCESS;
}


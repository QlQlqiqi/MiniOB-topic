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
#include "common/type/vector_type.h"
#include "common/types.h"
#include "sql/stmt/create_table_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "sql/expr/expression.h"
#include "event/sql_debug.h"

RC CreateTableStmt::create(Db *db, const CreateTableSqlNode &create_table, Stmt *&stmt)
{
  StorageFormat storage_format = StorageFormat::UNKNOWN_FORMAT;
  if (create_table.storage_format.length() == 0) {
    storage_format = StorageFormat::ROW_FORMAT;
  } else {
    storage_format = get_storage_format(create_table.storage_format.c_str());
  }
  if (storage_format == StorageFormat::UNKNOWN_FORMAT) {
    return RC::INVALID_ARGUMENT;
  }
  // vector 的维度不得过高
  for (auto &attr : create_table.attr_infos) {
    if (attr.type == AttrType::VECTORS) {
      if (attr.dim > VECTOR_MAX_SIZE) {
        LOG_WARN("dont support too high dim for vector: %d", attr.dim);
        return RC::INVALID_ARGUMENT;
      }
    }
  }

  //select_stmt
  RC rc = RC::SUCCESS;
  auto& select_sql_node = create_table.select_sql_node;
  auto attr_infos = create_table.attr_infos;
  if(select_sql_node != nullptr){
    Stmt* select_stmt = nullptr;
    ASSERT(create_table.select_sql_node->flag == SCF_SELECT, "select_stmt is not select");
    rc = Stmt::create_stmt(db, *create_table.select_sql_node, select_stmt);
    if(OB_FAIL(rc)){
      return rc;
    }
    ASSERT(select_stmt != nullptr && select_stmt->type() == StmtType::SELECT, "select stmt is null");
    std::unique_ptr<SelectStmt> select_stmt_ptr = nullptr;
    select_stmt_ptr.reset(static_cast<SelectStmt*>(select_stmt));
    auto &select_query_expressions = select_stmt_ptr->query_expressions();

    //创建表的时候没有指定类型
    if(attr_infos.size() == 0){
      attr_infos.resize(select_query_expressions.size());
      for(size_t i = 0; i < select_query_expressions.size(); i++){
        auto &query_expr = select_query_expressions[i];
        auto &attr_info = attr_infos[i];
        if(query_expr->type() == ExprType::FIELD){
          attr_info.name = query_expr->has_alias() ? query_expr->alias() : static_cast<FieldExpr*>(query_expr.get())->field_name();
        }else{
          attr_info.name = query_expr->has_alias() ? query_expr->alias() : query_expr->name();
        }
        attr_info.type = query_expr->value_type();
        attr_info.nullable = query_expr->value_nullable();       
        attr_info.length = query_expr->value_length();
        attr_info.dim = attr_info.type == AttrType::VECTORS? attr_info.length : 0;
        attr_info.high_vector = attr_info.dim > VECTOR_HIGH_DIM;
      }
    }else{
      if(attr_infos.size() != select_query_expressions.size()){
        LOG_WARN("select query expressions size %d not equal to attr infos size %d", select_query_expressions.size(), attr_infos.size());
        return RC::INVALID_ARGUMENT;
      }
    }
    stmt = new CreateTableStmt(create_table.relation_name, std::move(attr_infos), storage_format, std::move(select_stmt_ptr));
  }else{
    stmt = new CreateTableStmt(create_table.relation_name, std::move(attr_infos), storage_format, nullptr);
  }
  sql_debug("create table statement: table name %s", create_table.relation_name.c_str());
  return RC::SUCCESS;
}

StorageFormat CreateTableStmt::get_storage_format(const char *format_str) {
  StorageFormat format = StorageFormat::UNKNOWN_FORMAT;
  if (0 == strcasecmp(format_str, "ROW")) {
    format = StorageFormat::ROW_FORMAT;
  } else if (0 == strcasecmp(format_str, "PAX")) {
    format = StorageFormat::PAX_FORMAT;
  } else {
    format = StorageFormat::UNKNOWN_FORMAT;
  }
  return format;
}

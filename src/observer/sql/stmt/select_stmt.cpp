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
// Created by Wangyunlai on 2022/6/6.
//

#include "sql/stmt/select_stmt.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include "sql/parser/expression_binder.h"

using namespace std;
using namespace common;

SelectStmt::~SelectStmt()
{
  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
}

RC SelectStmt::create(Db *db, SelectSqlNode &select_sql, Stmt *&stmt)
{
  if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }

  BinderContext binder_context;

  // collect tables in `from` statement
  vector<Table *>                tables;
  unordered_map<string, Table *> table_map;

  auto check_and_collect_table = [&](const std::string& relation, Table **table){
    const char *table_name = relation.c_str();
    if (nullptr == table_name) {
      LOG_WARN("invalid argument. relation name is null.");
      return RC::INVALID_ARGUMENT;
    }

    *table = db->find_table(table_name);
    if (nullptr == *table) {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }
    return RC::SUCCESS;
  };

  for (size_t i = 0; i < select_sql.relations.size(); i++) {
    const char *table_name = select_sql.relations[i].c_str();
    Table* table = nullptr;
    RC rc = check_and_collect_table(select_sql.relations[i], &table);

    if(rc != RC::SUCCESS){
      return rc;
    }

    binder_context.add_table(table);
    tables.push_back(table);
    table_map.insert({table_name, table});
  }



  // inner join statement
  std::unordered_map<Table* , std::unique_ptr<FilterStmt>> join_conditions;
  if(select_sql.inner_join != nullptr){
    auto &inner_join_relations = select_sql.inner_join->relations;
    auto &inner_join_conditions = select_sql.inner_join->conditions; 
    assert(inner_join_conditions.size() == inner_join_relations.size());
    for(size_t i = 0; i < inner_join_relations.size(); i++){
      Table *table = nullptr;
      RC rc = RC::SUCCESS;
      if((rc = check_and_collect_table(inner_join_relations[i], &table)) != RC::SUCCESS){
        return rc;
      }

      binder_context.add_table(table);
      tables.push_back(table);
      table_map.insert({inner_join_relations[i], table});

      FilterStmt *filter_stmt = nullptr;
      rc                      = FilterStmt::create(db,
        table,
        &table_map,
        inner_join_conditions[i].data(),
        static_cast<int>(inner_join_conditions[i].size()),
        filter_stmt);
      if (rc != RC::SUCCESS) {
        LOG_WARN("cannot construct filter stmt");
        return rc;
      }
      join_conditions.insert({table, std::unique_ptr<FilterStmt>(filter_stmt)});
    }
  }

  bool mutil_tables = tables.size() > 1;

  // collect query fields in `select` statement
  vector<unique_ptr<Expression>> bound_expressions;
  ExpressionBinder expression_binder(binder_context);
  
  for (unique_ptr<Expression> &expression : select_sql.expressions) {
    // 多表联查的时候，project 算子应该输出 table.field
    RC rc = expression_binder.bind_expression(expression, bound_expressions, mutil_tables);
    if (OB_FAIL(rc)) {
      LOG_INFO("bind expression failed. rc=%s", strrc(rc));
      return rc;
    }
  }

  vector<unique_ptr<Expression>> group_by_expressions;
  for (unique_ptr<Expression> &expression : select_sql.group_by) {
    RC rc = expression_binder.bind_expression(expression, group_by_expressions);
    if (OB_FAIL(rc)) {
      LOG_INFO("bind expression failed. rc=%s", strrc(rc));
      return rc;
    }
  }

  unique_ptr<OrderByStmt> order_by_stmt = make_unique<OrderByStmt>();
  for (size_t i = 0; i < select_sql.order_by.size(); i++) {
    RC rc = expression_binder.bind_expression(select_sql.order_by[i]->unbound_field, order_by_stmt->order_by_expressions);
    if (OB_FAIL(rc)) {
      LOG_INFO("order by bind expression failed. rc=%s", strrc(rc));
      return rc;
    }
    order_by_stmt->order_by_ops.emplace_back(select_sql.order_by[i]->order_op);
  }

  assert(order_by_stmt->order_by_ops.size() == order_by_stmt->order_by_expressions.size());

  Table *default_table = nullptr;
  if (tables.size() == 1) {
    default_table = tables[0];
  }

  // create filter statement in `where` statement
  FilterStmt *filter_stmt = nullptr;
  RC          rc          = FilterStmt::create(db, default_table, &table_map, select_sql.conditions, filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }

  // bind exprs in filter statement
  rc = Stmt::bind_filter_stmt(db, select_sql.relations, filter_stmt);
  if (OB_FAIL(rc)) {
    LOG_WARN("bind filter stmt failed in select stmt");
    return rc;
  }

  // everything alright
  SelectStmt *select_stmt = new SelectStmt();

  select_stmt->tables_.swap(tables);
  select_stmt->query_expressions_.swap(bound_expressions);
  select_stmt->filter_stmt_ = filter_stmt;
  select_stmt->group_by_.swap(group_by_expressions);
  select_stmt->order_by_.swap(order_by_stmt);
  select_stmt->join_conditions_.swap(join_conditions);
  stmt                      = select_stmt;
  return RC::SUCCESS;
}

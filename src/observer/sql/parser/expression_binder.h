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
// Created by Wangyunlai on 2024/05/29.
//

#pragma once

#include <vector>

#include "sql/expr/expression.h"

class BinderContext
{
public:
  BinderContext()          = default;
  virtual ~BinderContext() = default;

  void add_table(Table *table) { 
    if(table!= nullptr){
        if(table_set_.count(table) == 0){
            query_table_maps_[table->name()] = table;
            table_full_names_.insert(table->name());
            table_set_.insert(table);
            query_tables_.push_back(table);
        }
    }
  }

  // 调用前必须保证已经调用了 add_table
  // 此处也可能传入表全名
  RC add_alias(const std::string& table_name, Table* table) {
    if (table_full_names_.contains(table_name))
    {
      return RC::SUCCESS;  // 此处不考虑 select * from a b, b a;
    }

    //query_table_map 映射存在，表示有相同别名或者表名已经存在映射
    if(!table_aliases_.contains(table_name) && table_set_.contains(table)){
      query_table_maps_.insert({table_name, table});
    } else {
      LOG_WARN("zyq: add alias failed, because %s", table_aliases_.contains(table_name) ? "there have been it." : "we require you call add_table first.");

      return RC::INVALID_ARGUMENT;
    }
    return RC::SUCCESS;
  }

  Table *find_table(const char *table_name) const;

  const std::vector<Table *> &query_tables() const { return query_tables_; }
  const std::unordered_map<std::string, Table*> &query_table_maps() const { return query_table_maps_; }

private:
  std::vector<Table *> query_tables_;                        // 有序记录查询涉及的表
  std::unordered_map<std::string, Table*> query_table_maps_; // 记录表名/别名 到 Table* 的映射

  std::set<Table *>                       table_set_;        // 检查表是否已存在时用
  std::set<std::string>                   table_full_names_; // 检查表全名是否已存在时用
  std::set<std::string>                   table_aliases_;    // 检查表别名是否已存在时用
};

/**
 * @brief 绑定表达式
 * @details 绑定表达式，就是在SQL解析后，得到文本描述的表达式，将表达式解析为具体的数据库对象
 */
class ExpressionBinder
{
public:
  ExpressionBinder(BinderContext &context) : context_(context) {}
  virtual ~ExpressionBinder() = default;

  RC bind_expression(std::unique_ptr<Expression> &expr, std::vector<std::unique_ptr<Expression>> &bound_expressions, bool mutil_tables = false, Table *default_table = nullptr);

private:
  RC bind_star_expression(std::unique_ptr<Expression> &star_expr,
      std::vector<std::unique_ptr<Expression>> &bound_expressions, bool mutil_tables = false);
  RC bind_unbound_field_expression(std::unique_ptr<Expression> &unbound_field_expr,
      std::vector<std::unique_ptr<Expression>> &bound_expressions, bool mutil_tables, Table *default_table);
  RC bind_field_expression(
      std::unique_ptr<Expression> &field_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_value_expression(
      std::unique_ptr<Expression> &value_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_cast_expression(
      std::unique_ptr<Expression> &cast_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_comparison_expression(
      std::unique_ptr<Expression> &comparison_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions, Table *default_table);
  RC bind_conjunction_expression(
      std::unique_ptr<Expression> &conjunction_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_arithmetic_expression(
      std::unique_ptr<Expression> &arithmetic_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_function_expression(
      std::unique_ptr<Expression> &arithmetic_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_subquery_expression(
      std::unique_ptr<Expression> &arithmetic_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_exprlist_expression(
      std::unique_ptr<Expression> &arithmetic_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_aggregate_expression(
      std::unique_ptr<Expression> &aggregate_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);

private:
  BinderContext &context_;
};
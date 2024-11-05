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
  BinderContext(BinderContext *parent_context):parent_context_(parent_context){}
  virtual ~BinderContext() = default;

  RC add_table(Table *table) { 
    if(table == nullptr){
      return RC::INVALID_ARGUMENT;
    }
    return add_table(table->name(), table);
  }

  RC add_table(std::string table_name, Table *table) { 
    if(table!= nullptr){
        if(query_table_maps_.contains(table_name) == 0){
            query_table_maps_[table_name] = table;
            query_tables_.push_back(table);
        }else{
          return RC::INVALID_ARGUMENT;
        }
    }else{
      return RC::INVALID_ARGUMENT;
    }
    return RC::SUCCESS;
  }

  void add_table_without_check(Table *table) {
    query_table_maps_[table->name()] = table;
    query_tables_.push_back(table);
  }

  Table *find_table(const char *table_name) const;

  const std::vector<Table *> &query_tables() const { return query_tables_; }

  const BinderContext* parent_context() const {return parent_context_;}

  void set_parent_context(BinderContext* parent_context){
    this->parent_context_ = parent_context;
  }
private:
  std::vector<Table *> query_tables_;                        // 有序记录查询涉及的表
  std::unordered_map<std::string, Table*> query_table_maps_; // 记录表名/别名 到 Table* 的映射
  BinderContext* parent_context_ = nullptr;
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
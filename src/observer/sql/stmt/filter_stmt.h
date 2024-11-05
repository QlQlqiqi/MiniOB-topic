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

#pragma once

#include "sql/expr/expression.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/stmt.h"
#include <unordered_map>
#include <vector>

class Db;
class Table;
class FieldMeta;
class BinderContext;

struct FilterObj
{
  explicit FilterObj(std::unique_ptr<Expression> &&expr = nullptr) : expr_(std::move(expr)) {}
  std::unique_ptr<Expression> expr_;
};

/**
 * @brief Filter/谓词/过滤语句
 * @ingroup Statement
 */
class FilterStmt
{
public:
  FilterStmt() = default;
  virtual ~FilterStmt();

public:
  // const std::vector<FilterUnit *> &filter_units() const { return filter_units_; }

  void set_expr(std::unique_ptr<Expression> &&expr) { expr_ = std::move(expr); }
  const std::unique_ptr<Expression> &get_expr() const { return expr_; }
  std::unique_ptr<Expression> &expr() { return expr_; }

public:
  static RC create(Db *db, Table *default_table, BinderContext& binder_context,
      const Expression *conditions, FilterStmt *&stmt);


private:
  // std::vector<FilterUnit *> filter_units_;  // 默认当前都是AND关系
  std::unique_ptr<Expression> expr_ = nullptr;
};

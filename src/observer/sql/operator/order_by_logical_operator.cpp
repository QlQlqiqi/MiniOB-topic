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
// Created by WangYunlai on 2024/05/30.
//

#include <memory>

#include "common/log/log.h"
#include "sql/operator/order_by_logical_operator.h"
#include "sql/expr/expression.h"

using namespace std;

OrderByLogicalOperator::OrderByLogicalOperator(vector<unique_ptr<Expression>> &&order_by_exprs_,
                                               vector<OrderOp> &&order_ops_)
{
  this->expressions_.swap(order_by_exprs_);
  this->order_ops_.swap(order_ops_);
}
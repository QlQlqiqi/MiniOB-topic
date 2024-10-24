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
// Created by WangYunlai on 2024/06/11.
//
#include <algorithm>

#include "common/log/log.h"
#include "sql/operator/order_by_physical_operator.h"
#include "sql/expr/expression_tuple.h"
#include "sql/expr/composite_tuple.h"
#include "order_by_physical_operator.h"

using namespace std;
using namespace common;

OrderByPhysicalOperator::OrderByPhysicalOperator(std::vector<std::unique_ptr<Expression>> &&expressions, std::vector<OrderOp> && order_ops)
:order_by_expressions_(std::move(expressions)), order_ops_(std::move(order_ops)){
}
RC OrderByPhysicalOperator::open(Trx *trx) {
  if(children_.size() != 1){
    LOG_WARN("sort physical operator has %d children", children_.size());
    return RC::INTERNAL;
  }
  auto &child = children_[0];
  return child->open(trx);
}

RC OrderByPhysicalOperator::next() { 
  RC rc;
  if(idx_ == -1){
    if((rc = init()) != RC::SUCCESS){
      return rc;
    }
  }
  idx_++;
  if(idx_ == tuples_.size()){
    return RC::RECORD_EOF;
  }
  return RC::SUCCESS;
}

RC OrderByPhysicalOperator::close() { 
  idx_ = -1;
  return children_[0]->close();
}

RC OrderByPhysicalOperator::init() { 
  RC rc = read_all();
  if(rc != RC::SUCCESS){
    return rc;
  }

  assert(order_by_expressions_.size() == order_ops_.size());

  std::sort(tuples_.begin(), tuples_.end(), [this](const std::unique_ptr<Tuple>& a, const std::unique_ptr<Tuple>& b){
    for(size_t i = 0; i < order_by_expressions_.size(); i++){
      auto& expr = order_by_expressions_[i];
      /*order_by_expression should be FieldExpression*/
      Value a_val, b_val;
      assert(expr->type() == ExprType::FIELD); 
      FieldExpr* filed_expr = static_cast<FieldExpr*>(expr.get());
      filed_expr->get_value(*a, a_val);
      filed_expr->get_value(*b, b_val);
      auto cmp = a_val.compare(b_val);
      if (cmp == 0)
        continue;
      if (cmp == -1) {
        return order_ops_[i] == OrderOp::ASC;
      }
      if (cmp == 1) {
        return order_ops_[i] == OrderOp::DESC;
      }
    }
    return false;
  });
  return RC::SUCCESS;
}

RC OrderByPhysicalOperator::read_all() { 
  RC rc = RC::SUCCESS;
  while ((rc = children_[0]->next()) == RC::SUCCESS) {
    RowTuple* child_tuple_ =static_cast<RowTuple*>(children_[0]->current_tuple());
    auto clone_tuple_ = child_tuple_->clone();
    tuples_.emplace_back(std::move(clone_tuple_));
  }
  if (rc != RC::RECORD_EOF) {
    return rc;
  }
  return RC::SUCCESS;
}

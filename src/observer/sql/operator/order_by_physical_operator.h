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
// Created by WangYunlai on 2024/05/29.
//

#pragma once

#include "sql/operator/physical_operator.h"
#include "sql/expr/composite_tuple.h"

/**
 * @brief Group By 物理算子基类
 * @ingroup PhysicalOperator
 */
class OrderByPhysicalOperator : public PhysicalOperator
{
public:
  OrderByPhysicalOperator(std::vector<std::unique_ptr<Expression>> &&expressions, std::vector<OrderOp> && order_ops);
  virtual ~OrderByPhysicalOperator() = default;
  PhysicalOperatorType type() const override {return PhysicalOperatorType::ORDER_BY;}
  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;
  RC init();
  RC read_all();

  Tuple *current_tuple() override { return tuples_[idx_].get(); }

protected:
  std::vector<std::unique_ptr<Expression>> order_by_expressions_;  /// 
  std::vector<OrderOp> order_ops_;      /// 
  std::vector<std::unique_ptr<Tuple>> tuples_;          ///
  int64_t idx_ = -1;
};
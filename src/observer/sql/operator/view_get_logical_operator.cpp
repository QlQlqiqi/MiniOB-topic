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
// Created by Wangyunlai on 2022/12/15
//

#include "sql/operator/view_get_logical_operator.h"
#include "sql/optimizer/logical_plan_generator.h"

ViewGetLogicalOperator::ViewGetLogicalOperator(View *view, ReadWriteMode mode)
    : view_(view), mode_(mode)
{
  ASSERT(view_->generate_select_stmt() == RC::SUCCESS, "the select generate failed");
  ASSERT(view_->select_stmt() != nullptr, "the select statment should not be null");
  LogicalPlanGenerator::create(view->select_stmt().get(), select_logical_operator_);
  ASSERT(view_->select_stmt() != nullptr, "the select statment should not be null after generator");
  ASSERT(select_logical_operator_ != nullptr, "the logica operator should not be null");
}

void ViewGetLogicalOperator::set_predicates(std::vector<std::unique_ptr<Expression>> &&exprs)
{
  predicates_ = std::move(exprs);
}

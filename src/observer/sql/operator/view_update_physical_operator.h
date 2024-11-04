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
// Created by yqzhang4480 on 2024/10/18.
//

#pragma once

#include "sql/operator/physical_operator.h"
#include "sql/parser/parse.h"
#include "storage/field/field.h"
#include <vector>


class UpdateStmt;
class View;

/**
 * @brief 更新物理算子
 * @ingroup PhysicalOperator
 */
class ViewUpdatePhysicalOperator : public PhysicalOperator
{
public:
  ViewUpdatePhysicalOperator(View *view, std::vector<std::pair<FieldMeta, std::unique_ptr<Expression>>>&& values);

  virtual ~ViewUpdatePhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::UPDATE; }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override { return nullptr; }


private:
  // TODO(qiqi): 暂时被用于 rollback
  RC rollback(Trx *trx, std::vector<Record> &deleted_records, std::vector<Record> &inserted_records) const;

  View                 *view_ = nullptr;
  Trx                   *trx_   = nullptr;
  std::vector<Record>    records_;
  std::vector<ViewRowTuple> tuples_;
  std::vector<std::pair<FieldMeta, std::unique_ptr<Expression>>> values_;
};

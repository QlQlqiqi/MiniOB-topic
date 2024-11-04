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
// Created by Wangyunlai on 2022/12/07.
//
#pragma once

#include "sql/operator/logical_operator.h"
#include "sql/parser/parse_defs.h"
#include "storage/field/field.h"
#include "common/types.h"

/**
 * @brief vector index
 * @details 比如使用全表扫描、通过索引获取数据等
 * @ingroup LogicalOperator
 */
class VectorIndexScanLogicalOperator : public LogicalOperator
{
public:
  VectorIndexScanLogicalOperator(
      Table *table, Index *index, const FieldMeta *field_meta, const OrderOp order_op, const int limit_num)
      : table_(table), index_(index), order_op_(order_op), limit_num_(limit_num)
  {
    // 如果没有 field meta 也可以
    if (field_meta == nullptr) {
      field_meta_ = nullptr;
      return;
    }

    field_meta_ = std::make_shared<FieldMeta>(*field_meta);
  }
  virtual ~VectorIndexScanLogicalOperator() = default;

  LogicalOperatorType type() const override { return LogicalOperatorType::VECTOR_INDEX_SCAN; }

  Table                           *table() const { return table_; }
  ReadWriteMode                    read_write_mode() const { return mode_; }
  Index                           *index() { return index_; }
  const std::shared_ptr<FieldMeta> field_meta() const { return field_meta_; }
  OrderOp                          order_op() const { return order_op_; }
  int                              limit_num() const { return limit_num_; }

private:
  Table                     *table_ = nullptr;
  ReadWriteMode              mode_  = ReadWriteMode::READ_ONLY;
  Index                     *index_;
  std::shared_ptr<FieldMeta> field_meta_;
  OrderOp                    order_op_;
  int                        limit_num_;
};

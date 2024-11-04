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
// Created by Wangyunlai on 2022/07/08.
//

#pragma once

#include "sql/expr/tuple.h"
#include "sql/operator/physical_operator.h"
#include "storage/record/record_manager.h"

/**
 * @brief vector 索引扫描物理算子
 * @ingroup PhysicalOperator
 */
class VectorIndexScanPhysicalOperator : public PhysicalOperator
{
public:
  VectorIndexScanPhysicalOperator(
      Table *table, Index *index, const FieldMeta *field_meta, const OrderOp order_op, const int limit_num)
      :table_(table), index_(index), order_op_(order_op), limit_num_(limit_num)
  {
    // 如果没有 field meta 也可以
    if (field_meta == nullptr) {
      field_meta_ = nullptr;
      return;
    }

    field_meta_ = std::make_shared<FieldMeta>(*field_meta);
  }
  virtual ~VectorIndexScanPhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::VECTOR_INDEX_SCAN; }

  std::string param() const override;

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override;

private:
  Trx               *trx_            = nullptr;
  Table             *table_          = nullptr;
  ReadWriteMode      mode_           = ReadWriteMode::READ_ONLY;
  Index             *index_          = nullptr;
  IndexScanner      *index_scanner_  = nullptr;
  RecordFileHandler *record_handler_ = nullptr;

  Record   current_record_;
  RowTuple tuple_;

  std::shared_ptr<FieldMeta> field_meta_;
  OrderOp                    order_op_;
  int                        limit_num_;
};

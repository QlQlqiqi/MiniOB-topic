/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#pragma once

#include "common/type/data_type.h"

// vector 维度不得超过
const int VECTOR_MAX_SIZE = 16000;
// 如果维度超过这个，则被视为高维度
const int VECTOR_HIGH_DIM = 10;

/**
 * @brief 向量类型
 * @ingroup DataType
 */
class VectorType : public DataType
{
public:
  enum VectorOp
  {
    VECTOR_ADD,
    VECTOR_SUB,
    VECTOR_MULTI,
    VECTOR_DIV,
  };

  VectorType() : DataType(AttrType::VECTORS) {}
  virtual ~VectorType() = default;

  int compare(const Value &left, const Value &right) const override;
  // 如果 left 和 right 为 chars，那么将其转为 vector，填充在 result
  RC check(const Value &left, const Value &right, Value &result1, Value &result2) const;

  void compute(const VectorOp &op, const double *l, const double *r, const size_t &sz, Value &result) const;
  RC add(const Value &left, const Value &right, Value &result) const override;
  RC subtract(const Value &left, const Value &right, Value &result) const override;
  RC multiply(const Value &left, const Value &right, Value &result) const override;
  RC divide(const Value &left, const Value &right, Value &result) const override;

  int cast_cost(AttrType type) override;
  RC cast_to(const Value &val, AttrType type, Value &result) const override;

  RC to_string(const Value &val, string &result) const override;
};
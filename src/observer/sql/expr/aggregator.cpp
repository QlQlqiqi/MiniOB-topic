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

#include "sql/expr/aggregator.h"
#include "common/log/log.h"

RC SumAggregator::accumulate(const Value &value)
{
  if (value_.attr_type() == AttrType::UNDEFINED) {
    value_ = value;
    return RC::SUCCESS;
  }

  if (!value.is_null() && !value_.is_null())
  {
    ASSERT(value.attr_type() == value_.attr_type(), "type mismatch. value type: %s, value_.type: %s", 
          attr_type_to_string(value.attr_type()), attr_type_to_string(value_.attr_type()));
  }

  if (value.is_null())
  {
    return RC::SUCCESS;
  }

  if (value_.is_null())
  {
    value_ = value;
    return RC::SUCCESS;
  }

  Value::add(value, value_, value_);
  return RC::SUCCESS;
}

RC CountAggregator::accumulate(const Value & value)
{
  if (value.attr_type() == AttrType::NULLS)
  {
    return RC::SUCCESS;
  }
  ++cnt_;
  return RC::SUCCESS;
}

RC CountAggregator::evaluate(Value &result)
{
  result.set_type(AttrType::INTS);
  result.set_data((char *)&cnt_, sizeof(cnt_));
  return RC::SUCCESS;
}

RC AvgAggregator::accumulate(const Value& value_)
{
  if (RC rc = CountAggregator::accumulate(value_); OB_FAIL(rc))
  {
    return rc;
  }
  if (RC rc = SumAggregator::accumulate(value_); OB_FAIL(rc))
  {
    return rc;
  }

  return RC::SUCCESS;
}

RC AvgAggregator::evaluate(Value &result)
{
  Value sum;
  Value float_sum;
  Value cnt;
  if (RC rc = CountAggregator::evaluate(cnt); OB_FAIL(rc))
  {
    return rc;
  }
  if (cnt.get_int() == 0)
  {
    result.set_type(AttrType::NULLS);
    return RC::SUCCESS;
  }
  if (RC rc = SumAggregator::evaluate(sum); OB_FAIL(rc))
  {
    return rc;
  }
  
  if (sum.attr_type() != AttrType::FLOATS)
  {
    if (RC rc = Value::cast_to(sum, AttrType::FLOATS, float_sum); OB_FAIL(rc))
    {
      LOG_WARN("failed to cast to float from a value(%s) with attr_type=%d", value_.to_string().c_str(), value_.attr_type());
      return rc;
    }
  }
  else
  {
    float_sum = sum;
  }

  Value::divide(float_sum, cnt, float_sum);
  result = float_sum;
  return RC::SUCCESS;
}

RC MinAggregator::accumulate(const Value &value)
{
  if (value_.attr_type() == AttrType::UNDEFINED) {
    value_ = value;
    return RC::SUCCESS;
  }
  
  ASSERT(value.attr_type() == value_.attr_type(), "type mismatch. value type: %s, value_.type: %s", 
        attr_type_to_string(value.attr_type()), attr_type_to_string(value_.attr_type()));
  
  if (value_.compare(value) == ValCmpRes::GREAT)
  {
    value_ = value;
  }
  return RC::SUCCESS;
}

RC MaxAggregator::accumulate(const Value &value)
{
  if (value_.attr_type() == AttrType::UNDEFINED) {
    value_ = value;
    return RC::SUCCESS;
  }
  
  ASSERT(value.attr_type() == value_.attr_type(), "type mismatch. value type: %s, value_.type: %s", 
        attr_type_to_string(value.attr_type()), attr_type_to_string(value_.attr_type()));
  
  if (value_.compare(value) == ValCmpRes::LESS)
  {
    value_ = value;
  }
  return RC::SUCCESS;
}
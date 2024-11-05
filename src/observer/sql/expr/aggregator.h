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

#pragma once

#include "common/value.h"
#include "common/rc.h"

class Aggregator
{
public:
  virtual ~Aggregator() = default;

  virtual RC accumulate(const Value &value) = 0;
  virtual RC evaluate(Value &result)        = 0;
};

class CountAggregator : virtual public Aggregator
{
public:
  RC accumulate(const Value &value) override;
  RC evaluate(Value &result) override;
protected:
  size_t cnt_ = 0;
};

class ImmediateAggregator : virtual public Aggregator
{
public:
  RC evaluate(Value &result) override
  {
    if (value_.attr_type() == AttrType::UNDEFINED)
    {
      value_.set_null();
    }
    result = value_;
    return RC::SUCCESS;
  }

protected:
  Value value_;
};

class SumAggregator : public ImmediateAggregator
{
public:
  RC accumulate(const Value &value) override;
};

class AvgAggregator : public SumAggregator, public CountAggregator
{
public:
  RC accumulate(const Value &value) override;
  RC evaluate(Value &result) override;
};

class MinAggregator : public ImmediateAggregator
{
public:
  RC accumulate(const Value &value) override;
};

class MaxAggregator : public ImmediateAggregator
{
public:
  RC accumulate(const Value &value) override;
};
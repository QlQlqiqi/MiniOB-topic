/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include "common/lang/comparator.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "common/type/char_type.h"
#include "common/value.h"

int CharType::compare(const Value &left, const Value &right) const
{
  ASSERT(left.attr_type() == AttrType::CHARS && right.attr_type() == AttrType::CHARS, "invalid type");
  return common::compare_string(
      (void *)left.value_.pointer_value_, left.length_, (void *)right.value_.pointer_value_, right.length_);
}

RC CharType::set_value_from_str(Value &val, const string &data) const
{
  val.set_string(data.c_str());
  return RC::SUCCESS;
}

int CharType::cast_cost(AttrType type)
{
  // 如果内容形如 '[num1, num2]'，可以被转为 vector
  if (type == AttrType::CHARS || type == AttrType::VECTORS) {
    return 0;
  }
  return INT32_MAX;
}

RC CharType::cast_to(const Value &val, AttrType type, Value &result) const
{
  result.set_type(type);
  switch (type) {
    case AttrType::CHARS: {
      result = val;
      break;
    }
    case AttrType::VECTORS: {
      return char2vector(val, result);
      break;
    }
    case AttrType::NULLS: {
      result.set_null();
    } break;
    case AttrType::INTS:{
        int int_val;
        if(val.get_int(int_val) != RC::SUCCESS){
          LOG_WARN("failed to convert string to int. s=%s", val.value_.pointer_value_);
          return RC::INTERNAL;
        }
        result.set_int(int_val);
    } break;
    case AttrType::FLOATS:{
        float float_val;
        if(val.get_float(float_val) != RC::SUCCESS){
          LOG_WARN("failed to convert string to float. s=%s", val.value_.pointer_value_);
          return RC::INTERNAL;
        }
        result.set_float(float_val);
    }
    default: {
      LOG_WARN("failed to cast to: from %s to %s", attr_type_to_string(attr_type_), attr_type_to_string(type));
      return RC::UNSUPPORTED;
    }
  }
  return RC::SUCCESS;
}

RC CharType::char2vector(const Value &val, Value &result) const
{
  ASSERT(val.attr_type() == AttrType::CHARS, "val should be chars, but now is %s", attr_type_to_string(attr_type_));

  // 因为形如 [1.1, 2]，所以长度至少 2
  auto len = val.length();
  if (len < 2) {
    LOG_WARN("length of val %d should be >= 2", len);
    return RC::UNSUPPORTED;
  }
  auto str = val.data();
  if (str[0] != '[' || str[len - 1] != ']') {
    LOG_WARN("invalid format: %s", str);
    return RC::UNSUPPORTED;
  }
  str++;
  len -= 2;
  std::vector<std::string> vec;
  common::split_string(str, ",", vec);
  std::vector<double> nums;
  nums.reserve(vec.size());
  for (auto &item : vec) {
    double num;
    sscanf(item.c_str(), "%lf", &num);
    nums.emplace_back(num);
  }
  result = Value(nums);

  return RC::SUCCESS;
}

RC CharType::to_string(const Value &val, string &result) const
{
  stringstream ss;
  ss << val.value_.pointer_value_;
  result = ss.str();
  return RC::SUCCESS;
}
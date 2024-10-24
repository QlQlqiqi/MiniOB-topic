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
#include "common/lang/sstream.h"
#include "common/log/log.h"
#include "common/type/date_type.h"
#include "common/value.h"
#include "common/lang/limits.h"
#include "common/value.h"

int DateType::compare(const Value &left, const Value &right) const
{
  ASSERT(left.attr_type() == AttrType::DATES, "left type is not date");
  if (right.attr_type() == AttrType::DATES) {
    return common::compare_date((void *)&left.value_.int_value_, (void *)&right.value_.int_value_);
  } 
  return INT32_MAX;
}

RC DateType::add(const Value &left, const Value &right, Value &result) const
{
  return RC::UNIMPLEMENTED;
}

RC DateType::subtract(const Value &left, const Value &right, Value &result) const
{
  return RC::UNIMPLEMENTED;
}

RC DateType::multiply(const Value &left, const Value &right, Value &result) const
{
  return RC::UNIMPLEMENTED;
}

RC DateType::negative(const Value &val, Value &result) const
{
  return RC::UNIMPLEMENTED;
}

RC DateType::set_value_from_str(Value &val, const string &data) const
{
  RC                rc = RC::SUCCESS;
  stringstream deserialize_stream;
  common::DateTime date_time(data);
  if(!common::DateTime::is_valid_date(data))
  {
    rc = RC::SCHEMA_FIELD_TYPE_MISMATCH;
  }else
  {
    val.set_date(date_time);
  }
  return rc;
}

RC DateType::cast_to(const Value &val, AttrType type, Value &result) const
{
  result.set_type(type);
  switch (type) {
    case AttrType::DATES: {
      result = val;
    } break;
    case AttrType::NULLS: {
      result.set_null();
    } break;
    default: {
      LOG_WARN("failed to cast to: from %s to %s", attr_type_to_string(attr_type_), attr_type_to_string(type));
      return RC::UNSUPPORTED;
    } break; 
  }
  return RC::SUCCESS;
}

RC DateType::to_string(const Value &val, string &result) const
{
  result = common::Date(val.value_.date_time_value_).to_string();
  return RC::SUCCESS;
}
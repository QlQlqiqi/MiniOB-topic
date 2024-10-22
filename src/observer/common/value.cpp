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
// Created by WangYunlai on 2023/06/28.
//

#include "common/value.h"

#include "common/lang/comparator.h"
#include "common/lang/exception.h"
#include "common/lang/sstream.h"
#include "common/lang/string.h"
#include "common/time/datetime.h"
#include "common/log/log.h"
#include "value.h"

Value::Value(int val) { set_int(val); }

Value::Value(float val) { set_float(val); }

Value::Value(bool val) { set_boolean(val); }

Value::Value(common::DateTime val) { set_date(val); }

Value::Value(const char *s, int len /*= 0*/) { set_string(s, len); }

Value::Value(const std::vector<double> &v)
{
  set_vector(reinterpret_cast<const char *>(v.data()), v.size() * sizeof(double));
}

Value::Value(const Value &other)
{
  this->attr_type_ = other.attr_type_;
  this->length_    = other.length_;
  this->own_data_  = other.own_data_;
  switch (this->attr_type_) {
    case AttrType::VECTORS:
    case AttrType::CHARS: {
      set_string_from_other(other);
    } break;

    default: {
      this->value_ = other.value_;
    } break;
  }
}

Value::Value(Value &&other)
{
  this->attr_type_ = other.attr_type_;
  this->length_    = other.length_;
  this->own_data_  = other.own_data_;
  this->value_     = other.value_;
  other.own_data_  = false;
  other.length_    = 0;
}

Value &Value::operator=(const Value &other)
{
  if (this == &other) {
    return *this;
  }
  reset();
  this->attr_type_ = other.attr_type_;
  this->length_    = other.length_;
  this->own_data_  = other.own_data_;
  switch (this->attr_type_) {
    case AttrType::VECTORS:
    case AttrType::CHARS: {
      set_string_from_other(other);
    } break;

    default: {
      this->value_ = other.value_;
    } break;
  }
  return *this;
}

Value &Value::operator=(Value &&other)
{
  if (this == &other) {
    return *this;
  }
  reset();
  this->attr_type_ = other.attr_type_;
  this->length_    = other.length_;
  this->own_data_  = other.own_data_;
  this->value_     = other.value_;
  other.own_data_  = false;
  other.length_    = 0;
  return *this;
}

void Value::reset()
{
  switch (attr_type_) {
    case AttrType::VECTORS:
    case AttrType::CHARS:
      if (own_data_ && value_.pointer_value_ != nullptr) {
        delete[] value_.pointer_value_;
        value_.pointer_value_ = nullptr;
      }
      break;
    default: break;
  }

  attr_type_ = AttrType::UNDEFINED;
  length_    = 0;
  own_data_  = false;
}

void Value::set_null()
{
  reset();
  attr_type_ = AttrType::NULLS;
}

bool Value::is_null() const
{
  return attr_type_ == AttrType::NULLS;
}

void Value::set_data(char *data, int length)
{
  switch (attr_type_) {
    case AttrType::VECTORS: {
      set_vector(data, length);
    } break;
    case AttrType::CHARS: {
      set_string(data, length);
    } break;
    case AttrType::INTS: {
      value_.int_value_ = *(int *)data;
      length_           = length;
    } break;
    case AttrType::FLOATS: {
      value_.float_value_ = *(float *)data;
      length_             = length;
    } break;
    case AttrType::BOOLEANS: {
      value_.bool_value_ = *(int *)data != 0;
      length_            = length;
    } break;
    case AttrType::DATES:{
      value_.int_value_  = *(int *)data;
      length_            = length;
    }break;
    default: {
      LOG_WARN("unknown data type: %d", attr_type_);
    } break;
  }
}


void Value::set_int(int val)
{
  reset();
  attr_type_        = AttrType::INTS;
  value_.int_value_ = val;
  length_           = sizeof(val);
}

void Value::set_float(float val)
{
  reset();
  attr_type_          = AttrType::FLOATS;
  value_.float_value_ = val;
  length_             = sizeof(val);
}
void Value::set_boolean(bool val)
{
  reset();
  attr_type_         = AttrType::BOOLEANS;
  value_.bool_value_ = val;
  length_            = sizeof(val);
}

void Value::set_date(common::DateTime val)
{
  reset();
  attr_type_         = AttrType::DATES;
  value_.date_time_value_ = val; 
  length_            = sizeof(val);
}

void Value::set_vector(const char *s, int len)
{
  reset();
  attr_type_ = AttrType::VECTORS;
  if (s == nullptr) {
    value_.pointer_value_ = nullptr;
    length_               = 0;
  } else {
    own_data_ = true;
    // 如果是 vector，这里不需要查看 len
    value_.pointer_value_ = new char[len + 1];
    length_               = len;
    memcpy(value_.pointer_value_, s, len);
    value_.pointer_value_[len] = '\0';
  }
}

void Value::set_string(const char *s, int len /*= 0*/)
{
  reset();
  attr_type_ = AttrType::CHARS;
  if (s == nullptr) {
    value_.pointer_value_ = nullptr;
    length_               = 0;
  } else {
    own_data_ = true;
    if (len > 0) {
      len = strnlen(s, len);
    } else {
      len = strlen(s);
    }
    value_.pointer_value_ = new char[len + 1];
    length_               = len;
    memcpy(value_.pointer_value_, s, len);
    value_.pointer_value_[len] = '\0';
  }
}

void Value::set_value(const Value &value)
{
  switch (value.attr_type_) {
    case AttrType::INTS: {
      set_int(value.get_int());
    } break;
    case AttrType::FLOATS: {
      set_float(value.get_float());
    } break;
    case AttrType::VECTORS: {
      set_vector(value.get_string().c_str(), value.length());
    } break;
    case AttrType::CHARS: {
      set_string(value.get_string().c_str());
    } break;
    case AttrType::DATES:{
      set_date(value.get_date());
    } break;
    case AttrType::BOOLEANS: {
      set_boolean(value.get_boolean());
    } break;
    default: {
      ASSERT(false, "got an invalid value type");
    } break;
  }
}

void Value::set_neg()
{
  switch (attr_type_) {
    case AttrType::INTS: {
      set_int(get_int() * -1);
    } break;
    case AttrType::VECTORS: {
      auto pointer = value_.pointer_value_;
      for (int i = 0, sz = length() / sizeof(double); i < sz; i++) {
        pointer[i] *= -1;
      }
    } break;
    case AttrType::FLOATS: {
      set_float(get_float() * -1);
    } break;
    default: {
      ASSERT(false, "got an invalid value type in get_neg");
    } break;
  }
}

void Value::set_string_from_other(const Value &other)
{
  ASSERT(attr_type_ == AttrType::CHARS || attr_type_ == AttrType::VECTORS, "attr type is not CHARS or VECTORS");
  if (own_data_ && other.value_.pointer_value_ != nullptr && length_ != 0) {
    this->value_.pointer_value_ = new char[this->length_ + 1];
    memcpy(this->value_.pointer_value_, other.value_.pointer_value_, this->length_);
    this->value_.pointer_value_[this->length_] = '\0';
  }
}

const char *Value::data() const
{
  switch (attr_type_) {
    case AttrType::VECTORS:
    case AttrType::CHARS: {
      return value_.pointer_value_;
    } break;
    default: {
      return (const char *)&value_;
    } break;
  }
}

string Value::to_string() const
{
  string res;
  RC     rc = DataType::type_instance(this->attr_type_)->to_string(*this, res);
  if (OB_FAIL(rc)) {
    LOG_WARN("failed to convert value to string. type=%s", attr_type_to_string(this->attr_type_));
    return "";
  }
  return res;
}

ValCmpRes Value::compare(const Value &other) const {
  if(this->attr_type_ == AttrType::NULLS || other.attr_type_ == AttrType::NULLS){
    return ValCmpRes::NULL_VAL;
  }
  
  //转换逻辑
  Value cast_val;
  RC rc = RC::SUCCESS;
  const Value* left_val = this;
  const Value* right_val = &other;

  if(this->attr_type_ != other.attr_type_){
    if((rc = Value::cast_to(*this, other.attr_type_, cast_val)) == RC::SUCCESS){
      left_val = &cast_val;
    }
    if((rc = Value::cast_to(other, this->attr_type_, cast_val)) == RC::SUCCESS){
      right_val = &cast_val;
    }
    return ValCmpRes::CANNOT;
  }

  switch(DataType::type_instance(this->attr_type_)->compare(*left_val, *right_val)){
    case -1:  return ValCmpRes::LESS;
    case  0:  return ValCmpRes::EQUAL;
    case  1:  return ValCmpRes::GREAT;
    default:  return ValCmpRes::CANNOT;
  }
}

int Value::get_int() const
{
  switch (attr_type_) {
    case AttrType::CHARS: {
      try {
        return (int)(std::stol(value_.pointer_value_));
      } catch (exception const &ex) {
        LOG_TRACE("failed to convert string to number. s=%s, ex=%s", value_.pointer_value_, ex.what());
        return 0;
      }
    }
    case AttrType::INTS: {
      return value_.int_value_;
    }
    case AttrType::FLOATS: {
      return (int)(value_.float_value_);
    }
    case AttrType::BOOLEANS: {
      return (int)(value_.bool_value_);
    }
    case AttrType::DATES: {
      return (int)(value_.date_time_value_.to_time_t());
    }
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return 0;
    }
  }
  return 0;
}

float Value::get_float() const
{
  switch (attr_type_) {
    case AttrType::CHARS: {
      try {
        return std::stof(value_.pointer_value_);
      } catch (exception const &ex) {
        LOG_TRACE("failed to convert string to float. s=%s, ex=%s", value_.pointer_value_, ex.what());
        return 0.0;
      }
    } break;
    case AttrType::INTS: {
      return float(value_.int_value_);
    } break;
    case AttrType::FLOATS: {
      return value_.float_value_;
    } break;
    case AttrType::DATES: {
      return float(value_.int_value_);
    } break;
    case AttrType::BOOLEANS: {
      return float(value_.bool_value_);
    } break;
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return 0;
    }
  }
  return 0;
}
common::DateTime Value::get_date()  const{
  switch (attr_type_) {
    case AttrType::CHARS: 
    case AttrType::INTS: 
    case AttrType::FLOATS: 
    case AttrType::BOOLEANS: {
      LOG_TRACE("the value type is not date.");
      return common::DateTime();
    }
    case AttrType::DATES: {
      return value_.date_time_value_;
    }
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return common::DateTime();
    }
  }
  return common::DateTime();
}

string Value::get_string() const { return this->to_string(); }

bool Value::get_boolean() const
{
  switch (attr_type_) {
    case AttrType::CHARS: {
      std::string str_value(value_.pointer_value_);
      std::transform(str_value.begin(), str_value.end(), str_value.begin(), ::tolower);
      if (str_value == "true" || str_value == "1") {
        return true;
      } else if (str_value == "false" || str_value == "0") {
        return false;
      } else {
        LOG_TRACE("failed to convert string to boolean. s=%s", value_.pointer_value_);
        return false; // Indicating an error
      }
    }
    case AttrType::INTS: {
      return value_.int_value_ != 0;
    }
    case AttrType::FLOATS: {
      return value_.float_value_ != 0.0f;
    }
    case AttrType::BOOLEANS: {
      return value_.bool_value_;
    }
    case AttrType::DATES: {
      LOG_WARN("cannot convert date to boolean. type=%d", attr_type_);
      return false; // Indicating an error
    }
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return false; // Indicating an error
    }
  }
}



RC Value::get_int(int &val) const { 
  switch (attr_type_) {
    case AttrType::CHARS: {
      try {
        val = (int)(std::stol(value_.pointer_value_));
      } catch (exception const &ex) {
        LOG_TRACE("failed to convert string to number. s=%s, ex=%s", value_.pointer_value_, ex.what());
        return RC::INTERNAL;
      }
    }
    case AttrType::INTS: {
      val = value_.int_value_;
      return RC::SUCCESS;
    }
    case AttrType::FLOATS: {
      val = (int)(value_.float_value_);
      return RC::SUCCESS;
    }
    case AttrType::BOOLEANS: {
      val = (int)(value_.bool_value_);
      return RC::SUCCESS;
    }
    case AttrType::DATES: {
      val = (int)(value_.date_time_value_.to_time_t());
    }
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return RC::UNSUPPORTED;
    }
  }
  return RC::SUCCESS;
}

RC Value::get_float(float &val) const { 
  switch (attr_type_) {
    case AttrType::CHARS: {
      try {
        val = std::stof(value_.pointer_value_);
      } catch (exception const &ex) {
        LOG_TRACE("failed to convert string to float. s=%s, ex=%s", value_.pointer_value_, ex.what());
        return RC::INTERNAL;
      }
      return RC::SUCCESS;
    }
    case AttrType::INTS: {
      val = float(value_.int_value_);
      return RC::SUCCESS;
    }
    case AttrType::FLOATS: {
      val = value_.float_value_;
      return RC::SUCCESS;
    }
    case AttrType::BOOLEANS: {
      val = float(value_.bool_value_);
      return RC::SUCCESS;
    }
    case AttrType::DATES: {
      val = float(value_.date_time_value_.to_time_t());
      return RC::SUCCESS;
    }
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return RC::UNSUPPORTED;
    }
  }
  return RC::SUCCESS;
}

RC Value::get_date(common::DateTime &val) const {
    switch (attr_type_) {
    case AttrType::CHARS: 
    case AttrType::INTS: 
    case AttrType::FLOATS: 
    case AttrType::BOOLEANS: {
      LOG_TRACE("the value type is not date.");
      return RC::UNSUPPORTED;
    }
    case AttrType::DATES: {
      val = value_.date_time_value_;
      return RC::SUCCESS;
    }
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return RC::UNSUPPORTED;
    }
  }
  return RC::SUCCESS;
}

RC Value::get_string(string &val) const { 
  return DataType::type_instance(this->attr_type_)->to_string(*this, val);
}

RC Value::get_boolean(bool &val) const {
  switch (attr_type_) {
    case AttrType::CHARS: {
      std::string str_value(value_.pointer_value_);
      std::transform(str_value.begin(), str_value.end(), str_value.begin(), ::tolower);
      if (str_value == "true" || str_value == "1") {
        val = true;
      } else if (str_value == "false" || str_value == "0") {
        val = false;
      } else {
        LOG_TRACE("failed to convert string to boolean. s=%s", value_.pointer_value_);
        return RC::INTERNAL;
      }
      return RC::SUCCESS;
    }
    case AttrType::INTS: {
      val = (value_.int_value_ != 0);
      return RC::SUCCESS;
    }
    case AttrType::FLOATS: {
      val = (value_.float_value_ != 0.0f);
      return RC::SUCCESS;
    }
    case AttrType::BOOLEANS: {
      val = value_.bool_value_;
      return RC::SUCCESS;
    }
    case AttrType::DATES: {
      LOG_WARN("cannot convert date to boolean. type=%d", attr_type_);
      return RC::UNSUPPORTED;
    }
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return RC::UNSUPPORTED;
    }
  }
  return RC::SUCCESS;
}
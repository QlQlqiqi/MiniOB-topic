#pragma once

#include "common/type/data_type.h"

/**
 * @brief null 类型
 * @ingroup NullType
 */
class NullType : public DataType
{
public:
  NullType() : DataType(AttrType::NULLS) {}
  virtual ~NullType() = default;

  RC cast_to(const Value &val, AttrType type, Value &result) const override;
  int cast_cost(AttrType type) override;
  RC to_string(const Value &val, string &result) const override;
};

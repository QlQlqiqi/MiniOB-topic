#include "common/value.h"
#include "common/type/null_type.h"

RC NullType::to_string(const Value &val, string &result) const
{
  result = "NULL";
  return RC::SUCCESS;
}

int NullType::cast_cost(AttrType type)
{
  return INT32_MAX;
}

RC NullType::cast_to(const Value &val, AttrType type, Value &result) const
{
  return RC::UNSUPPORTED;
}

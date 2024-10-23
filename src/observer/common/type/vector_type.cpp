#include "common/log/log.h"
#include "common/rc.h"
#include "common/type/attr_type.h"
#include "common/type/vector_type.h"
#include "common/value.h"
#include "common/lang/comparator.h"

RC VectorType::check(const Value &left, const Value &right, Value &result1, Value &result2) const
{
  result1 = left;
  result2 = right;
  // 这两个至少一个 vector，另一个是 chars
  if (left.attr_type() == AttrType::CHARS) {
    auto rc = left.cast_to(left, AttrType::VECTORS, result1);
    if (OB_FAIL(rc)) {
      LOG_WARN("cast to vectors failed: %s", left.to_string().c_str());
      return RC::UNSUPPORTED;
    }
  }
  if (right.attr_type() == AttrType::CHARS) {
    auto rc = right.cast_to(right, AttrType::VECTORS, result2);
    if (OB_FAIL(rc)) {
      LOG_WARN("cast to vectors failed: %s", right.to_string().c_str());
      return RC::UNSUPPORTED;
    }
  }

  if (result1.attr_type() != AttrType::VECTORS || result2.attr_type() != AttrType::VECTORS) {
    LOG_WARN("left type %s should be same as right's %s", attr_type_to_string(result1.attr_type()),attr_type_to_string(result2.attr_type()));
    return RC::UNSUPPORTED;
  }

  // vector 的 len 必须相同
  if (result1.length() != result2.length()) {
    LOG_WARN("left length %d is different of right's %d", result1.length(), result2.length());
    return RC::UNSUPPORTED;
  }
  return RC::SUCCESS;
}

int VectorType::compare(const Value &left, const Value &right) const
{
  Value tmp1;
  Value tmp2;
  if (OB_FAIL(check(left, right, tmp1, tmp2))) {
    return INT32_MAX;
  }

  auto l   = reinterpret_cast<const double *>(tmp1.data());
  auto r   = reinterpret_cast<const double *>(tmp2.data());
  int  num = tmp1.length() / sizeof(double);

  for (int i = 0; i < num; i++) {
    auto res = common::compare_double(reinterpret_cast<const void *>(l + i), reinterpret_cast<const void *>(r + i));
    if (res) {
      return res;
    }
  }

  return 0;
}

void VectorType::compute(const VectorOp &op, const double *l, const double *r, const size_t &sz, Value &result) const
{
  std::vector<double> res;
  res.reserve(sz);
  for (size_t i = 0; i < sz; i++) {
    double num = 0;
    switch (op) {
      case VECTOR_ADD: num = l[i] + r[i]; break;
      case VECTOR_SUB: num = l[i] - r[i]; break;
      case VECTOR_MULTI: num = l[i] * r[i]; break;
      case VECTOR_DIV: num = l[i] / r[i]; break;
    }
    res.emplace_back(num);
  }
  result = Value(res);
}

RC VectorType::add(const Value &left, const Value &right, Value &result) const
{
  Value tmp1;
  Value tmp2;
  if (OB_FAIL(check(left, right, tmp1,tmp2))) {
    return RC::UNSUPPORTED;
  }

  auto l   = reinterpret_cast<const double *>(tmp1.data());
  auto r   = reinterpret_cast<const double *>(tmp2.data());
  int  num = tmp1.length() / sizeof(double);

  compute(VECTOR_ADD, l, r, num, result);

  return RC::SUCCESS;
}

RC VectorType::subtract(const Value &left, const Value &right, Value &result) const
{
  Value tmp1;
  Value tmp2;
  if (OB_FAIL(check(left, right, tmp1,tmp2))) {
    return RC::UNSUPPORTED;
  }

  auto l   = reinterpret_cast<const double *>(tmp1.data());
  auto r   = reinterpret_cast<const double *>(tmp2.data());
  int  num = tmp1.length() / sizeof(double);

  compute(VECTOR_SUB, l, r, num, result);

  return RC::SUCCESS;
}

RC VectorType::multiply(const Value &left, const Value &right, Value &result) const
{
  Value tmp1;
  Value tmp2;
  if (OB_FAIL(check(left, right, tmp1,tmp2))) {
    return RC::UNSUPPORTED;
  }

  auto l   = reinterpret_cast<const double *>(tmp1.data());
  auto r   = reinterpret_cast<const double *>(tmp2.data());
  int  num = tmp1.length() / sizeof(double);

  compute(VECTOR_MULTI, l, r, num, result);

  return RC::SUCCESS;
}

RC VectorType::divide(const Value &left, const Value &right, Value &result) const
{
  Value tmp1;
  Value tmp2;
  if (OB_FAIL(check(left, right, tmp1,tmp2))) {
    return RC::UNSUPPORTED;
  }

  auto l   = reinterpret_cast<const double *>(tmp1.data());
  auto r   = reinterpret_cast<const double *>(tmp2.data());
  int  num = tmp1.length() / sizeof(double);

  compute(VECTOR_DIV, l, r, num, result);

  return RC::SUCCESS;
}

int VectorType::cast_cost(AttrType type)
{
  if (type == AttrType::VECTORS) {
    return 0;
  }
  return INT32_MAX;
}

RC VectorType::cast_to(const Value &val, AttrType type, Value &result) const
{
  result.set_type(type);
  switch (type) {
    case AttrType::VECTORS: {
      result = val;
      break;
    }
    case AttrType::NULLS: {
      result.set_null();
      break;
    }
    default: {
      LOG_WARN("failed to cast to: from %s to %s", attr_type_to_string(attr_type_), attr_type_to_string(type));
      return RC::UNSUPPORTED;
    }
  }
  return RC::SUCCESS;
}

RC VectorType::to_string(const Value &val, string &result) const
{
  ASSERT(val.length() % sizeof(double) == 0, "value length %d should be mutiple of %d", val.length(), sizeof(double));
  stringstream ss;
  ss << "[";
  for (int i = 0, num = val.length() / sizeof(double); i < num; i++) {
    ss << common::double_to_str(*(reinterpret_cast<const double *>(val.data()) + i));
    if (i + 1 != num) {
      ss << ",";
    }
  }
  ss << "]";
  result = ss.str();
  return RC::SUCCESS;
}

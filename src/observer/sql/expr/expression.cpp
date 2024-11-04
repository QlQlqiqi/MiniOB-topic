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
// Created by Wangyunlai on 2022/07/05.
//

#include "sql/expr/expression.h"
#include "common/lang/defer.h"
#include "common/type/vector_type.h"
#include "sql/expr/tuple.h"
#include "sql/expr/arithmetic_operator.hpp"
#include "sql/stmt/select_stmt.h"
#include "sql/operator/logical_operator.h"
#include "sql/operator/physical_operator.h"
#include "sql/optimizer/logical_plan_generator.h"
#include "sql/optimizer/physical_plan_generator.h"
#include <regex>

using namespace std;

static void replace_all(std::string &str, const std::string &from, const std::string &to)
{
  if (from.empty()) {
    return;
  }
  size_t pos = 0;
  while (std::string::npos != (pos = str.find(from, pos))) {
    str.replace(pos, from.length(), to);
    pos += to.length();  // in case 'to' contains 'from'
  }
}

static bool str_like(const Value &left, const Value &right)
{
  std::string raw_reg(right.data());
  replace_all(raw_reg, "_", "[^']");
  replace_all(raw_reg, "%", "[^']*");
  std::regex reg(raw_reg.c_str(), std::regex_constants::ECMAScript | std::regex_constants::icase);
  bool res = std::regex_match(left.data(), reg);
  return res;
}

RC FieldExpr::get_value(const Tuple &tuple, Value &value) const
{
  RC rc = tuple.find_cell(TupleCellSpec(table_name(), field_name()), value);
  if (rc == RC::NOTFOUND && g_table_tuple_map.contains(table_name())) {
    return g_table_tuple_map.at(table_name())->find_cell(TupleCellSpec(table_name(), field_name()), value);
  }
  return rc;
}

bool FieldExpr::equal(const Expression &other) const
{
  if (this == &other) {
    return true;
  }
  if (other.type() != ExprType::FIELD) {
    return false;
  }
  const auto &other_field_expr = static_cast<const FieldExpr &>(other);
  return table_name() == other_field_expr.table_name() && field_name() == other_field_expr.field_name();
}

// TODO: 在进行表达式计算时，`chunk` 包含了所有列，因此可以通过 `field_id` 获取到对应列。
// 后续可以优化成在 `FieldExpr` 中存储 `chunk` 中某列的位置信息。
RC FieldExpr::get_column(Chunk &chunk, Column &column)
{
  if (pos_ != -1) {
    column.reference(chunk.column(pos_));
  } else {
    column.reference(chunk.column(field().meta()->field_id()));
  }
  return RC::SUCCESS;
}

bool ValueExpr::equal(const Expression &other) const
{
  if (this == &other) {
    return true;
  }
  if (other.type() != ExprType::VALUE) {
    return false;
  }
  const auto &other_value_expr = static_cast<const ValueExpr &>(other);
  return value_.compare(other_value_expr.get_value()) == ValCmpRes::EQUAL;
}

RC ValueExpr::get_value(const Tuple &tuple, Value &value) const
{
  value = value_;
  return RC::SUCCESS;
}

RC ValueExpr::get_column(Chunk &chunk, Column &column)
{
  column.init(value_);
  return RC::SUCCESS;
}

void ValueExpr::set_neg()
{
  value_.set_neg();
}

/////////////////////////////////////////////////////////////////////////////////
CastExpr::CastExpr(unique_ptr<Expression> child, AttrType cast_type) : child_(std::move(child)), cast_type_(cast_type)
{}

CastExpr::~CastExpr() {}

RC CastExpr::cast(const Value &value, Value &cast_value) const
{
  RC rc = RC::SUCCESS;
  if (this->value_type() == value.attr_type()) {
    cast_value = value;
    return rc;
  }

  // 如果 value 是 float，且自己是 int，那么转为 float
  if (value.attr_type() == AttrType::FLOATS && value_type() == AttrType::INTS) {
    return Value::cast_to(value, AttrType::FLOATS, cast_value);
  }

  rc = Value::cast_to(value, cast_type_, cast_value);
  return rc;
}

RC CastExpr::get_value(const Tuple &tuple, Value &result) const
{
  Value value;
  RC rc = child_->get_value(tuple, value);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return cast(value, result);
}

RC CastExpr::try_get_value(Value &result) const
{
  Value value;
  RC rc = child_->try_get_value(value);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return cast(value, result);
}

////////////////////////////////////////////////////////////////////////////////

ComparisonExpr::ComparisonExpr(CompOp comp, Expression* left, Expression* right)
    : comp_(comp), left_(left), right_(right)
{}

ComparisonExpr::ComparisonExpr(CompOp comp, unique_ptr<Expression> left, unique_ptr<Expression> right)
    : comp_(comp), left_(std::move(left)), right_(std::move(right))
{}

ComparisonExpr::~ComparisonExpr() {}

RC ComparisonExpr::compare_value(const Value &left, const Value &right, bool &result) const
{
  RC  rc         = RC::SUCCESS;
  ValCmpRes cmp_result = ValCmpRes::CANNOT;

  if (comp_ == IS_NULL || comp_ == IS_NOT_NULL) {
    ASSERT(right.is_null(), "right value must be null");
    result = comp_ == IS_NULL ? left.is_null() : !left.is_null();
    return rc;
  }

  // 需要判断 left 和 value 如果不能比较应该如何处理，
  // 比如：1 < null、1 < bool，默认是为 false，这里目前只是对 null 进行
  // 特判，事实上需要处理所有不能比较的类型，让结果为 false
  if(left.is_null() || right.is_null()) {
    result = false;
    return rc;
  }

  switch (comp_)
  {
    case EQUAL_TO:
    case LESS_EQUAL:
    case NOT_EQUAL:
    case LESS_THAN:
    case GREAT_EQUAL:
    case GREAT_THAN:
      cmp_result = left.compare(right);
    default: break;
  }

  result         = false;
  switch (comp_) {
    case EQUAL_TO: {
      result = (ValCmpRes::EQUAL == cmp_result);
    } break;
    case LESS_EQUAL: {
      result = (cmp_result == ValCmpRes::LESS) || (cmp_result == ValCmpRes::EQUAL);;
    } break;
    case NOT_EQUAL: {
      result = (cmp_result == ValCmpRes::GREAT) || (cmp_result == ValCmpRes::LESS);
    } break;
    case LESS_THAN: {
      result = (cmp_result == ValCmpRes::LESS);
    } break;
    case GREAT_EQUAL: {
      result = (cmp_result == ValCmpRes::GREAT) || (cmp_result == ValCmpRes::EQUAL);
    } break;
    case GREAT_THAN: {
      result = (cmp_result == ValCmpRes::GREAT);
    } break;
    case LIKE_OP:{
      result = str_like(left, right); 
    } break;
    case NOT_LIKE_OP:{
      result = !str_like(left, right);
    } break;
    default: {
      LOG_WARN("unsupported comparison. %d", comp_);
      rc = RC::INTERNAL;
    } break;
  }

  return rc;
}

RC ComparisonExpr::try_get_value(Value &cell) const
{
  if (left_->type() == ExprType::VALUE && right_->type() == ExprType::VALUE) {
    ValueExpr *  left_value_expr  = static_cast<ValueExpr *>(left_.get());
    ValueExpr *  right_value_expr = static_cast<ValueExpr *>(right_.get());
    const Value &left_cell        = left_value_expr->get_value();
    const Value &right_cell       = right_value_expr->get_value();

    bool value = false;
    RC   rc    = compare_value(left_cell, right_cell, value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to compare tuple cells. rc=%s", strrc(rc));
    } else {
      cell.set_boolean(value);
    }
    return rc;
  }

  return RC::INVALID_ARGUMENT;
}

RC ComparisonExpr::get_value(const Tuple &tuple, Value &value) const
{
  Value left_value;
  Value right_value;
  RC    rc = RC::SUCCESS;

  rc = left_->get_value(tuple, left_value);
  if (rc != RC::SUCCESS)
  {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    if (rc == RC::RECORD_EOF) { rc = RC::INVALID_ARGUMENT; }
    return rc;
  }

  switch (comp_)
  {
    case EXISTS_OP:
    case NOT_EXISTS_OP:
    {
      rc = right_->get_value(tuple, right_value);
      if (rc != RC::SUCCESS && rc != RC::RECORD_EOF)
      {
        LOG_WARN("EXISTS/NOT_EXISTS get right value failed.");
        return rc;
      }
      value.set_boolean(comp_ == EXISTS_OP ? rc == RC::SUCCESS : rc == RC::RECORD_EOF);
      rc = RC::SUCCESS;
    } break;
    
    case IN_OP:
    case NOT_IN_OP:
    {
      if (left_value.is_null())
      {
        value.set_boolean(false);
        return RC::SUCCESS;
      }

      bool result = false;
      bool has_a_null = false;
      if (right_->type() != ExprType::SUBQUERY && right_->type() != ExprType::EXPRLIST)
      {
        LOG_WARN("Expected an enumerable expression after `IN`.");
        return RC::INVALID_ARGUMENT;
      }
      auto sq_expr    = static_cast<const EnumerableExpr *>(right_.get());
      while (RC::SUCCESS == (rc = sq_expr->get_value_with_eof(tuple, right_value))) {
        if (right_value.is_null()) { has_a_null = true; }
        else if (left_value.compare(right_value) == ValCmpRes::EQUAL) { result = true; }
      }

      value.set_boolean(comp_ == IN_OP ? result : (has_a_null ? false : !result));
      rc = rc == RC::RECORD_EOF ? RC::SUCCESS : rc;
    } break;

    default:
    {
      rc = right_->get_value(tuple, right_value);
      if (rc != RC::SUCCESS)
      {
        LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
        return rc;
      }

      bool bool_value = false;

      rc = compare_value(left_value, right_value, bool_value);

      if (right_->type() == ExprType::SUBQUERY || right_->type() == ExprType::EXPRLIST)
      {
        auto sq_expr    = static_cast<const EnumerableExpr *>(right_.get());
        if (sq_expr->get_value_with_eof(tuple, right_value) != RC::RECORD_EOF)
        {
          LOG_WARN("Expected a scalar expression to compare.");
          return RC::INVALID_ARGUMENT;
        }
      }

      if (rc == RC::SUCCESS)
      {
        value.set_boolean(bool_value);
      }
    } break;
  }

  return rc;
}

RC ComparisonExpr::eval(Chunk &chunk, std::vector<uint8_t> &select)
{
  RC     rc = RC::SUCCESS;
  Column left_column;
  Column right_column;

  rc = left_->get_column(chunk, left_column);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }
  rc = right_->get_column(chunk, right_column);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
    return rc;
  }
  if (left_column.attr_type() != right_column.attr_type()) {
    LOG_WARN("cannot compare columns with different types");
    return RC::INTERNAL;
  }
  if (left_column.attr_type() == AttrType::INTS) {
    rc = compare_column<int>(left_column, right_column, select);
  } else if (left_column.attr_type() == AttrType::FLOATS) {
    rc = compare_column<float>(left_column, right_column, select);
  } else {
    // TODO: support string compare
    LOG_WARN("unsupported data type %d", left_column.attr_type());
    return RC::INTERNAL;
  }
  return rc;
}

template <typename T>
RC ComparisonExpr::compare_column(const Column &left, const Column &right, std::vector<uint8_t> &result) const
{
  RC rc = RC::SUCCESS;

  bool left_const  = left.column_type() == Column::Type::CONSTANT_COLUMN;
  bool right_const = right.column_type() == Column::Type::CONSTANT_COLUMN;
  if (left_const && right_const) {
    compare_result<T, true, true>((T *)left.data(), (T *)right.data(), left.count(), result, comp_);
  } else if (left_const && !right_const) {
    compare_result<T, true, false>((T *)left.data(), (T *)right.data(), right.count(), result, comp_);
  } else if (!left_const && right_const) {
    compare_result<T, false, true>((T *)left.data(), (T *)right.data(), left.count(), result, comp_);
  } else {
    compare_result<T, false, false>((T *)left.data(), (T *)right.data(), left.count(), result, comp_);
  }
  return rc;
}

////////////////////////////////////////////////////////////////////////////////
ConjunctionExpr::ConjunctionExpr(Type type, vector<unique_ptr<Expression>> &children)
    : conjunction_type_(type), children_(std::move(children))
{}

ConjunctionExpr::ConjunctionExpr(Type type, Expression* left, Expression* right)
    : conjunction_type_(type)
{
  children_.emplace_back(left);
  children_.emplace_back(right);
}

RC ConjunctionExpr::get_value(const Tuple &tuple, Value &value) const
{
  RC rc = RC::SUCCESS;
  if (children_.empty()) {
    value.set_boolean(true);
    return rc;
  }

  Value tmp_value;
  for (const unique_ptr<Expression> &expr : children_) {
    rc = expr->get_value(tuple, tmp_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value by child expression. rc=%s", strrc(rc));
      return rc;
    }
    bool bool_value = tmp_value.get_boolean();
    if ((conjunction_type_ == Type::AND && !bool_value) || (conjunction_type_ == Type::OR && bool_value)) {
      value.set_boolean(bool_value);
      return rc;
    }
  }

  bool default_value = (conjunction_type_ == Type::AND);
  value.set_boolean(default_value);
  return rc;
}

////////////////////////////////////////////////////////////////////////////////

ArithmeticExpr::ArithmeticExpr(ArithmeticExpr::Type type, Expression *left, Expression *right)
    : arithmetic_type_(type), left_(left), right_(right)
{}
ArithmeticExpr::ArithmeticExpr(ArithmeticExpr::Type type, unique_ptr<Expression> left, unique_ptr<Expression> right)
    : arithmetic_type_(type), left_(std::move(left)), right_(std::move(right))
{}

bool ArithmeticExpr::equal(const Expression &other) const
{
  if (this == &other) {
    return true;
  }
  if (type() != other.type()) {
    return false;
  }
  auto &other_arith_expr = static_cast<const ArithmeticExpr &>(other);
  return arithmetic_type_ == other_arith_expr.arithmetic_type() && left_->equal(*other_arith_expr.left_) &&
         right_->equal(*other_arith_expr.right_);
}
AttrType ArithmeticExpr::value_type() const
{
  // 负数
  if (!right_) {
    return left_->value_type();
  }

  // 任何数和 null 比较均为 null
  if ((left_->value_type() == AttrType::NULLS) || (right_->value_type() == AttrType::NULLS)) {
    return AttrType::NULLS;
  }

  // 数字之间比较
  if ((left_->value_type() == AttrType::INTS || left_->value_type() == AttrType::FLOATS) &&
      (right_->value_type() == AttrType::INTS || right_->value_type() == AttrType::FLOATS)) {
    if (left_->value_type() == AttrType::FLOATS || right_->value_type() == AttrType::FLOATS) {
      return AttrType::FLOATS;
    }
    if (arithmetic_type_ == Type::DIV) {
      return AttrType::FLOATS;
    }
    return AttrType::INTS;
  }

  // 如果 type 相同，直接返回
  if (left_->value_type() == right_->value_type()) {
    return left_->value_type();
  }

  // vector 和 chars 比较的时候，转为 chars 比较
  if ((left_->value_type() == AttrType::VECTORS && right_->value_type() == AttrType::CHARS) ||
      (left_->value_type() == AttrType::CHARS && right_->value_type() == AttrType::VECTORS)) {
    return AttrType::VECTORS;
  }

  return AttrType::FLOATS;
}

RC ArithmeticExpr::calc_value(const Value &left_value, const Value &right_value, Value &value) const
{
  RC rc = RC::SUCCESS;

  // 如果 left_value 和 right_value 有一个是 nulls，则结果为 null
  if (left_value.attr_type() == AttrType::NULLS || right_value.attr_type() == AttrType::NULLS) {
    value.set_type(AttrType::NULLS);
    return rc;
  }
  value.set_type(value_type());

  switch (arithmetic_type_) {
    case Type::ADD: {
      rc = Value::add(left_value, right_value, value);
    } break;

    case Type::SUB: {
      rc = Value::subtract(left_value, right_value, value);
    } break;

    case Type::MUL: {
      rc = Value::multiply(left_value, right_value, value);
    } break;

    case Type::DIV: {
      rc = Value::divide(left_value, right_value, value);
    } break;

    case Type::NEGATIVE: {
      rc = Value::negative(left_value, value);
    } break;

    default: {
      rc = RC::INTERNAL;
      LOG_WARN("unsupported arithmetic type. %d", arithmetic_type_);
    } break;
  }
  return rc;
}

template <bool LEFT_CONSTANT, bool RIGHT_CONSTANT>
RC ArithmeticExpr::execute_calc(
    const Column &left, const Column &right, Column &result, Type type, AttrType attr_type) const
{
  RC rc = RC::SUCCESS;
  switch (type) {
    case Type::ADD: {
      if (attr_type == AttrType::INTS) {
        binary_operator<LEFT_CONSTANT, RIGHT_CONSTANT, int, AddOperator>(
            (int *)left.data(), (int *)right.data(), (int *)result.data(), result.capacity());
      } else if (attr_type == AttrType::FLOATS) {
        binary_operator<LEFT_CONSTANT, RIGHT_CONSTANT, float, AddOperator>(
            (float *)left.data(), (float *)right.data(), (float *)result.data(), result.capacity());
      } else {
        rc = RC::UNIMPLEMENTED;
      }
    } break;
    case Type::SUB:
      if (attr_type == AttrType::INTS) {
        binary_operator<LEFT_CONSTANT, RIGHT_CONSTANT, int, SubtractOperator>(
            (int *)left.data(), (int *)right.data(), (int *)result.data(), result.capacity());
      } else if (attr_type == AttrType::FLOATS) {
        binary_operator<LEFT_CONSTANT, RIGHT_CONSTANT, float, SubtractOperator>(
            (float *)left.data(), (float *)right.data(), (float *)result.data(), result.capacity());
      } else {
        rc = RC::UNIMPLEMENTED;
      }
      break;
    case Type::MUL:
      if (attr_type == AttrType::INTS) {
        binary_operator<LEFT_CONSTANT, RIGHT_CONSTANT, int, MultiplyOperator>(
            (int *)left.data(), (int *)right.data(), (int *)result.data(), result.capacity());
      } else if (attr_type == AttrType::FLOATS) {
        binary_operator<LEFT_CONSTANT, RIGHT_CONSTANT, float, MultiplyOperator>(
            (float *)left.data(), (float *)right.data(), (float *)result.data(), result.capacity());
      } else {
        rc = RC::UNIMPLEMENTED;
      }
      break;
    case Type::DIV:
      if (attr_type == AttrType::INTS) {
        binary_operator<LEFT_CONSTANT, RIGHT_CONSTANT, int, DivideOperator>(
            (int *)left.data(), (int *)right.data(), (int *)result.data(), result.capacity());
      } else if (attr_type == AttrType::FLOATS) {
        binary_operator<LEFT_CONSTANT, RIGHT_CONSTANT, float, DivideOperator>(
            (float *)left.data(), (float *)right.data(), (float *)result.data(), result.capacity());
      } else {
        rc = RC::UNIMPLEMENTED;
      }
      break;
    case Type::NEGATIVE:
      if (attr_type == AttrType::INTS) {
        unary_operator<LEFT_CONSTANT, int, NegateOperator>((int *)left.data(), (int *)result.data(), result.capacity());
      } else if (attr_type == AttrType::FLOATS) {
        unary_operator<LEFT_CONSTANT, float, NegateOperator>(
            (float *)left.data(), (float *)result.data(), result.capacity());
      } else {
        rc = RC::UNIMPLEMENTED;
      }
      break;
    default: rc = RC::UNIMPLEMENTED; break;
  }
  if (rc == RC::SUCCESS) {
    result.set_count(result.capacity());
  }
  return rc;
}

RC ArithmeticExpr::get_value(const Tuple &tuple, Value &value) const
{
  RC rc = RC::SUCCESS;

  Value left_value;
  Value right_value;

  rc = left_->get_value(tuple, left_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }
  if (right_) {
    rc = right_->get_value(tuple, right_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
      return rc;
    }
  }
  return calc_value(left_value, right_value, value);
}

RC ArithmeticExpr::get_column(Chunk &chunk, Column &column)
{
  RC rc = RC::SUCCESS;
  if (pos_ != -1) {
    column.reference(chunk.column(pos_));
    return rc;
  }
  Column left_column;
  Column right_column;

  rc = left_->get_column(chunk, left_column);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get column of left expression. rc=%s", strrc(rc));
    return rc;
  }
  rc = right_->get_column(chunk, right_column);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get column of right expression. rc=%s", strrc(rc));
    return rc;
  }
  return calc_column(left_column, right_column, column);
}

RC ArithmeticExpr::calc_column(const Column &left_column, const Column &right_column, Column &column) const
{
  RC rc = RC::SUCCESS;

  const AttrType target_type = value_type();
  column.init(target_type, left_column.attr_len(), std::max(left_column.count(), right_column.count()));
  bool left_const  = left_column.column_type() == Column::Type::CONSTANT_COLUMN;
  bool right_const = right_column.column_type() == Column::Type::CONSTANT_COLUMN;
  if (left_const && right_const) {
    column.set_column_type(Column::Type::CONSTANT_COLUMN);
    rc = execute_calc<true, true>(left_column, right_column, column, arithmetic_type_, target_type);
  } else if (left_const && !right_const) {
    column.set_column_type(Column::Type::NORMAL_COLUMN);
    rc = execute_calc<true, false>(left_column, right_column, column, arithmetic_type_, target_type);
  } else if (!left_const && right_const) {
    column.set_column_type(Column::Type::NORMAL_COLUMN);
    rc = execute_calc<false, true>(left_column, right_column, column, arithmetic_type_, target_type);
  } else {
    column.set_column_type(Column::Type::NORMAL_COLUMN);
    rc = execute_calc<false, false>(left_column, right_column, column, arithmetic_type_, target_type);
  }
  return rc;
}

RC ArithmeticExpr::try_get_value(Value &value) const
{
  RC rc = RC::SUCCESS;

  Value left_value;
  Value right_value;

  rc = left_->try_get_value(left_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }

  if (right_) {
    rc = right_->try_get_value(right_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
      return rc;
    }
  }

  return calc_value(left_value, right_value, value);
}

bool ArithmeticExpr::exp2value(Expression *exp, Value *value)
{
  if (exp->type() == ExprType::VALUE) {
    ValueExpr *tmp = static_cast<ValueExpr *>(exp);
    *value         = tmp->get_value();
    return true;
  }
  if (exp->type() == ExprType::ARITHMETIC) {
    ArithmeticExpr *tmp = static_cast<ArithmeticExpr *>(exp);
    if (tmp->arithmetic_type() != ArithmeticExpr::Type::NEGATIVE && tmp->left()->type() != ExprType::VALUE) {
      return false;
    }
    ValueExpr *lhs = static_cast<ValueExpr *>(tmp->left().get());
    *value         = lhs->get_value();
    value->set_neg();
    return true;
  }
  return false;
}

////////////////////////////////////////////////////////////////////////////////

UnboundAggregateExpr::UnboundAggregateExpr(const char *aggregate_name, Expression *child)
    : aggregate_name_(aggregate_name), child_(child)
{}

////////////////////////////////////////////////////////////////////////////////
AggregateExpr::AggregateExpr(Type type, Expression *child) : aggregate_type_(type), child_(child) {}

AggregateExpr::AggregateExpr(Type type, unique_ptr<Expression> child) : aggregate_type_(type), child_(std::move(child))
{}

RC AggregateExpr::get_column(Chunk &chunk, Column &column)
{
  RC rc = RC::SUCCESS;
  if (pos_ != -1) {
    column.reference(chunk.column(pos_));
  } else {
    rc = RC::INTERNAL;
  }
  return rc;
}

bool AggregateExpr::equal(const Expression &other) const
{
  if (this == &other) {
    return true;
  }
  if (other.type() != type()) {
    return false;
  }
  const AggregateExpr &other_aggr_expr = static_cast<const AggregateExpr &>(other);
  return aggregate_type_ == other_aggr_expr.aggregate_type() && child_->equal(*other_aggr_expr.child());
}

unique_ptr<Aggregator> AggregateExpr::create_aggregator() const
{
  unique_ptr<Aggregator> aggregator;
  switch (aggregate_type_) {
    case Type::COUNT: {
      aggregator = make_unique<CountAggregator>();
      break;
    }
    case Type::SUM: {
      aggregator = make_unique<SumAggregator>();
      break;
    }
    case Type::AVG: {
      aggregator = make_unique<AvgAggregator>();
      break;
    }
    case Type::MIN: {
      aggregator = make_unique<MinAggregator>();
      break;
    }
    case Type::MAX: {
      aggregator = make_unique<MaxAggregator>();
      break;
    }
    default: {
      ASSERT(false, "unsupported aggregate type");
      break;
    }
  }
  return aggregator;
}

RC AggregateExpr::get_value(const Tuple &tuple, Value &value) const
{
  return tuple.find_cell(TupleCellSpec(name()), value);
}

RC AggregateExpr::type_from_string(const char *type_str, AggregateExpr::Type &type)
{
  RC rc = RC::SUCCESS;
  if (0 == strcasecmp(type_str, "count")) {
    type = Type::COUNT;
  } else if (0 == strcasecmp(type_str, "sum")) {
    type = Type::SUM;
  } else if (0 == strcasecmp(type_str, "avg")) {
    type = Type::AVG;
  } else if (0 == strcasecmp(type_str, "max")) {
    type = Type::MAX;
  } else if (0 == strcasecmp(type_str, "min")) {
    type = Type::MIN;
  } else {
    rc = RC::INVALID_ARGUMENT;
  }
  return rc;
}

////////////////////////////////////////////////////////////////////////////////
FunctionExpr::FunctionExpr(Type type, Expression *left, Expression *right)
    : function_type_(type), left_(left), right_(right)
{}

FunctionExpr::FunctionExpr(Type type, std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
    : function_type_(type), left_(std::move(left)), right_(std::move(right))
{}

bool FunctionExpr::equal(const Expression &other) const
{
  if (this == &other) {
    return true;
  }
  if (other.type() != type()) {
    return false;
  }
  const FunctionExpr &func_expr = static_cast<const FunctionExpr &>(other);
  return function_type() == func_expr.function_type() && value_length() == func_expr.value_length() &&
         left_->equal(*func_expr.left()) && right_->equal(*func_expr.right());
}

RC FunctionExpr::try_get_value(Value &value) const
{
  RC rc = RC::SUCCESS;

  Value left_value;
  Value right_value;

  rc = left_->try_get_value(left_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to try get value of left expression. rc=%s", strrc(rc));
    return rc;
  }
  if (right_) {
    rc = right_->try_get_value(right_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to try get value of right expression. rc=%s", strrc(rc));
      return rc;
    }
  }
  switch (function_type_) {
    case Type::L2_DISTANCE: rc = calc_l2_distance(left_value, right_value, value); break;
    case Type::COSINE_DISTANCE: rc = calc_cosine_distance(left_value, right_value, value); break;
    case Type::INNER_PRODUCT: rc = calc_inner_product(left_value, right_value, value); break;
  }
  return rc;
}

RC FunctionExpr::get_value(const Tuple &tuple, Value &value) const
{
  RC rc = RC::SUCCESS;

  Value left_value;
  Value right_value;

  rc = left_->get_value(tuple, left_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }
  if (right_) {
    rc = right_->get_value(tuple, right_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
      return rc;
    }
  }
  // 检查两个 vector 是否可以计算
  Value tmp1 = left_value;
  Value tmp2 = right_value;
  if (OB_FAIL(rc = reinterpret_cast<const VectorType *>(DataType::type_instance(AttrType::CHARS))
                       ->check(tmp1, tmp2, left_value, right_value))) {
    return rc;
  }
  switch (function_type_) {
    case Type::L2_DISTANCE: rc = calc_l2_distance(left_value, right_value, value); break;
    case Type::COSINE_DISTANCE: rc = calc_cosine_distance(left_value, right_value, value); break;
    case Type::INNER_PRODUCT: rc = calc_inner_product(left_value, right_value, value); break;
  }
  return rc;
}

RC FunctionExpr::calc_l2_distance(const Value &left, const Value &right, Value &result) const
{
  auto   l   = reinterpret_cast<const double *>(left.data());
  auto   r   = reinterpret_cast<const double *>(right.data());
  int    len = left.length() / sizeof(double);
  double ans = 0;
  for (int i = 0; i < len; i++) {
    ans += (l[i] - r[i]) * (l[i] - r[i]);
  }
  ans    = std::sqrt(ans);
  result = Value(static_cast<float>(ans));
  return RC::SUCCESS;
}

RC FunctionExpr::calc_cosine_distance(const Value &left, const Value &right, Value &result) const
{
  auto   l    = reinterpret_cast<const double *>(left.data());
  auto   r    = reinterpret_cast<const double *>(right.data());
  int    len  = left.length() / sizeof(double);
  double ans1 = 0;
  double ans2 = 0;
  double ans3 = 0;
  for (int i = 0; i < len; i++) {
    ans1 += l[i] * r[i];
    ans2 += l[i] * l[i];
    ans3 += r[i] * r[i];
  }
  if (ans2 == 0 || ans3 == 0) {
    ans1 = 1;
  } else {
    ans1 = 1 - ans1 / std::sqrt(ans2) / std::sqrt(ans3);
  }
  result = Value(static_cast<float>(ans1));
  return RC::SUCCESS;
}

RC FunctionExpr::calc_inner_product(const Value &left, const Value &right, Value &result) const
{
  auto   l   = reinterpret_cast<const double *>(left.data());
  auto   r   = reinterpret_cast<const double *>(right.data());
  int    len = left.length() / sizeof(double);
  double ans = 0;
  for (int i = 0; i < len; i++) {
    ans += l[i] * r[i];
  }
  result = Value(static_cast<float>(ans));
  return RC::SUCCESS;
}

RC FunctionExpr::type_from_string(const char *type_str, FunctionExpr::Type &type)
{
  RC rc = RC::SUCCESS;
  if (0 == strcasecmp(type_str, "l2_distance")) {
    type = Type::L2_DISTANCE;
  } else if (0 == strcasecmp(type_str, "cosine_distance")) {
    type = Type::COSINE_DISTANCE;
  } else if (0 == strcasecmp(type_str, "inner_product")) {
    type = Type::INNER_PRODUCT;
  }
  return rc;
}

SubQueryExpr::SubQueryExpr(std::shared_ptr<SelectSqlNode> sql_node) : sql_node_(std::move(sql_node)) {}
SubQueryExpr::SubQueryExpr(SelectSqlNode &&sql_node) :  sql_node_(std::make_shared<SelectSqlNode>(std::move(sql_node))) {}
SubQueryExpr::~SubQueryExpr()
{
  if (is_open_) { physical_oper_->close(); }
}
RC SubQueryExpr::get_value(const Tuple &tuple, Value &value) const
{
  RC rc = get_value_with_eof(tuple, value);
  if (rc == RC::RECORD_EOF)
  {
    rc = get_value_with_eof(tuple, value);
  }
  return rc;
}

RC SubQueryExpr::get_value_with_eof(const Tuple &tuple, Value &value) const
{
  if (cached_)
  {
    // ignore the argument tuple
    try
    {
      value = selected_values_.at(current_++);
      return RC::SUCCESS;
    }
    catch(const std::out_of_range& e)
    {
      current_ = 0;
      return RC::RECORD_EOF;
    }
  }

  if (!is_open_) { _open(nullptr); }
  RC rc = physical_oper_->next();
  if (OB_FAIL(rc))
  {
    cached_ |= (rc == RC::RECORD_EOF);
    return rc;
  }
  auto t = physical_oper_->current_tuple();
  if (t->cell_num() != 1)
  {
    t->cell_at(0, value);
    return RC::INVALID_ARGUMENT;
  }
  rc = t->cell_at(0, value);

  if (OB_SUCC(rc))
  {
    selected_values_.push_back(value);
  }
  return rc;
}


RC SubQueryExpr::_open(Trx* trx) const
{
  LogicalPlanGenerator lpg;
  std::unique_ptr<LogicalOperator> sub_query_logi_oper;
  if (RC rc = lpg.create(stmt_.get(), sub_query_logi_oper); RC::SUCCESS != rc) {
    return rc;
  }

  PhysicalPlanGenerator ppg;
  std::unique_ptr<PhysicalOperator> sub_query_phy_oper;
  if (RC rc = ppg.create(*sub_query_logi_oper.get(), sub_query_phy_oper); RC::SUCCESS != rc) {
    return rc;
  }

  logical_oper_ = std::move(sub_query_logi_oper);
  physical_oper_ = std::move(sub_query_phy_oper);

  RC rc = physical_oper_->open(trx);
  if (OB_FAIL(rc))
  {
    LOG_WARN("sub query open failed");
    return rc;
  }
  
  is_open_ = true;
  return rc;
}

const std::shared_ptr<SelectSqlNode>    &SubQueryExpr::sql_node() const { return sql_node_; }
void                                     SubQueryExpr::set_select_stmt(SelectStmt *stmt) const { stmt_.reset(stmt); }
const std::shared_ptr<SelectStmt>       &SubQueryExpr::select_stmt() const { return stmt_; }

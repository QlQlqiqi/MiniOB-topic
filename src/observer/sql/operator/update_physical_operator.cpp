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
// Created by yqzhang4480 on 2024/10/18.
//

#include "sql/operator/update_physical_operator.h"
#include "sql/stmt/update_stmt.h"
#include "storage/table/table.h"
#include "storage/trx/trx.h"
#include <algorithm>
#include "event/sql_debug.h"

UpdatePhysicalOperator::UpdatePhysicalOperator(
    Table *table, std::vector<std::pair<FieldMeta, std::unique_ptr<Expression>>>&& values)
    : table_(table), values_(std::move(values))
{}

// RC UpdatePhysicalOperator::rollback(
//     Trx *trx, std::vector<Record> &deleted_records, std::vector<Record> &inserted_records) const
// {
//   for (auto &record : inserted_records) {
//     RC rc = trx->delete_record(table_, record);
//     if (OB_FAIL(rc)) {
//       LOG_WARN("failed to rollback in delete records: %s", strrc(rc));
//       return rc;
//     }
//   }
//   for (auto &record : deleted_records) {
//     RC rc = trx->insert_record(table_, record);
//     if (OB_FAIL(rc)) {
//       LOG_WARN("failed to rollback in insert records: %s", strrc(rc));
//       return rc;
//     }
//   }
//   LOG_INFO("rollback records success");
//   return RC::SUCCESS;
// }

// TODO(qiqi): 这里有性能问题，在这 delete 和 insert 阶段中，都会将 record 深度复制一遍 (zyq:现在在Table::update_record存在复制)
RC UpdatePhysicalOperator::open(Trx *trx)
{
  if (children_.empty()) {
    return RC::SUCCESS;
  }

  RC rc = children_[0]->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  trx_ = trx;

  return RC::SUCCESS;
}

RC UpdatePhysicalOperator::next()
{
  RC rc = RC::SUCCESS;
  if (children_.empty())
  {
    return RC::RECORD_EOF;
  }

  auto child = children_[0].get();

  while (RC::SUCCESS == (rc = child->next())) {
    Tuple *tuple = child->current_tuple();
    if (!tuple)
    {
      LOG_WARN("failed to get current record: %s", strrc(rc));
      return rc;
    }

    RowTuple *row_tuple = static_cast<RowTuple *>(tuple);
    records_.emplace_back(std::move(row_tuple->record()));
  }

  child->close();

  for (auto& record : records_)
  {
    auto match = [](FieldMeta &f, Value &v) {
      if (auto ftype = f.type(), vtype = v.attr_type(); ftype != vtype) {
        if (f.nullable() && v.attr_type() == AttrType::NULLS) {
          return RC::SUCCESS;
        }
        Value t;
        if (OB_FAIL(Value::strictly_cast_to(v, ftype, t))) {
          return RC::SCHEMA_FIELD_TYPE_MISMATCH;
        }
        v = t;
      }
      return RC::SUCCESS;
    };

    std::vector<std::pair<FieldMeta, Value>> raw_values;
    for (auto &[f, expr] : values_) {
      Value v;
      RC    rc = expr->get_value(RowTuple{}, v); // unrelated to tuple
      if (OB_FAIL(rc)) {
        if (rc == RC::RECORD_EOF) {
          v.set_null();
        } else {
          return rc;
        }
      }

      rc = match(f, v);
      if (OB_FAIL(rc)) {
        sql_debug("schema mismatch. field(%s) type: %d, value type: %d",
            f.name(),
            static_cast<int>(f.type()),
            static_cast<int>(v.attr_type()));
        LOG_WARN("schema mismatch. field type: %d, value type: %d", static_cast<int>(f.type()), static_cast<int>(v.attr_type()));
        return rc;
      }

      if (expr->type() == ExprType::SUBQUERY || expr->type() == ExprType::EXPRLIST) {
        auto sq_expr = static_cast<const EnumerableExpr *>(expr.get());
        if (sq_expr->get_value_with_eof(RowTuple{}, v) != RC::RECORD_EOF) {
          LOG_WARN("Expected a scalar expression to update.");
          return RC::INVALID_ARGUMENT;
        }
      }

      raw_values.emplace_back(f, v);
    }

    rc = trx_->update_record(table_, record, raw_values);
  }

  return RC::RECORD_EOF;
}



RC UpdatePhysicalOperator::close()
{
  return RC::SUCCESS;
}

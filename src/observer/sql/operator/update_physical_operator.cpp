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

RC UpdatePhysicalOperator::rollback(
    Trx *trx, std::vector<Record> &deleted_records, std::vector<Record> &inserted_records) const
{
  for (auto &record : inserted_records) {
    RC rc = trx->delete_record(table_, record);
    if (OB_FAIL(rc)) {
      LOG_WARN("failed to rollback in delete records: %s", strrc(rc));
      return rc;
    }
  }
  for (auto &record : deleted_records) {
    RC rc = trx->insert_record(table_, record);
    if (OB_FAIL(rc)) {
      LOG_WARN("failed to rollback in insert records: %s", strrc(rc));
      return rc;
    }
  }
  LOG_INFO("rollback records success");
  return RC::SUCCESS;
}

// TODO(qiqi): 这里有性能问题，在这 delete 和 insert 阶段中，都会将 record 深度复制一遍
RC UpdatePhysicalOperator::open(Trx *trx)
{
  if (children_.empty()) {
    return RC::SUCCESS;
  }

  std::unique_ptr<PhysicalOperator> &child = children_[0];

  RC rc = child->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  trx_ = trx;

  RowTuple *row_tuple = nullptr;
  while (OB_SUCC(rc = child->next())) {
    Tuple *tuple = child->current_tuple();
    if (nullptr == tuple) {
      LOG_WARN("failed to get current record: %s", strrc(rc));
      return rc;
    }

    row_tuple = static_cast<RowTuple *>(tuple);
    Record   &record    = row_tuple->record();
    records_.emplace_back(std::move(record));
  }

  if (rc != RC::RECORD_EOF)
  {
    return rc;
  }

  child->close();

  // TODO(qiqi): 因为目前没有 trx 功能，所以需要手动恢复
  std::vector<Record> deleted_records;
  std::vector<Record> inserted_records;

  for (Record &record : records_){
    Record table_record;
    rc = table_->get_record(record.rid(), table_record);
    if (OB_FAIL(rc)) {
      LOG_WARN("failed to get record. rid=%d, rc=%s", record.rid(), strrc(rc));
      trx->rollback();
      rollback(trx, deleted_records, inserted_records);
      return rc;
    }

    // 1. prepare a record...
    for (auto &[f, expr] : values_) {
      Value v;
      if (nullptr == row_tuple) {
        return RC::INTERNAL;
      }
      RC rc = expr->get_value(*row_tuple, v);
      if (OB_FAIL(rc)) {
        if (rc == RC::RECORD_EOF) {
          v.set_null();
        } else {
          return rc;
        }
      }

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

      // 读取 text 内容
      // if (f.type() == AttrType::TEXTS && !v.is_null()) {
      //   ASSERT(v.attr_type() == AttrType::CHARS, "value must be chars");
      //   RC rc = table_->get_text_from_record(record.data() + f.offset() + f.nullable(), v);
      //   if (RC::SUCCESS != rc) {
      //     LOG_WARN("Failed to read text rc=%s", strrc(rc));
      //     return rc;
      //   }
      // }

      rc = match(f, v);
      if (OB_FAIL(rc)) {
        sql_debug("schema mismatch. field(%s) type: %d, value type: %d",
          f.name(),
          static_cast<int>(f.type()),
          static_cast<int>(v.attr_type()));
        LOG_WARN("schema mismatch. field type: %d, value type: %d", static_cast<int>(f.type()), static_cast<int>(v.attr_type()));
        return rc;
      }

      if (expr->type() == ExprType::SUBQUERY || expr->type() == ExprType::EXPRLIST)
      {
        auto sq_expr    = static_cast<const EnumerableExpr *>(expr.get());
        if (sq_expr->get_value_with_eof(*row_tuple, v) != RC::RECORD_EOF)
        {
          LOG_WARN("Expected a scalar expression to update.");
          return RC::INVALID_ARGUMENT;
        }
      }

      switch (v.attr_type()) {
        case AttrType::NULLS: {
          assert(f.nullable());
          auto ones = std::vector<char>(f.len(), '\1');
          rc        = table_record.set_field(f.offset(), f.len(), ones.data());
          if (OB_FAIL(rc)) {
            LOG_WARN("failed to update record. rid=%d, rc=%s", record.rid(), strrc(rc));
            trx->rollback();
            return rc;
          }
        } break;
        case AttrType::CHARS: {
          // text 不应处理，因为 text 的 value 长度是变长的
          if (f.type() == AttrType::TEXTS) {
            // 检查 text 是否超过限制
            if (v.length() > TEXT_MAX_SIZE) {
              LOG_WARN("text length is too large: %d", v.length());
              return RC::INVALID_ARGUMENT;
            }
            // 先置 is_null 标志位为 0
            table_record.set_field(f.offset(), 1, "\0");
            // 为了下面 insert 的使用，这里先将目标内容插入到 text buffer pool 中
            RC rc = table_->set_text_and_store_record(
                v.data(), v.length(), table_record.data() + f.offset() + f.nullable());
            if (OB_FAIL(rc)) {
              LOG_WARN("failed to write text into text_buffer_pool_");
              return rc;
            }
            break;
          }
          auto zeros = std::vector<char>(f.len(), '\0');
          rc         = table_record.set_field(f.offset(), f.len(), zeros.data());
          if (OB_FAIL(rc)) {
            LOG_WARN("failed to update record. rid=%d, rc=%s", record.rid(), strrc(rc));
            trx->rollback();
            return rc;
          }
          [[fallthrough]];
        }
        default: {
          rc = table_record.set_field(f.offset() + f.nullable(), v.length(), v.data());
          if (OB_FAIL(rc)) {
            LOG_WARN("failed to update record. rid=%d, rc=%s", record.rid(), strrc(rc));
            trx->rollback();
            return rc;
          }
        } break;
      }
    }

    // 2. remove old record...
    rc = trx->delete_record(table_, record);
    if (OB_FAIL(rc)) {
      sql_debug("failed to remove old record. rid=%d, rc=%s", record.rid(), strrc(rc));
      LOG_WARN("failed to remove old record. rid=%d, rc=%s", record.rid(), strrc(rc));
      trx->rollback();
      rollback(trx, deleted_records, inserted_records);
      return rc;
    }
    Record tmp1 = record;
    tmp1.copy_data(record.data(), record.len());
    deleted_records.emplace_back(tmp1);

    // 3. insert new record...
    rc = trx->insert_record(table_, table_record);
    if (OB_FAIL(rc)) {
      sql_debug("failed to insert new record. rid=%d, rc=%s", table_record.rid(), strrc(rc));
      LOG_WARN("failed to insert new record. rid=%d, rc=%s", table_record.rid(), strrc(rc));
      trx->rollback();
      rollback(trx, deleted_records, inserted_records);
      return rc;
    }
    Record tmp2 = table_record;
    tmp2.copy_data(table_record.data(), table_record.len());
    inserted_records.emplace_back(tmp2);
  }

  return RC::SUCCESS;

}

RC UpdatePhysicalOperator::next() { return RC::RECORD_EOF; }

RC UpdatePhysicalOperator::close() { return RC::SUCCESS; }


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

#include "sql/operator/view_update_physical_operator.h"
#include "sql/stmt/update_stmt.h"
#include "storage/view/view.h"
#include "storage/trx/trx.h"
#include "event/sql_debug.h"
#include <algorithm>

using namespace std;

ViewUpdatePhysicalOperator::ViewUpdatePhysicalOperator(
    View *view, std::vector<std::pair<FieldMeta, std::unique_ptr<Expression>>>&& values)
    : view_(view), values_(std::move(values))
{}

RC ViewUpdatePhysicalOperator::rollback(
    Trx *trx, std::vector<Record> &deleted_records, std::vector<Record> &inserted_records) const
{
  for (auto &record : inserted_records) {
    RC rc = trx->delete_record(view_, record);
    if (OB_FAIL(rc)) {
      LOG_WARN("failed to rollback in delete records: %s", strrc(rc));
      return rc;
    }
  }
  for (auto &record : deleted_records) {
    RC rc = trx->insert_record(view_, record);
    if (OB_FAIL(rc)) {
      LOG_WARN("failed to rollback in insert records: %s", strrc(rc));
      return rc;
    }
  }
  LOG_INFO("rollback records success");
  return RC::SUCCESS;
}

// TODO(qiqi): 这里有性能问题，在这 delete 和 insert 阶段中，都会将 record 深度复制一遍
RC ViewUpdatePhysicalOperator::open(Trx *trx)
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

  std::vector<Record> deleted_records;
  std::vector<Record> inserted_records;
  std::unordered_map<Table*, Record> old_records;
  std::unordered_map<Table*, Record> update_records;
  while (OB_SUCC(rc = child->next())) {
    // TODO(qiqi): 因为目前没有 trx 功能，所以需要手动恢复
    Tuple *tuple = child->current_tuple();
    if (nullptr == tuple) {
      LOG_WARN("failed to get current record: %s", strrc(rc));
      return rc;
    }

    ViewRowTuple *view_row_tuple = static_cast<ViewRowTuple *>(tuple);
    auto &rid_maps = view_row_tuple->get_rid_maps();

    for(auto & [table, rid]: rid_maps){
      Record record;
      table->get_record(rid, record);
      old_records[table] = record;
      update_records[table] = record;
    }

    // 1. prepare a record...
    auto &origin_fields = view_->origin_fields();
    for (auto &[field_meta, expr] : values_) {
      //这里 field_id 和 origin_fields index 是一一对应的
      //详细请看 create view 的逻辑
      auto &origin_field = origin_fields[field_meta.field_id()];
      auto origin_field_meta = origin_field->meta(); 
      //这里强行转换
      auto origin_table = const_cast<Table*>(origin_field->table());
      auto &origin_record = update_records[origin_table];

    // 1. prepare a record...
      Value v;
      if (nullptr == view_row_tuple) {
        return RC::INTERNAL;
      }
      RC rc = expr->get_value(*view_row_tuple, v);
      if (OB_FAIL(rc)) {
        if (rc == RC::RECORD_EOF) {
          v.set_null();
        } else {
          return rc;
        }
      }

      auto match = [](const FieldMeta &f, Value &v) {
        if (AttrType ftype = f.type(), vtype = v.attr_type(); ftype != vtype) {
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
      //   RC rc = origin_table->get_text_from_record(origin_record.data() + f.offset() + f.nullable(), v);
      //   if (RC::SUCCESS != rc) {
      //     LOG_WARN("Failed to read text rc=%s", strrc(rc));
      //     return rc;
      //   }
      // }

      rc = match(*origin_field_meta, v);
      if (OB_FAIL(rc)) {
        sql_debug("schema mismatch. field(%s) type: %d, value type: %d",
          field_meta.name(),
          static_cast<int>(origin_field_meta->type()),
          static_cast<int>(v.attr_type()));
        LOG_WARN("schema mismatch. field type: %d, value type: %d", static_cast<int>(origin_field_meta->type()), static_cast<int>(v.attr_type()));
        return rc;
      }

      if (expr->type() == ExprType::SUBQUERY || expr->type() == ExprType::EXPRLIST)
      {
        auto sq_expr    = static_cast<const EnumerableExpr *>(expr.get());
        if (sq_expr->get_value_with_eof(*view_row_tuple, v) != RC::RECORD_EOF)
        {
          LOG_WARN("Expected a scalar expression to update.");
          return RC::INVALID_ARGUMENT;
        }
      }

      switch (v.attr_type()) {
        case AttrType::NULLS: {
          assert(origin_field_meta->nullable());
          auto zeros = std::vector<char>(origin_field_meta->len(), '\1');
          rc         = origin_record.set_field(origin_field_meta->offset(), origin_field_meta->len(), zeros.data());
          if (OB_FAIL(rc)) {
            LOG_WARN("failed to update origin_record. rid=%d, rc=%s", origin_record.rid(), strrc(rc));
            trx->rollback();
            return rc;
          }
        } break;
        case AttrType::VECTORS: {
          // high vector 与 text 处理方式类似
          if (origin_field_meta->high_vector()) {
            // 检查 high vector dim
            if (origin_field_meta->dim() * sizeof(double) != v.length()) {
              LOG_WARN("high field's length %d should be the same as value's %d", origin_field_meta->dim() * sizeof(double), v.length());
              trx->rollback();
              return RC::INVALID_ARGUMENT;
            }
            // 先置 is_null 标志位为 0
            origin_record.set_field(origin_field_meta->offset(), 1, "\0");
            // 为了下面 insert 的使用，这里先将目标内容插入到 text buffer pool 中
            RC rc = origin_table->set_text_and_store_record(
                v.data(), v.length(), origin_record.data() + origin_field_meta->offset() + origin_field_meta->nullable());
            if (OB_FAIL(rc)) {
              LOG_WARN("failed to write text into text_buffer_pool_");
              trx->rollback();
              return rc;
            }
          } else {
            rc = origin_record.set_field(origin_field_meta->offset() + origin_field_meta->nullable(), v.length(), v.data());
            if (OB_FAIL(rc)) {
              LOG_WARN("failed to update origin_record. rid=%d, rc=%s", origin_record.rid(), strrc(rc));
              trx->rollback();
              return rc;
            }
          }
        } break;
        case AttrType::CHARS: {
          // text 不应处理，因为 text 的 value 长度是变长的
          if (origin_field_meta->type() == AttrType::TEXTS) {
            // 检查 text 是否超过限制
            if (v.length() > TEXT_MAX_SIZE) {
              LOG_WARN("text length is too large: %d", v.length());
              trx->rollback();
              return RC::INVALID_ARGUMENT;
            }
            // 先置 is_null 标志位为 0
            origin_record.set_field(origin_field_meta->offset(), 1, "\0");
            // 为了下面 insert 的使用，这里先将目标内容插入到 text buffer pool 中
            RC rc = origin_table->set_text_and_store_record(
                v.data(), v.length(), origin_record.data() + origin_field_meta->offset() + origin_field_meta->nullable());
            if (OB_FAIL(rc)) {
              LOG_WARN("failed to write text into text_buffer_pool_");
              trx->rollback();
              return rc;
            }
            break;
          }
          auto zeros = std::vector<char>(origin_field_meta->len(), '\0');
          rc         = origin_record.set_field(origin_field_meta->offset(), origin_field_meta->len(), zeros.data());
          if (OB_FAIL(rc)) {
            LOG_WARN("failed to update origin_record. rid=%d, rc=%s", origin_record.rid(), strrc(rc));
            trx->rollback();
            return rc;
          }
          [[fallthrough]];
        }
        default: {
          ASSERT((size_t)origin_field_meta->nullable() <= 1, "we assume that casting a bool value to an integer returns either a 0 or an 1.");
          // 先置 is_null 标志位为 0
          origin_record.set_field(origin_field_meta->offset(), origin_field_meta->nullable(), "\0");
          // 然后修改值
          rc = origin_record.set_field(origin_field_meta->offset() + origin_field_meta->nullable(), v.length(), v.data());
          if (OB_FAIL(rc)) {
            LOG_WARN("failed to update origin_record. rid=%d, rc=%s", origin_record.rid(), strrc(rc));
            trx->rollback();
            return rc;
          }
        } break;
      }
    }

    // 2. remove old record...
    for(auto &[table, record] : old_records){
      rc = trx->delete_record(table, record);
      if (OB_FAIL(rc)) {
        LOG_WARN("failed to remove old record. rid=%d, rc=%s", record.rid(), strrc(rc));
        trx->rollback();
        rollback(trx, deleted_records, inserted_records);
        return rc;
      }
      Record tmp1 = record;
      tmp1.copy_data(record.data(), record.len());
      deleted_records.emplace_back(tmp1);
    }

    // 3. insert new record...
    for(auto &[table, record] : update_records){
      rc = trx->insert_record(table, record);
      if (OB_FAIL(rc)) {
        LOG_WARN("failed to insert new record. rid=%d, rc=%s", record.rid(), strrc(rc));
        trx->rollback();
        rollback(trx, deleted_records, inserted_records);
        return rc;
      }
      Record tmp2 = record;
      tmp2.copy_data(record.data(), record.len());
      inserted_records.emplace_back(tmp2);
    }
  }

  if (rc != RC::RECORD_EOF)
  {
    child->close();
    return rc;
  }

  child->close();
  return RC::SUCCESS;

}

RC ViewUpdatePhysicalOperator::next() { return RC::RECORD_EOF; }

RC ViewUpdatePhysicalOperator::close() { return RC::SUCCESS; }

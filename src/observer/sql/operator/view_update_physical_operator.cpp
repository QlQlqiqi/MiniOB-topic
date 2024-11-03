
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
#include <algorithm>

using namespace std;

ViewUpdatePhysicalOperator::ViewUpdatePhysicalOperator(
    View *view, std::vector<std::pair<FieldMeta, Value>> values)
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
    for (auto &item : values_) {
      auto &field_meta = item.first;
      auto &v = item.second;
      //这里 field_id 和 origin_fields index 是一一对应的
      //详细请看 create view 的逻辑
      auto &origin_field = origin_fields[field_meta.field_id()];
      auto origin_field_meta = origin_field->meta(); 
      //这里强行转换
      auto origin_table = const_cast<Table*>(origin_field->table());
      auto &origin_record = update_records[origin_table];

      switch (v.attr_type()) {
        case AttrType::NULLS: {
          assert(origin_field_meta->nullable());
          auto zeros = std::vector<char>(origin_field_meta->len(), '\1');
          rc         = origin_record.set_field(origin_field_meta->offset(), origin_field_meta->len(), zeros.data());
          if (OB_FAIL(rc)) {
            LOG_WARN("failed to update record. rid=%d, rc=%s", origin_record.rid(), strrc(rc));
            trx->rollback();
            return rc;
          }
        } break;
        case AttrType::CHARS: {
          auto zeros = std::vector<char>(origin_field_meta->len(), '\0');
          rc         = origin_record.set_field(origin_field_meta->offset(), origin_field_meta->len(), zeros.data());
          if (OB_FAIL(rc)) {
            LOG_WARN("failed to update record. rid=%d, rc=%s", origin_record.rid(), strrc(rc));
            trx->rollback();
            return rc;
          }
          [[fallthrough]];
        }
        default: {
          rc = origin_record.set_field(origin_field_meta->offset() + origin_field_meta->nullable(), v.length() - origin_field_meta->nullable(), v.data());
          if (OB_FAIL(rc)) {
            LOG_WARN("failed to update record. rid=%d, rc=%s", origin_record.rid(), strrc(rc));
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

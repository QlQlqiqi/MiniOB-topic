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

using namespace std;

UpdatePhysicalOperator::UpdatePhysicalOperator(
    Table *table, std::vector<std::pair<FieldMeta, Value>> values)
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

// TODO(qiqi): 这里有性能问题，在这 3 个阶段中，都会将 record深度复制一遍
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

  while (OB_SUCC(rc = child->next())) {
    Tuple *tuple = child->current_tuple();
    if (nullptr == tuple) {
      LOG_WARN("failed to get current record: %s", strrc(rc));
      return rc;
    }

    RowTuple *row_tuple = static_cast<RowTuple *>(tuple);
    Record   &record    = row_tuple->record();
    Record    tmp       = record;
    tmp.copy_data(record.data(), record.len());

    // 1. prepare a record...
    for (auto &item : values_) {
      auto &f = item.first;
      auto &v = item.second;
      switch (v.attr_type()) {
        case AttrType::NULLS: {
          assert(f.nullable());
          auto zeros = std::vector<char>(f.len(), '\1');
          rc         = tmp.set_field(f.offset(), f.len(), zeros.data());
          if (OB_FAIL(rc)) {
            LOG_WARN("failed to update record. rid=%d, rc=%s", record.rid(), strrc(rc));
            trx->rollback();
            return rc;
          }
        } break;
        case AttrType::CHARS: {
          auto zeros = std::vector<char>(f.len(), '\0');
          rc         = tmp.set_field(f.offset(), f.len(), zeros.data());
          if (OB_FAIL(rc)) {
            LOG_WARN("failed to update record. rid=%d, rc=%s", record.rid(), strrc(rc));
            trx->rollback();
            return rc;
          }
          [[fallthrough]];
        }
        default: {
          rc = tmp.set_field(f.offset() + f.nullable(), v.length() - f.nullable(), v.data());
          if (OB_FAIL(rc)) {
            LOG_WARN("failed to update record. rid=%d, rc=%s", record.rid(), strrc(rc));
            trx->rollback();
            return rc;
          }
        } break;
      }
    }

    records_.emplace_back(std::move(tmp));
  }

  if (rc != RC::RECORD_EOF)
  {
    return rc;
  }

  child->close();

  // TODO(qiqi): 因为目前没有 trx 功能，所以需要手动恢复
  std::vector<Record> deleted_records;
  std::vector<Record> inserted_records;

  // 2. remove old record...
  for (Record &record : records_){
    rc = trx->delete_record(table_, record);
    if (OB_FAIL(rc)) {
      LOG_WARN("failed to remove old record. rid=%d, rc=%s", record.rid(), strrc(rc));
      trx->rollback();
      rollback(trx, deleted_records, inserted_records);
      return rc;
    }
    Record tmp = record;
    tmp.copy_data(record.data(), record.len());
    deleted_records.emplace_back(tmp);
  }

  // 3. insert new record...
  for (Record &record : records_){
    rc = trx->insert_record(table_, record);
    if (OB_FAIL(rc)) {
      LOG_WARN("failed to insert new record. rid=%d, rc=%s", record.rid(), strrc(rc));
      trx->rollback();
      rollback(trx, deleted_records, inserted_records);
      return rc;
    }
    Record tmp = record;
    tmp.copy_data(record.data(), record.len());
    inserted_records.emplace_back(tmp);
  }

  return RC::SUCCESS;

}

RC UpdatePhysicalOperator::next() { return RC::RECORD_EOF; }

RC UpdatePhysicalOperator::close() { return RC::SUCCESS; }

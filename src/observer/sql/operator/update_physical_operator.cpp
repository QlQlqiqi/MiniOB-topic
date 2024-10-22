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

using namespace std;

UpdatePhysicalOperator::UpdatePhysicalOperator(
    Table *table, std::vector<Value> values, std::vector<FieldMeta> field_metas)
    : table_(table), values_(std::move(values)), field_metas_(std::move(field_metas))
{}

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
    records_.emplace_back(std::move(record));
  }

  if (rc != RC::RECORD_EOF)
  {
    return rc;
  }

  child->close();

  for (Record &record : records_)
  {
    Record table_record;
    table_->get_record(record.rid(), table_record);

    for (size_t i = 0; i < values_.size(); ++i)
    {
      auto &f       = field_metas_[i];
      auto &v       = values_[i];

      // 1. prepare a record...
      switch (v.attr_type())
      {
        case AttrType::NULLS:
        {
          assert(f.nullable());
          auto zeros = std::vector<char>(f.len(), '\1');
          rc = table_record.set_field(f.offset(), f.len(), zeros.data());
          if (OB_FAIL(rc))
          {
            LOG_WARN("failed to update record. rid=%d, rc=%s", record.rid(), strrc(rc));
            trx->rollback();
            return rc;
          }
        } break;
        case AttrType::CHARS:
        {
          auto zeros = std::vector<char>(f.len(), '\0');
          rc = table_record.set_field(f.offset(), f.len(), zeros.data());
          if (OB_FAIL(rc))
          {
            LOG_WARN("failed to update record. rid=%d, rc=%s", record.rid(), strrc(rc));
            trx->rollback();
            return rc;
          }
          [[fallthrough]];
        }
        default:
        {
          rc = table_record.set_field(f.offset() + f.nullable(), v.length() - f.nullable(), values_[i].data());
          if (OB_FAIL(rc)) {
            LOG_WARN("failed to update record. rid=%d, rc=%s", record.rid(), strrc(rc));
            trx->rollback();
            return rc;
          }
        } break;
      }

      // 2. remove old record...
      rc = trx->delete_record(table_, record);
      if (OB_FAIL(rc))
      {
        LOG_WARN("failed to remove old record. rid=%d, rc=%s", record.rid(), strrc(rc));
        trx->rollback();
        return rc;
      }

      // 3. insert new record...
      rc = trx->insert_record(table_, table_record);
      if (OB_FAIL(rc))
      {
        LOG_WARN("failed to insert new record. rid=%d, rc=%s", record.rid(), strrc(rc));
        trx->rollback();
        return rc;
      }
    }
  }

  return RC::SUCCESS;

}

RC UpdatePhysicalOperator::next() { return RC::RECORD_EOF; }

RC UpdatePhysicalOperator::close() { return RC::SUCCESS; }

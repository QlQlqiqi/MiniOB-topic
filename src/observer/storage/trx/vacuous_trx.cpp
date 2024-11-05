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
// Created by Wangyunlai on 2023/4/24.
//

#include "storage/trx/vacuous_trx.h"

RC VacuousTrxKit::init() { return RC::SUCCESS; }

const vector<FieldMeta> *VacuousTrxKit::trx_fields() const { return nullptr; }

Trx *VacuousTrxKit::create_trx(LogHandler &) { return new VacuousTrx; }

Trx *VacuousTrxKit::create_trx(LogHandler &, int32_t /*trx_id*/) { return nullptr; }

void VacuousTrxKit::destroy_trx(Trx *trx) { delete trx; }

Trx *VacuousTrxKit::find_trx(int32_t /* trx_id */) { return nullptr; }

void VacuousTrxKit::all_trxes(vector<Trx *> &trxes) { return; }

LogReplayer *VacuousTrxKit::create_log_replayer(Db &, LogHandler &) { return new VacuousTrxLogReplayer; }

////////////////////////////////////////////////////////////////////////////////

RC VacuousTrx::insert_record(Table *table, Record &record) { return table->insert_record(record); }

RC VacuousTrx::delete_record(Table *table, Record &record) { return table->delete_record(record); }

RC VacuousTrx::update_record(Table *table, Record &old_record, Record &new_record)
{
  RC rc = table->delete_record(old_record);
  if (OB_FAIL(rc)) {
    LOG_WARN("failed to delete old record.");
    return rc;
  }
  Record tmp1 = old_record;
  tmp1.copy_data(old_record.data(), old_record.len());

  rc = table->insert_record(new_record);
  if (OB_FAIL(rc)) {
    RC rc2 = table->insert_record(tmp1);
    LOG_WARN("failed to insert new record, will rollback.");
    if (OB_FAIL(rc2)) {
      LOG_ERROR("failed to insert old record back, yet it has been removed by a failed update.");
      return rc2;
    }
    return rc;
  }
  return rc;
}

RC VacuousTrx::visit_record(Table *table, Record &record, ReadWriteMode) { return RC::SUCCESS; }

RC VacuousTrx::start_if_need() { return RC::SUCCESS; }

RC VacuousTrx::commit() { return RC::SUCCESS; }

RC VacuousTrx::rollback() { return RC::SUCCESS; }

RC VacuousTrx::redo(Db *, const LogEntry &) { return RC::SUCCESS; }

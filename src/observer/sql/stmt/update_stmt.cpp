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
// Created by Wangyunlai on 2022/5/22.
//

#include "sql/stmt/update_stmt.h"
#include "common/log/log.h"
#include "storage/db/db.h"
#include "storage/table/table.h"

UpdateStmt::UpdateStmt(Table *table, const Value *values, int value_amount, const FieldMeta *field_metas,
    int field_amount, FilterStmt *stmt)
    : table_(table),
      values_(values),
      value_amount_(value_amount),
      field_metas_(field_metas),
      field_amount_(field_amount),
      filter_stmt_(stmt)
{}

UpdateStmt::~UpdateStmt()
{
  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
}

RC UpdateStmt::create(Db *db, const UpdateSqlNode &update, Stmt *&stmt)
{
  const char *table_name = update.relation_name.c_str();
  if (nullptr == db || nullptr == table_name) {
    LOG_WARN("invalid argument. db=%p, table_name=%p",
        db, table_name);
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  // check the schema
  const TableMeta              &table_meta    = table->table_meta();
  const std::vector<FieldMeta> *field_metas   = table_meta.field_metas();
  const FieldMeta              *to_be_updated = nullptr;
  for (auto &field_meta : *field_metas) {
    if (strcmp(field_meta.name(), update.attribute_name.c_str()) == 0) {
      if (auto ftype = field_meta.type(), vtype = update.value.attr_type(); ftype != vtype) {
        if (!(vtype == AttrType::NULLS && field_meta.nullable()))
        {
          LOG_WARN("schema mismatch. field type: %d, value type: %d", static_cast<int>(ftype), static_cast<int>(vtype));
          return RC::SCHEMA_FIELD_TYPE_MISMATCH;
        }
      }
      // Only single update supported for now.
      to_be_updated = &field_meta;
      break;
    }
  }

  // filter
  std::unordered_map<std::string, Table *> table_map;
  table_map.insert(std::pair<std::string, Table *>(std::string(table_name), table));

  FilterStmt *filter_stmt = nullptr;

  RC rc = FilterStmt::create(db, table, &table_map, update.conditions, filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create filter statement. rc=%d:%s", rc, strrc(rc));
    return rc;
  }
  
  // bind exprs in filter statement
  Stmt::bind_filter_stmt(db, {update.relation_name}, filter_stmt);

  // everything alright
  stmt = new UpdateStmt(table, &update.value, 1, to_be_updated, 1, filter_stmt);
  return RC::SUCCESS;
}

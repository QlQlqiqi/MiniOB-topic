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

UpdateStmt::UpdateStmt(Table *table, Value *values, int value_amount)
    : table_(table), values_(values), value_amount_(value_amount)
{}

RC UpdateStmt::create(Db *db, const UpdateSqlNode &update, Stmt *&stmt)
{
  const char* table_name = update.relation_name.c_str();
  if (nullptr == db || nullptr == table_name) {
    LOG_WARN("invalid argument. db=%p, table_name=%p",
        db, table_name);
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  Table* table = db->find_table(table_name);
  if (nullptr == table)
  {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  // check the schema
  const TableMeta&              table_meta  = table->table_meta();
  const std::vector<FieldMeta>* field_metas = table_meta.field_metas();
  for (auto& field_meta : *field_metas)
  {
    if (strcmp(field_meta.name(), update.attribute_name.c_str()) == 0)
    {
      if (auto ftype = field_meta.type(), vtype = update.value.attr_type(); ftype != vtype)
      {
        LOG_WARN("schema mismatch. field type: %d, value type: %d", static_cast<int>(ftype), static_cast<int>(vtype));
        return RC::SCHEMA_FIELD_TYPE_MISMATCH;
      }
    }
  }

  // everything alright
  stmt = new UpdateStmt(table, &update.value, 1);
  return RC::SUCCESS;
}

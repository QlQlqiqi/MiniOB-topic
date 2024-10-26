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

UpdateStmt::UpdateStmt(Table *table, std::vector<std::pair<FieldMeta, std::unique_ptr<Expression>>> values, FilterStmt *stmt)
    : table_(table),
      filter_stmt_(stmt),
      values_(std::move(values))
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
  if (nullptr == db || nullptr == table_name)
  {
    LOG_WARN("invalid argument. db=%p, table_name=%p",
        db, table_name);
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  Table *table = db->find_table(table_name);
  if (nullptr == table)
  {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  // find out the fields, and check the schema
  const TableMeta              &table_meta    = table->table_meta();
  const std::vector<FieldMeta> *field_metas   = table_meta.field_metas();

  std::unordered_map<std::string, const FieldMeta *> field_name_map;
  for (auto& field_meta : *field_metas)
  {
    field_name_map.insert({ field_meta.name(), &field_meta });
  }

  std::vector<std::pair<FieldMeta, std::unique_ptr<Expression>>> to_be_updated{};

  ASSERT(update.value.size() == update.attribute_name.size(), "");
  for (size_t i = 0; i < update.value.size(); ++i)
  {
    auto name = update.attribute_name[i];
    if (!field_name_map.contains(name) || name.empty()) {
      LOG_WARN("failed to create filter statement. attr=%s", name.c_str());
      return RC::INVALID_ARGUMENT;
    }

    auto &field_meta = *(field_name_map.find(name)->second);
    auto  value      = update.value[i];

    if (auto ftype = field_meta.type(), vtype = value->value_type(); ftype != vtype) {
      if (!(vtype == AttrType::NULLS && field_meta.nullable()))
      {
        LOG_WARN("schema mismatch. field type: %d, value type: %d", static_cast<int>(ftype), static_cast<int>(vtype));
        return RC::SCHEMA_FIELD_TYPE_MISMATCH;
      }
    }

    to_be_updated.emplace_back(std::make_pair(field_meta, std::unique_ptr<Expression>(value)));
  }

  // filter
  std::unordered_map<std::string, Table *> table_map;
  table_map.insert(std::pair<std::string, Table *>(std::string(table_name), table));

  FilterStmt *filter_stmt = nullptr;

  RC rc = FilterStmt::create(db, table, &table_map, update.conditions, filter_stmt);
  if (rc != RC::SUCCESS)
  {
    LOG_WARN("failed to create filter statement. rc=%d:%s", rc, strrc(rc));
    return rc;
  }
  
  // everything alright
  stmt = new UpdateStmt(table, std::move(to_be_updated), filter_stmt);
  return RC::SUCCESS;
}

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
// Created by Wangyunlai.wyl on 2021/5/18.
//

#include "storage/index/index_meta.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "storage/field/field_meta.h"
#include "storage/table/table_meta.h"
#include "json/json.h"
#include <sstream>

const static Json::StaticString FIELD_NAME("name");
const static Json::StaticString FIELD_UNIQUE("unique");
const static Json::StaticString FIELD_FIELD_NUM("field_num");
const static Json::StaticString FIELD_FIELD_NAME("field_name");
const static Json::StaticString WITH_FUNC_TYPE("with_func_type");
const static Json::StaticString WITH_TYPE("with_type");
const static Json::StaticString WITH_LISTS("with_lists");
const static Json::StaticString WITH_PROBES("with_probes");

RC IndexMeta::init(const char *name, const std::vector<const FieldMeta *> &fields, const bool unique,
    const std::unique_ptr<VectorIndexWith> &with)
{
  if (common::is_blank(name)) {
    LOG_ERROR("Failed to init index, name is empty.");
    return RC::INVALID_ARGUMENT;
  }

  name_ = name;
  for (const FieldMeta *field : fields) {
    field_.emplace_back(field->name());
  }
  unique_ = unique;

  if (with) {
    with_ = std::make_unique<VectorIndexWith>(*with);
  } else {
    with_ = std::make_unique<VectorIndexWith>();
  }
  return RC::SUCCESS;
}

void IndexMeta::to_json(Json::Value &json_value) const
{
  json_value[FIELD_NAME] = name_;
  json_value[FIELD_UNIQUE] = unique_;
  json_value[FIELD_FIELD_NUM] = field_.size();
  Json::Value fields;
  for (int i = 0; i < static_cast<int>(field_.size()); i++) {
    fields[i] = field_[i];
  }
  json_value[FIELD_FIELD_NAME] = std::move(fields);
  json_value[WITH_FUNC_TYPE]   = with_ ? with_->func_type : 0;
  json_value[WITH_TYPE]        = with_ ? with_->type : 0;
  json_value[WITH_LISTS]       = with_ ? with_->lists : 0;
  json_value[WITH_PROBES]      = with_ ? with_->probes : 0;
}

RC IndexMeta::from_json(const TableMeta &table, const Json::Value &json_value, IndexMeta &index)
{
  const Json::Value &name_value = json_value[FIELD_NAME];
  const Json::Value &unique = json_value[FIELD_UNIQUE];
  const Json::Value &field_num = json_value[FIELD_FIELD_NUM];
  const Json::Value &field_value = json_value[FIELD_FIELD_NAME];
  const Json::Value &func_type_value = json_value[WITH_FUNC_TYPE];
  const Json::Value &type_value = json_value[WITH_TYPE];
  const Json::Value &lists_value = json_value[WITH_LISTS];
  const Json::Value &probes_value = json_value[WITH_PROBES];
  if (!name_value.isString()) {
    LOG_ERROR("Index name is not a string. json value=%s", name_value.toStyledString().c_str());
    return RC::INTERNAL;
  }

  if (!unique.isBool()) {
    LOG_ERROR("Index unique_option is not a bool. json value=%s", unique.toStyledString().c_str());
    return RC::INTERNAL;
  }

  if (!field_num.isInt()) {
    LOG_ERROR("Field num of index [%s] is not a integer. json value=%s",
        name_value.asCString(),
        field_num.toStyledString().c_str());
        return RC::INTERNAL;
  }

  if (field_num.asInt() != static_cast<int>(field_value.size())) {
    LOG_ERROR("Field num of index [%s] is %d, not equal to field size %d",
        name_value.asCString(),
        field_num.asInt(),
        field_value.size());
        return RC::INTERNAL;
  }

  for (int i = 0; i < field_num.asInt(); i++) {
    if (!field_value[i].isString()) {
      LOG_ERROR("Field name of index [%s] is not a string. json value=%s",
          name_value.asCString(),
          field_value.toStyledString().c_str());
      return RC::INTERNAL;
    }
  }

  std::vector<const FieldMeta*> fields;
  for (int i = 0; i < static_cast<int>(field_value.size()); i++) {
    const FieldMeta *field = table.field(field_value[i].asCString());
    if (nullptr == field) {
      LOG_ERROR("Deserialize index [%s]: no such field: %s", name_value.asCString(), field_value.asCString());
      return RC::SCHEMA_FIELD_MISSING;
    }
    fields.emplace_back(field);
  }

  if (!func_type_value.isInt() && !type_value.isInt() && !lists_value.isInt() && !probes_value.isInt()) {
    LOG_ERROR("with must be integer.");
    return RC::INTERNAL;
  }

  auto with       = std::make_unique<VectorIndexWith>();
  with->func_type = func_type_value.asInt();
  with->type      = type_value.asInt();
  with->lists     = lists_value.asInt();
  with->probes    = probes_value.asInt();

  return index.init(name_value.asCString(), fields, unique.asBool(), with);
}

const char *IndexMeta::name() const { return name_.c_str(); }

const std::vector<std::string> &IndexMeta::field() const
{
  return field_;
}

const bool IndexMeta::unique() const { return unique_; }

std::string IndexMeta::to_string() const
{
  std::stringstream s;
  std::string       fields;
  for (const std::string &field : field_) {
    fields += field;
    fields += " ";
  }
  s << "index name=" << name_ << "unique" << unique_ << ", field=" << fields;
  if (with_) {
    s << "func type=" << with_->func_type << "type=" << with_->type << "lists=" << with_->lists
      << "probes=" << with_->probes;
  }
  return s.str();
}

void IndexMeta::desc(std::ostream &os) const
{
  os << to_string();
}

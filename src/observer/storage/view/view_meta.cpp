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
// Created by Meiyi & Wangyunlai on 2021/5/12.
//

#include "common/lang/string.h"
#include "common/lang/algorithm.h"
#include "common/log/log.h"
#include "common/global_context.h"
#include "storage/view/view_meta.h"
#include "storage/trx/trx.h"
#include "json/json.h"
#include "view_meta.h"

static const Json::StaticString FIELD_VIEW_ID("view_id");
static const Json::StaticString FIELD_VIEW_NAME("view_name");
static const Json::StaticString FIELD_FIELD_NAMES("view_field_names");
static const Json::StaticString FIELD_SELECT_SQL("select_sql");
static const Json::StaticString FIELD_INDEXES("indexes");

ViewMeta::ViewMeta(const ViewMeta &other)
    : view_id_(other.view_id_),
      view_name_(other.view_name_)
{}

void ViewMeta::swap(ViewMeta &other) noexcept
{
  view_name_.swap(other.view_name_);
}


int ViewMeta::serialize(std::ostream &os) const 
{ 
  Json::Value table_value;
  table_value[FIELD_VIEW_ID]   = view_id_;
  table_value[FIELD_VIEW_NAME] = view_name_;
  table_value[FIELD_SELECT_SQL] = select_sql_; 

  Json::Value field_names_value(Json::arrayValue);
  for (const string &field : view_field_names_) {
    field_names_value.append(field);
  }
  table_value[FIELD_FIELD_NAMES] = std::move(field_names_value);

  Json::StreamWriterBuilder builder;
  Json::StreamWriter       *writer = builder.newStreamWriter();

  std::streampos old_pos = os.tellp();
  writer->write(table_value, &os);
  int ret = (int)(os.tellp() - old_pos);

  delete writer;
  return ret;
}

int ViewMeta::deserialize(std::istream &is)
{
  Json::Value             view_value;
  Json::CharReaderBuilder builder;
  std::string             errors;

  std::streampos old_pos = is.tellg();
  if (!Json::parseFromStream(builder, is, &view_value, &errors)) {
    LOG_ERROR("Failed to deserialize table meta. error=%s", errors.c_str());
    return -1;
  }

  const Json::Value &view_id_value = view_value[FIELD_VIEW_ID];
  if (!view_id_value.isInt()) {
    LOG_ERROR("Invalid table id. json value=%s", view_id_value.toStyledString().c_str());
    return -1;
  }
  int32_t view_id = view_id_value.asInt();

  const Json::Value &view_name_value = view_value[FIELD_VIEW_NAME];
  if (!view_name_value.isString()) {
    LOG_ERROR("Invalid table name. json value=%s", view_name_value.toStyledString().c_str());
    return -1;
  }
  std::string view_name = view_name_value.asString();

  const Json::Value &field_name_values = view_value[FIELD_FIELD_NAMES];
  if (!field_name_values.isArray() || field_name_values.size() <= 0) {
    LOG_ERROR("Invalid table meta. fields is not array, json value=%s", field_name_values.toStyledString().c_str());
    return -1;
  }
  int field_num = field_name_values.size();
  std::vector<std::string> field_names(field_num);
  for (int i = 0; i < field_num; i++) {
    std::string &field_name = field_names[i];
    ASSERT(field_name_values[i].isString(), "Invalid field name. json value=%s", field_name_values.toStyledString().c_str());
    field_name = field_name_values[i].asString();
  }

  const Json::Value &select_sql_value = view_value[FIELD_SELECT_SQL];
  if (!select_sql_value.isString()) {
    LOG_ERROR("Invalid storage format. json value=%s", select_sql_value.toStyledString().c_str());
    return -1;
  }
  std::string select_sql = select_sql_value.asString();
  ASSERT(!select_sql.empty(), "select sql is empty. json value=%s", select_sql.c_str());

  view_id_ = view_id;
  view_name_.swap(view_name);
  view_field_names_.swap(field_names);
  select_sql_ = std::move(select_sql);

  return (int)(is.tellg() - old_pos);
}

int ViewMeta::get_serial_size() const { return 0; }

void ViewMeta::to_string(std::string &output) const {}

RC ViewMeta::init(
    int32_t view_id, const char *view_name, const std::vector<std::string> *view_fields_names, const std::string &select_sql)
{
  this->view_id_ = view_id;
  this->view_name_ = view_name;
  this->view_field_names_ = *view_fields_names;
  this->select_sql_ = select_sql;
  return RC::SUCCESS;
}

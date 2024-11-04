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

#pragma once

#include "common/rc.h"
#include "common/lang/string.h"
#include "sql/parser/parse_defs.h"

namespace Json {
class Value;
}  // namespace Json

/**
 * @brief 字段元数据
 *
 */
class FieldMeta
{
public:
  FieldMeta();
  FieldMeta(const char *name, AttrType attr_type, int attr_offset, int attr_len, bool visible, int field_id,
      bool attr_nullable = true, bool high_vector = false, int dim = 0);
  ~FieldMeta() = default;

  RC init(const char *name, AttrType attr_type, int attr_offset, int attr_len, bool visible, int field_id,
      bool attr_nullable = true, bool high_vector = false, int dim = 0);

public:
  const char *name() const;
  AttrType    type() const;
  int         offset() const;
  int         len() const;
  bool        visible() const;
  int         field_id() const;
  bool is_vector() const;
  bool        nullable() const;
  bool        high_vector() const;
  int         dim() const;

  void set_name(const string& new_name);

public:
  void desc(ostream &os) const;

public:
  void      to_json(Json::Value &json_value) const;
  static RC from_json(const Json::Value &json_value, FieldMeta &field);
protected:
  string   name_;
  AttrType attr_type_;
  int      attr_offset_;
  int      attr_len_;
  bool     visible_;
  int      field_id_;
  bool     attr_nullable_;
  // 对于高维 vector，record 中只存储 offset 和 length，
  // 类似 text，将具体内容存储在 text 溢出页中
  bool high_vector_;
  // vector 的维度数量
  int dim_;
};

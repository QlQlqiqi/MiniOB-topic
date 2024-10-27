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
// Created by Wangyunlai on 2021/5/12.
//

#pragma once

#include <string>
#include <vector>
#include <span>

#include "common/lang/serializable.h"
#include "common/rc.h"
#include "common/types.h"
#include "storage/field/field_meta.h"
#include "storage/index/index_meta.h"

/**
 * @brief 表元数据
 *
 */
class ViewMeta : public common::Serializable
{
public:
  ViewMeta()          = default;
  virtual ~ViewMeta() = default;
  ViewMeta(const ViewMeta &other);

  void swap(ViewMeta &other) noexcept;

public:
  int  serialize(std::ostream &os) const override;
  int  deserialize(std::istream &is) override;
  int  get_serial_size() const override;
  void to_string(std::string &output) const override;


public:
  RC init(int32_t view_id, const char *view_name, const std::vector<std::string> *view_field_names, const std::string& sql);
      


public:
  int32_t                         view_id() const { return view_id_; }
  const char                     *name() const { return view_name_.c_str(); }
  const std::string&              select_sql()const { return select_sql_; }
  const std::vector<std::string> &view_field_names()const{return view_field_names_;}

protected:
  int32_t                  view_id_ = -1;
  std::string              view_name_;
  std::vector<std::string> view_field_names_;
  std::string select_sql_;

private:
  bool updatable_;
  bool insertable_;
  bool deletable_;
  bool has_aggregation_;
};

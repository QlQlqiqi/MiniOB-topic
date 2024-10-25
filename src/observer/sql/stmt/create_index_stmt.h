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
// Created by Wangyunlai on 2023/4/25.
//

#pragma once

#include <string>

#include "common/log/log.h"
#include "sql/stmt/stmt.h"

struct CreateIndexSqlNode;
class Table;
class FieldMeta;

/**
 * @brief 创建索引的语句
 * @ingroup Statement
 */
class CreateIndexStmt : public Stmt
{
public:
  CreateIndexStmt(Table *table, const FieldMeta *field_meta, const std::string &index_name, const bool unique)
      : table_(table), field_meta_(field_meta), index_name_(index_name), unique_(unique)
  {}

  CreateIndexStmt(
      Table *table, std::vector<const FieldMeta *> field_metas, const std::string &index_name, const bool unique)
      : table_(table), field_metas_(field_metas), index_name_(index_name), unique_(unique)
  {
    // TODO(qiqi): 为了测试，这里只是使用一个 field meta
    ASSERT(field_metas_.size() == 1, "it is test now");
    field_meta_ = field_metas_[0];
  }

  virtual ~CreateIndexStmt() = default;

  StmtType type() const override { return StmtType::CREATE_INDEX; }

  Table             *table() const { return table_; }
  const FieldMeta   *field_meta() const { return field_meta_; }
  const std::vector<const FieldMeta *> field_metas() const { return field_metas_; }
  const std::string &index_name() const { return index_name_; }
  bool unique() const { return unique_; }

public:
  static RC create(Db *db, const CreateIndexSqlNode &create_index, Stmt *&stmt);

private:
  Table           *table_      = nullptr;
  const FieldMeta *field_meta_ = nullptr;
  std::vector<const FieldMeta *> field_metas_;
  std::string      index_name_;
  bool unique_;
};

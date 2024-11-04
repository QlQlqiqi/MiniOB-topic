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
  CreateIndexStmt(Table *table, std::vector<const FieldMeta *> &field_meta, const std::string &index_name,
      const bool unique, const std::unique_ptr<VectorIndexWith> &with = nullptr)
      : table_(table), field_meta_(field_meta), index_name_(index_name), unique_(unique)
  {
    with_ = nullptr;
    if (with) {
      // gram.y 中固化了 type 为 1
      ASSERT(with->type == 1, "type must be 1 when creating ivfflat index");
      with_ = std::make_unique<VectorIndexWith>(*with);
    }
  }

  virtual ~CreateIndexStmt() = default;

  StmtType type() const override { return StmtType::CREATE_INDEX; }

  Table             *table() const { return table_; }
  const std::vector<const FieldMeta *> &field_meta() const { return field_meta_; }
  const std::string &index_name() const { return index_name_; }
  bool unique() const { return unique_; }
  bool is_ivfflat() const { return with_ != nullptr && with_->type == 1; }
  const std::unique_ptr<VectorIndexWith> &with() const { return with_; }

public:
  static RC create(Db *db, const CreateIndexSqlNode &create_index, Stmt *&stmt);

private:
  Table           *table_      = nullptr;
  std::vector<const FieldMeta*> field_meta_;
  std::string      index_name_;
  bool unique_;
  std::unique_ptr<VectorIndexWith> with_;
};

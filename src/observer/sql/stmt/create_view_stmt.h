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
// Created by Wangyunlai on 2023/6/13.
//

#pragma once

#include <string>
#include <vector>

#include "sql/stmt/stmt.h"
#include "select_stmt.h"

class Db;

/**
 * @brief 表示创建表的语句
 * @ingroup Statement
 * @details 虽然解析成了stmt，但是与原始的SQL解析后的数据也差不多
 */
class CreateViewStmt : public Stmt
{
public:
  CreateViewStmt(const std::string &view_name, const std::vector<std::string> &attr_ids,
      std::unique_ptr<SelectStmt> &&select_stmt, const std::string &select_sql)
      : view_name_(view_name),
        attr_ids_(std::move(attr_ids)),
        select_stmt_(std::move(select_stmt)),
        select_sql_(select_sql)
  {}
  virtual ~CreateViewStmt() = default;

  StmtType type() const override { return StmtType::CREATE_VIEW; }

  const std::string                 &view_name() const { return view_name_; }
  const std::vector<std::string>    &attr_ids() const { return attr_ids_; }
  const std::vector<AttrInfoSqlNode> &attr_infos() const { return attr_infos_; }
  const std::vector<std::unique_ptr<Field>>      &origin_fields() const { return origin_fields_; }
  const std::unique_ptr<SelectStmt> &select_stmt() const { return select_stmt_; }
  std::unique_ptr<SelectStmt>       &select_stmt() { return select_stmt_; }
  const std::string                 &select_sql() const { return select_sql_; }

  std::vector<std::unique_ptr<Field>>      &origin_fields(){ return origin_fields_; }

  static RC create(Db *db, const CreateViewSqlNode &create_view, Stmt *&stmt);

private:
  std::string                 view_name_;
  std::vector<std::string>    attr_ids_;
  std::unique_ptr<SelectStmt> select_stmt_;
  std::vector<AttrInfoSqlNode> attr_infos_;
  std::vector<std::unique_ptr<Field>>         origin_fields_;
  std::string                 select_sql_;

  bool is_insertable_;
  bool is_updateable_;
};
/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
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

#include "storage/view/view_meta.h"
#include "common/types.h"
#include "common/lang/span.h"
#include "common/lang/functional.h"
#include "sql/stmt/select_stmt.h"

struct RID;
class Record;
class DiskBufferPool;
class RecordFileHandler;
class RecordFileScanner;
class ChunkFileScanner;
class ConditionFilter;
class DefaultConditionFilter;
class Index;
class IndexScanner;
class RecordDeleter;
class Trx;
class Db;
class SelectStmt;

/**
 * @brief 表
 *
 */
class View
{
public:
  View() = default;
  ~View();

  RC create(Db *db, int32_t view_id, const char *view_name, const char *view_file_path, const char *base_dir,
      std::unique_ptr<SelectStmt> &&select, const std::vector<std::string> &attr_ids, const std::string &select_sql);
  RC open(Db *db, const char *meta_file, const char *base_dir);
  RC open_without_parse(const char *meta_file, const char *base_dir);

public:
  std::string                        name() { return view_meta_.name(); }
  int32_t                            view_id() const { return view_meta_.view_id(); }
  const std::unique_ptr<SelectStmt> &select() { return select_stmt_; }
  const ViewMeta                    &view_meta() { return view_meta_; }

private:
  Db                         *db_ = nullptr;
  string                      view_name_;
  string                      base_dir_;
  ViewMeta                    view_meta_;
  std::unique_ptr<SelectStmt> select_stmt_;
};

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
#include "sql/operator/logical_operator.h"

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
class CreateViewStmt;

/**
 * @brief 表
 *
 */
class View : public Table
{
public:
  View() = default;
  virtual ~View();

  RC create(Db *db, int32_t view_id, const char *view_name, const char *base_dir,
      CreateViewStmt *create_view_stmt);
  RC open(Db *db, const char *view_meta_file, const char* view_table_meta_file,  const char *base_dir);
  RC drop(const char *path, const char *name, const char *base_dir) override;

public:
  const char*                        name() const{ return view_meta_.view_name(); }
  int32_t                            view_id() const { return view_meta_.view_id(); }
  const std::unique_ptr<SelectStmt> &select_stmt() const{ return select_stmt_; }
  const ViewMeta                    &view_meta() const{ return view_meta_; }
  const TableMeta                   &table_meta() const{return table_meta_;}
  virtual TableType                  type() const { return TableType::VIEW; }
  // void init_table_meta();
  std::unique_ptr<SelectStmt> &select_stmt() { return select_stmt_; }

  RC                        generate_select_stmt();


private:
  RC open(Db *db, const char *meta_file, const char *base_dir) override {return RC::UNIMPLEMENTED;}
  ViewMeta                    view_meta_;
  std::unique_ptr<SelectStmt>      select_stmt_;
  std::vector<std::unique_ptr<Field>> origin_fields_;

};

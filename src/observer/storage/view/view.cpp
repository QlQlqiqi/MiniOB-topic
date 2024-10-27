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
// Created by Meiyi & Wangyunlai on 2021/5/13.
//

#include <limits.h>
#include <string.h>

#include "common/defs.h"
#include "common/lang/string.h"
#include "common/lang/span.h"
#include "common/lang/algorithm.h"
#include "common/log/log.h"
#include "common/global_context.h"
#include "storage/db/db.h"
#include "storage/buffer/disk_buffer_pool.h"
#include "storage/common/condition_filter.h"
#include "storage/common/meta_util.h"
#include "storage/index/bplus_tree_index.h"
#include "storage/index/index.h"
#include "storage/record/record_manager.h"
#include "storage/view/view.h"
#include "storage/trx/trx.h"
#include "sql/expr/expression.h"
#include "view.h"

View::~View() {}

RC View::create(Db *db, int32_t view_id, const char *view_name, const char *view_file_path, const char *base_dir,
    std::unique_ptr<SelectStmt> &&select, const std::vector<std::string> &attr_ids, const std::string &select_sql)
{
  this->view_name_   = view_name;
  this->select_stmt_ = std::move(select);
  if (view_id < 0) {
    LOG_WARN("invalid view id. view_id=%d, view_name=%s", view_id, view_name);
    return RC::INVALID_ARGUMENT;
  }

  if (common::is_blank(view_name)) {
    LOG_WARN("view cannot be empty");
    return RC::INVALID_ARGUMENT;
  }
  LOG_INFO("Begin to create view:%s", view_name);

  std::vector<std::string> view_field_names(attr_ids);
  if (!attr_ids.empty()) {
    if (attr_ids.size() != select_stmt_->query_expressions().size()) {
      LOG_WARN("Invalid arguments.the view attr ids size is not equal to the select attr size.");
      return RC::INVALID_ARGUMENT;
    }
    view_field_names = attr_ids;
  } else {
    for (size_t i = 0; i < select_stmt_->query_expressions().size(); i++) {
      view_field_names.push_back((select_stmt_->query_expressions())[i]->name());
    }
  }

  ASSERT(attr_ids.empty() || view_field_names.size() == select_stmt_->query_expressions().size(),
        "Invalid arguments. the view attr ids size is not equal to the select attr size.");

  RC rc = RC::SUCCESS;

  // 使用 view_name.view记录一个表的元数据
  // 判断表文件是否已经存在
  int fd = ::open(view_file_path, O_WRONLY | O_CREAT | O_EXCL | O_CLOEXEC, 0600);
  if (fd < 0) {
    if (EEXIST == errno) {
      LOG_ERROR("Failed to create table file, it has been created. %s, EEXIST, %s", view_file_path, strerror(errno));
      return RC::SCHEMA_VIEW_EXIST;
    }
    LOG_ERROR("Create table file failed. filename=%s, errmsg=%d:%s", view_file_path, errno, strerror(errno));
    return RC::IOERR_OPEN;
  }

  close(fd);

  // 创建文件
  if ((rc = view_meta_.init(view_id, view_name, &view_field_names, select_sql)) != RC::SUCCESS) {
    LOG_ERROR("Failed to init table meta. name:%s, ret:%d", view_name, rc);
    return rc;  // delete table file
  }

  fstream fs;
  fs.open(view_file_path, ios_base::out | ios_base::binary);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open file for write.view file name=%s, errmsg=%s", view_file_path, strerror(errno));
    return RC::IOERR_OPEN;
  }

  // 记录元数据到文件中
  view_meta_.serialize(fs);
  fs.close();

  db_ = db;
  base_dir_ = base_dir;

  LOG_INFO("Successfully create view %s:%s", view_file_path, view_name);
  return rc;

  return RC();
}

RC View::open(Db *db, const char *meta_file, const char *base_dir)
{
  // 加载元数据文件
  fstream fs;
  string  meta_file_path = string(base_dir) + common::FILE_PATH_SPLIT_STR + meta_file;
  fs.open(meta_file_path, ios_base::in | ios_base::binary);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open meta file for read. file name=%s, errmsg=%s", meta_file_path.c_str(), strerror(errno));
    return RC::IOERR_OPEN;
  }
  if (view_meta_.deserialize(fs) < 0) {
    LOG_ERROR("Failed to deserialize table meta. file name=%s", meta_file_path.c_str());
    fs.close();
    return RC::INTERNAL;
  }
  fs.close();

  db_       = db;
  base_dir_ = base_dir;

  //通过 sql语句加载 select_stmt
  ParsedSqlResult sql_result;
  RC rc = RC::SUCCESS;
  const std::string& sql = view_meta_.select_sql();
  ASSERT(!sql.empty(), "select sql is empty. json value=%s", sql.c_str());
  rc = parse(sql.c_str(), &sql_result);
  if(rc != RC::SUCCESS){
    LOG_ERROR("Failed to parse sql. sql=%s, rc=%s", sql.c_str(), strrc(rc));
    return rc;
  }
  if (sql_result.sql_nodes().size() != 1){
    LOG_ERROR("sql node count should be one. sql=%s", sql.c_str());
    return RC::INTERNAL;
  }
  Stmt* stmt;
  rc = Stmt::create_stmt(db_, *sql_result.sql_nodes()[0], stmt);
  if(rc != RC::SUCCESS){
    LOG_ERROR("Failed to resolve sql. sql=%s, rc=%s", sql.c_str(), strrc(rc));
    return rc;
  }
  if(stmt->type() != StmtType::SELECT){
    LOG_ERROR("stmt type should be select. sql=%s", sql.c_str());
    return RC::INTERNAL; 
  } 
  select_stmt_.reset(static_cast<SelectStmt*>(stmt));
  return RC::SUCCESS;
}

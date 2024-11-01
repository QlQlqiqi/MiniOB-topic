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
#include "sql/stmt/create_view_stmt.h"
#include "sql/optimizer/logical_plan_generator.h"
#include "sql/optimizer/physical_plan_generator.h"
#include "view.h"

View::~View() {}

RC View::create(Db *db, int32_t view_id, const char *view_name, const char *base_dir,
    CreateViewStmt *create_view_stmt)

{
  string view_file_path = view_meta_file(base_dir, view_name);
  string view_table_meta_file_path = view_table_meta_file(base_dir, view_name);

  auto  select_stmt     = std::move(create_view_stmt->select_stmt());
  auto  attr_ids   = create_view_stmt->attr_ids();
  auto &select_sql = create_view_stmt->select_sql();
  auto &attr_infos = create_view_stmt->attr_infos();

  if (view_id < 0) {
    LOG_WARN("invalid view id. view_id=%d, view_name=%s", view_id, view_name);
    return RC::INVALID_ARGUMENT;
  }

  if (common::is_blank(view_name)) {
    LOG_WARN("view cannot be empty");
    return RC::INVALID_ARGUMENT;
  }
  LOG_INFO("Begin to create view:%s", view_name);


  //origin_fields
  this->origin_fields_.swap(create_view_stmt->origin_fields());
  
  //view_fields_names
  std::vector<std::string> view_field_names(attr_ids);
  if (!attr_ids.empty()) {
    if (attr_ids.size() != select_stmt->query_expressions().size()) {
      LOG_WARN("Invalid arguments.the view attr ids size is not equal to the select attr size.");
      return RC::INVALID_ARGUMENT;
    }
    view_field_names = attr_ids;
  } else {
    for (size_t i = 0; i < select_stmt->query_expressions().size(); i++) {
      view_field_names.push_back((select_stmt->query_expressions())[i]->name());
    }
  }
  ASSERT(attr_ids.empty() || view_field_names.size() == select_stmt->query_expressions().size(),
        "Invalid arguments. the view attr ids size is not equal to the select attr size.");
  RC rc = RC::SUCCESS;

  // 使用 view_name.view记录一个表的元数据
  // 判断表文件是否已经存在
  int fd = ::open(view_file_path.c_str(), O_WRONLY | O_CREAT | O_EXCL | O_CLOEXEC, 0600);
  if (fd < 0) {
    if (EEXIST == errno) {
      LOG_ERROR("Failed to create table file, it has been created. %s, EEXIST, %s", view_file_path, strerror(errno));
      return RC::SCHEMA_VIEW_EXIST;
    }
    LOG_ERROR("Create table file failed. filename=%s, errmsg=%d:%s", view_file_path, errno, strerror(errno));
    return RC::IOERR_OPEN;
  }
  close(fd);

  // init view_meta
  if ((rc = view_meta_.init(view_id, view_name, &view_field_names, select_stmt, select_sql)) != RC::SUCCESS) {
    LOG_ERROR("Failed to init view meta. name:%s, ret:%d", view_name, rc);
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

  //init table_meta
  fs.open(view_table_meta_file_path, ios_base::out | ios_base::binary);
  if((rc = this->table_meta_.init(view_id, view_name, attr_infos)) != RC::SUCCESS){
    LOG_ERROR("Failed to init table meta. name:%s, ret:%d", view_name, rc);
    return rc;  // delete table file
  }
  // 记录元数据到文件中
  table_meta_.serialize(fs);
  fs.close();

  //select_physical_oper
  //注意，create 后 ，select_stmt 里面的成员变量可以无法使用，因为 std::move 的作用，所以调用之后不能使用原有的 select_stmt

  this->select_stmt_ = std::move(select_stmt);
  this->db_       = db;
  this->base_dir_ = base_dir;
  LOG_INFO("Successfully create view %s:%s", view_file_path, view_name);
  return rc;
}

RC View::open(Db *db, const char *view_meta_file, const char* view_table_meta_file,  const char *base_dir)
{
  // 加载元数据文件
  fstream fs;
  string  meta_file_path = string(base_dir) + common::FILE_PATH_SPLIT_STR + view_meta_file;
  string table_meta_file_path = string(base_dir) + common::FILE_PATH_SPLIT_STR + view_table_meta_file;

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

  fs.open(table_meta_file_path, ios_base::in | ios_base::binary);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open meta file for read. file name=%s, errmsg=%s", meta_file_path.c_str(), strerror(errno));
    return RC::IOERR_OPEN;
  }
  if (table_meta_.deserialize(fs) < 0) {
    LOG_ERROR("Failed to deserialize table meta. file name=%s", meta_file_path.c_str());
    fs.close();
    return RC::INTERNAL;
  }
  fs.close();

  db_       = db;
  base_dir_ = base_dir;

  RC              rc = RC::SUCCESS;

  if(OB_FAIL(rc = generate_select_stmt())){
    return rc;
  }

  ASSERT(this->select_stmt_ != nullptr, "the select stmt should not be null");
  std::unique_ptr<SelectStmt>& select_stmt = this->select_stmt_;
  //初始化 tale meta
  // init_table_meta();

  //通过 view_meta 和 select_stmt 加载 origin_field
  std::vector<std::unique_ptr<Field>>& origin_fields = this->origin_fields_;
  for(auto &expr : select_stmt->query_expressions()){
    Expression* expression = expr.get();
    switch(expr->type()){
      case ExprType::ARITHMETIC:
      case ExprType::COMPARISON:
      case ExprType::SUBQUERY:
      case ExprType::AGGREGATION:{
        origin_fields.push_back(nullptr);
      } break;
      case ExprType::FIELD:{
        FieldExpr * field_expr = static_cast<FieldExpr*>(expression);
        origin_fields.push_back(std::make_unique<Field>(field_expr->field()));
      } break;
      case ExprType::VALUE:{
        origin_fields.push_back(nullptr);
      } break;
      default:{
        LOG_WARN("invalid argument. expression type is not supported");
        return RC::INVALID_ARGUMENT;
      }
    }
  }

  // rc = LogicalPlanGenerator::create(stmt, select_logical_oper_);
  // if (rc != RC::SUCCESS) {
  //   LOG_ERROR("Failed to create select logical operator. rc=%s", strrc(rc));
  //   return rc;
  // }
  return RC::SUCCESS;
}

RC View::drop(const char *path, const char *name, const char *base_dir)
{
  if (common::is_blank(name)) {
    LOG_WARN("Name cannot be empty");
    return RC::INVALID_ARGUMENT;
  }

  // 这里 remove 失败可能因为权限等问题，不过目前不知道
  // 新增 RC 会不会影响测试，目前就返回现有的 RC。
  if (::remove(path) != 0) {
    LOG_ERROR("Delete view file failed. filename=%s, errmsg=%d:%s", path, errno, strerror(errno));
    return RC::FILE_NOT_EXIST;
  }
  return RC::SUCCESS;
}

RC View::generate_select_stmt() {
  //通过 sql语句加载 select_stmt
  ParsedSqlResult sql_result;
  RC              rc = RC::SUCCESS;
  // sql语句
  const std::string &sql = view_meta_.select_sql();
  ASSERT(!sql.empty(), "select sql is empty. json value=%s", sql.c_str());
  rc = parse(sql.c_str(), &sql_result);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to parse sql. sql=%s, rc=%s", sql.c_str(), strrc(rc));
    return rc;
  }
  if (sql_result.sql_nodes().size() != 1) {
    LOG_ERROR("sql node count should be one. sql=%s", sql.c_str());
    return RC::INTERNAL;
  }
  //创建select stmt 对象
  Stmt *stmt;
  rc = Stmt::create_stmt(db_, *sql_result.sql_nodes()[0], stmt);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to resolve sql. sql=%s, rc=%s", sql.c_str(), strrc(rc));
    return rc;
  }
  if (stmt->type() != StmtType::SELECT) {
    LOG_ERROR("stmt type should be select. sql=%s", sql.c_str());
    return RC::INTERNAL;
  }
  this->select_stmt_.reset(static_cast<SelectStmt*>(stmt));
  return rc;
}


// void View::init_table_meta()
// {
//   table_meta_.name_ = view_meta_.name();
//   ASSERT(select_stmt_ != nullptr,"the select stmt is nullptr");
//   auto &query_expression = select_stmt_->query_expressions();
//   ASSERT(view_meta_.view_field_names_.size() == query_expression.size(),
//       "the view field names size should be equal to the select expressions size");
//   for (size_t i = 0; i < query_expression.size(); i++) {
//     auto     &expression = query_expression[i];
//     FieldMeta field_meta;
//     if (expression->type() == ExprType::FIELD) {
//       ASSERT(expression->type() == ExprType::FIELD, "the expression type should be field");
//       auto field_expr = static_cast<FieldExpr *>(expression.get());
//       field_meta      = *field_expr->field().meta();
//       field_meta.set_name(view_meta_.view_field_names_[i]);
//       table_meta_.fields_.push_back(field_meta);
//     } else {
//       field_meta.init(view_meta_.view_field_names_[i].c_str(), expression->value_type(), -1, -1, true, false, 0);
//     }
//   }
// }

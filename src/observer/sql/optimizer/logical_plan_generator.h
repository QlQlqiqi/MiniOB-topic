/* Copyright (c) 2023 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2023/08/16.
//

#pragma once

#include <memory>

#include "common/rc.h"
#include "common/type/attr_type.h"
#include "common/types.h"

class Stmt;
class CalcStmt;
class SelectStmt;
class FilterStmt;
class InsertStmt;
class UpdateStmt;
class DeleteStmt;
class ExplainStmt;
class LimitStmt;
class CreateTableStmt;
class LogicalOperator;
class SQLStageEvent;

class LogicalPlanGenerator
{
public:
  LogicalPlanGenerator()          = default;
  virtual ~LogicalPlanGenerator() = default;

  static RC create(Stmt *stmt, std::unique_ptr<LogicalOperator> &logical_operator, SQLStageEvent *sql_event = nullptr);
  static RC create_view_scan_plan(SelectStmt *select_stmt, std::unique_ptr<LogicalOperator> &logical_operator, ReadWriteMode read_write_mode);

private:
  static RC create_plan(CalcStmt *calc_stmt, std::unique_ptr<LogicalOperator> &logical_operator);
  static RC create_plan(SelectStmt *select_stmt, std::unique_ptr<LogicalOperator> &logical_operator, ReadWriteMode read_write_mode = ReadWriteMode::READ_ONLY);
  static RC create_plan(FilterStmt *filter_stmt, std::unique_ptr<LogicalOperator> &logical_operator);
  static RC create_plan(LimitStmt *limit_stmt, std::unique_ptr<LogicalOperator> &logical_operator);
  static RC create_plan(InsertStmt *insert_stmt, std::unique_ptr<LogicalOperator> &logical_operator);
  static RC create_plan(UpdateStmt *insert_stmt, std::unique_ptr<LogicalOperator> &logical_operator);
  static RC create_plan(DeleteStmt *delete_stmt, std::unique_ptr<LogicalOperator> &logical_operator);
  static RC create_plan(ExplainStmt *explain_stmt, std::unique_ptr<LogicalOperator> &logical_operator);

  static RC create_plan_with_event(CreateTableStmt *create_table_stmt, std::unique_ptr<LogicalOperator> &logical_operator, SQLStageEvent* sql_event);
  static RC create_group_by_plan(SelectStmt *select_stmt, std::unique_ptr<LogicalOperator> &logical_operator);
  static RC create_order_by_plan(SelectStmt *select_stmt, std::unique_ptr<LogicalOperator> &logical_operator);

  static int implicit_cast_cost(AttrType from, AttrType to);
};
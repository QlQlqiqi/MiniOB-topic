//
// Created by QlQl on 2024/10/18.
//

#pragma once

#include "sql/stmt/stmt.h"

class Db;

/**
 * @brief 表示删除表的语句
 * @ingroup Statement
 * @details 虽然解析成了stmt，但是与原始的SQL解析后的数据也差不多
 */
class DropViewStmt : public Stmt
{
public:
  DropViewStmt(const std::string &view_name) : view_name_(view_name) {}
  virtual ~DropViewStmt() = default;

  StmtType type() const override { return StmtType::DROP_TABLE; }

  const std::string &view_name() const { return view_name_; }

  static RC create(Db *db, const DropViewSqlNode &drop_view, Stmt *&stmt);

private:
  std::string view_name_;
};
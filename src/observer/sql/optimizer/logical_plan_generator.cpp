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

#include "sql/optimizer/logical_plan_generator.h"

#include <common/log/log.h>

#include "logical_plan_generator.h"

#include "sql/operator/calc_logical_operator.h"
#include "sql/operator/delete_logical_operator.h"
#include "sql/operator/explain_logical_operator.h"
#include "sql/operator/insert_logical_operator.h"
#include "sql/operator/limit_logical_operator.h"
#include "sql/operator/update_logical_operator.h"
#include "sql/operator/join_logical_operator.h"
#include "sql/operator/logical_operator.h"
#include "sql/operator/predicate_logical_operator.h"
#include "sql/operator/project_logical_operator.h"
#include "sql/operator/table_get_logical_operator.h"
#include "sql/operator/view_get_logical_operator.h"
#include "sql/operator/group_by_logical_operator.h"
#include "sql/operator/order_by_logical_operator.h"


#include "sql/operator/vector_index_scan_logical_operator.h"
#include "sql/stmt/calc_stmt.h"
#include "sql/stmt/delete_stmt.h"
#include "sql/stmt/explain_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/insert_stmt.h"
#include "sql/stmt/update_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "sql/stmt/stmt.h"
#include "sql/expr/expression_iterator.h"
#include "storage/index/ivfflat_index.h"


using namespace std;
using namespace common;

RC LogicalPlanGenerator::create(Stmt *stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  RC rc = RC::SUCCESS;
  switch (stmt->type()) {
    case StmtType::CALC: {
      CalcStmt *calc_stmt = static_cast<CalcStmt *>(stmt);

      rc = create_plan(calc_stmt, logical_operator);
    } break;

    case StmtType::SELECT: {
      SelectStmt *select_stmt = static_cast<SelectStmt *>(stmt);

      rc = create_plan(select_stmt, logical_operator);
    } break;

    case StmtType::INSERT: {
      InsertStmt *insert_stmt = static_cast<InsertStmt *>(stmt);

      rc = create_plan(insert_stmt, logical_operator);
    } break;

    case StmtType::UPDATE: {
      UpdateStmt *update_stmt = static_cast<UpdateStmt *>(stmt);

      rc = create_plan(update_stmt, logical_operator);
    } break;

    case StmtType::DELETE: {
      DeleteStmt *delete_stmt = static_cast<DeleteStmt *>(stmt);

      rc = create_plan(delete_stmt, logical_operator);
    } break;

    case StmtType::EXPLAIN: {
      ExplainStmt *explain_stmt = static_cast<ExplainStmt *>(stmt);

      rc = create_plan(explain_stmt, logical_operator);
    } break;
    default: {
      rc = RC::UNIMPLEMENTED;
    }
  }
  return rc;
}

RC LogicalPlanGenerator::create_view_scan_plan(
    SelectStmt *select_stmt, std::unique_ptr<LogicalOperator> &logical_operator, ReadWriteMode read_write_mode)
{
  return create_plan(select_stmt, logical_operator, read_write_mode);
}
RC LogicalPlanGenerator::create_plan(CalcStmt *calc_stmt, std::unique_ptr<LogicalOperator> &logical_operator)
{
  logical_operator.reset(new CalcLogicalOperator(std::move(calc_stmt->expressions())));
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(SelectStmt *select_stmt, unique_ptr<LogicalOperator> &logical_operator, ReadWriteMode read_write_mode)
{
  RC rc = RC::SUCCESS;
  unique_ptr<LogicalOperator> *last_oper = nullptr;

  unique_ptr<LogicalOperator> table_oper(nullptr);

  last_oper = &table_oper;

  const std::vector<Table *> &tables = select_stmt->tables();

  //join operator
  for (Table *table : tables) {
    unique_ptr<LogicalOperator> table_get_oper = nullptr;

    switch(table->type()){
      case TableType::TABLE:{
        table_get_oper.reset(new TableGetLogicalOperator(table, read_write_mode));
      } break;
      case TableType::VIEW:{
        table_get_oper.reset(new ViewGetLogicalOperator(static_cast<View*>(table), read_write_mode));
      } break;
      default:{
        ASSERT(false, "unknown table type");
        return RC::INTERNAL;
      }
    }

    if (table_oper == nullptr) {
      table_oper = std::move(table_get_oper);
    } else {
      unique_ptr<LogicalOperator> predicate_oper;
      unique_ptr<JoinLogicalOperator> join_oper = std::make_unique<JoinLogicalOperator>();
      if(select_stmt->join_conditions().size() != 0 && select_stmt->join_conditions().count(table) != 0){
        FilterStmt *filter_stmt = select_stmt->join_conditions()[table].get();
        rc = create_plan(filter_stmt, predicate_oper);
        if (rc != RC::SUCCESS) {
          return rc;
        }
      }
      join_oper->add_child(std::move(table_oper));
      if (predicate_oper) {
        join_oper->add_child(std::move(table_get_oper));
        predicate_oper->add_child(std::move(join_oper));
        table_oper = std::move(predicate_oper);

      } else {
        join_oper->add_child(std::move(table_get_oper));
        table_oper = std::move(join_oper);
      }
    }
  }

  // limit clause
  std::unique_ptr<LogicalOperator> limit_oper;
  if (select_stmt->limit()) {
    rc = create_plan(select_stmt->limit().get(), limit_oper);
    if (OB_FAIL(rc)) {
      LOG_WARN("failed to create limit logical plan. rc=%s", strrc(rc));
      return rc;
    }
  }

  unique_ptr<LogicalOperator> order_by_oper;
  rc = create_order_by_plan(select_stmt, order_by_oper);
  if (OB_FAIL(rc)) {
    LOG_WARN("failed to create group by logical plan. rc=%s", strrc(rc));
    return rc;
  }

  // 对于向量索引，需要使用 ivafflat 将其重写，详细可参考
  // @see: { https://oceanbase.github.io/miniob/game/miniob-vectordb/#_7 }
  bool rewrited = false;
  std::unique_ptr<VectorIndexScanLogicalOperator> vec_index_scan_oper;
  // 1. 有 limit 和 order by
  if (limit_oper && order_by_oper) {
    // 2. order by expr 只有 1 哥，且为 vector_func
    auto &order_by_exprs = order_by_oper->expressions();
    if (order_by_exprs.size() == 1 && order_by_exprs[0]->type() == ExprType::FUNCTION) {
      auto order_by_expr = static_cast<FunctionExpr *>(order_by_exprs[0].get());
      // 3. order by 的左右 expr 一个是 field，一个是 vector
      auto &left  = order_by_expr->left();
      auto &right = order_by_expr->right();
      if (left && right &&
          ((left->type() == ExprType::FIELD && right->type() == ExprType::VALUE) ||
              (left->type() == ExprType::VALUE && right->type() == ExprType::FIELD))) {
        // 4. 在这个 field 上有对应的 ivafflat index
        auto field_name =
            static_cast<FieldExpr *>(left->type() == ExprType::FIELD ? left.get() : right.get())->field_name();
        for (auto table : tables) {
          for (auto index : table->indexes()) {
            auto &index_meta = index->index_meta();
            if (index_meta.is_ivfflat() && index_meta.field().size() == 1 && index_meta.field().at(0) == field_name) {
              auto ivafflat_index = dynamic_cast<const IvfflatIndex *>(index);
              if (ivafflat_index != nullptr) {
                // 5. 将 limit、order by 改为 vector index scan
                vec_index_scan_oper = std::make_unique<VectorIndexScanLogicalOperator>(table,
                    index,
                    &index->field_metas()[0],
                    static_cast<OrderByLogicalOperator *>(order_by_oper.get())->order_ops()[0],
                    static_cast<LimitLogicalOperator *>(limit_oper.get())->num_);
                table_oper          = std::move(vec_index_scan_oper);
                rewrited = true;
                break;
              }
            }
          }
        }
      }
    }
  }

  //where operator
  unique_ptr<LogicalOperator> predicate_oper;
  rc = create_plan(select_stmt->filter_stmt(), predicate_oper);
  if (OB_FAIL(rc)) {
    LOG_WARN("failed to create predicate logical plan. rc=%s", strrc(rc));
    return rc;
  }

  if (predicate_oper) {
    if (*last_oper) {
      predicate_oper->add_child(std::move(*last_oper));
    }

    last_oper = &predicate_oper;
  }

  //group by operator
  unique_ptr<LogicalOperator> group_by_oper;
  rc = create_group_by_plan(select_stmt, group_by_oper);
  if (OB_FAIL(rc)) {
    LOG_WARN("failed to create group by logical plan. rc=%s", strrc(rc));
    return rc;
  }

  if (group_by_oper) {
    if (*last_oper) {
      group_by_oper->add_child(std::move(*last_oper));
    }

    last_oper = &group_by_oper;
  }

  //having operator 
  unique_ptr<LogicalOperator> having_predicate_oper;

  rc = create_plan(select_stmt->having_filter_stmt(), having_predicate_oper);
  if (OB_FAIL(rc)) {
    LOG_WARN("failed to create predicate logical plan. rc=%s", strrc(rc));
    return rc;
  }

  if (having_predicate_oper) {
    if (*last_oper) {
      having_predicate_oper->add_child(std::move(*last_oper));
    }

    last_oper = &having_predicate_oper;
  }

  if (order_by_oper && !rewrited) {
    if (*last_oper) {
      order_by_oper->add_child(std::move(*last_oper));
    }
    last_oper = &order_by_oper;
  }

  // limit clause
  if (limit_oper && !rewrited) {
    if (*last_oper) {
      limit_oper->add_child(std::move(*last_oper));
    }
    last_oper = &limit_oper;
  }

  auto project_oper = make_unique<ProjectLogicalOperator>(std::move(select_stmt->query_expressions()));
  if (*last_oper) {
    project_oper->add_child(std::move(*last_oper));
  }

  logical_operator = std::move(project_oper);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(FilterStmt *filter_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  // 原来这里会把 value 的 type 统一，这块改成不统一，
  // 并且改成使用 expr
  RC rc = RC::SUCCESS;

  auto                                &expr = filter_stmt->get_expr();
  unique_ptr<PredicateLogicalOperator> pre_oper;

  if (expr) {
    pre_oper = std::make_unique<PredicateLogicalOperator>(expr->Clone());
  }
  logical_operator = std::move(pre_oper);
  return rc;
}

RC LogicalPlanGenerator::create_plan(LimitStmt *limit_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  RC rc = RC::SUCCESS;

  auto limit_oper = std::make_unique<LimitLogicalOperator>(limit_stmt->num_);

  logical_operator = std::move(limit_oper);
  return rc;
}

int LogicalPlanGenerator::implicit_cast_cost(AttrType from, AttrType to)
{
  if (from == to) {
    return 0;
  }
  return DataType::type_instance(from)->cast_cost(to);
}

RC LogicalPlanGenerator::create_plan(InsertStmt *insert_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Table        *table = insert_stmt->table();
  vector<Value> values(insert_stmt->values(), insert_stmt->values() + insert_stmt->value_amount());

  if(table->type() == TableType::VIEW)
  {
    LOG_WARN("InsertLogicalOperator: table type is VIEW");
    View *view = static_cast<View*>(table);
    if(!view->view_meta().is_insertable()){
        LOG_WARN("this view cannot be inserted");
        return RC::UNSUPPORTED;
    }
    ASSERT(view->select_stmt()->tables().size() == 1, "view should have only one table");
    Table* origin_table = const_cast<Table*>(view->origin_fields()[0]->table());
    auto field_num = origin_table->table_meta().field_num();
    vector<Value> view_insert_values;
    view_insert_values.resize(field_num);
    for_each(view_insert_values.begin(), view_insert_values.end(), [&](Value &v){
      v.set_null();
    });
    auto &origin_fields = view->origin_fields(); 
    ASSERT(origin_fields.size() == values.size(), "values size should be equal to origin fields size");
    for(size_t i = 0; i < origin_fields.size(); i++){
      auto &field =  origin_fields[i];
      ASSERT(field != nullptr, "field should not be nullptr");
      auto field_id = field->meta()->field_id();
      view_insert_values[field_id] = values[i];
    }

    values = std::move(view_insert_values); 
    table = origin_table;
  }
  InsertLogicalOperator *insert_operator = new InsertLogicalOperator(table, values);
  logical_operator.reset(insert_operator);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(UpdateStmt *update_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Table *table  = update_stmt->table();
  auto  &values = const_cast<std::vector<std::pair<FieldMeta, std::unique_ptr<Expression>>>&>(update_stmt->values());

  FilterStmt                 *filter_stmt = update_stmt->filter_stmt();
  unique_ptr<LogicalOperator> table_get_oper;
  if(table->type() == TableType::VIEW){
    if(!static_cast<View*>(table)->view_meta().is_updateable()){
      return RC::INVALID_ARGUMENT;
    }
    table_get_oper = make_unique<ViewGetLogicalOperator>(static_cast<View*>(table), ReadWriteMode::READ_WRITE);
  }else{
    table_get_oper = make_unique<TableGetLogicalOperator>(table, ReadWriteMode::READ_WRITE);
  }

  unique_ptr<LogicalOperator> predicate_oper;

  RC rc = create_plan(filter_stmt, predicate_oper);

  if (rc != RC::SUCCESS) {
    return rc;
  }

  UpdateLogicalOperator *update_oper = new UpdateLogicalOperator(table, std::move(values));

  if (predicate_oper) {
    predicate_oper->add_child(std::move(table_get_oper));
    update_oper->add_child(std::move(predicate_oper));
  } else {
    update_oper->add_child(std::move(table_get_oper));
  }

  logical_operator.reset(update_oper);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(DeleteStmt *delete_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Table                      *table       = delete_stmt->table();
  FilterStmt                 *filter_stmt = delete_stmt->filter_stmt();
  unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, ReadWriteMode::READ_WRITE));

  unique_ptr<LogicalOperator> predicate_oper;

  RC rc = create_plan(filter_stmt, predicate_oper);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  unique_ptr<LogicalOperator> delete_oper(new DeleteLogicalOperator(table));

  if (predicate_oper) {
    predicate_oper->add_child(std::move(table_get_oper));
    delete_oper->add_child(std::move(predicate_oper));
  } else {
    delete_oper->add_child(std::move(table_get_oper));
  }

  logical_operator = std::move(delete_oper);
  return rc;
}

RC LogicalPlanGenerator::create_plan(ExplainStmt *explain_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  unique_ptr<LogicalOperator> child_oper;

  Stmt *child_stmt = explain_stmt->child();

  RC rc = create(child_stmt, child_oper);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create explain's child operator. rc=%s", strrc(rc));
    return rc;
  }

  logical_operator = unique_ptr<LogicalOperator>(new ExplainLogicalOperator);
  logical_operator->add_child(std::move(child_oper));
  return rc;
}

RC LogicalPlanGenerator::create_group_by_plan(SelectStmt *select_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  vector<unique_ptr<Expression>>             &group_by_expressions = select_stmt->group_by();
  vector<Expression *>                        aggregate_expressions;
  vector<unique_ptr<Expression>>             &query_expressions = select_stmt->query_expressions();
  auto                                       &having_filter_expression = select_stmt->having_filter_stmt()->expr();

  function<RC(std::unique_ptr<Expression> &)> collector         = [&](unique_ptr<Expression> &expr) -> RC {
    RC rc = RC::SUCCESS;
    if (expr->type() == ExprType::AGGREGATION) {
      expr->set_pos(aggregate_expressions.size() + group_by_expressions.size());
      aggregate_expressions.push_back(expr.get());
    }
    rc = ExpressionIterator::iterate_child_expr(*expr, collector);
    return rc;
  };

  function<RC(std::unique_ptr<Expression> &)> bind_group_by_expr = [&](unique_ptr<Expression> &expr) -> RC {
    RC rc = RC::SUCCESS;
    for (size_t i = 0; i < group_by_expressions.size(); i++) {
      auto &group_by = group_by_expressions[i];
      if (expr->type() == ExprType::AGGREGATION) {
        break;
      } else if (expr->equal(*group_by)) {
        expr->set_pos(i);
        continue;
      } else {
        rc = ExpressionIterator::iterate_child_expr(*expr, bind_group_by_expr);
      }
    }
    return rc;
  };

  bool                                        found_unbound_column = false;
  function<RC(std::unique_ptr<Expression> &)> find_unbound_column  = [&](unique_ptr<Expression> &expr) -> RC {
    RC rc = RC::SUCCESS;
    if (expr->type() == ExprType::AGGREGATION) {
      // do nothing
    } else if (expr->pos() != -1) {
      // do nothing
    } else if (expr->type() == ExprType::FIELD) {
      found_unbound_column = true;
    } else {
      rc = ExpressionIterator::iterate_child_expr(*expr, find_unbound_column);
    }
    return rc;
  };

  for (unique_ptr<Expression> &expression : query_expressions) {
    bind_group_by_expr(expression);
  }

  for (unique_ptr<Expression> &expression : query_expressions) {
    find_unbound_column(expression);
  }

  // collect all aggregate expressions
  for (unique_ptr<Expression> &expression : query_expressions) {
    collector(expression);
  }

  //collect having aggregate expressions
  if(having_filter_expression != nullptr){
    collector(having_filter_expression);
  }

  if (group_by_expressions.empty() && aggregate_expressions.empty()) {
    // 既没有group by也没有聚合函数，不需要group by
    return RC::SUCCESS;
  }

  if (found_unbound_column) {
    LOG_WARN("column must appear in the GROUP BY clause or must be part of an aggregate function");
    return RC::INVALID_ARGUMENT;
  }

  // 如果只需要聚合，但是没有group by 语句，需要生成一个空的group by 语句

  auto group_by_oper =
      make_unique<GroupByLogicalOperator>(std::move(group_by_expressions), std::move(aggregate_expressions));
  logical_operator = std::move(group_by_oper);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_order_by_plan(SelectStmt *select_stmt, std::unique_ptr<LogicalOperator> &logical_operator){
  auto &order_stmt = select_stmt->order_by();
  if(order_stmt == nullptr || order_stmt->order_by_ops.empty()){
    return RC::SUCCESS;
  }
  assert(order_stmt->order_by_expressions.size() == order_stmt->order_by_ops.size());
  logical_operator.reset(new OrderByLogicalOperator(std::move(order_stmt->order_by_expressions), std::move(order_stmt->order_by_ops)));
  return RC::SUCCESS;
}
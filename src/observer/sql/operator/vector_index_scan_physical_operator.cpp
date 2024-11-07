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
// Created by Wangyunlai on 2022/07/08.
//

#include "sql/operator/vector_index_scan_physical_operator.h"
#include "storage/index/index.h"
#include "storage/trx/trx.h"

RC VectorIndexScanPhysicalOperator::open(Trx *trx)
{
  if (nullptr == table_ || nullptr == index_) {
    return RC::INTERNAL;
  }

  IndexScanner *index_scanner = index_->create_scanner(nullptr, 0, true, nullptr, 0, true, field_meta_);
  if (nullptr == index_scanner) {
    LOG_WARN("failed to create index scanner");
    return RC::INTERNAL;
  }

  record_handler_ = table_->record_handler();
  if (nullptr == record_handler_) {
    LOG_WARN("invalid record handler");
    index_scanner->destroy();
    return RC::INTERNAL;
  }
  index_scanner_ = index_scanner;

  tuple_.set_schema(table_, table_->table_meta().field_metas());

  trx_ = trx;
  return RC::SUCCESS;
}

RC VectorIndexScanPhysicalOperator::next()
{
  if (limit_num_ == 0) {
    return RC::RECORD_EOF;
  }

  RC rc;
  if (idx_ == -1) {
    if ((rc = init()) != RC::SUCCESS) {
      return rc;
    }
  }
  idx_++;
  if (idx_ == static_cast<int64_t>(tuples_.size())) {
    return RC::RECORD_EOF;
  }
  limit_num_--;
  return RC::SUCCESS;
}

RC VectorIndexScanPhysicalOperator::close()
{
  index_scanner_->destroy();
  index_scanner_ = nullptr;
  return RC::SUCCESS;
}

Tuple *VectorIndexScanPhysicalOperator::current_tuple()
{
  if (idx_ < 0) {
    return nullptr;
  }
  return tuples_[idx_].get();
}

std::string VectorIndexScanPhysicalOperator::param() const
{
  return std::string(index_->index_meta().name()) + " ON " + table_->name();
}

RC VectorIndexScanPhysicalOperator::init()
{
  RC rc = read_all();
  if (rc != RC::SUCCESS) {
    return rc;
  }

  // std::sort(tuples_.begin(), tuples_.end(), [&](const std::unique_ptr<Tuple> &a, const std::unique_ptr<Tuple> &b) {
  //   Value a_val, b_val;
  //   assert(expr_->type() == ExprType::FUNCTION);
  //   Expression *expression = expr_.get();
  //   expression->get_value(*a, a_val);
  //   expression->get_value(*b, b_val);
  //   auto cmp = a_val.compare_without_cast(b_val);
  //   if (cmp == ValCmpRes::EQUAL)
  //     return false;
  //   if (cmp == ValCmpRes::LESS) {
  //     return order_op_ == OrderOp::ASC;
  //   }
  //   if (cmp == ValCmpRes::GREAT) {
  //     return order_op_ == OrderOp::DESC;
  //   }
  //   if (cmp == ValCmpRes::NULL_VAL) {
  //     // if a_val.is_null() and b_val.is_null() should continue
  //     if (a_val.is_null() && b_val.is_null()) {
  //       return false;
  //     }
  //     return order_op_ == OrderOp::ASC ? a_val.is_null() : b_val.is_null();
  //   }
  //   return false;
  // });
  return RC::SUCCESS;
}

RC VectorIndexScanPhysicalOperator::read_all()
{
  auto order_by_expr = static_cast<FunctionExpr *>(expr_.get());
  // order by 的左右 expr 一个是 field，一个是 vector
  auto &left  = order_by_expr->left();
  auto &right = order_by_expr->right();

  Value tmp;
  if (left->type() == ExprType::VALUE) {
    left->get_value(tuple_, tmp);
  } else {
    right->get_value(tuple_, tmp);
  }

  Value value;
  tmp.cast_to(tmp, AttrType::VECTORS, value);
  std::vector<double> target;
  target.resize(field_meta_->dim());
  memcpy(target.data(), value.data(), value.length());

  std::vector<RID> res;
  index_->ann_search(target, limit_num_, res);
  for (auto &rid : res) {
    Record tmp_record;
    RC     rc = record_handler_->get_record(rid, tmp_record);
    if (OB_FAIL(rc)) {
      LOG_TRACE("failed to get record. rid=%s, rc=%s", rid.to_string().c_str(), strrc(rc));
      return rc;
    }
    LOG_TRACE("got a record. rid=%s", rid.to_string().c_str());
    tuple_.set_record(&tmp_record);

    rc = trx_->visit_record(table_, tmp_record, mode_);
    if (rc == RC::RECORD_INVISIBLE) {
      LOG_TRACE("record invisible");
      continue;
    }
    tuples_.emplace_back(tuple_.clone());
  }

  return RC::SUCCESS;
}

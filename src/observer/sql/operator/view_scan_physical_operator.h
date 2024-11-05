
#pragma once

#include "common/rc.h"
#include "sql/operator/physical_operator.h"
#include "storage/record/record_manager.h"
#include "common/types.h"

class View;

/**
 * @brief 表扫描物理算子
 * @ingroup PhysicalOperator
 */
class ViewScanPhysicalOperator : public PhysicalOperator
{
public:
  ViewScanPhysicalOperator(View *view, ReadWriteMode mode) : view_(view), mode_(mode) {}

  virtual ~ViewScanPhysicalOperator() = default;

  std::string param() const override;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::VIEW_SCAN; }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override;

private:
  View                                   *view_ = nullptr;
  Trx                                     *trx_   = nullptr;
  ReadWriteMode                            mode_  = ReadWriteMode::READ_WRITE;
  RecordFileScanner                        record_scanner_;
  Record                                   current_record_;
  ViewRowTuple                             tuple_;
  std::vector<std::unique_ptr<Expression>> predicates_;  // TODO chang predicate to view tuple filter
};

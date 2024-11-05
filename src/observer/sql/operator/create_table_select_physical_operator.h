
#pragma once

#include "common/rc.h"
#include "sql/operator/physical_operator.h"
#include "storage/record/record_manager.h"
#include "common/types.h"

class Table;

/**
 * @brief 表扫描物理算子
 * @ingroup PhysicalOperator
 */
class CreateTableSelectPhysicalOperator : public PhysicalOperator
{
public:
  CreateTableSelectPhysicalOperator(Table * table) : table_(table){}

  virtual ~CreateTableSelectPhysicalOperator() = default;

  std::string param() const override;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::TABLE_CREATE_SELECT; }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override;

private:
  Table                                   *table_ = nullptr;
  Trx                                     *trx_   = nullptr;
};

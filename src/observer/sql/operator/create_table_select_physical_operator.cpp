#include "create_table_select_physical_operator.h"
#include "storage/trx/trx.h"

std::string CreateTableSelectPhysicalOperator::param() const { return std::string(); }

RC CreateTableSelectPhysicalOperator::open(Trx *trx)
{
  ASSERT(table_!= nullptr, "the table should not be null");
  ASSERT(children_.size() == 1, "the children num should be 1");
  auto & select_physical_oper = children_[0];
  RC    rc          = RC::SUCCESS;
  rc = select_physical_oper->open(trx);
  if(OB_FAIL(rc)){
    return rc;
  }

  while(OB_SUCC(select_physical_oper->next())){
    Tuple *tuple = select_physical_oper->current_tuple();
    if (nullptr == tuple) {
      LOG_WARN("failed to get current record: %s", strrc(rc));
      return rc;
    }

    std::vector<Value> values;
    for(int i = 0; i < tuple->cell_num(); i++){
        Value val;
        rc = tuple->cell_at(i, val);
        values.emplace_back(val);
    }

    //insert record 逻辑
    Record record;
    RC     rc = table_->make_record(static_cast<int>(values.size()), values.data(), record);
    if (rc != RC::SUCCESS) {
        LOG_WARN("failed to make record. rc=%s", strrc(rc));
        return rc;
    }

    rc = trx->insert_record(table_, record);
    if (rc != RC::SUCCESS) {
        LOG_WARN("failed to insert record by transaction. rc=%s", strrc(rc));
        return rc;
    }
  }
  return RC::SUCCESS;
}

RC CreateTableSelectPhysicalOperator::next() { 
    return RC::RECORD_EOF; 
}

Tuple *CreateTableSelectPhysicalOperator::current_tuple() { return nullptr; }

RC CreateTableSelectPhysicalOperator::close() { 
    ASSERT(children_.size() == 1, "the chilren size should be 1                                                                                                                                                                                                                                                                                                                                            ");
    return children_[0]->close();
}

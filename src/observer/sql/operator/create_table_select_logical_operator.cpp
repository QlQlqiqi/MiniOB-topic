#include "create_table_select_logical_operator.h"

CreateTableSelectLogicalOperator::CreateTableSelectLogicalOperator(
    Table *table, unique_ptr<LogicalOperator> &&select_logical_operator)
    : table_(table), select_logical_operator_(std::move(select_logical_operator)){}
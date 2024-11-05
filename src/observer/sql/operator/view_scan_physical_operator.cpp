#include "view_scan_physical_operator.h"
#include "storage/view/view.h"

std::string ViewScanPhysicalOperator::param() const { return std::string(); }

RC ViewScanPhysicalOperator::open(Trx *trx)
{
  ASSERT(view_ != nullptr, "the view should be not null");
  ASSERT(children_.size() == 1, "the children num should be 1");
  auto &child_oper  = children_[0];
  RC    rc          = RC::SUCCESS;

  std::string view_name = view_->view_meta().view_name();

  tuple_.set_schema(view_, &view_->table_meta().field_metas());

  if (rc != RC::SUCCESS && rc != RC::RECORD_EOF) {
    return rc;
  }

  return child_oper->open(trx);
}

RC ViewScanPhysicalOperator::next()
{
  RC rc = children_[0]->next();

  if (rc != RC::SUCCESS) {
    return rc;
  }

  std::string view_name = view_->view_meta().view_name();
  Tuple      *child_tuple = children_[0]->current_tuple();
  ProjectTuple *project_tuple = static_cast<ProjectTuple *>(child_tuple);
  ASSERT(project_tuple != nullptr, "the child_tuple should be project tuple");
  auto field_metas = view_->table_meta().field_metas();
  ASSERT(static_cast<int>(field_metas.size()) == project_tuple->cell_num(), "the field meta size should be equal to project tuple cell num");
  Record view_record;
  vector<Value> values;

  for (int i = 0; i < project_tuple->cell_num(); i++) {
    Value val;
    rc     = project_tuple->cell_at(i, val);
    values.emplace_back(val);
    // switch (val.attr_type()) {
    //   case AttrType::NULLS: {
    //     ASSERT(f.nullable(), "f should be nullable");
    //     auto zeros = std::vector<char>(f.len(), '\1');
    //     rc         = view_record.set_field(f.offset(), f.len(), zeros.data());
    //     if (OB_FAIL(rc)) {
    //       LOG_WARN("failed to update record. rid=%d, rc=%s", view_record.rid(), strrc(rc));
    //       return rc;
    //     }
    //   } break;
    //   case AttrType::CHARS: {
    //     auto zeros = std::vector<char>(f.len(), '\0');
    //     rc         = view_record.set_field(f.offset(), f.len(), zeros.data());
    //     if (OB_FAIL(rc)) {
    //       LOG_WARN("failed to set field when create view record. rid=%d, rc=%s", view_record.rid(), strrc(rc));
    //       return rc;
    //     }
    //     [[fallthrough]];
    //   }
    //   default: {
    //     rc = view_record.set_field(f.offset() + f.nullable(), val.length() - f.nullable(), val.data());
    //     if (OB_FAIL(rc)) {
    //       LOG_WARN("failed to set field when create view record rc=%s", strrc(rc));
    //       return rc;
    //     }
    //   } break;
    // }
  }
  view_->make_record(project_tuple->cell_num(), values.data(), current_record_);
  tuple_.set_record(&current_record_);
  tuple_.set_rid_maps(project_tuple);
  return rc;
}

RC ViewScanPhysicalOperator::close() { 
    for(auto& child :children_){
        child->close();
    }
    children_[0];
    return RC::SUCCESS;
}

Tuple *ViewScanPhysicalOperator::current_tuple() { return &tuple_; }

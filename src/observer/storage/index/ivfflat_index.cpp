#include "common/log/log.h"
#include "sql/expr/expression.h"
#include "storage/index/bplus_tree_index.h"
#include "storage/table/table.h"
#include "storage/db/db.h"
#include "storage/index/bplus_tree.h"
#include "storage/index/ivfflat_index.h"
#include "storage/index/dkm.hpp"
#include <functional>
#include <queue>

RC IvfflatIndex::create(Table *table, const char *file_name, const IndexMeta &index_meta,
    const std::vector<int> &field_ids, const std::vector<const FieldMeta *> &field_metas)
{
  // 理论上来说，这里应该有且只有一个 field_metas
  if (inited_ || field_metas.size() != 1) {
    LOG_WARN("Failed to create index due to the index has been created before. file_name:%s, index_meta: %s",
        file_name, index_meta.to_string().c_str());
    return RC::RECORD_OPENNED;
  }

  Index::init(index_meta, field_metas);

  BufferPoolManager &bpm = table->db()->buffer_pool_manager();
  RC                 rc =
      index_handler_.create(table->db()->log_handler(), bpm, file_name, field_ids, field_metas, index_meta.unique());
  if (RC::SUCCESS != rc) {
    LOG_WARN("Failed to create index_handler, file_name:%s, index_meta: %s, rc:%s",
        file_name, index_meta.to_string().c_str(), strrc(rc));
    return rc;
  }

  inited_ = true;
  table_  = table;
  lists_  = index_meta.with()->lists;
  probes_    = index_meta.with()->probes;
  func_type_ = index_meta.with()->func_type;
  LOG_INFO("Successfully create index, file_name:%s, index_meta: %s",
    file_name, index_meta.to_string().c_str());
  return RC::SUCCESS;
};

RC IvfflatIndex::open(
    Table *table, const char *file_name, const IndexMeta &index_meta, const std::vector<const FieldMeta *> &field_metas)
{
  if (inited_) {
    LOG_WARN("Failed to open index due to the index has been initedd before. file_name:%s, index_meta: %s",
        file_name, index_meta.to_string().c_str());
    return RC::RECORD_OPENNED;
  }

  Index::init(index_meta, field_metas);

  BufferPoolManager &bpm = table->db()->buffer_pool_manager();
  RC                 rc  = index_handler_.open(table->db()->log_handler(), bpm, file_name);
  if (RC::SUCCESS != rc) {
    LOG_WARN("Failed to open index_handler, file_name:%s, index_meta: %s, rc:%s",
        file_name, index_meta.to_string().c_str(), strrc(rc));
    return rc;
  }

  inited_ = true;
  table_  = table;
  lists_  = index_meta.with()->lists;
  probes_    = index_meta.with()->probes;
  func_type_ = index_meta.with()->func_type;
  LOG_INFO("Successfully open index, file_name:%s, index_meta: %s",
    file_name, index_meta.to_string().c_str());
  return RC::SUCCESS;
};

void IvfflatIndex::ann_search(const std::vector<double> &target, size_t limit, std::vector<RID> &res)
{
  if (!is_clean_) {
    kmeans_ptr_->resize(lists_);
    points_ptr_->resize(lists_);
    std::vector<std::vector<double>> data;
    for (auto &record_ptr : *data_ptr_) {
      data.emplace_back(record_ptr->second);
    }
    auto cluster_data = dkm::kmeans_lloyd<double>(data, lists_);
    int  idx          = 0;
    kmeans_ptr_->resize(std::get<1>(cluster_data).size());
    for (const auto &label : std::get<1>(cluster_data)) {
      (*kmeans_ptr_)[label].emplace_back(data_ptr_->at(idx++));
    }
    idx = 0;
    points_ptr_->resize(std::get<0>(cluster_data).size());
    for (const auto &point : std::get<0>(cluster_data)) {
      points_ptr_->emplace_back(std::make_pair(idx, point));
    }
    is_clean_ = true;
  }

  // auto cmp = [&](const int &a, const int &b) {
  //   Value tmp1;
  //   Value tmp2;
  //   tmp1.set_type(AttrType::VECTORS);
  //   tmp2.set_type(AttrType::VECTORS);
  //   auto &tmp_point1 = points_ptr_->at(a).second;
  //   auto &tmp_point2 = points_ptr_->at(b).second;
  //   tmp1.set_data(reinterpret_cast<const char *>(tmp_point1.data()), tmp_point1.size() * sizeof(double));
  //   tmp2.set_data(reinterpret_cast<const char *>(tmp_point2.data()), tmp_point2.size() * sizeof(double));
  //   Value value;
  //   value.set_type(AttrType::VECTORS);
  //   RC rc;
  //   switch (static_cast<FunctionExpr::Type>(func_type_)) {
  //     case FunctionExpr::Type::L2_DISTANCE: rc = FunctionExpr::calc_l2_distance(tmp1, tmp2, value); break;
  //     case FunctionExpr::Type::COSINE_DISTANCE: rc = FunctionExpr::calc_cosine_distance(tmp1, tmp2, value); break;
  //     case FunctionExpr::Type::INNER_PRODUCT: rc = FunctionExpr::calc_inner_product(tmp1, tmp2, value); break;
  //   }
  //     ASSERT(OB_FAIL(rc),"Failed to compare in cmp in ivfflat index");
  //   auto cmp_res = v
  // };
  // std::priority_queue<int, std::vector<int>, function<bool(const int &, const int &)>> pq(cmp);
}

RC IvfflatIndex::close()
{
  if (inited_) {
    LOG_INFO("Begin to close index, index_meta: %s", index_meta_.name());
    index_handler_.close();
    inited_ = false;
  }
  LOG_INFO("Successfully close index.");
  return RC::SUCCESS;
}

RC IvfflatIndex::insert_entry(const char *record, const RID *rid)
{
  RC rc;
  data_ptr_->emplace_back();
  auto &tmp_record_ptr = data_ptr_->at(data_ptr_->size() - 1);
  auto &field_meta     = field_metas_[0];
  auto  nullable       = field_meta.nullable();
  int   off            = nullable + field_meta.offset();

  Value s;
  if (field_meta.high_vector()) {
    rc = table_->get_text_from_record(record + off, s);
    if (OB_FAIL(rc)) {
      data_ptr_->resize(data_ptr_->size() - 1);
      LOG_ERROR("Failed to insert entry in ivfflat index");
      return rc;
    }
    tmp_record_ptr->second.resize(field_meta.dim() * sizeof(double));
    memcpy(tmp_record_ptr->second.data(), s.data(), s.length() - nullable);
  } else {
    tmp_record_ptr->second.resize(field_meta.len() - nullable);
    memcpy(tmp_record_ptr->second.data(), record + off, field_meta.len() - nullable);
  }
  tmp_record_ptr->first.copy_data(record, field_meta.len());
  tmp_record_ptr->first.set_rid(*rid);

  rc = index_handler_.insert_entry(record, rid);
  if (OB_FAIL(rc)) {
    LOG_ERROR("Failed to insert entry in ivfflat index");
    data_ptr_->resize(data_ptr_->size() - 1);
  } else {
    is_clean_ = false;
  }
  return rc;
}

RC IvfflatIndex::delete_entry(const char *record, const RID *rid)
{
  auto iter =
      std::find_if(data_ptr_->begin(), data_ptr_->end(), [&](const RecordPtr &a) { return a->first.rid() == *rid; });
  if (iter == data_ptr_->end()) {
    LOG_ERROR("Failed to find vector whiling deleting entry in ivfflat index");
    return RC::RECORD_NOT_EXIST;
  }
  data_ptr_->erase(iter);

  RC rc = index_handler_.delete_entry(record, rid);
  if (OB_FAIL(rc)) {
    LOG_ERROR("Failed to delete entry in ivfflat index");
  } else {
    is_clean_ = false;
  }
  return rc;
}

IndexScanner *IvfflatIndex::create_scanner(const char *left_key, int left_len, bool left_inclusive,
    const char *right_key, int right_len, bool right_inclusive, const std::shared_ptr<FieldMeta> field_meta)
{
  BplusTreeIndexScanner *index_scanner = new BplusTreeIndexScanner(index_handler_);
  RC rc = index_scanner->open(left_key, left_len, left_inclusive, right_key, right_len, right_inclusive, field_meta);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open index scanner. rc=%d:%s", rc, strrc(rc));
    delete index_scanner;
    return nullptr;
  }
  return index_scanner;
}

#include "common/log/log.h"
#include "sql/expr/expression.h"
#include "storage/index/bplus_tree_index.h"
#include "storage/table/table.h"
#include "storage/db/db.h"
#include "storage/index/bplus_tree.h"
#include "storage/index/ivfflat_index.h"
#include "storage/index/dkm_parallel.hpp"
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
  data_ptr_ = std::make_unique<std::vector<RecordPtr>>();
  kmeans_ptr_ = std::make_unique<std::vector<std::vector<RecordPtr>>>();
  points_ptr_ = std::make_unique<std::vector<std::pair<int, std::vector<double>>>>();
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
  data_ptr_ = std::make_unique<std::vector<RecordPtr>>();
  kmeans_ptr_ = std::make_unique<std::vector<std::vector<RecordPtr>>>();
  points_ptr_ = std::make_unique<std::vector<std::pair<int, std::vector<double>>>>();
  LOG_INFO("Successfully open index, file_name:%s, index_meta: %s",
    file_name, index_meta.to_string().c_str());
  return RC::SUCCESS;
};

void IvfflatIndex::ann_search(const std::vector<double> &target, size_t limit, std::vector<RID> &res)
{
  if (!is_clean_) {
    auto starttime = std::chrono::system_clock::now();
    cleaner();
    auto diff = std::chrono::system_clock::now()- starttime;
    printf("=============================================\n");
    printf("cleaner cost: %ldms\n", diff.count() / 1000000);
    is_clean_ = true;
  }

  Value tar_val;
  tar_val.set_type(AttrType::VECTORS);
  tar_val.set_data(reinterpret_cast<const char *>(target.data()), target.size() * sizeof(double));

  // 找距离最小的
  auto low_distance = [&](const std::vector<double> &a, const std::vector<double> &b, const Value &tar_val) {
    Value tmp1;
    Value tmp2;
    tmp1.set_type(AttrType::VECTORS);
    tmp2.set_type(AttrType::VECTORS);
    tmp1.set_data(reinterpret_cast<const char *>(a.data()), a.size() * sizeof(double));
    tmp2.set_data(reinterpret_cast<const char *>(b.data()), b.size() * sizeof(double));
    Value value1;
    value1.set_type(AttrType::VECTORS);
    Value value2;
    value2.set_type(AttrType::VECTORS);
    switch (static_cast<FunctionExpr::Type>(func_type_)) {
      case FunctionExpr::Type::L2_DISTANCE:
        FunctionExpr::calc_l2_distance(tmp1, tar_val, value1);
        FunctionExpr::calc_l2_distance(tmp2, tar_val, value2);
        break;
      case FunctionExpr::Type::COSINE_DISTANCE:
        FunctionExpr::calc_cosine_distance(tmp1, tar_val, value1);
        FunctionExpr::calc_cosine_distance(tmp2, tar_val, value2);
        break;
      case FunctionExpr::Type::INNER_PRODUCT:
        FunctionExpr::calc_inner_product(tmp1, tar_val, value1);
        FunctionExpr::calc_inner_product(tmp2, tar_val, value2);
        break;
    }
    auto cmp_res = value1.compare(value2);
    // LOG_INFO("low_distance cmp_res: %d", cmp_res);
    if (cmp_res == ValCmpRes::LESS || cmp_res == ValCmpRes::EQUAL || cmp_res == ValCmpRes::GREAT) {
      return cmp_res;
    }
    ASSERT(false, "unreachable");
  };

  auto cmp = [&](const RecordPtr &a, const RecordPtr &b) {
    return low_distance(a->second, b->second, tar_val) != ValCmpRes::LESS;
  };
  std::priority_queue<RecordPtr, std::vector<RecordPtr>, function<bool(const RecordPtr &, const RecordPtr &)>> pq(cmp);

  // TODO(qiqi): 这里暂时写的抽象
  if (!is_second_) {
    std::sort(points_ptr_->begin(), points_ptr_->end(), [&](const auto &a, const auto &b) {
      return low_distance(a.second, b.second, tar_val) == ValCmpRes::LESS;
    });

    // 1. 找 probes 个距离最短的质点
    for (int i = 0; i < std::min(probes_, (int)points_ptr_->size()); i++) {
      int point = points_ptr_->at(i).first;
      ASSERT(point < kmeans_ptr_->size(), "point should be less than kmeans_ptr_ size");
      for (auto &record_ptr : kmeans_ptr_->at(point)) {
        pq.emplace(record_ptr);
      }
    }

    // 2. 在这些簇里选 limit 个距离最短的点
    // 3. 将结果返回
    while (limit-- && !pq.empty()) {
      auto &top = pq.top();
      res.emplace_back(top->first.rid());
      pq.pop();
    }
  } else {
    auto starttime = std::chrono::system_clock::now();
    for (int i = 0; i < first_points_size_; i++) {
      std::sort(child_points_ptr_[i]->begin(), child_points_ptr_[i]->end(), [&](const auto &a, const auto &b) {
        return low_distance(a.second, b.second, tar_val) == ValCmpRes::LESS;
      });
    }
    auto diff      = std::chrono::system_clock::now() - starttime;
    printf("sort cost: %ldms\n", diff.count() / 1000000);

    starttime = std::chrono::system_clock::now();
    for (int i = 0; i < first_points_size_; i++) {
      // 1. 找 probes 个距离最短的质点
      auto &kmeans_ptr = child_kmeans_ptr_[i];
      auto &points_ptr = child_points_ptr_[i];
      for (int i = 0; i < std::min(probes_, (int)points_ptr->size()); i++) {
        int point = points_ptr->at(i).first;
        ASSERT(point < kmeans_ptr->size(), "point should be less than kmeans_ptr size");
        for (auto &record_ptr : kmeans_ptr->at(point)) {
          pq.emplace(record_ptr);
        }
      }
    }
    diff      = std::chrono::system_clock::now() - starttime;
    printf("priority cost: %ldms\n", diff.count() / 1000000);

    // 2. 在这些簇里选 limit 个距离最短的点
    // 3. 将结果返回
    while (limit-- && !pq.empty()) {
      auto &top = pq.top();
      res.emplace_back(top->first.rid());
      pq.pop();
    }
  }
}

void IvfflatIndex::cleaner()
{
  // 这里性能会减弱
  kmeans_ptr_->clear();
  points_ptr_->clear();
  child_kmeans_ptr_.clear();
  child_points_ptr_.clear();

  is_second_ = data_ptr_->size() > 10000;
  std::vector<std::vector<double>> data;
  data.reserve(data_ptr_->size());
  for (auto &record_ptr : *data_ptr_) {
    data.emplace_back(record_ptr->second);
  }
  // TODO(qiqi): 这里暂时写的抽象
  if (!is_second_) {
    auto num          = std::min(lists_, (int)data.size());
    auto cluster_data = dkm::kmeans_lloyd_parallel<double>(data, num);
    data.clear();

    int  idx          = 0;
    kmeans_ptr_->resize(num);
    for (const auto &label : std::get<1>(cluster_data)) {
      (*kmeans_ptr_)[label].emplace_back(data_ptr_->at(idx++));
    }
    data_ptr_->clear();
    idx = 0;
    points_ptr_->reserve(std::get<0>(cluster_data).size());
    for (const auto &point : std::get<0>(cluster_data)) {
      points_ptr_->emplace_back(std::make_pair(idx++, point));
    }
  } else {
    // 二次聚类
    first_points_size_  = (int)std::floor(std::sqrt(lists_));

    // 1. 先做 first_points_size_ 个质点数的聚类
    first_points_size_          = std::min(first_points_size_, (int)data.size());
    auto cluster_data = dkm::kmeans_lloyd_parallel<double>(data, first_points_size_);
    data.clear();

    int idx = 0;
    kmeans_ptr_->resize(first_points_size_);
    for (const auto &label : std::get<1>(cluster_data)) {
      (*kmeans_ptr_)[label].emplace_back(data_ptr_->at(idx++));
    }
    data_ptr_->clear();

    // 2. 对每个聚类所属的数据进行二次聚类
    second_points_size_ = (int)std::ceil(lists_ / first_points_size_);
    child_kmeans_ptr_.reserve(first_points_size_);
    child_points_ptr_.reserve(first_points_size_);
    for (int i = 0; i < first_points_size_; i++) {
      child_kmeans_ptr_.emplace_back(std::make_unique<std::vector<std::vector<RecordPtr>>>());
      child_points_ptr_.emplace_back(std::make_unique<std::vector<std::pair<int, std::vector<double>>>>());
      auto &data_ptr = kmeans_ptr_->at(i);
      data.reserve(data_ptr.size());
      for (auto &record_ptr : data_ptr) {
        data.emplace_back(record_ptr->second);
      }

      second_points_size_ = std::min(second_points_size_, (int)data.size());
      auto cluster_data  = dkm::kmeans_lloyd_parallel<double>(data, second_points_size_);
      data.clear();

      int  idx           = 0;
      child_kmeans_ptr_[i]->resize(second_points_size_);
      for (const auto &label : std::get<1>(cluster_data)) {
        (*child_kmeans_ptr_[i])[label].emplace_back(data_ptr.at(idx++));
      }

      data_ptr.clear();
      idx = 0;
      child_points_ptr_[i]->reserve(std::get<0>(cluster_data).size());
      for (const auto &point : std::get<0>(cluster_data)) {
        child_points_ptr_[i]->emplace_back(std::make_pair(idx++, point));
      }
      data.clear();
    }
  }
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
  data_ptr_->emplace_back(std::make_shared<std::pair<Record, std::vector<double>>>());
  auto &tmp_record_ptr = data_ptr_->at(data_ptr_->size() - 1);
  auto &field_meta     = field_metas_[0];
  auto  nullable       = field_meta.nullable();
  int   off            = nullable + field_meta.offset();

  // 忽略 isnull
  Value s;
  if (field_meta.high_vector()) {
    rc = table_->get_text_from_record(record + off, s, field_meta.high_vector());
    if (OB_FAIL(rc)) {
      data_ptr_->resize(data_ptr_->size() - 1);
      LOG_ERROR("Failed to insert entry in ivfflat index");
      return rc;
    }
    tmp_record_ptr->second.resize(field_meta.dim());
    memcpy(tmp_record_ptr->second.data(), s.data(), s.length());
  } else {
    tmp_record_ptr->second.resize(field_meta.dim());
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

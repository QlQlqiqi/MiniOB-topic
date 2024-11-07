#include "common/log/log.h"
#include "sql/expr/expression.h"
#include "storage/index/bplus_tree_index.h"
#include "storage/index/dkm_parallel.hpp"
#include "storage/table/table.h"
#include "storage/db/db.h"
#include "storage/index/bplus_tree.h"
#include "storage/index/ivfflat_index.h"
// #include "storage/index/dkm.hpp"
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

  inited_     = true;
  table_      = table;
  lists_      = index_meta.with()->lists;
  probes_     = index_meta.with()->probes;
  func_type_  = index_meta.with()->func_type;
  data_ptr_   = std::make_unique<std::vector<RID>>();
  kmeans_ptr_ = std::make_unique<std::vector<std::vector<RID>>>();
  points_ptr_ = std::make_unique<std::vector<std::pair<int, Vector>>>();
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

  inited_     = true;
  table_      = table;
  lists_      = index_meta.with()->lists;
  probes_     = index_meta.with()->probes;
  func_type_  = index_meta.with()->func_type;
  data_ptr_   = std::make_unique<std::vector<RID>>();
  kmeans_ptr_ = std::make_unique<std::vector<std::vector<RID>>>();
  points_ptr_ = std::make_unique<std::vector<std::pair<int, Vector>>>();
  LOG_INFO("Successfully open index, file_name:%s, index_meta: %s",
    file_name, index_meta.to_string().c_str());
  return RC::SUCCESS;
};

void IvfflatIndex::ann_search(const Vector &target, size_t limit, std::vector<RID> &res)
{
  if (!is_clean_) {
    auto start = std::chrono::high_resolution_clock::now();
    cleaner();
    printf("=============================================\n");
    auto finish = std::chrono::high_resolution_clock::now();
    std::cout << "cleaner cost: " << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count()
              << "ms.\n";
    is_clean_ = true;
  }

  // 计算距离
  auto distance = [&](const double *a, const double *b, const int len) {
    double res;
    switch (static_cast<FunctionExpr::Type>(func_type_)) {
      case FunctionExpr::Type::L2_DISTANCE: FunctionExpr::calc_l2_distance(a, b, len, res); break;
      case FunctionExpr::Type::COSINE_DISTANCE: FunctionExpr::calc_cosine_distance(a, b, len, res); break;
      case FunctionExpr::Type::INNER_PRODUCT: FunctionExpr::calc_inner_product(a, b, len, res); break;
    }
    return res;
  };

  auto cmp = [&](const std::shared_ptr<std::pair<RID, Vector>> &a, const std::shared_ptr<std::pair<RID, Vector>> &b) {
    return distance(a->second.data(), target.data(), target.size()) >
           distance(b->second.data(), target.data(), target.size());
  };
  std::priority_queue<std::shared_ptr<std::pair<RID, Vector>>,
      std::vector<std::shared_ptr<std::pair<RID, Vector>>>,
      function<bool(const std::shared_ptr<std::pair<RID, Vector>> &, const std::shared_ptr<std::pair<RID, Vector>> &)>>
      pq(cmp);

  // TODO(qiqi): 这里暂时写的抽象
  if (!is_second_) {
    std::sort(points_ptr_->begin(), points_ptr_->end(), [&](const auto &a, const auto &b) {
      return distance(a.second.data(), target.data(), target.size()) <
             distance(b.second.data(), target.data(), target.size());
    });

    // 1. 找 probes 个距离最短的质点
    for (int i = 0; i < std::min(probes_, (int)points_ptr_->size()); i++) {
      int point = points_ptr_->at(i).first;
      ASSERT(point < kmeans_ptr_->size(), "point should be less than kmeans_ptr_ size");
      std::vector<std::shared_ptr<std::pair<RID, std::vector<double>>>> data;
      read_all_vector(kmeans_ptr_->at(point), data);
      for (auto &item : data) {
        pq.emplace(item);
      }
    }

    // 2. 在这些簇里选 limit 个距离最短的点
    // 3. 将结果返回
    while (limit-- && !pq.empty()) {
      auto &top = pq.top();
      res.emplace_back(top->first);
      pq.pop();
    }
  } else {
    auto start = std::chrono::high_resolution_clock::now();
    // 先在 1 级聚类中寻找质点
    std::sort(points_ptr_->begin(), points_ptr_->end(), [&](const auto &a, const auto &b) {
      return distance(a.second.data(), target.data(), target.size()) <
             distance(b.second.data(), target.data(), target.size());
    });
    for (int i = 0; i < std::min(probes_, first_points_size_); i++) {
      auto point = points_ptr_->at(i).first;
      std::sort(child_points_ptr_[point]->begin(), child_points_ptr_[point]->end(), [&](const auto &a, const auto &b) {
        return distance(a.second.data(), target.data(), target.size()) <
               distance(b.second.data(), target.data(), target.size());
      });
    }
    auto finish = std::chrono::high_resolution_clock::now();
    std::cout << "sort cost: " << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count()
              << "ms.\n";

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < std::min(probes_, first_points_size_); i++) {
      // 1. 找 probes 个距离最短的质点
      auto point = points_ptr_->at(i).first;
      auto &kmeans_ptr = child_kmeans_ptr_[point];
      auto &points_ptr = child_points_ptr_[point];
      for (int i = 0; i < std::min(probes_, (int)points_ptr->size()); i++) {
        int point = points_ptr->at(i).first;
        ASSERT(point < kmeans_ptr->size(), "point should be less than kmeans_ptr size");
        std::vector<std::shared_ptr<std::pair<RID, Vector>>> data;
        read_all_vector(kmeans_ptr->at(point), data);
        for (auto &item : data) {
          pq.emplace(item);
        }
      }
    }
    finish = std::chrono::high_resolution_clock::now();
    std::cout << "priority cost: " << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count()
              << "ms.\n";

    // 2. 在这些簇里选 limit 个距离最短的点
    // 3. 将结果返回
    while (limit-- && !pq.empty()) {
      auto &top = pq.top();
      res.emplace_back(top->first);
      pq.pop();
    }
  }
}

void IvfflatIndex::cleaner()
{
  if (is_clean_) {
    return;
  }

  // 这里性能会减弱
  kmeans_ptr_->clear();
  kmeans_ptr_->shrink_to_fit();
  points_ptr_->clear();
  child_kmeans_ptr_.clear();
  child_kmeans_ptr_.shrink_to_fit();
  child_points_ptr_.clear();
  child_points_ptr_.shrink_to_fit();
  data_ptr_->clear();
  data_ptr_->shrink_to_fit();

  // 讲所有的数据 RID 读入到 data_ptr_，并且会将所有的 vector 读入 dkm_data
  DkmData dkm_data;
  read_all_rid(data_ptr_);
  read_all_vector(*data_ptr_, dkm_data);

  is_second_ = dkm_data.size() > 10000;
  // is_second_ = true;
  // TODO(qiqi): 这里暂时写的抽象
  if (!is_second_) {
    auto num          = std::min(lists_, (int)dkm_data.size());
    auto cluster_data = dkm::kmeans_lloyd_parallel<double>(dkm_data, num);
    dkm_data.clear();
    dkm_data.shrink_to_fit();

    int idx = 0;
    kmeans_ptr_->resize(num);
    for (const auto &label : std::get<1>(cluster_data)) {
      (*kmeans_ptr_)[label].emplace_back(data_ptr_->at(idx++));
    }
    data_ptr_->clear();
    data_ptr_->shrink_to_fit();

    idx = 0;
    points_ptr_->reserve(std::get<0>(cluster_data).size());
    for (const auto &point : std::get<0>(cluster_data)) {
      points_ptr_->emplace_back(std::make_pair(idx++, point));
    }
    ASSERT(num == idx, "error number");
  } else {
    // 二次聚类
    first_points_size_ = std::min((int)std::floor(std::cbrt(lists_)), (int)dkm_data.size());

    // 1. 先做 first_points_size_ 个质点数的聚类
    auto cluster_data = dkm::kmeans_lloyd_parallel<double>(dkm_data, first_points_size_);
    dkm_data.clear();
    dkm_data.shrink_to_fit();

    int idx = 0;
    kmeans_ptr_->resize(first_points_size_);
    for (const auto &label : std::get<1>(cluster_data)) {
      (*kmeans_ptr_)[label].emplace_back(data_ptr_->at(idx++));
    }
    data_ptr_->clear();
    data_ptr_->shrink_to_fit();

    idx = 0;
    points_ptr_->reserve(std::get<0>(cluster_data).size());
    for (const auto &point : std::get<0>(cluster_data)) {
      points_ptr_->emplace_back(std::make_pair(idx++, point));
    }
    ASSERT(first_points_size_ == idx, "error number");

    // 2. 对每个聚类所属的数据进行二次聚类
    auto second_points_size = (int)std::ceil(lists_ / first_points_size_);
    child_kmeans_ptr_.reserve(first_points_size_);
    child_points_ptr_.reserve(first_points_size_);
    for (int i = 0; i < first_points_size_; i++) {
      child_kmeans_ptr_.emplace_back(std::make_unique<std::vector<std::vector<RID>>>());
      child_points_ptr_.emplace_back(std::make_unique<std::vector<std::pair<int, Vector>>>());
      auto &data_ptr = kmeans_ptr_->at(i);
      read_all_vector(data_ptr, dkm_data);

      second_points_size = std::min(second_points_size, (int)dkm_data.size());
      auto cluster_data  = dkm::kmeans_lloyd_parallel<double>(dkm_data, second_points_size);
      dkm_data.clear();
      dkm_data.shrink_to_fit();

      int idx = 0;
      child_kmeans_ptr_[i]->resize(second_points_size);
      for (const auto &label : std::get<1>(cluster_data)) {
        (*child_kmeans_ptr_[i])[label].emplace_back(data_ptr.at(idx++));
      }
      data_ptr.clear();
      data_ptr.shrink_to_fit();

      idx = 0;
      child_points_ptr_[i]->reserve(std::get<0>(cluster_data).size());
      for (const auto &point : std::get<0>(cluster_data)) {
        child_points_ptr_[i]->emplace_back(std::make_pair(idx++, point));
      }
      ASSERT(second_points_size == idx, "error number");
    }
  }
}

void IvfflatIndex::read_all_rid(DataPtr &rids)
{
  auto          field_meta_ptr = std::make_shared<FieldMeta>(field_metas_[0]);
  IndexScanner *index_scanner  = create_scanner(nullptr, 0, true, nullptr, 0, true, field_meta_ptr);

  RID rid;
  rids->reserve(cnt_);
  RC rc;
  while (RC::SUCCESS == (rc = index_scanner->next_entry(&rid))) {
    rids->emplace_back(rid);
  }
  index_scanner->destroy();
}

void IvfflatIndex::read_all_vector(const std::vector<RID> &rids, DkmData &dkm_data)
{
  int    idx = 0;
  auto &field_meta      = field_metas_[0];
  dkm_data              = std::vector<Vector>(rids.size(), Vector(field_meta.dim(), 0));
  auto  nullable        = field_meta.nullable();
  int   off             = nullable + field_meta.offset();
  auto   record_handler = table_->record_handler();
  Record record;
  for (auto &rid : rids) {
    auto &vp = cache_[rid];
    if (vp) {
      memcpy(dkm_data.at(idx++).data(), vp->data(), vp->size() * sizeof(double));
      continue;
    }
    RC rc = record_handler->get_record(rid, record);
    if (rc != RC::SUCCESS) {
      ASSERT(false, "Failed to get entry in read_all_vector in ivfflat index");
    }

    // 忽略 isnull
    Value s;
    vp = std::make_shared<Vector>();
    vp->resize(field_meta.dim());
    if (field_meta.high_vector()) {
      rc = table_->get_text_from_record(record.data() + off, s, field_meta.high_vector());
      if (OB_FAIL(rc)) {
        ASSERT(false, "Failed to get entry in read_all_vector in ivfflat index");
      }
      memcpy(dkm_data.at(idx++).data(), s.data(), s.length());
      memcpy(vp->data(), s.data(), s.length());
    } else {
      memcpy(dkm_data.at(idx++).data(), record.data() + off, field_meta.len() - nullable);
      memcpy(vp->data(), record.data() + off, field_meta.len() - nullable);
    }
    cache_[rid] = vp;
  }
}

void IvfflatIndex::read_all_vector(
    const std::vector<RID> &rids, std::vector<std::shared_ptr<std::pair<RID, Vector>>> &data)
{
  auto &field_meta      = field_metas_[0];
  auto  nullable        = field_meta.nullable();
  int   off             = nullable + field_meta.offset();
  data                  = std::vector<std::shared_ptr<std::pair<RID, Vector>>>(rids.size(), nullptr);
  auto   record_handler = table_->record_handler();
  Record record;
  int    idx = 0;
  for (auto &rid : rids) {
    data[idx] = std::make_shared<std::pair<RID, Vector>>();
    data[idx]->first = rid;
    data[idx]->second.resize(field_meta.dim(), 0);

    auto &vp = cache_[rid];
    if (vp) {
      memcpy(data.at(idx++)->second.data(), vp->data(), vp->size() * sizeof(double));
      continue;
    }

    RC rc = record_handler->get_record(rid, record);
    if (rc != RC::SUCCESS) {
      ASSERT(false, "Failed to get entry in read_all_vector in ivfflat index");
    }

    // 忽略 isnull
    Value s;
    if (field_meta.high_vector()) {
      rc = table_->get_text_from_record(record.data() + off, s, field_meta.high_vector());
      if (OB_FAIL(rc)) {
        ASSERT(OB_FAIL(rc), "Failed to read all vector in ivfflat index");
      }
      memcpy(data.at(idx++)->second.data(), s.data(), s.length());
    } else {
      memcpy(data.at(idx++)->second.data(), record.data() + off, field_meta.len() - nullable);
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
  RC rc = index_handler_.insert_entry(record, rid);
  if (OB_FAIL(rc)) {
    LOG_ERROR("Failed to insert entry in ivfflat index");
    // data_ptr_->resize(data_ptr_->size() - 1);
  } else {
    cnt_++;
    data_ptr_->clear();
    data_ptr_->shrink_to_fit();
    is_clean_ = false;
  }
  return rc;
}

RC IvfflatIndex::delete_entry(const char *record, const RID *rid)
{
  RC rc = index_handler_.delete_entry(record, rid);
  if (OB_FAIL(rc)) {
    // 忽略移除不存在的记录
    if (rc != RC::FILE_NOT_EXIST) {
      LOG_ERROR("Failed to delete entry in ivfflat index");
    }
  } else {
    if (cnt_ > 0) {
      cnt_--;
    }
    data_ptr_->clear();
    data_ptr_->shrink_to_fit();
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

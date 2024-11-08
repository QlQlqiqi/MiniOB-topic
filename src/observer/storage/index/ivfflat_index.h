/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#pragma once

#include "storage/index/bplus_tree.h"
#include "storage/index/index.h"
#include "storage/index/annoylib.h"
#include "storage/index/kissrandom.h"

class BplusTreeHandler;

/**
 * @brief ivfflat 向量索引
 * @ingroup Index
 */
class IvfflatIndex : public Index
{
public:
  IvfflatIndex(){};

  virtual ~IvfflatIndex() noexcept { close(); };

  RC create(Table *table, const char *file_name, const IndexMeta &index_meta, const std::vector<int> &field_ids,
      const std::vector<const FieldMeta *> &field_metas) override;

  RC open(Table *table, const char *file_name, const IndexMeta &index_meta,
      const std::vector<const FieldMeta *> &field_metas) override;

  using Vector = std::vector<double>;
  using VectorPtr = std::shared_ptr<Vector>;
  void ann_search(const Vector &target, size_t limit, std::vector<RID> &res);

  // 做聚类算法
  // 如果数据量过大，比如数据量超过 1w，并且质点数量超过 100，
  // 那么会先对全部数据做一次 k-means，质点数为 floor(cbrt(lists_))；
  // 然后将数据分到每个质点中，然后对每个质点所属的数据进行二次 k-means，
  // 质点数为 ceil(lists_ / floor(cbrt(lists_)))；
  void cleaner();

  RC close();

  RC insert_entry(const char *record, const RID *rid) override;
  RC delete_entry(const char *record, const RID *rid) override;

  RC sync() override { return index_handler_.sync(); };

  IndexScanner *create_scanner(const char *left_key, int left_len, bool left_inclusive, const char *right_key,
      int right_len, bool right_inclusive, const std::shared_ptr<FieldMeta> field_meta = nullptr) override;

  int func_type() const { return func_type_; }

private:
  using DataPtr = std::unique_ptr<std::vector<RID>>;
  // KMeansPtr 第一维存储的是某个簇包含的所有 RID
  using KMeansPtr = std::unique_ptr<std::vector<std::vector<RID>>>;
  // PointsPtr 存储的是 KMeansPtr 下标和其对应的质点
  using PointsPtr = std::unique_ptr<std::vector<std::pair<int, Vector>>>;
  // dkm 算法使用数据的结构
  using DkmData = std::vector<Vector>;

  using PQData = std::pair<RID, std::shared_ptr<Vector>>;

  void insert_index(const RID &rid, const double *data);

  void init_index();
  void deinit_index();

  BplusTreeHandler index_handler_;
  Table           *table_     = nullptr;
  bool             inited_    = false;
  int              lists_     = 0;
  int              probes_    = 0;
  int              func_type_ = 0;

  // 是否需要重新构建 index
  bool is_clean_ = true;
  int dim_ = 0;

  // 这里本应使用模板来处理，但是为了影响最小，定义多个
  Annoy::AnnoyIndex<uint64_t, double, Annoy::Euclidean, Annoy::Kiss32Random, Annoy::AnnoyIndexSingleThreadedBuildPolicy>
      *index_l2_disance_ = nullptr;
  Annoy::AnnoyIndex<uint64_t, double, Annoy::Angular, Annoy::Kiss32Random, Annoy::AnnoyIndexSingleThreadedBuildPolicy>
      *index_cosine_ = nullptr;
  Annoy::AnnoyIndex<uint64_t, double, Annoy::DotProduct, Annoy::Kiss32Random, Annoy::AnnoyIndexSingleThreadedBuildPolicy>
      *index_inner_product_ = nullptr;
  std::map<int, uint64_t> mp_;
  uint64_t lsn_ = 0;
};

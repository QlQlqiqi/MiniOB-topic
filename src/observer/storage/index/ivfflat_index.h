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

  void ann_search(const std::vector<double> &target, size_t limit, std::vector<RID> &res);

  RC close();

  RC insert_entry(const char *record, const RID *rid) override;
  RC delete_entry(const char *record, const RID *rid) override;

  RC sync() override { return index_handler_.sync(); };

  IndexScanner *create_scanner(const char *left_key, int left_len, bool left_inclusive, const char *right_key,
      int right_len, bool right_inclusive, const std::shared_ptr<FieldMeta> field_meta = nullptr) override;

  int func_type() const { return func_type_; }

private:
  BplusTreeHandler index_handler_;
  Table           *table_     = nullptr;
  bool             inited_    = false;
  int              lists_     = 0;
  int              probes_    = 0;
  int              func_type_ = 0;

  // first 中是完整的 record，second 是 vector 内容
  using RecordPtr = std::shared_ptr<std::pair<Record, std::vector<double>>>;

  // 这里存储的数据是整个 record 全部

  // 会将数据在内存中保存一份，存储在 data_ 中
  // NOTES: 这里的数据不存储 isnull 标识符
  std::unique_ptr<std::vector<RecordPtr>> data_ptr_;
  // 第一个 vector 是簇的数量，长度是 lists_
  std::unique_ptr<std::vector<std::vector<RecordPtr>>> kmeans_ptr_;
  // kmeans 的每个簇的在 kmeans_ptr_ 中的下标和质点坐标
  std::unique_ptr<std::vector<std::pair<int, std::vector<double>>>> points_ptr_;
  // 是否需要重新执行 kmeans 算法
  bool is_clean_ = true;
};

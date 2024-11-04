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

  vector<RID> ann_search(const vector<float> &base_vector, size_t limit);

  RC close();

  RC insert_entry(const char *record, const RID *rid) override { return index_handler_.insert_entry(record, rid); };
  RC delete_entry(const char *record, const RID *rid) override { return index_handler_.delete_entry(record, rid); };

  RC sync() override { return index_handler_.sync(); };

  IndexScanner *create_scanner(const char *left_key, int left_len, bool left_inclusive, const char *right_key,
      int right_len, bool right_inclusive, const std::shared_ptr<FieldMeta> field_meta = nullptr) override;

private:
  BplusTreeHandler index_handler_;
  Table           *table_     = nullptr;
  bool             inited_    = false;
  int              lists_     = 0;
  int              probes_    = 0;
  int              func_type_ = 0;
};

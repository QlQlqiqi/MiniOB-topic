#include "common/log/log.h"
#include "storage/index/bplus_tree_index.h"
#include "storage/table/table.h"
#include "storage/db/db.h"
#include "storage/index/bplus_tree.h"
#include "storage/index/ivfflat_index.h"

RC IvfflatIndex::create(Table *table, const char *file_name, const IndexMeta &index_meta,
    const std::vector<int> &field_ids, const std::vector<const FieldMeta *> &field_metas)
{
  if (inited_) {
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

  inited_    = true;
  table_     = table;
  lists_     = index_meta.with()->lists;
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
  LOG_INFO("Successfully open index, file_name:%s, index_meta: %s",
    file_name, index_meta.to_string().c_str());
  return RC::SUCCESS;
};

vector<RID> IvfflatIndex::ann_search(const vector<float> &base_vector, size_t limit) { return vector<RID>(); }

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

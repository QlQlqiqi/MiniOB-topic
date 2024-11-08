#include "common/log/log.h"
#include "sql/expr/expression.h"
#include "storage/index/bplus_tree_index.h"
#include "storage/table/table.h"
#include "storage/db/db.h"
#include "storage/index/bplus_tree.h"
#include "storage/index/ivfflat_index.h"
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

  inited_    = true;
  table_     = table;
  lists_     = index_meta.with()->lists;
  probes_    = index_meta.with()->probes;
  func_type_ = index_meta.with()->func_type;
  dim_       = field_metas[0]->dim();
  init_index();
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

  inited_    = true;
  table_     = table;
  lists_     = index_meta.with()->lists;
  probes_    = index_meta.with()->probes;
  func_type_ = index_meta.with()->func_type;
  dim_       = field_metas[0]->dim();
  init_index();
  LOG_INFO("Successfully open index, file_name:%s, index_meta: %s",
    file_name, index_meta.to_string().c_str());
  return RC::SUCCESS;
};

void IvfflatIndex::ann_search(const Vector &target, size_t limit, std::vector<RID> &res)
{
  if (!is_clean_) {
    cleaner();
    is_clean_ = true;
  }

  if (!is_built_) {
    if (build_index() != RC::SUCCESS) {
      LOG_ERROR("Failed to build index in ivfflat index");
    }
    is_built_ = true;
  }

  std::vector<uint64_t> tmp;
  switch (static_cast<FunctionExpr::Type>(func_type_)) {
    case FunctionExpr::Type::L2_DISTANCE:
      index_l2_disance_->get_nns_by_vector(target.data(), limit, -1, &tmp, nullptr);
      break;
    case FunctionExpr::Type::COSINE_DISTANCE:
      index_cosine_->get_nns_by_vector(target.data(), limit, -1, &tmp, nullptr);
      break;
    case FunctionExpr::Type::INNER_PRODUCT:
      index_inner_product_->get_nns_by_vector(target.data(), limit, -1, &tmp, nullptr);
      break;
  }

  res.resize(tmp.size());
  for (int i = 0; i < tmp.size(); i++) {
    auto id         = mp_[tmp[i]];
    res[i].page_num = id >> 32;
    res[i].slot_num = id;
  }
}

void IvfflatIndex::cleaner()
{
  if (is_clean_) {
    return;
  }

  // 如果有被 delete 了，那就从文件重新读
  deinit_index();
  init_index();
  auto          field_meta_ptr = std::make_shared<FieldMeta>(field_metas_[0]);
  IndexScanner *index_scanner  = create_scanner(nullptr, 0, true, nullptr, 0, true, field_meta_ptr);
  auto          record_handler = table_->record_handler();

  RID    rid;
  RC     rc;
  Record record;
  auto  &field_meta = field_metas_[0];
  auto   nullable   = field_meta.nullable();
  int    off        = nullable + field_meta.offset();
  while (RC::SUCCESS == (rc = index_scanner->next_entry(&rid))) {
    rc = record_handler->get_record(rid, record);
    if (OB_FAIL(rc)) {
      LOG_TRACE("failed to get record. rid=%s, rc=%s", rid.to_string().c_str(), strrc(rc));
      return;
    }
    // 忽略 isnull
    Value s;
    if (field_meta.high_vector()) {
      rc = table_->get_text_from_record(record.data() + off, s, field_meta.high_vector());
      if (OB_FAIL(rc)) {
        LOG_ERROR("Failed to get_text_from_record in ivfflat index");
        return;
      }
      rc = insert_index(rid, reinterpret_cast<const double *>(s.data()));
    } else {
      rc = insert_index(rid, reinterpret_cast<const double *>(record.data() + off));
    }
    if (OB_FAIL(rc)) {
      LOG_ERROR("Failed to insert index in ivfflat index");
      return;
    }
  }
  record_handler->close();
  index_scanner->destroy();
}

RC IvfflatIndex::close()
{
  if (inited_) {
    LOG_INFO("Begin to close index, index_meta: %s", index_meta_.name());
    index_handler_.close();
    deinit_index();
    inited_ = false;
  }
  LOG_INFO("Successfully close index.");
  return RC::SUCCESS;
}

RC IvfflatIndex::insert_entry(const char *record, const RID *rid)
{
  RC    rc;
  auto &field_meta = field_metas_[0];
  auto  nullable   = field_meta.nullable();
  int   off        = nullable + field_meta.offset();

  // 忽略 isnull
  Value s;
  if (field_meta.high_vector()) {
    rc = table_->get_text_from_record(record + off, s, field_meta.high_vector());
    if (OB_FAIL(rc)) {
      LOG_ERROR("Failed to insert entry in ivfflat index");
      return rc;
    }
    rc = insert_index(*rid, reinterpret_cast<const double *>(s.data()));
  } else {
    rc = insert_index(*rid, reinterpret_cast<const double *>(record + off));
  }

  if (OB_FAIL(rc)) {
    LOG_ERROR("Failed to insert index in ivfflat index");
    return rc;
  }

  rc = index_handler_.insert_entry(record, rid);
  if (OB_FAIL(rc)) {
    LOG_ERROR("Failed to insert entry in ivfflat index");
  }
  return rc;
}

RC IvfflatIndex::delete_entry(const char *record, const RID *rid)
{
  RC rc = index_handler_.delete_entry(record, rid);
  // 忽略移除不存在的记录
  if (OB_FAIL(rc) && rc != RC::FILE_NOT_EXIST) {
    LOG_ERROR("Failed to delete entry in ivfflat index");
    return rc;
  }
  is_clean_ = false;
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

RC IvfflatIndex::insert_index(const RID &rid, const double *data)
{
  bool ret;
  mp_[lsn_] = (uint64_t)rid.page_num << 32 | rid.slot_num;
  switch (static_cast<FunctionExpr::Type>(func_type_)) {
    case FunctionExpr::Type::L2_DISTANCE: ret = index_l2_disance_->add_item(lsn_, data); break;
    case FunctionExpr::Type::COSINE_DISTANCE: ret = index_cosine_->add_item(lsn_, data); break;
    case FunctionExpr::Type::INNER_PRODUCT: ret = index_inner_product_->add_item(lsn_, data); break;
  }
  lsn_++;
  return ret ? RC::SUCCESS : RC::INTERNAL;
}

void IvfflatIndex::init_index()
{
  lsn_ = 0;
  mp_.clear();
  is_built_ = false;
  switch (static_cast<FunctionExpr::Type>(func_type_)) {
    case FunctionExpr::Type::L2_DISTANCE:
      index_l2_disance_ = new Annoy::AnnoyIndex<uint64_t,
          double,
          Annoy::Euclidean,
          Annoy::Kiss32Random,
          Annoy::AnnoyIndexSingleThreadedBuildPolicy>(dim_);
      // index_l2_disance_->build(lists_);
      break;
    case FunctionExpr::Type::COSINE_DISTANCE:
      index_cosine_ = new Annoy::
          AnnoyIndex<uint64_t, double, Annoy::Angular, Annoy::Kiss32Random, Annoy::AnnoyIndexSingleThreadedBuildPolicy>(
              dim_);
      // index_cosine_->build(lists_);
      break;
    case FunctionExpr::Type::INNER_PRODUCT:
      index_inner_product_ = new Annoy::AnnoyIndex<uint64_t,
          double,
          Annoy::DotProduct,
          Annoy::Kiss32Random,
          Annoy::AnnoyIndexSingleThreadedBuildPolicy>(dim_);
      // index_inner_product_->build(lists_);
      break;
  }
}

void IvfflatIndex::deinit_index()
{
  lsn_ = 0;
  mp_.clear();
  is_built_ = false;
  switch (static_cast<FunctionExpr::Type>(func_type_)) {
    case FunctionExpr::Type::L2_DISTANCE:
      delete index_l2_disance_;
      index_l2_disance_ = nullptr;
      break;
    case FunctionExpr::Type::COSINE_DISTANCE:
      delete index_cosine_;
      index_cosine_ = nullptr;
      break;
    case FunctionExpr::Type::INNER_PRODUCT:
      delete index_inner_product_;
      index_inner_product_ = nullptr;
      break;
  }
}

RC IvfflatIndex::build_index()
{
  if (is_built_) {
    return RC::SUCCESS;
  }
  bool ret;
  switch (static_cast<FunctionExpr::Type>(func_type_)) {
    case FunctionExpr::Type::L2_DISTANCE: ret = index_l2_disance_->build(std::min(lists_, 70)); break;
    case FunctionExpr::Type::COSINE_DISTANCE: ret = index_cosine_->build(std::min(lists_, 70)); break;
    case FunctionExpr::Type::INNER_PRODUCT: ret = index_inner_product_->build(std::min(lists_, 70)); break;
  }
  return ret ? RC::SUCCESS : RC::INTERNAL;
}

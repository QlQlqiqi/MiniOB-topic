/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Meiyi & Longda on 2021/4/13.
//
#include "storage/record/record_manager.h"
#include "common/log/log.h"
#include "storage/common/condition_filter.h"
#include "storage/trx/trx.h"
#include "storage/clog/log_handler.h"

using namespace common;

// bitmap 存在 page header 中，其长度粗略计算为：
// align8(BP_PAGE_DATA_SIZE / (sizeof(int) + sizeof(SlotNum))) / 8
// static constexpr int PAGE_HEADER_BITMAP_SIZE = ((BP_PAGE_DATA_SIZE / ((sizeof(int) + sizeof(SlotNum)))) + 7) / 8;

// static constexpr int PAGE_HEADER_SIZE = (sizeof(PageHeader) + PAGE_HEADER_BITMAP_SIZE - sizeof(char *));
static constexpr int PAGE_HEADER_SIZE = (sizeof(PageHeader));

RecordPageHandler   *RecordPageHandler::create(StorageFormat format)
{
  if (format == StorageFormat::ROW_FORMAT) {
    return new RowRecordPageHandler();
  } else {
    return new PaxRecordPageHandler();
  }
}
/**
 * @brief 8字节对齐
 * 注: ceiling(a / b) = floor((a + b - 1) / b)
 *
 * @param size 待对齐的字节数
 */
int align8(int size) { return (size + 7) & ~7; }

/**
 * @brief 计算指定大小的页面，可以容纳多少个记录
 *
 * @param page_size   页面的大小
 * @param record_size 记录的大小
 * @param fixed_size  除 PAGE_HEADER 外，页面中其余固定长度占用，目前为PAX存储格式中的
 *                    列偏移索引大小（column index）。
 */
int page_record_capacity(int page_size, int record_size, int fixed_size)
{
  // (record_capacity * record_size) + record_capacity/8 + 1 <= (page_size - fix_size)
  // ==> record_capacity = ((page_size - fix_size) - 1) / (record_size + 0.125)
  return (int)((page_size - PAGE_HEADER_SIZE - fixed_size - 1) / (record_size + 0.125));
}

/**
 * 与 page_record_capacity 类似，这个是返回 page 最大记录容量
*/
int get_page_record_max_size(int page_size, int fixed_size) {
  return (int)(page_size - PAGE_HEADER_SIZE - fixed_size - 1);
}

/**
 * @brief bitmap 记录了某个位置是否有有效的记录数据，这里给定记录个数时需要多少字节来存放bitmap数据
 * 注: ceiling(a / b) = floor((a + b - 1) / b)
 *
 * @param record_capacity 想要存放多少记录
 */
int page_bitmap_size(int record_capacity) { return (record_capacity + 7) / 8; }

string PageHeader::to_string() const
{
  stringstream ss;
  ss << "record_num:" << record_num << ",column_num:" << column_num;
  return ss.str();
}

////////////////////////////////////////////////////////////////////////////////
RecordPageIterator::RecordPageIterator() {}
RecordPageIterator::~RecordPageIterator() {}

void RecordPageIterator::init(RecordPageHandler *record_page_handler, SlotNum start_slot_num /*=0*/)
{
  record_page_handler_ = record_page_handler;
  page_num_            = record_page_handler->get_page_num();
  // bitmap_.init(record_page_handler->page_header_->bitmap, PAGE_HEADER_BITMAP_SIZE);
  // next_slot_num_ = bitmap_.next_setted_bit(start_slot_num);
  // 默认是第一个 record
  next_slot_num_ = PAGE_HEADER_SIZE;
}

bool RecordPageIterator::has_next() { return -1 != next_slot_num_; }

RC RecordPageIterator::next(Record &record)
{
  record_page_handler_->get_record(RID(page_num_, next_slot_num_), record);

  if (next_slot_num_ >= 0) {
    next_slot_num_ = bitmap_.next_setted_bit(next_slot_num_ + 1);
  }
  return record.rid().slot_num != -1 ? RC::SUCCESS : RC::RECORD_EOF;
}

////////////////////////////////////////////////////////////////////////////////

RecordPageHandler::~RecordPageHandler() { cleanup(); }

RC RecordPageHandler::init(DiskBufferPool &buffer_pool, LogHandler &log_handler, PageNum page_num, ReadWriteMode mode)
{
  if (disk_buffer_pool_ != nullptr) {
    if (frame_->page_num() == page_num) {
      LOG_WARN("Disk buffer pool has been opened for page_num %d.", page_num);
      return RC::RECORD_OPENNED;
    } else {
      cleanup();
    }
  }

  RC ret = RC::SUCCESS;
  if ((ret = buffer_pool.get_this_page(page_num, &frame_)) != RC::SUCCESS) {
    LOG_ERROR("Failed to get page handle from disk buffer pool. ret=%d:%s", ret, strrc(ret));
    return ret;
  }

  char *data = frame_->data();

  if (mode == ReadWriteMode::READ_ONLY) {
    frame_->read_latch();
  } else {
    frame_->write_latch();
  }
  disk_buffer_pool_ = &buffer_pool;

  rw_mode_     = mode;
  page_header_ = (PageHeader *)(data);

  (void)log_handler_.init(log_handler, buffer_pool.id(), storage_format_);

  LOG_TRACE("Successfully init page_num %d.", page_num);
  return ret;
}

RC RecordPageHandler::recover_init(DiskBufferPool &buffer_pool, PageNum page_num)
{
  if (disk_buffer_pool_ != nullptr) {
    LOG_WARN("Disk buffer pool has been opened for page_num %d.", page_num);
    return RC::RECORD_OPENNED;
  }

  RC ret = RC::SUCCESS;
  if ((ret = buffer_pool.get_this_page(page_num, &frame_)) != RC::SUCCESS) {
    LOG_ERROR("Failed to get page handle from disk buffer pool. ret=%d:%s", ret, strrc(ret));
    return ret;
  }

  char *data = frame_->data();

  frame_->write_latch();
  disk_buffer_pool_ = &buffer_pool;
  rw_mode_          = ReadWriteMode::READ_WRITE;
  page_header_      = (PageHeader *)(data);

  buffer_pool.recover_page(page_num);

  LOG_TRACE("Successfully init page_num %d.", page_num);
  return ret;
}

RC RecordPageHandler::init_empty_page(
    DiskBufferPool &buffer_pool, LogHandler &log_handler, PageNum page_num, TableMeta *table_meta)
{
  RC rc = init(buffer_pool, log_handler, page_num, ReadWriteMode::READ_WRITE);
  if (OB_FAIL(rc)) {
    LOG_ERROR("Failed to init empty page page_num: %d. rc=%s", page_num, strrc(rc));
    return rc;
  }

  (void)log_handler_.init(log_handler, buffer_pool.id(), storage_format_);

  int column_num = 0;
  // only pax format need column index
  if (table_meta != nullptr && storage_format_ == StorageFormat::PAX_FORMAT) {
    column_num = table_meta->field_num();
  }
  page_header_->record_num = 0;
  page_header_->column_num = column_num;
  page_header_->next_slot = PAGE_HEADER_SIZE;

  rc = log_handler_.init_new_page(frame_, page_num);
  if (OB_FAIL(rc)) {
    LOG_ERROR("Failed to init empty page: write log failed. page_num:%d. rc=%s", 
              page_num,  strrc(rc));
    return rc;
  }

  return RC::SUCCESS;
}

RC RecordPageHandler::init_empty_page(
    DiskBufferPool &buffer_pool, LogHandler &log_handler, PageNum page_num, int column_num /* =0 */)
{
  RC rc = init(buffer_pool, log_handler, page_num, ReadWriteMode::READ_WRITE);
  if (OB_FAIL(rc)) {
    LOG_ERROR("Failed to init empty page page_num:%d. rc=%s", page_num,  strrc(rc));
    return rc;
  }

  (void)log_handler_.init(log_handler, buffer_pool.id(), storage_format_);

  page_header_->record_num = 0;
  page_header_->column_num = column_num;
  page_header_->next_slot = PAGE_HEADER_SIZE;

  if (OB_FAIL(rc)) {
    LOG_ERROR("Failed to init empty page: write log failed. page_num:%d. rc=%s", 
              page_num,  strrc(rc));
    return rc;
  }

  return RC::SUCCESS;
}

RC RecordPageHandler::cleanup()
{
  if (disk_buffer_pool_ != nullptr) {
    if (rw_mode_ == ReadWriteMode::READ_ONLY) {
      frame_->read_unlatch();
    } else {
      frame_->write_unlatch();
    }
    disk_buffer_pool_->unpin_page(frame_);
    disk_buffer_pool_ = nullptr;
  }

  return RC::SUCCESS;
}

RC RowRecordPageHandler::insert_record(const char *data, const int record_size, RID *rid)
{
  ASSERT(rw_mode_ != ReadWriteMode::READ_ONLY, 
         "cannot insert record into page while the page is readonly");

  if (is_full()) {
    LOG_WARN("Page is full, page_num %d:%d.", disk_buffer_pool_->file_desc(), frame_->page_num());
    return RC::RECORD_NOMEM;
  }

  // 找到空闲位置
  auto next_slot = page_header_->next_slot;
  page_header_->record_num++;

  RC rc = log_handler_.insert_record(frame_, RID(get_page_num(), next_slot), data, record_size);
  if (OB_FAIL(rc)) {
    LOG_ERROR("Failed to insert record. page_num %d:%d. rc=%s", disk_buffer_pool_->file_desc(), frame_->page_num(), strrc(rc));
    // return rc; // ignore errors
  }

  auto info =  get_all_info(next_slot);
  ASSERT(info.size() == 4, "error info");

  bool  exists      = true;
  memcpy(info[0], &exists, sizeof(exists));
  memcpy(info[1], &record_size, sizeof(record_size));
  memcpy(info[2], data, record_size);
  RID tmp_rid = {BP_INVALID_PAGE_NUM, -1};
  memcpy(info[3], rid, sizeof(tmp_rid));

  frame_->mark_dirty();

  if (rid) {
    rid->page_num = get_page_num();
    rid->slot_num = next_slot;
  }

  page_header_->next_slot += (info[3] - info[0] + sizeof(RID));

  // LOG_TRACE("Insert record. rid page_num=%d, slot num=%d", get_page_num(), index);
  return RC::SUCCESS;
}

RC RowRecordPageHandler::recover_insert_record(const char *data, const int record_size, const RID &rid)
{
  if (is_full()) {
    LOG_WARN("Page is full, page_num %d:%d.", disk_buffer_pool_->file_desc(), frame_->page_num());
    return RC::RECORD_NOMEM;
  }

  auto info =  get_all_info(rid.slot_num);
  ASSERT(info.size() == 4, "error info");

  // 恢复数据
  bool  exists      = true;
  memcpy(info[0], &exists, sizeof(exists));
  memcpy(info[1], &record_size, sizeof(record_size));
  memcpy(info[2], data, record_size);
  RID tmp_rid = {BP_INVALID_PAGE_NUM, -1};
  memcpy(info[3], &rid, sizeof(tmp_rid));

  frame_->mark_dirty();

  return RC::SUCCESS;
}

RC RowRecordPageHandler::delete_record(const RID *rid)
{
  ASSERT(rw_mode_ != ReadWriteMode::READ_ONLY, 
         "cannot delete record from page while the page is readonly");

  char *record_data = get_record_data(rid->slot_num);
  bool  exists      = true;
  memcpy(&exists, record_data, sizeof(exists));
  if (!exists) {
    LOG_DEBUG("Invalid slot_num %d, slot is empty, page_num %d.", rid->slot_num, frame_->page_num());
    return RC::RECORD_NOT_EXIST;
  }

  page_header_->record_num--;
  frame_->mark_dirty();
  RC rc = log_handler_.delete_record(frame_, *rid);
  if (OB_FAIL(rc)) {
    LOG_ERROR("Failed to delete record. page_num %d:%d. rc=%s", disk_buffer_pool_->file_desc(), frame_->page_num(), strrc(rc));
    // return rc; // ignore errors
  }

  return RC::SUCCESS;
}

RC RowRecordPageHandler::update_record(const RID &rid, const char *data)
{
  return RC::UNIMPLEMENTED;
  // TODO(qiqi): 这个主要是针对 mvcc 和 trx 的，目前不予实现

  // ASSERT(rw_mode_ != ReadWriteMode::READ_ONLY, "cannot delete record from page while the page is readonly");

  // if (rid.slot_num >= page_header_->record_capacity) {
  //   LOG_ERROR("Invalid slot_num %d, exceed page's record capacity, frame=%s, page_header=%s",
  //             rid.slot_num, frame_->to_string().c_str(), page_header_->to_string().c_str());
  //   return RC::INVALID_ARGUMENT;
  // }

  // Bitmap bitmap(bitmap_, page_header_->record_capacity);
  // if (bitmap.get_bit(rid.slot_num)) {
  //   frame_->mark_dirty();

  //   char *record_data = get_record_data(rid.slot_num);
  //   if (record_data == data) {
  //     // nothing to do
  //   } else {
  //     memcpy(record_data, data, page_header_->record_real_size);
  //   }

  //   RC rc = log_handler_.update_record(frame_, rid, data);
  //   if (OB_FAIL(rc)) {
  //     LOG_ERROR("Failed to update record. page_num %d:%d. rc=%s", 
  //               disk_buffer_pool_->file_desc(), frame_->page_num(), strrc(rc));
  //     // return rc; // ignore errors
  //   }

  //   return RC::SUCCESS;
  // } else {
  //   LOG_DEBUG("Invalid slot_num %d, slot is empty, page_num %d.", rid.slot_num, frame_->page_num());
  //   return RC::RECORD_NOT_EXIST;
  // }
}

RC RowRecordPageHandler::get_record(const RID &rid, Record &record)
{
  char *record_data = get_record_data(rid.slot_num);
  bool  exists      = true;
  memcpy(&exists, record_data, sizeof(exists));
  record_data += sizeof(exists);
  if (!exists) {
    LOG_DEBUG("Invalid slot_num %d, slot is empty, page_num %d.", rid.slot_num, frame_->page_num());
    return RC::RECORD_NOT_EXIST;
  }

  int len = 0;
  memcpy(&len, record_data, sizeof(len));
  record_data += sizeof(len);

  record.set_rid(rid);
  record.set_data(record_data, len);
  return RC::SUCCESS;
}

void RowRecordPageHandler::set_next_rid(const RID *now_rid, const RID *next_rid)
{
  ASSERT(now_rid->page_num == next_rid->page_num, "page num should be equal");

  // 假设 record 存在
  auto info = get_all_info(now_rid->slot_num);
  ASSERT(info.size() == 4, "error info");

  memcpy(info[4], next_rid, sizeof(*next_rid));

  frame_->mark_dirty();
}

std::vector<char *> RowRecordPageHandler::get_all_info(const SlotNum &slot_num)
{
  std::vector<char *> res;
  char               *record_data = get_record_data(slot_num);
  // 1. 是否存在
  res.emplace_back(record_data);
  record_data += sizeof(bool);
  // 2. record 内容长度
  res.emplace_back(record_data);
  int record_size = 0;
  memcpy(&record_size, record_data, sizeof(record_size));
  record_data += sizeof(record_size);
  // 3. record 内容
  res.emplace_back(record_data);
  record_data += record_size;
  // 4. next rid
  res.emplace_back(record_data);

  return res;
}

PageNum RecordPageHandler::get_page_num() const
{
  if (nullptr == page_header_) {
    return (PageNum)(-1);
  }
  return frame_->page_num();
}

bool RecordPageHandler::is_full() const { return get_remain_record_space() <= 0; }

int32_t RecordPageHandler::get_remain_record_space() const
{
  return BP_PAGE_DATA_SIZE - page_header_->next_slot - MIN_PAGE_SPACE;
}

char *RecordPageHandler::get_record_data(SlotNum slot_num) { return frame_->data() + slot_num; }

RC PaxRecordPageHandler::insert_record(const char *data, RID *rid)
{
  // your code here
  exit(-1);
}

RC PaxRecordPageHandler::delete_record(const RID *rid)
{
  // TODO(qiqi): 暂不支持
  return RC::UNIMPLEMENTED;
  // ASSERT(rw_mode_ != ReadWriteMode::READ_ONLY, 
  //        "cannot delete record from page while the page is readonly");

  // Bitmap bitmap(bitmap_, page_header_->record_capacity);
  // if (bitmap.get_bit(rid->slot_num)) {
  //   bitmap.clear_bit(rid->slot_num);
  //   page_header_->record_num--;
  //   frame_->mark_dirty();

  //   RC rc = log_handler_.delete_record(frame_, *rid);
  //   if (OB_FAIL(rc)) {
  //     LOG_ERROR("Failed to delete record. page_num %d:%d. rc=%s", disk_buffer_pool_->file_desc(), frame_->page_num(), strrc(rc));
  //     // return rc; // ignore errors
  //   }

  //   return RC::SUCCESS;
  // } else {
  //   LOG_DEBUG("Invalid slot_num %d, slot is empty, page_num %d.", rid->slot_num, frame_->page_num());
  //   return RC::RECORD_NOT_EXIST;
  // }
}

RC PaxRecordPageHandler::get_record(const RID &rid, Record &record)
{
  // your code here
  exit(-1);
}

// TODO: specify the column_ids that chunk needed. currenly we get all columns
RC PaxRecordPageHandler::get_chunk(Chunk &chunk)
{
  // your code here
  exit(-1);
}

char *PaxRecordPageHandler::get_field_data(SlotNum slot_num, int col_id)
{
  // TODO(qiqi): 暂不支持
  ASSERT(false, "dont support it now");
  // int *col_idx = reinterpret_cast<int *>(frame_->data() + page_header_->col_idx_offset);
  // if (col_id == 0) {
  //   return frame_->data() + page_header_->data_offset + (get_field_len(col_id) * slot_num);
  // } else {
  //   return frame_->data() + page_header_->data_offset + col_idx[col_id - 1] + (get_field_len(col_id) * slot_num);
  // }
}

int PaxRecordPageHandler::get_field_len(int col_id)
{
  // TODO(qiqi): 暂不支持
  ASSERT(false, "dont support it now");
  // int *col_idx = reinterpret_cast<int *>(frame_->data() + page_header_->col_idx_offset);
  // if (col_id == 0) {
  //   return col_idx[col_id] / page_header_->record_capacity;
  // } else {
  //   return (col_idx[col_id] - col_idx[col_id - 1]) / page_header_->record_capacity;
  // }
}

////////////////////////////////////////////////////////////////////////////////

RecordFileHandler::~RecordFileHandler() { this->close(); }

RC RecordFileHandler::init(DiskBufferPool &buffer_pool, LogHandler &log_handler, TableMeta *table_meta)
{
  if (disk_buffer_pool_ != nullptr) {
    LOG_ERROR("record file handler has been openned.");
    return RC::RECORD_OPENNED;
  }

  disk_buffer_pool_ = &buffer_pool;
  log_handler_      = &log_handler;
  table_meta_       = table_meta;

  RC rc = init_free_pages();

  LOG_INFO("open record file handle done. rc=%s", strrc(rc));
  return RC::SUCCESS;
}

void RecordFileHandler::close()
{
  if (disk_buffer_pool_ != nullptr) {
    free_pages_.clear();
    disk_buffer_pool_ = nullptr;
    log_handler_      = nullptr;
    table_meta_       = nullptr;
  }
}

RC RecordFileHandler::init_free_pages()
{
  // 遍历当前文件上所有页面，找到没有满的页面
  // 这个效率很低，会降低启动速度
  // NOTE: 由于是初始化时的动作，所以不需要加锁控制并发

  RC rc = RC::SUCCESS;

  BufferPoolIterator bp_iterator;
  bp_iterator.init(*disk_buffer_pool_, 1);
  unique_ptr<RecordPageHandler> record_page_handler(RecordPageHandler::create(storage_format_));
  PageNum                       current_page_num = 0;

  while (bp_iterator.has_next()) {
    current_page_num = bp_iterator.next();

    rc = record_page_handler->init(*disk_buffer_pool_, *log_handler_, current_page_num, ReadWriteMode::READ_ONLY);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to init record page handler. page num=%d, rc=%d:%s", current_page_num, rc, strrc(rc));
      return rc;
    }

    if (!record_page_handler->is_full()) {
      free_pages_.insert(current_page_num);
    }
    record_page_handler->cleanup();
  }
  LOG_INFO("record file handler init free pages done. free page num=%d, rc=%s", free_pages_.size(), strrc(rc));
  return rc;
}

RC RecordFileHandler::insert_record(const char *data, int record_size, RID *rid)
{
  RC ret = RC::SUCCESS;

  // 对于过大的 record，需要分批处理
  auto remain_record_size = record_size;
  // 上一个 page 的 rid
  RID                           tmp_rid;
  RID                           last_rid;
  unique_ptr<RecordPageHandler> last_record_page_handler = nullptr;
  bool is_first = true;

reinsert:
  unique_ptr<RecordPageHandler> record_page_handler(RecordPageHandler::create(storage_format_));
  bool                          page_found       = false;
  PageNum                       current_page_num = 0;

  // 当前要访问free_pages对象，所以需要加锁。在非并发编译模式下，不需要考虑这个锁
  lock_.lock();

  // 找到没有填满的页面
  while (!free_pages_.empty()) {
    current_page_num = *free_pages_.begin();

    ret = record_page_handler->init(*disk_buffer_pool_, *log_handler_, current_page_num, ReadWriteMode::READ_WRITE);
    if (OB_FAIL(ret)) {
      lock_.unlock();
      LOG_WARN("failed to init record page handler. page num=%d, rc=%d:%s", current_page_num, ret, strrc(ret));
      return ret;
    }

    if (!record_page_handler->is_full()) {
      page_found = true;
      break;
    }
    record_page_handler->cleanup();
    free_pages_.erase(free_pages_.begin());
  }
  lock_.unlock();  // 如果找到了一个有效的页面，那么此时已经拿到了页面的写锁

  // 找不到就分配一个新的页面
  if (!page_found) {
    Frame *frame = nullptr;
    if ((ret = disk_buffer_pool_->allocate_page(&frame)) != RC::SUCCESS) {
      LOG_ERROR("Failed to allocate page while inserting record. ret:%d", ret);
      return ret;
    }

    current_page_num = frame->page_num();

    ret = record_page_handler->init_empty_page(*disk_buffer_pool_, *log_handler_, current_page_num, table_meta_);
    if (OB_FAIL(ret)) {
      frame->unpin();
      LOG_ERROR("Failed to init empty page. ret:%d", ret);
      // this is for allocate_page
      return ret;
    }

    // frame 在allocate_page的时候，是有一个pin的，在init_empty_page时又会增加一个，所以这里手动释放一个
    frame->unpin();

    // 这里的加锁顺序看起来与上面是相反的，但是不会出现死锁
    // 上面的逻辑是先加lock锁，然后加页面写锁，这里是先加上
    // 了页面写锁，然后加lock的锁，但是不会引起死锁。
    // 为什么？
    lock_.lock();
    free_pages_.insert(current_page_num);
    lock_.unlock();
  }

  // 找到空闲位置
  record_size = std::min(record_page_handler->get_remain_record_space(), record_size);
  RC rc = record_page_handler->insert_record(data, record_size, &tmp_rid);
  if (OB_FAIL(rc)) {
    // TODO(qiqi): 事实上，这里是有 bug 的，因为对于大 record 来说，部分已经成功插入，
    // 需要回滚，但是这里忽略这个问题
    LOG_ERROR("Failed to insert record and has not been rollback.");
    return rc;
  }

  // 把 page 连在一起
  if (!is_first) {
    last_record_page_handler->set_next_rid(&last_rid, &tmp_rid);
  } else {
    is_first = false;
    *rid = tmp_rid;
  }
  last_rid = tmp_rid;
  last_record_page_handler = std::move(record_page_handler);

  // 这时已经成功插入部分 record，开始插入其他部分
  remain_record_size -= record_size;
  data += record_size;
  if (remain_record_size > 0) {
    record_size = remain_record_size;
    goto reinsert;
  }

  return rc;
}

RC RecordFileHandler::recover_insert_record(const char *data, int record_size, const RID &rid)
{
  // recover 操作不需要对大数据进行特殊处理
  RC ret = RC::SUCCESS;

  unique_ptr<RecordPageHandler> record_page_handler(RecordPageHandler::create(storage_format_));

  ret = record_page_handler->recover_init(*disk_buffer_pool_, rid.page_num);
  if (OB_FAIL(ret)) {
    LOG_WARN("failed to init record page handler. page num=%d, rc=%s", rid.page_num, strrc(ret));
    return ret;
  }

  ret = record_page_handler->recover_insert_record(data, record_size, rid);
  if (OB_FAIL(ret)) {
    // TODO(qiqi): 事实上，这里是有 bug 的，因为对于大 record 来说，部分已经成功插入，
    // 需要回滚，但是这里忽略这个问题
    LOG_ERROR("Failed to recover insert record.");
    return ret;
  }
  return ret;
}

RC RecordFileHandler::delete_record(const RID *rid)
{
  RC rc = RC::SUCCESS;

  // 对于过大的 record，需要循环删除
  RID next_rid = *rid;
redelete:
  unique_ptr<RecordPageHandler> record_page_handler(RecordPageHandler::create(storage_format_));

  rc = record_page_handler->init(*disk_buffer_pool_, *log_handler_, next_rid.page_num, ReadWriteMode::READ_WRITE);
  if (OB_FAIL(rc)) {
    LOG_ERROR("Failed to init record page handler.page number=%d. rc=%s", next_rid.page_num, strrc(rc));
    return rc;
  }

  auto info = record_page_handler->get_all_info(next_rid.slot_num);
  ASSERT(info.size() == 4, "error info");
  RID tmp_rid;
  memcpy(&tmp_rid, info[3], sizeof(tmp_rid));

  rc = record_page_handler->delete_record(&next_rid);
  // 📢 这里注意要清理掉资源，否则会与insert_record中的加锁顺序冲突而可能出现死锁
  // delete record的加锁逻辑是拿到页面锁，删除指定记录，然后加上和释放record manager锁
  // insert record是加上 record manager锁，然后拿到指定页面锁再释放record manager锁
  // 
  // TODO(qiqi)：这里会存在并发问题，对于一个大 record 来说，如果这个 page 只删除了一部分，
  // 然后 cleanup，然后删除其他 page 上其余部分，这样可能在 cleanup 后、delete 前，被其他
  // 读取，会读到中间状态。但是如果等全部 delele 后 cleanup，可能会造成死锁
  record_page_handler->cleanup();
  if (OB_SUCC(rc)) {
    // 因为这里已经释放了页面锁，并发时，其它线程可能又把该页面填满了，那就不应该再放入 free_pages_
    // 中。但是这里可以不关心，因为在查找空闲页面时，会自动过滤掉已经满的页面
    lock_.lock();
    free_pages_.insert(next_rid.page_num);
    LOG_TRACE("add free page %d to free page list", next_rid.page_num);
    lock_.unlock();
  }

  next_rid = tmp_rid;
  if (next_rid.page_num != BP_INVALID_PAGE_NUM) {
    next_rid = tmp_rid;
    goto redelete;
  }
  return rc;
}

RC RecordFileHandler::get_record(const RID &rid, Record &record)
{
  // 对于过大的 record，需要循环
  RID         next_rid = rid;
  std::string res;
reget:
  unique_ptr<RecordPageHandler> page_handler(RecordPageHandler::create(storage_format_));

  RC rc = page_handler->init(*disk_buffer_pool_, *log_handler_, next_rid.page_num, ReadWriteMode::READ_WRITE);
  if (OB_FAIL(rc)) {
    LOG_ERROR("Failed to init record page handler.page number=%d", next_rid.page_num);
    return rc;
  }

  auto info = page_handler->get_all_info(next_rid.slot_num);
  ASSERT(info.size() == 4, "error info");
  RID tmp_rid;
  memcpy(&tmp_rid, info[3], sizeof(tmp_rid));

  Record inplace_record;
  rc = page_handler->get_record(next_rid, inplace_record);
  if (OB_FAIL(rc)) {
    LOG_WARN("failed to get record from record page handle. rid=%s, rc=%s", next_rid.to_string().c_str(), strrc(rc));
    return rc;
  }
  res.append(inplace_record.data(), inplace_record.len());

  next_rid = tmp_rid;
  if (next_rid.page_num != BP_INVALID_PAGE_NUM) {
    next_rid = tmp_rid;
    goto reget;
  }

  record.copy_data(res.c_str(), res.length());
  record.set_rid(rid);
  return rc;
}

RC RecordFileHandler::visit_record(const RID &rid, function<bool(Record &)> updater)
{
  return RC::UNIMPLEMENTED;
  // TODO(qiqi): 这个主要是针对 mvcc 和 trx 的，目前不予实现
  // 对于过大的 record，需要循环
//   RID  next_rid = rid;
//   std::string res;
// reget:
//   unique_ptr<RecordPageHandler> page_handler(RecordPageHandler::create(storage_format_));

//   RC rc = page_handler->init(*disk_buffer_pool_, *log_handler_, rid.page_num, ReadWriteMode::READ_WRITE);
//   if (OB_FAIL(rc)) {
//     LOG_ERROR("Failed to init record page handler.page number=%d", rid.page_num);
//     return rc;
//   }

//   Record inplace_record;
//   rc = page_handler->get_record(rid, inplace_record);
//   if (OB_FAIL(rc)) {
//     LOG_WARN("failed to get record from record page handle. rid=%s, rc=%s", rid.to_string().c_str(), strrc(rc));
//     return rc;
//   }
//   res.append(inplace_record.data(), inplace_record.len());

//   next_rid.page_num = page_handler->get_next_page_num();
//   // 过大数据的 slot num 永远为 0
//   next_rid.slot_num = 0;
//   if (next_rid.page_num != -1) {
//     goto reget;
//   }

//   // 需要将数据复制出来再修改，否则update_record调用失败但是实际上数据却更新成功了，
//   // 会导致数据库状态不正确
//   Record record;
//   record.copy_data(res.c_str(), res.length());
//   record.set_rid(rid);

//   bool updated = updater(record);
//   if (updated) {
//     rc = page_handler->update_record(rid, record.data());
//   }
//   return rc;
}

////////////////////////////////////////////////////////////////////////////////

RecordFileScanner::~RecordFileScanner() { close_scan(); }

RC RecordFileScanner::open_scan(Table *table, DiskBufferPool &buffer_pool, Trx *trx, LogHandler &log_handler,
    ReadWriteMode mode, ConditionFilter *condition_filter)
{
  close_scan();

  table_            = table;
  disk_buffer_pool_ = &buffer_pool;
  trx_              = trx;
  log_handler_      = &log_handler;
  rw_mode_          = mode;

  RC rc = bp_iterator_.init(buffer_pool, 1);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to init bp iterator. rc=%d:%s", rc, strrc(rc));
    return rc;
  }
  condition_filter_ = condition_filter;
  if (table == nullptr || table->table_meta().storage_format() == StorageFormat::ROW_FORMAT) {
    record_page_handler_ = new RowRecordPageHandler();
  } else {
    record_page_handler_ = new PaxRecordPageHandler();
  }

  return rc;
}

/**
 * @brief 从当前位置开始找到下一条有效的记录
 *
 * 如果当前页面还有记录没有访问，就遍历当前的页面。
 * 当前页面遍历完了，就遍历下一个页面，然后找到有效的记录
 */
RC RecordFileScanner::fetch_next_record()
{
  RC rc = RC::SUCCESS;
  if (record_page_iterator_.is_valid()) {
    // 当前页面还是有效的，尝试看一下是否有有效记录
    rc = fetch_next_record_in_page();
    if (rc == RC::SUCCESS || rc != RC::RECORD_EOF) {
      // 有有效记录：RC::SUCCESS
      // 或者出现了错误，rc != (RC::SUCCESS or RC::RECORD_EOF)
      // RECORD_EOF 表示当前页面已经遍历完了
      return rc;
    }
  }

  // 上个页面遍历完了，或者还没有开始遍历某个页面，那么就从一个新的页面开始遍历查找
  while (bp_iterator_.has_next()) {
    PageNum page_num = bp_iterator_.next();
    record_page_handler_->cleanup();
    rc = record_page_handler_->init(*disk_buffer_pool_, *log_handler_, page_num, rw_mode_);
    if (OB_FAIL(rc)) {
      LOG_WARN("failed to init record page handler. page_num=%d, rc=%s", page_num, strrc(rc));
      return rc;
    }

    record_page_iterator_.init(record_page_handler_);
    rc = fetch_next_record_in_page();
    if (rc == RC::SUCCESS || rc != RC::RECORD_EOF) {
      // 有有效记录：RC::SUCCESS
      // 或者出现了错误，rc != (RC::SUCCESS or RC::RECORD_EOF)
      // RECORD_EOF 表示当前页面已经遍历完了
      return rc;
    }
  }

  // 所有的页面都遍历完了，没有数据了
  next_record_.rid().slot_num = -1;
  record_page_handler_->cleanup();
  return RC::RECORD_EOF;
}

/**
 * @brief 遍历当前页面，尝试找到一条有效的记录
 */
RC RecordFileScanner::fetch_next_record_in_page()
{
  RC rc = RC::SUCCESS;
  while (record_page_iterator_.has_next()) {
    rc = record_page_iterator_.next(next_record_);
    if (rc != RC::SUCCESS) {
      const auto page_num = record_page_handler_->get_page_num();
      LOG_TRACE("failed to get next record from page. page_num=%d, rc=%s", page_num, strrc(rc));
      return rc;
    }

    // 如果有过滤条件，就用过滤条件过滤一下
    if (condition_filter_ != nullptr && !condition_filter_->filter(next_record_)) {
      continue;
    }

    // 如果是某个事务上遍历数据，还要看看事务访问是否有冲突
    if (trx_ == nullptr) {
      return rc;
    }

    // 让当前事务探测一下是否访问冲突，或者需要加锁、等锁等操作，由事务自己决定
    // TODO 把判断事务有效性的逻辑从Scanner中移除
    rc = trx_->visit_record(table_, next_record_, rw_mode_);
    if (rc == RC::RECORD_INVISIBLE) {
      // 可以参考MvccTrx，表示当前记录不可见
      // 这种模式仅在 readonly 事务下是有效的
      continue;
    }
    return rc;
  }

  next_record_.rid().slot_num = -1;
  return RC::RECORD_EOF;
}

RC RecordFileScanner::close_scan()
{
  if (disk_buffer_pool_ != nullptr) {
    disk_buffer_pool_ = nullptr;
  }

  if (condition_filter_ != nullptr) {
    condition_filter_ = nullptr;
  }
  if (record_page_handler_ != nullptr) {
    record_page_handler_->cleanup();
    delete record_page_handler_;
    record_page_handler_ = nullptr;
  }

  return RC::SUCCESS;
}

RC RecordFileScanner::next(Record &record)
{
  RC rc = fetch_next_record();
  if (OB_FAIL(rc)) {
    return rc;
  }

  record = next_record_;
  return RC::SUCCESS;
}

RC RecordFileScanner::update_current(const Record &record)
{
  if (record.rid() != next_record_.rid()) {
    return RC::INVALID_ARGUMENT;
  }

  return record_page_handler_->update_record(record.rid(), record.data());
}

ChunkFileScanner::~ChunkFileScanner() { close_scan(); }

RC ChunkFileScanner::close_scan()
{
  if (disk_buffer_pool_ != nullptr) {
    disk_buffer_pool_ = nullptr;
  }

  if (record_page_handler_ != nullptr) {
    record_page_handler_->cleanup();
    delete record_page_handler_;
    record_page_handler_ = nullptr;
  }

  return RC::SUCCESS;
}

RC ChunkFileScanner::open_scan_chunk(
    Table *table, DiskBufferPool &buffer_pool, LogHandler &log_handler, ReadWriteMode mode)
{
  close_scan();

  table_            = table;
  disk_buffer_pool_ = &buffer_pool;
  log_handler_      = &log_handler;
  rw_mode_          = mode;

  RC rc = bp_iterator_.init(buffer_pool, 1);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to init bp iterator. rc=%d:%s", rc, strrc(rc));
    return rc;
  }
  if (table == nullptr || table->table_meta().storage_format() == StorageFormat::ROW_FORMAT) {
    record_page_handler_ = new RowRecordPageHandler();
  } else {
    record_page_handler_ = new PaxRecordPageHandler();
  }

  return rc;
}

RC ChunkFileScanner::next_chunk(Chunk &chunk)
{
  RC rc = RC::SUCCESS;

  while (bp_iterator_.has_next()) {
    PageNum page_num = bp_iterator_.next();
    record_page_handler_->cleanup();
    rc = record_page_handler_->init(*disk_buffer_pool_, *log_handler_, page_num, rw_mode_);
    if (OB_FAIL(rc)) {
      LOG_WARN("failed to init record page handler. page_num=%d, rc=%s", page_num, strrc(rc));
      return rc;
    }
    rc = record_page_handler_->get_chunk(chunk);
    if (rc == RC::SUCCESS) {
      return rc;
    } else if (rc == RC::RECORD_EOF) {
      break;
    } else {
      LOG_WARN("failed to get chunk from page. page_num=%d, rc=%s", page_num, strrc(rc));
      return rc;
    }
  }

  record_page_handler_->cleanup();
  return RC::RECORD_EOF;
}

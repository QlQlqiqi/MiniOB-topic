/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2023/03/07.
//

#pragma once

#include "common/types.h"
#include <stdint.h>

using TrxID = int32_t;

static constexpr PageNum BP_INVALID_PAGE_NUM = -1;

static constexpr PageNum BP_HEADER_PAGE = 0;

// 当 page 剩余空间不大于此时，且要插入一个 record，那么就认为这个 page 已经满了，
// 新起一个 page
static constexpr const int MIN_PAGE_SPACE = (sizeof(bool) + sizeof(int) + sizeof(SlotNum) + sizeof(PageNum));

static constexpr const int BP_PAGE_SIZE      = (1 << 13);
static constexpr const int BP_PAGE_HEAD_SIZE = (sizeof(PageNum) + sizeof(LSN) + sizeof(CheckSum));
static constexpr const int BP_PAGE_DATA_SIZE = (BP_PAGE_SIZE - BP_PAGE_HEAD_SIZE);

/**
 * @brief 表示一个页面，可能放在内存或磁盘上
 * @ingroup BufferPool
 */
struct Page
{
  LSN      lsn;
  CheckSum check_sum;
  char     data[BP_PAGE_DATA_SIZE];
};

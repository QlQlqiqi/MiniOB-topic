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

/**
 * @brief 属性的类型
 * @details AttrType 枚举列出了属性的各种数据类型。
 */
enum class AttrType
{
  UNDEFINED,
  CHARS,     ///< 字符串类型
  INTS,      ///< 整数类型(4字节)
  FLOATS,    ///< 浮点数类型(4字节)
  BOOLEANS,  ///< boolean类型，当前不是由parser解析出来的，是程序内部使用的
  VECTORS,   ///< 向量类型
  // 这个 TEXTS 是给 field 准备的，不允许 value 使用 text
  TEXTS,     ///< text 类型
  DATES,
  NULLS,     ///< null 类型
  MAXTYPE,   ///< 请在 UNDEFINED 与 MAXTYPE 之间增加新类型
};

const char *attr_type_to_string(AttrType type);
AttrType    attr_type_from_string(const char *s);

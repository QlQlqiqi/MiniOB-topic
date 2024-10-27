//
// Created by QlQl on 2024/10/18.
//

#pragma once

#include "common/rc.h"

class SQLStageEvent;

/**
 * @brief 删除表的执行器
 * @ingroup Executor
 */
class DropViewExecutor
{
public:
  DropViewExecutor()          = default;
  virtual ~DropViewExecutor() = default;

  RC execute(SQLStageEvent *sql_event);
};
//
// Created by QlQl on 2024/10/18.
//

#include "sql/executor/drop_view_executor.h"

#include "common/log/log.h"
#include "event/session_event.h"
#include "event/sql_event.h"
#include "session/session.h"
#include "sql/stmt/drop_view_stmt.h"
#include "storage/db/db.h"

RC DropViewExecutor::execute(SQLStageEvent *sql_event)
{
  Stmt    *stmt    = sql_event->stmt();
  Session *session = sql_event->session_event()->session();
  ASSERT(stmt->type() == StmtType::DROP_VIEW,
      "drop view executor can not run this command: %d",
      static_cast<int>(stmt->type()));

  DropViewStmt *drop_view_stmt = static_cast<DropViewStmt *>(stmt);

  const char *view_name = drop_view_stmt->view_name().c_str();

  return session->get_current_db()->drop_view(view_name);
}

%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.hpp"
#include "sql/parser/lex_sql.h"
#include "sql/expr/expression.h"
#include "common/time/datetime.h"
#include "common/type/vector_type.h"

using namespace std;

string token_name(const char *sql_string, YYLTYPE *llocp)
{
  return string(sql_string + llocp->first_column, llocp->last_column - llocp->first_column + 1);
}

int yyerror(YYLTYPE *llocp, const char *sql_string, ParsedSqlResult *sql_result, yyscan_t scanner, const char *msg, bool flag = false)
{
  std::unique_ptr<ParsedSqlNode> error_sql_node = std::make_unique<ParsedSqlNode>(SCF_ERROR);
  error_sql_node->error.error_msg = msg;
  error_sql_node->error.line = llocp->first_line;
  error_sql_node->error.column = llocp->first_column;
  error_sql_node->error.flag = flag;
  sql_result->add_sql_node(std::move(error_sql_node));
  return 0;
}

ArithmeticExpr *create_arithmetic_expression(ArithmeticExpr::Type type,
                                             Expression *left,
                                             Expression *right,
                                             const char *sql_string,
                                             YYLTYPE *llocp)
{
  ArithmeticExpr *expr = new ArithmeticExpr(type, left, right);
  expr->set_name(token_name(sql_string, llocp));
  return expr;
}

UnboundAggregateExpr *create_aggregate_expression(const char* type,
                                                  Expression *child,
                                                  const char *sql_string,
                                                  YYLTYPE *llocp)
{
  UnboundAggregateExpr *expr = new UnboundAggregateExpr(type, child);
  expr->set_name(token_name(sql_string, llocp));
  return expr;
}

Expression *create_function_expression(const FunctionExpr::Type type,
                                       const char *sql_string,
                                       Expression *left,
                                       Expression *right,
                                       YYLTYPE *llocp)
{
  Expression *expr = new FunctionExpr(type, left, right);
  expr->set_name(token_name(sql_string, llocp));
  return expr;
}

Value *vec2val(const char *sql_string, YYLTYPE *llocp)
{
  auto str = token_name(sql_string, llocp);
  std::cout << str << std::endl;
  auto tmp = Value(str.c_str());
  auto result = new Value();
  DataType::type_instance(AttrType::CHARS)->cast_to(tmp, AttrType::VECTORS, *result);
  return result;
}

%}

%define api.pure full
%define parse.error verbose
/** 启用位置标识 **/
%locations
%lex-param { yyscan_t scanner }
/** 这些定义了在yyparse函数中的参数 **/
%parse-param { const char * sql_string }
%parse-param { ParsedSqlResult * sql_result }
%parse-param { void * scanner }

//标识tokens
%token  SEMICOLON
        BY
        CREATE
        DROP
        GROUP
        ORDER
        ASC
        HAVING
        TABLE
        TABLES
        INDEX
        CALC
        SELECT
        DESC
        SHOW
        SYNC
        INSERT
        DELETE
        UPDATE
        INNER
        JOIN
        LBRACE
        RBRACE
        COMMA
        TRX_BEGIN
        TRX_COMMIT
        TRX_ROLLBACK
        INT_T
        STRING_T
        FLOAT_T
        VECTOR_T
        TEXT_T
        IS
        NOT
        NULL_T
        DATE_T
        HELP
        EXIT
        DOT //QUOTE
        INTO
        VALUES
        FROM
        WHERE
        AND
        OR
        SET
        ON
        AS
        LOAD
        DATA
        INFILE
        EXPLAIN
        STORAGE
        FORMAT
        EQ
        LT
        GT
        LE
        GE
        NE
        LIKE
        COUNT
        SUM
        AVG
        MAX
        MIN
        L2_DISTANCE
        COSINE_DISTANCE
        INNER_PRODUCT
        IN
        EXISTS
        VECTORS
        QUOTE
        UNIQUE

/** union 中定义各种数据类型，真实生成的代码也是union类型，所以不能有非POD类型的数据 **/
%union {
  ParsedSqlNode *                            sql_node;
  Value *                                    value;
  enum CompOp                                comp;
  RelAttrSqlNode *                           rel_attr;
  std::vector<AttrInfoSqlNode> *             attr_infos;
  AttrInfoSqlNode *                          attr_info;
  Expression *                               expression;
  std::vector<std::unique_ptr<Expression>> * expression_list;
  std::vector<Value> *                       value_list;
  std::vector<RelAttrSqlNode> *              rel_attr_list;
  std::vector<std::string> *                 relation_list;
  std::vector<std::unique_ptr<OrderBySqlNode>>* order_by_list;
  OrderBySqlNode*                            order_unit;
  OrderOp                                    order_op;
  InnerJoinUnit*                             inner_join_unit;
  InnerJoinSqlNode*                          inner_join;
  char *                                     string;
  int                                        number;
  float                                      floats;
  bool                                       bools;
  std::vector<double> *                      double_list;
  double                                     float_number;
  KeyValueList *                             kv_list;
}

%token <number> NUMBER
%token <floats> FLOAT
%token <string> ID
%token <string> SSS
%token <string> DATE_STR
//非终结符

/** type 定义了各种解析后的结果输出的是什么类型。类型对应了 union 中的定义的成员变量名称 **/
%type <float_number>       float_number
%type <double_list>         double_list
%type <number>              type
%type <expression>          condition
%type <value>               value
%type <number>              number
%type <string>              relation
%type <string>              alias;
%type <comp>                comp_op
%type <comp>                exists_op
%type <rel_attr>            rel_attr
%type <attr_infos>          attr_def_list
%type <attr_info>           attr_def
%type <relation_list>       idx_col_list
%type <bools>               opt_null
%type <bools>               opt_unique
%type <value>               insert_value
%type <value_list>          value_list
%type <kv_list>             update_kv_list
%type <expression>          where
%type <string>              storage_format
%type <relation_list>       rel_list
%type <inner_join>          inner_join_list
%type <inner_join_unit>     inner_join_rel
%type <expression>          expression
%type <expression>          sub_query_expr
%type <expression>          aggregate_expr
%type <expression>          aggr_argument_list
%type <expression_list>     expression_list
%type <expression_list>     group_by
%type <expression>          opt_having
%type <order_by_list>       order_by_list
%type <order_by_list>       order_by
%type <order_unit>          order_unit
%type <order_op>            order_op
%type <sql_node>            calc_stmt
%type <sql_node>            select_stmt
%type <sql_node>            insert_stmt
%type <sql_node>            update_stmt
%type <sql_node>            delete_stmt
%type <sql_node>            create_table_stmt
%type <sql_node>            drop_table_stmt
%type <sql_node>            show_tables_stmt
%type <sql_node>            desc_table_stmt
%type <sql_node>            create_index_stmt
%type <sql_node>            drop_index_stmt
%type <sql_node>            sync_stmt
%type <sql_node>            begin_stmt
%type <sql_node>            commit_stmt
%type <sql_node>            rollback_stmt
%type <sql_node>            load_data_stmt
%type <sql_node>            explain_stmt
%type <sql_node>            set_variable_stmt
%type <sql_node>            help_stmt
%type <sql_node>            exit_stmt
%type <sql_node>            command_wrapper
// commands should be a list but I use a single command instead
%type <sql_node>            commands

%left OR
%left AND
%left EQ LT GT LE GE NE
%left '+' '-'
%left '*' '/'
%nonassoc UMINUS
%%

commands: command_wrapper opt_semicolon  //commands or sqls. parser starts here.
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>($1);
    sql_result->add_sql_node(std::move(sql_node));
  }
  ;

command_wrapper:
    calc_stmt
  | select_stmt
  | insert_stmt
  | update_stmt
  | delete_stmt
  | create_table_stmt
  | drop_table_stmt
  | show_tables_stmt
  | desc_table_stmt
  | create_index_stmt
  | drop_index_stmt
  | sync_stmt
  | begin_stmt
  | commit_stmt
  | rollback_stmt
  | load_data_stmt
  | explain_stmt
  | set_variable_stmt
  | help_stmt
  | exit_stmt
    ;

exit_stmt:      
    EXIT {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      $$ = new ParsedSqlNode(SCF_EXIT);
    };

help_stmt:
    HELP {
      $$ = new ParsedSqlNode(SCF_HELP);
    };

sync_stmt:
    SYNC {
      $$ = new ParsedSqlNode(SCF_SYNC);
    }
    ;

begin_stmt:
    TRX_BEGIN  {
      $$ = new ParsedSqlNode(SCF_BEGIN);
    }
    ;

commit_stmt:
    TRX_COMMIT {
      $$ = new ParsedSqlNode(SCF_COMMIT);
    }
    ;

rollback_stmt:
    TRX_ROLLBACK  {
      $$ = new ParsedSqlNode(SCF_ROLLBACK);
    }
    ;

drop_table_stmt:    /*drop table 语句的语法解析树*/
    DROP TABLE ID {
      $$ = new ParsedSqlNode(SCF_DROP_TABLE);
      $$->drop_table.relation_name = $3;
      free($3);
    };

show_tables_stmt:
    SHOW TABLES {
      $$ = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
    ;

desc_table_stmt:
    DESC ID  {
      $$ = new ParsedSqlNode(SCF_DESC_TABLE);
      $$->desc_table.relation_name = $2;
      free($2);
    }
    ;

create_index_stmt:    /*create index 语句的语法解析树*/
    CREATE opt_unique INDEX ID ON ID LBRACE ID idx_col_list RBRACE
    {
      $$ = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = $$->create_index;
      create_index.index_name = $4;
      create_index.relation_name = $6;
      create_index.unique = $2;
      create_index.attr_names.swap(*$9);
      create_index.attr_names.emplace_back($8);
      std::reverse(create_index.attr_names.begin(), create_index.attr_names.end());
      free($4);
      free($6);
      free($8);
      delete $9;
    }
    ;
opt_unique:
    /* empty */
    {
      $$ = false;
    }
    | UNIQUE
    {
      $$ = true;
    }
    ;
idx_col_list:
    /* empty */
    {
      $$ = new std::vector<std::string>;
    }
    | COMMA ID idx_col_list
    {
      $$ = $3;
      $$->emplace_back($2);
      free($2);
    }
    ;

drop_index_stmt:      /*drop index 语句的语法解析树*/
    DROP INDEX ID ON ID
    {
      $$ = new ParsedSqlNode(SCF_DROP_INDEX);
      $$->drop_index.index_name = $3;
      $$->drop_index.relation_name = $5;
      free($3);
      free($5);
    }
    ;
create_table_stmt:    /*create table 语句的语法解析树*/
    CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format
    {
      $$ = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = $$->create_table;
      create_table.relation_name = $3;
      free($3);

      std::vector<AttrInfoSqlNode> *src_attrs = $6;

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
        delete src_attrs;
      }
      create_table.attr_infos.emplace_back(*$5);
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete $5;
      if ($8 != nullptr) {
        create_table.storage_format = $8;
        free($8);
      }
    }
    ;
attr_def_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA attr_def attr_def_list
    {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<AttrInfoSqlNode>;
      }
      $$->emplace_back(*$2);
      delete $2;
    }
    ;
    
attr_def:
    ID type LBRACE number RBRACE opt_null
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = $6 == true;
      $$->high_vector = false;
      $$->dim = 0;
      // 如果是 vector，那么这里的 length 代表的是数量
      if($2 == static_cast<int>(AttrType::VECTORS)) {
        $$->dim = $4;
        // 如果其设置的 dim 过大，设置 vector 存储规则与 text 相同
        if($4 > VECTOR_HIGH_DIM) {
          $$->length += sizeof(uint64_t) + sizeof(int32_t);
          $$->high_vector = true;
        } else {
          $$->length += $4 * sizeof(double);
        }
      } else {
        $$->length += $4;
      }
      $$->nullable = $6;
      free($1);
    }
    | ID type opt_null
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      // 这块是 4 是因为 char 和 vector 需要用 ()
      $$->length = 4 + ($3 == true);
      $$->high_vector = false;
      $$->dim = 0;
      // 如果是 date，应该为 sizeof(common::DateTime)
      if($$->type == AttrType::DATES) {
        $$->length = sizeof(common::DateTime) + ($3 == true);
      }
      // 如果是 text，应该为 sizeof(uint64_t) + sizeof(int32_t)
      // 代表 text file 中 offset 和 text length
      else if($$->type == AttrType::TEXTS) {
        $$->length = sizeof(uint64_t) + sizeof(int32_t) + ($3 == true);
      }
      $$->nullable = $3;
      free($1);
    }
    ;

alias:
    /* empty */
    {
      $$ = nullptr;
    }
    |ID
    {
      $$ = $1;
    }
    | AS ID
    {
      $$ = $2;
    }
    ;
opt_null:
    /* empty */
    {
      // 根据 primary-null.result 来看，默认是 not null
      $$ = true;
    }
    | NOT NULL_T
    {
      $$ = false;
    }
    | NULL_T
    {
      $$ = true;
    }
    ;
number:
    NUMBER {$$ = $1;}
    ;
type:
    INT_T      { $$ = static_cast<int>(AttrType::INTS); }
    | STRING_T { $$ = static_cast<int>(AttrType::CHARS); }
    | FLOAT_T  { $$ = static_cast<int>(AttrType::FLOATS); }
    | VECTOR_T { $$ = static_cast<int>(AttrType::VECTORS); }
    | TEXT_T   { $$ = static_cast<int>(AttrType::TEXTS); }
    | DATE_T   { $$ = static_cast<int>(AttrType::DATES); }
    ;
insert_stmt:        /*insert   语句的语法解析树*/
    INSERT INTO ID VALUES LBRACE value value_list RBRACE 
    {
      $$ = new ParsedSqlNode(SCF_INSERT);
      $$->insertion.relation_name = $3;
      if ($7 != nullptr) {
        $$->insertion.values.swap(*$7);
        delete $7;
      }
      $$->insertion.values.emplace_back(*$6);
      std::reverse($$->insertion.values.begin(), $$->insertion.values.end());
      delete $6;
      free($3);
    }
    ;

value_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA insert_value value_list  { 
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<Value>;
      }
      $$->emplace_back(*$2);
      delete $2;
    }
    ;
insert_value: expression
    {
      auto tmp = new Value();
      if(!ArithmeticExpr::exp2value($1, tmp)) {
        delete $1;
        delete tmp;
        yyerror(&@$, sql_string, sql_result, scanner, "error");
        YYERROR;
      }
      delete $1;
      $$ = tmp;
    }
    ;

value:
    NUMBER {
      $$ = new Value((int)$1);
      @$ = @1;
    }
    |FLOAT {
      $$ = new Value((float)$1);
      @$ = @1;
    }
    |DATE_STR{
      char *tmp = common::substr($1, 1, strlen($1)-2);
      std::string str(tmp);
      common::DateTime date_time(str);
      if(!common::DateTime::is_valid_date(str))
      {
        yyerror(&@$,sql_string,sql_result,scanner,"date invaid",true);
        YYERROR;
      }else
      {
        $$ = new Value(date_time);
      }

    }
    | '[' double_list ']'
    {
      $$ = vec2val(sql_string, &@$);
    }
    |SSS {
      char *tmp = common::substr($1,1,strlen($1)-2);
      $$ = new Value(tmp);
      free(tmp);
      free($1);
    }
    | NULL_T {
      $$ = new Value();
      $$->set_null();
    }
    ;
storage_format:
    /* empty */
    {
      $$ = nullptr;
    }
    | STORAGE FORMAT EQ ID
    {
      $$ = $4;
    }
    ;
double_list: {
      $$ = new std::vector<double>();
    }
    | float_number {
      $$ = new std::vector<double>();
      $$->emplace_back($1);
    }
    | double_list COMMA float_number {
      $$ = $1;
      $$->emplace_back($3);
    }
    ;
float_number: NUMBER {
      $$ = $1;
    }
    | FLOAT {
      $$ = $1;
    }
    ;
delete_stmt:    /*  delete 语句的语法解析树*/
    DELETE FROM ID alias where 
    {
      $$ = new ParsedSqlNode(SCF_DELETE);
      $$->deletion.relation_name = $3;
      if($4 != nullptr){
      $$->deletion.relation_alias = $4;
      }
      $$->deletion.conditions = $5;
      free($3);
      free($4);
    }
    ;
update_stmt:      /*  update 语句的语法解析树*/
    UPDATE ID alias SET update_kv_list where 
    {
      $$ = new ParsedSqlNode(SCF_UPDATE);
      $$->update.relation_name = $2;
      if($3 != nullptr){
        $$->update.relation_alias = $3;
      }
      $$->update.attribute_name.swap($5->attrs);
      $$->update.value.swap($5->values);
      $$->update.conditions = $6;
      free($2);
      free($3);
      delete($5);
    }
    ;
update_kv_list:
    ID EQ expression
    {
      $$ = new KeyValueList{};
      $$->attrs.emplace_back($1);
      $$->values.emplace_back($3);
      free($1);
    }
    | update_kv_list COMMA ID EQ expression
    {
      $$ = $1;
      $$->attrs.emplace_back($3);
      $$->values.emplace_back($5);
      free($3);
    }
    ;

select_stmt:        /*  select 语句的语法解析树*/
    SELECT expression_list FROM rel_list inner_join_list where group_by opt_having order_by
    {
      $$ = new ParsedSqlNode(SCF_SELECT);
      if ($2 != nullptr) {
        $$->selection.expressions.swap(*$2);
        delete $2;
      }

      if ($4 != nullptr) {
        if($5 != nullptr && $4->size() != 2){
          yyerror(&@$,sql_string,sql_result,scanner,"inner join only support one table",true);
          delete $4;
          YYERROR;
        }
        $$->selection.relations.swap(*$4);
        delete $4;
      }

      if($5 != nullptr){
        $$->selection.inner_join.reset($5);
      }

      if ($6 != nullptr) {
        $$->selection.conditions.reset($6);
      }

      if ($7 != nullptr) {
        $$->selection.group_by.swap(*$7);
        delete $7;
      }

      if($8 != nullptr){
        $$->selection.having_conditions.reset($8);
      }

      if($9 != nullptr){
        $$->selection.order_by.swap(*$9);
        delete $9;
      }
    }
    | SELECT expression_list
    {
      $$ = new ParsedSqlNode(SCF_CALC);
      std::reverse($2->begin(), $2->end());
      $$->calc.expressions.swap(*$2);
      delete $2;
    }

    ;
calc_stmt:
    CALC expression_list
    {
      $$ = new ParsedSqlNode(SCF_CALC);
      $$->calc.expressions.swap(*$2);
      delete $2;
    }
    ;

expression_list:
    expression alias
    {
      $$ = new std::vector<std::unique_ptr<Expression>>;
      $$->emplace_back($1);
      if($2 != nullptr){
        $1->set_alias($2);
        free($2);
      }
    }
    | expression alias COMMA expression_list
    {
      if ($4 != nullptr) {
        $$ = $4;
      } else {
        $$ = new std::vector<std::unique_ptr<Expression>>;
      }
      if($2 != nullptr){
        $1->set_alias($2);
        free($2);
      }
      $$->emplace($$->begin(), $1);
    }
    ;

aggr_argument_list:
  /* empty */
  {
    $$ = nullptr;
  }
  | expression alias
  {
    if($2 != nullptr){
      $1->set_alias($2);
      free($2);
    }
    $$ = $1;
  }
  | expression alias COMMA expression_list
  {
    $$ = nullptr;
    delete $1;
    free($2);
    delete $4;
  }
  ;

expression:
    expression '+' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::ADD, $1, $3, sql_string, &@$);
    }
    | expression '-' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::SUB, $1, $3, sql_string, &@$);
    }
    | expression '*' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::MUL, $1, $3, sql_string, &@$);
    }
    | expression '/' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::DIV, $1, $3, sql_string, &@$);
    }
    | LBRACE expression_list RBRACE {
      if ($2->size() == 1) {
        $$ = $2->front().release();
      } else {
        $$ = new ExprListExpr(std::move(*$2));
      }
      $$->set_name(token_name(sql_string, &@$));
      delete $2;
    }
    | '-' expression %prec UMINUS {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, $2, nullptr, sql_string, &@$);
    }
    | value {
      $$ = new ValueExpr(*$1);
      $$->set_name(token_name(sql_string, &@$));
      delete $1;
    }
    | rel_attr {
      RelAttrSqlNode *node = $1;
      $$ = new UnboundFieldExpr(node->relation_name, node->attribute_name);
      $$->set_name(token_name(sql_string, &@$));
      delete $1;
    }
    | L2_DISTANCE LBRACE expression COMMA expression RBRACE {
      $$ = create_function_expression(FunctionExpr::Type::L2_DISTANCE, sql_string, $3, $5, &@$);
    }
    | COSINE_DISTANCE LBRACE expression COMMA expression RBRACE {
      $$ = create_function_expression(FunctionExpr::Type::COSINE_DISTANCE, sql_string, $3, $5, &@$);
    }
    | INNER_PRODUCT LBRACE expression COMMA expression RBRACE {
      $$ = create_function_expression(FunctionExpr::Type::INNER_PRODUCT, sql_string, $3, $5, &@$);
    }
    | aggregate_expr {
      $$ = $1;
    }
    | sub_query_expr {
      $$ = $1;
    }
    | '*' {
      $$ = new StarExpr();
    }
    ;

aggregate_expr:
    COUNT LBRACE aggr_argument_list RBRACE {
      $$ = create_aggregate_expression("count", $3, sql_string, &@$);
    }
    | SUM LBRACE aggr_argument_list RBRACE {
      $$ = create_aggregate_expression("sum", $3, sql_string, &@$);
    }
    | AVG LBRACE aggr_argument_list RBRACE {
      $$ = create_aggregate_expression("avg", $3, sql_string, &@$);
    }
    | MIN LBRACE aggr_argument_list RBRACE {
      $$ = create_aggregate_expression("min", $3, sql_string, &@$);
    }
    | MAX LBRACE aggr_argument_list RBRACE {
      $$ = create_aggregate_expression("max", $3, sql_string, &@$);
    }

sub_query_expr:
    LBRACE select_stmt RBRACE
    {
      $$ = new SubQueryExpr(std::move($2->selection));
      delete $2;
    }
    ;

rel_attr:
    ID {
      $$ = new RelAttrSqlNode;
      $$->attribute_name = $1;
      free($1);
    }
    | ID DOT ID {
      $$ = new RelAttrSqlNode;
      $$->relation_name  = $1;
      $$->attribute_name = $3;
      free($1);
      free($3);
    }
    | ID DOT '*' {
      $$ = new RelAttrSqlNode;
      $$->relation_name  = $1;
      $$->attribute_name = "*";
      free($1);
    }
    ;

relation:
    ID {
      $$ = $1;
    }
    ;
rel_list:
    relation alias{
      $$ = new std::vector<std::string>();
      $$->push_back($1);
      if($2 != nullptr){
        $$->push_back($2); //存在别名
      }else{
        $$->push_back(""); //别名为空
      }
      free($1);
    }
    | relation alias COMMA rel_list { 
      if ($4 != nullptr) {
        $$ = $4;
      } else {
        $$ = new std::vector<std::string>;
      }

//Todo 改变遍历顺序
      if($2 != nullptr){
        $$->insert($$->begin(), $2); 
      }else{
        $$->insert($$->begin(),"");
      }
      $$->insert($$->begin(), $1);
      free($1);
    }
    ;

inner_join_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | inner_join_list inner_join_rel 
    {
      if($1 == nullptr){
        $$ = new InnerJoinSqlNode();
      }else{
        $$ = $1;
      }
      $$->relations.emplace_back($2->relation);
      $$->relations.emplace_back($2->relation_alias);
      $$->conditions.emplace_back(std::move($2->condition));
      delete $2;
    }
    ;
inner_join_rel:
    INNER JOIN relation alias ON condition{
      $$ = new InnerJoinUnit($3); 
      if($4 != nullptr){
        $$->relation_alias = $4;
        free($4);
      }else{
        $$->relation_alias = "";
      }
      $$->condition.reset($6); 
      free($3);
    }
    ;
  

where:
    /* empty */
    {
      $$ = nullptr;
    }
    | WHERE condition {
      $$ = $2;  
    }
    ;
condition:
    expression comp_op expression
    {
      $$ = new ComparisonExpr($2, $1, $3);
    }
    | exists_op expression
    {
      Value val;
      val.set_null();
      ValueExpr *value_expr = new ValueExpr(val);
      $$ = new ComparisonExpr($1, value_expr, $2);
    }
    | expression IS opt_null
    {
      Value val;
      val.set_null();
      ValueExpr *value_expr = new ValueExpr(val);
      $$ = new ComparisonExpr($3 ? IS_NULL : IS_NOT_NULL, $1, value_expr);
    }
    | condition AND condition
    {
      $$ = new ConjunctionExpr(ConjunctionExpr::Type::AND, $1, $3);
    }
    | condition OR condition
    {
      $$ = new ConjunctionExpr(ConjunctionExpr::Type::OR, $1, $3);
    }
    ;

comp_op:
      EQ { $$ = EQUAL_TO; }
    | LT { $$ = LESS_THAN; }
    | GT { $$ = GREAT_THAN; }
    | LE { $$ = LESS_EQUAL; }
    | LT GT { $$ = NOT_EQUAL; }
    | GE { $$ = GREAT_EQUAL; }
    | NE { $$ = NOT_EQUAL; }
    | LIKE { $$ = LIKE_OP; }
    | NOT LIKE { $$ = NOT_LIKE_OP; }
    | IN { $$ = IN_OP; }
    | NOT IN { $$ = NOT_IN_OP; }
    ;

exists_op:
  EXISTS { $$ = EXISTS_OP; }
  | NOT EXISTS { $$ = NOT_EXISTS_OP; }
  ;

group_by:
    /* empty */
    {
      $$ = nullptr;
    }
    | GROUP BY expression_list
    {
      $$ = $3;
    }
    ;

opt_having:
  /* empty */
  {
    $$ = nullptr;
  }
  | HAVING condition
  {
    $$ = $2;
  }

// your code here
order_by:
    /* empty */
    {
      $$ = nullptr;
    }
    | ORDER BY order_by_list
    {
      $$ = $3;
      std::reverse($$->begin(), $$->end());
    }
    ;

order_by_list:
    order_unit
    {
      $$ = new std::vector<std::unique_ptr<OrderBySqlNode>>();
      $$->emplace_back($1);
    }
    | order_unit COMMA order_by_list
    {
      $$ = $3;
      $$->emplace_back($1);
    }

order_unit:
    rel_attr order_op
    {
      $$ = new OrderBySqlNode;
      RelAttrSqlNode *node = $1;
      $$->unbound_field = std::make_unique<UnboundFieldExpr>(node->relation_name, node->attribute_name);
      $$->order_op = $2;
      delete $1;
    }
order_op:
    {
      $$ = OrderOp::ASC;
    }
    | ASC 
    {
      $$ = OrderOp::ASC;
    }
    | DESC
    {
      $$ = OrderOp::DESC;
    }

load_data_stmt:
    LOAD DATA INFILE SSS INTO TABLE ID 
    {
      char *tmp_file_name = common::substr($4, 1, strlen($4) - 2);
      
      $$ = new ParsedSqlNode(SCF_LOAD_DATA);
      $$->load_data.relation_name = $7;
      $$->load_data.file_name = tmp_file_name;
      free($7);
      free(tmp_file_name);
    }
    ;

explain_stmt:
    EXPLAIN command_wrapper
    {
      $$ = new ParsedSqlNode(SCF_EXPLAIN);
      $$->explain.sql_node = std::unique_ptr<ParsedSqlNode>($2);
    }
    ;

set_variable_stmt:
    SET ID EQ value
    {
      $$ = new ParsedSqlNode(SCF_SET_VARIABLE);
      $$->set_variable.name  = $2;
      $$->set_variable.value = *$4;
      free($2);
      delete $4;
    }
    ;

opt_semicolon: /*empty*/
    | SEMICOLON
    ;
%%
//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, ParsedSqlResult *sql_result) {
  yyscan_t scanner;
  yylex_init(&scanner);
  scan_string(s, scanner);
  int result = yyparse(s, sql_result, scanner);
  yylex_destroy(scanner);
  return result;
}

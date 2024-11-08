/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_YACC_SQL_HPP_INCLUDED
# define YY_YY_YACC_SQL_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    SEMICOLON = 258,
    BY = 259,
    CREATE = 260,
    DROP = 261,
    GROUP = 262,
    ORDER = 263,
    ASC = 264,
    HAVING = 265,
    TABLE = 266,
    TABLES = 267,
    VIEW = 268,
    INDEX = 269,
    CALC = 270,
    SELECT = 271,
    DESC = 272,
    SHOW = 273,
    SYNC = 274,
    INSERT = 275,
    DELETE = 276,
    UPDATE = 277,
    INNER = 278,
    JOIN = 279,
    LBRACE = 280,
    RBRACE = 281,
    COMMA = 282,
    TRX_BEGIN = 283,
    TRX_COMMIT = 284,
    TRX_ROLLBACK = 285,
    INT_T = 286,
    STRING_T = 287,
    FLOAT_T = 288,
    VECTOR_T = 289,
    WITH_T = 290,
    DISTANCE_T = 291,
    TYPE_T = 292,
    IVFFLAT_T = 293,
    LISTS_T = 294,
    PROBES_T = 295,
    TEXT_T = 296,
    IS = 297,
    NOT = 298,
    NULL_T = 299,
    DATE_T = 300,
    HELP = 301,
    EXIT = 302,
    DOT = 303,
    INTO = 304,
    VALUES = 305,
    FROM = 306,
    WHERE = 307,
    AND = 308,
    OR = 309,
    SET = 310,
    ON = 311,
    AS = 312,
    LOAD = 313,
    DATA = 314,
    INFILE = 315,
    EXPLAIN = 316,
    STORAGE = 317,
    FORMAT = 318,
    EQ = 319,
    LT = 320,
    GT = 321,
    LE = 322,
    GE = 323,
    NE = 324,
    LIKE = 325,
    COUNT = 326,
    SUM = 327,
    AVG = 328,
    MAX = 329,
    MIN = 330,
    L2_DISTANCE = 331,
    COSINE_DISTANCE = 332,
    INNER_PRODUCT = 333,
    IN = 334,
    EXISTS = 335,
    VECTORS = 336,
    QUOTE = 337,
    UNIQUE = 338,
    LIMIT = 339,
    NUMBER = 340,
    FLOAT = 341,
    ID = 342,
    SSS = 343,
    DATE_STR = 344,
    UMINUS = 345
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 175 "yacc_sql.y"

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
  std::vector<std::string> *                 id_list;
  std::vector<std::unique_ptr<OrderBySqlNode>>* order_by_list;
  LimitSqlNode *                             limit;
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
  VectorIndexWith *                          vector_index_with;

#line 177 "yacc_sql.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif



int yyparse (const char * sql_string, ParsedSqlResult * sql_result, void * scanner);

#endif /* !YY_YY_YACC_SQL_HPP_INCLUDED  */

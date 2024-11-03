/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_YACC_SQL_HPP_INCLUDED
# define YY_YY_YACC_SQL_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    SEMICOLON = 258,               /* SEMICOLON  */
    BY = 259,                      /* BY  */
    CREATE = 260,                  /* CREATE  */
    DROP = 261,                    /* DROP  */
    GROUP = 262,                   /* GROUP  */
    ORDER = 263,                   /* ORDER  */
    ASC = 264,                     /* ASC  */
    HAVING = 265,                  /* HAVING  */
    TABLE = 266,                   /* TABLE  */
    TABLES = 267,                  /* TABLES  */
    INDEX = 268,                   /* INDEX  */
    CALC = 269,                    /* CALC  */
    SELECT = 270,                  /* SELECT  */
    DESC = 271,                    /* DESC  */
    SHOW = 272,                    /* SHOW  */
    SYNC = 273,                    /* SYNC  */
    INSERT = 274,                  /* INSERT  */
    DELETE = 275,                  /* DELETE  */
    UPDATE = 276,                  /* UPDATE  */
    INNER = 277,                   /* INNER  */
    JOIN = 278,                    /* JOIN  */
    LBRACE = 279,                  /* LBRACE  */
    RBRACE = 280,                  /* RBRACE  */
    COMMA = 281,                   /* COMMA  */
    TRX_BEGIN = 282,               /* TRX_BEGIN  */
    TRX_COMMIT = 283,              /* TRX_COMMIT  */
    TRX_ROLLBACK = 284,            /* TRX_ROLLBACK  */
    INT_T = 285,                   /* INT_T  */
    STRING_T = 286,                /* STRING_T  */
    FLOAT_T = 287,                 /* FLOAT_T  */
    VECTOR_T = 288,                /* VECTOR_T  */
    TEXT_T = 289,                  /* TEXT_T  */
    IS = 290,                      /* IS  */
    NOT = 291,                     /* NOT  */
    NULL_T = 292,                  /* NULL_T  */
    DATE_T = 293,                  /* DATE_T  */
    HELP = 294,                    /* HELP  */
    EXIT = 295,                    /* EXIT  */
    DOT = 296,                     /* DOT  */
    INTO = 297,                    /* INTO  */
    VALUES = 298,                  /* VALUES  */
    FROM = 299,                    /* FROM  */
    WHERE = 300,                   /* WHERE  */
    AND = 301,                     /* AND  */
    OR = 302,                      /* OR  */
    SET = 303,                     /* SET  */
    ON = 304,                      /* ON  */
    AS = 305,                      /* AS  */
    LOAD = 306,                    /* LOAD  */
    DATA = 307,                    /* DATA  */
    INFILE = 308,                  /* INFILE  */
    EXPLAIN = 309,                 /* EXPLAIN  */
    STORAGE = 310,                 /* STORAGE  */
    FORMAT = 311,                  /* FORMAT  */
    EQ = 312,                      /* EQ  */
    LT = 313,                      /* LT  */
    GT = 314,                      /* GT  */
    LE = 315,                      /* LE  */
    GE = 316,                      /* GE  */
    NE = 317,                      /* NE  */
    LIKE = 318,                    /* LIKE  */
    COUNT = 319,                   /* COUNT  */
    SUM = 320,                     /* SUM  */
    AVG = 321,                     /* AVG  */
    MAX = 322,                     /* MAX  */
    MIN = 323,                     /* MIN  */
    L2_DISTANCE = 324,             /* L2_DISTANCE  */
    COSINE_DISTANCE = 325,         /* COSINE_DISTANCE  */
    INNER_PRODUCT = 326,           /* INNER_PRODUCT  */
    IN = 327,                      /* IN  */
    EXISTS = 328,                  /* EXISTS  */
    VECTORS = 329,                 /* VECTORS  */
    QUOTE = 330,                   /* QUOTE  */
    UNIQUE = 331,                  /* UNIQUE  */
    NUMBER = 332,                  /* NUMBER  */
    FLOAT = 333,                   /* FLOAT  */
    ID = 334,                      /* ID  */
    SSS = 335,                     /* SSS  */
    DATE_STR = 336,                /* DATE_STR  */
    UMINUS = 337                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 167 "yacc_sql.y"

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

#line 172 "yacc_sql.hpp"

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

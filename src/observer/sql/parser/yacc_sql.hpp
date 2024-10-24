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
    TABLE = 265,                   /* TABLE  */
    TABLES = 266,                  /* TABLES  */
    INDEX = 267,                   /* INDEX  */
    CALC = 268,                    /* CALC  */
    SELECT = 269,                  /* SELECT  */
    DESC = 270,                    /* DESC  */
    SHOW = 271,                    /* SHOW  */
    SYNC = 272,                    /* SYNC  */
    INSERT = 273,                  /* INSERT  */
    DELETE = 274,                  /* DELETE  */
    UPDATE = 275,                  /* UPDATE  */
    INNER = 276,                   /* INNER  */
    JOIN = 277,                    /* JOIN  */
    LBRACE = 278,                  /* LBRACE  */
    RBRACE = 279,                  /* RBRACE  */
    COMMA = 280,                   /* COMMA  */
    TRX_BEGIN = 281,               /* TRX_BEGIN  */
    TRX_COMMIT = 282,              /* TRX_COMMIT  */
    TRX_ROLLBACK = 283,            /* TRX_ROLLBACK  */
    INT_T = 284,                   /* INT_T  */
    STRING_T = 285,                /* STRING_T  */
    FLOAT_T = 286,                 /* FLOAT_T  */
    VECTOR_T = 287,                /* VECTOR_T  */
    IS = 288,                      /* IS  */
    NOT = 289,                     /* NOT  */
    NULL_T = 290,                  /* NULL_T  */
    DATE_T = 291,                  /* DATE_T  */
    HELP = 292,                    /* HELP  */
    EXIT = 293,                    /* EXIT  */
    DOT = 294,                     /* DOT  */
    INTO = 295,                    /* INTO  */
    VALUES = 296,                  /* VALUES  */
    FROM = 297,                    /* FROM  */
    WHERE = 298,                   /* WHERE  */
    AND = 299,                     /* AND  */
    OR = 300,                      /* OR  */
    SET = 301,                     /* SET  */
    ON = 302,                      /* ON  */
    LOAD = 303,                    /* LOAD  */
    DATA = 304,                    /* DATA  */
    INFILE = 305,                  /* INFILE  */
    EXPLAIN = 306,                 /* EXPLAIN  */
    STORAGE = 307,                 /* STORAGE  */
    FORMAT = 308,                  /* FORMAT  */
    EQ = 309,                      /* EQ  */
    LT = 310,                      /* LT  */
    GT = 311,                      /* GT  */
    LE = 312,                      /* LE  */
    GE = 313,                      /* GE  */
    NE = 314,                      /* NE  */
    LIKE = 315,                    /* LIKE  */
    COUNT = 316,                   /* COUNT  */
    SUM = 317,                     /* SUM  */
    AVG = 318,                     /* AVG  */
    MAX = 319,                     /* MAX  */
    MIN = 320,                     /* MIN  */
    L2_DISTANCE = 321,             /* L2_DISTANCE  */
    COSINE_DISTANCE = 322,         /* COSINE_DISTANCE  */
    INNER_PRODUCT = 323,           /* INNER_PRODUCT  */
    VECTORS = 324,                 /* VECTORS  */
    QUOTE = 325,                   /* QUOTE  */
    NUMBER = 326,                  /* NUMBER  */
    FLOAT = 327,                   /* FLOAT  */
    ID = 328,                      /* ID  */
    SSS = 329,                     /* SSS  */
    DATE_STR = 330,                /* DATE_STR  */
    UMINUS = 331                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 160 "yacc_sql.y"

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

#line 165 "yacc_sql.hpp"

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

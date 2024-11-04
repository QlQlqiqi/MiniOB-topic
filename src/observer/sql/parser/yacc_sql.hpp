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
    WITH_T = 289,                  /* WITH_T  */
    DISTANCE_T = 290,              /* DISTANCE_T  */
    TYPE_T = 291,                  /* TYPE_T  */
    IVFFLAT_T = 292,               /* IVFFLAT_T  */
    LISTS_T = 293,                 /* LISTS_T  */
    PROBES_T = 294,                /* PROBES_T  */
    TEXT_T = 295,                  /* TEXT_T  */
    IS = 296,                      /* IS  */
    NOT = 297,                     /* NOT  */
    NULL_T = 298,                  /* NULL_T  */
    DATE_T = 299,                  /* DATE_T  */
    HELP = 300,                    /* HELP  */
    EXIT = 301,                    /* EXIT  */
    DOT = 302,                     /* DOT  */
    INTO = 303,                    /* INTO  */
    VALUES = 304,                  /* VALUES  */
    FROM = 305,                    /* FROM  */
    WHERE = 306,                   /* WHERE  */
    AND = 307,                     /* AND  */
    OR = 308,                      /* OR  */
    SET = 309,                     /* SET  */
    ON = 310,                      /* ON  */
    AS = 311,                      /* AS  */
    LOAD = 312,                    /* LOAD  */
    DATA = 313,                    /* DATA  */
    INFILE = 314,                  /* INFILE  */
    EXPLAIN = 315,                 /* EXPLAIN  */
    STORAGE = 316,                 /* STORAGE  */
    FORMAT = 317,                  /* FORMAT  */
    EQ = 318,                      /* EQ  */
    LT = 319,                      /* LT  */
    GT = 320,                      /* GT  */
    LE = 321,                      /* LE  */
    GE = 322,                      /* GE  */
    NE = 323,                      /* NE  */
    LIKE = 324,                    /* LIKE  */
    COUNT = 325,                   /* COUNT  */
    SUM = 326,                     /* SUM  */
    AVG = 327,                     /* AVG  */
    MAX = 328,                     /* MAX  */
    MIN = 329,                     /* MIN  */
    L2_DISTANCE = 330,             /* L2_DISTANCE  */
    COSINE_DISTANCE = 331,         /* COSINE_DISTANCE  */
    INNER_PRODUCT = 332,           /* INNER_PRODUCT  */
    IN = 333,                      /* IN  */
    EXISTS = 334,                  /* EXISTS  */
    VECTORS = 335,                 /* VECTORS  */
    QUOTE = 336,                   /* QUOTE  */
    UNIQUE = 337,                  /* UNIQUE  */
    LIMIT = 338,                   /* LIMIT  */
    NUMBER = 339,                  /* NUMBER  */
    FLOAT = 340,                   /* FLOAT  */
    ID = 341,                      /* ID  */
    SSS = 342,                     /* SSS  */
    DATE_STR = 343,                /* DATE_STR  */
    UMINUS = 344                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 174 "yacc_sql.y"

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

#line 181 "yacc_sql.hpp"

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

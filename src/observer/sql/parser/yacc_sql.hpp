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
    VIEW = 268,                    /* VIEW  */
    INDEX = 269,                   /* INDEX  */
    CALC = 270,                    /* CALC  */
    SELECT = 271,                  /* SELECT  */
    DESC = 272,                    /* DESC  */
    SHOW = 273,                    /* SHOW  */
    SYNC = 274,                    /* SYNC  */
    INSERT = 275,                  /* INSERT  */
    DELETE = 276,                  /* DELETE  */
    UPDATE = 277,                  /* UPDATE  */
    INNER = 278,                   /* INNER  */
    JOIN = 279,                    /* JOIN  */
    LBRACE = 280,                  /* LBRACE  */
    RBRACE = 281,                  /* RBRACE  */
    COMMA = 282,                   /* COMMA  */
    TRX_BEGIN = 283,               /* TRX_BEGIN  */
    TRX_COMMIT = 284,              /* TRX_COMMIT  */
    TRX_ROLLBACK = 285,            /* TRX_ROLLBACK  */
    INT_T = 286,                   /* INT_T  */
    STRING_T = 287,                /* STRING_T  */
    FLOAT_T = 288,                 /* FLOAT_T  */
    VECTOR_T = 289,                /* VECTOR_T  */
    WITH_T = 290,                  /* WITH_T  */
    DISTANCE_T = 291,              /* DISTANCE_T  */
    TYPE_T = 292,                  /* TYPE_T  */
    IVFFLAT_T = 293,               /* IVFFLAT_T  */
    LISTS_T = 294,                 /* LISTS_T  */
    PROBES_T = 295,                /* PROBES_T  */
    TEXT_T = 296,                  /* TEXT_T  */
    IS = 297,                      /* IS  */
    NOT = 298,                     /* NOT  */
    NULL_T = 299,                  /* NULL_T  */
    DATE_T = 300,                  /* DATE_T  */
    HELP = 301,                    /* HELP  */
    EXIT = 302,                    /* EXIT  */
    DOT = 303,                     /* DOT  */
    INTO = 304,                    /* INTO  */
    VALUES = 305,                  /* VALUES  */
    FROM = 306,                    /* FROM  */
    WHERE = 307,                   /* WHERE  */
    AND = 308,                     /* AND  */
    OR = 309,                      /* OR  */
    SET = 310,                     /* SET  */
    ON = 311,                      /* ON  */
    AS = 312,                      /* AS  */
    LOAD = 313,                    /* LOAD  */
    DATA = 314,                    /* DATA  */
    INFILE = 315,                  /* INFILE  */
    EXPLAIN = 316,                 /* EXPLAIN  */
    STORAGE = 317,                 /* STORAGE  */
    FORMAT = 318,                  /* FORMAT  */
    EQ = 319,                      /* EQ  */
    LT = 320,                      /* LT  */
    GT = 321,                      /* GT  */
    LE = 322,                      /* LE  */
    GE = 323,                      /* GE  */
    NE = 324,                      /* NE  */
    LIKE = 325,                    /* LIKE  */
    COUNT = 326,                   /* COUNT  */
    SUM = 327,                     /* SUM  */
    AVG = 328,                     /* AVG  */
    MAX = 329,                     /* MAX  */
    MIN = 330,                     /* MIN  */
    L2_DISTANCE = 331,             /* L2_DISTANCE  */
    COSINE_DISTANCE = 332,         /* COSINE_DISTANCE  */
    INNER_PRODUCT = 333,           /* INNER_PRODUCT  */
    IN = 334,                      /* IN  */
    EXISTS = 335,                  /* EXISTS  */
    VECTORS = 336,                 /* VECTORS  */
    QUOTE = 337,                   /* QUOTE  */
    UNIQUE = 338,                  /* UNIQUE  */
    LIMIT = 339,                   /* LIMIT  */
    NUMBER = 340,                  /* NUMBER  */
    FLOAT = 341,                   /* FLOAT  */
    ID = 342,                      /* ID  */
    SSS = 343,                     /* SSS  */
    DATE_STR = 344,                /* DATE_STR  */
    UMINUS = 345                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
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

#line 183 "yacc_sql.hpp"

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

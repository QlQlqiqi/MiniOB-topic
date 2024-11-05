/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "yacc_sql.y"


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


#line 149 "yacc_sql.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "yacc_sql.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SEMICOLON = 3,                  /* SEMICOLON  */
  YYSYMBOL_BY = 4,                         /* BY  */
  YYSYMBOL_CREATE = 5,                     /* CREATE  */
  YYSYMBOL_DROP = 6,                       /* DROP  */
  YYSYMBOL_GROUP = 7,                      /* GROUP  */
  YYSYMBOL_ORDER = 8,                      /* ORDER  */
  YYSYMBOL_ASC = 9,                        /* ASC  */
  YYSYMBOL_HAVING = 10,                    /* HAVING  */
  YYSYMBOL_TABLE = 11,                     /* TABLE  */
  YYSYMBOL_TABLES = 12,                    /* TABLES  */
  YYSYMBOL_VIEW = 13,                      /* VIEW  */
  YYSYMBOL_INDEX = 14,                     /* INDEX  */
  YYSYMBOL_CALC = 15,                      /* CALC  */
  YYSYMBOL_SELECT = 16,                    /* SELECT  */
  YYSYMBOL_DESC = 17,                      /* DESC  */
  YYSYMBOL_SHOW = 18,                      /* SHOW  */
  YYSYMBOL_SYNC = 19,                      /* SYNC  */
  YYSYMBOL_INSERT = 20,                    /* INSERT  */
  YYSYMBOL_DELETE = 21,                    /* DELETE  */
  YYSYMBOL_UPDATE = 22,                    /* UPDATE  */
  YYSYMBOL_INNER = 23,                     /* INNER  */
  YYSYMBOL_JOIN = 24,                      /* JOIN  */
  YYSYMBOL_LBRACE = 25,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 26,                    /* RBRACE  */
  YYSYMBOL_COMMA = 27,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 28,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 29,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 30,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 31,                     /* INT_T  */
  YYSYMBOL_STRING_T = 32,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 33,                   /* FLOAT_T  */
  YYSYMBOL_VECTOR_T = 34,                  /* VECTOR_T  */
  YYSYMBOL_WITH_T = 35,                    /* WITH_T  */
  YYSYMBOL_DISTANCE_T = 36,                /* DISTANCE_T  */
  YYSYMBOL_TYPE_T = 37,                    /* TYPE_T  */
  YYSYMBOL_IVFFLAT_T = 38,                 /* IVFFLAT_T  */
  YYSYMBOL_LISTS_T = 39,                   /* LISTS_T  */
  YYSYMBOL_PROBES_T = 40,                  /* PROBES_T  */
  YYSYMBOL_TEXT_T = 41,                    /* TEXT_T  */
  YYSYMBOL_IS = 42,                        /* IS  */
  YYSYMBOL_NOT = 43,                       /* NOT  */
  YYSYMBOL_NULL_T = 44,                    /* NULL_T  */
  YYSYMBOL_DATE_T = 45,                    /* DATE_T  */
  YYSYMBOL_HELP = 46,                      /* HELP  */
  YYSYMBOL_EXIT = 47,                      /* EXIT  */
  YYSYMBOL_DOT = 48,                       /* DOT  */
  YYSYMBOL_INTO = 49,                      /* INTO  */
  YYSYMBOL_VALUES = 50,                    /* VALUES  */
  YYSYMBOL_FROM = 51,                      /* FROM  */
  YYSYMBOL_WHERE = 52,                     /* WHERE  */
  YYSYMBOL_AND = 53,                       /* AND  */
  YYSYMBOL_OR = 54,                        /* OR  */
  YYSYMBOL_SET = 55,                       /* SET  */
  YYSYMBOL_ON = 56,                        /* ON  */
  YYSYMBOL_AS = 57,                        /* AS  */
  YYSYMBOL_LOAD = 58,                      /* LOAD  */
  YYSYMBOL_DATA = 59,                      /* DATA  */
  YYSYMBOL_INFILE = 60,                    /* INFILE  */
  YYSYMBOL_EXPLAIN = 61,                   /* EXPLAIN  */
  YYSYMBOL_STORAGE = 62,                   /* STORAGE  */
  YYSYMBOL_FORMAT = 63,                    /* FORMAT  */
  YYSYMBOL_EQ = 64,                        /* EQ  */
  YYSYMBOL_LT = 65,                        /* LT  */
  YYSYMBOL_GT = 66,                        /* GT  */
  YYSYMBOL_LE = 67,                        /* LE  */
  YYSYMBOL_GE = 68,                        /* GE  */
  YYSYMBOL_NE = 69,                        /* NE  */
  YYSYMBOL_LIKE = 70,                      /* LIKE  */
  YYSYMBOL_COUNT = 71,                     /* COUNT  */
  YYSYMBOL_SUM = 72,                       /* SUM  */
  YYSYMBOL_AVG = 73,                       /* AVG  */
  YYSYMBOL_MAX = 74,                       /* MAX  */
  YYSYMBOL_MIN = 75,                       /* MIN  */
  YYSYMBOL_L2_DISTANCE = 76,               /* L2_DISTANCE  */
  YYSYMBOL_COSINE_DISTANCE = 77,           /* COSINE_DISTANCE  */
  YYSYMBOL_INNER_PRODUCT = 78,             /* INNER_PRODUCT  */
  YYSYMBOL_IN = 79,                        /* IN  */
  YYSYMBOL_EXISTS = 80,                    /* EXISTS  */
  YYSYMBOL_VECTORS = 81,                   /* VECTORS  */
  YYSYMBOL_QUOTE = 82,                     /* QUOTE  */
  YYSYMBOL_UNIQUE = 83,                    /* UNIQUE  */
  YYSYMBOL_LIMIT = 84,                     /* LIMIT  */
  YYSYMBOL_NUMBER = 85,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 86,                     /* FLOAT  */
  YYSYMBOL_ID = 87,                        /* ID  */
  YYSYMBOL_SSS = 88,                       /* SSS  */
  YYSYMBOL_DATE_STR = 89,                  /* DATE_STR  */
  YYSYMBOL_90_ = 90,                       /* '+'  */
  YYSYMBOL_91_ = 91,                       /* '-'  */
  YYSYMBOL_92_ = 92,                       /* '*'  */
  YYSYMBOL_93_ = 93,                       /* '/'  */
  YYSYMBOL_UMINUS = 94,                    /* UMINUS  */
  YYSYMBOL_95_ = 95,                       /* '['  */
  YYSYMBOL_96_ = 96,                       /* ']'  */
  YYSYMBOL_YYACCEPT = 97,                  /* $accept  */
  YYSYMBOL_commands = 98,                  /* commands  */
  YYSYMBOL_command_wrapper = 99,           /* command_wrapper  */
  YYSYMBOL_exit_stmt = 100,                /* exit_stmt  */
  YYSYMBOL_help_stmt = 101,                /* help_stmt  */
  YYSYMBOL_sync_stmt = 102,                /* sync_stmt  */
  YYSYMBOL_begin_stmt = 103,               /* begin_stmt  */
  YYSYMBOL_commit_stmt = 104,              /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 105,            /* rollback_stmt  */
  YYSYMBOL_create_table_stmt = 106,        /* create_table_stmt  */
  YYSYMBOL_drop_table_stmt = 107,          /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 108,         /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 109,          /* desc_table_stmt  */
  YYSYMBOL_create_view_stmt = 110,         /* create_view_stmt  */
  YYSYMBOL_drop_view_stmt = 111,           /* drop_view_stmt  */
  YYSYMBOL_create_index_stmt = 112,        /* create_index_stmt  */
  YYSYMBOL_vector_index_with = 113,        /* vector_index_with  */
  YYSYMBOL_opt_unique = 114,               /* opt_unique  */
  YYSYMBOL_view_brace_id_list = 115,       /* view_brace_id_list  */
  YYSYMBOL_idx_col_list = 116,             /* idx_col_list  */
  YYSYMBOL_drop_index_stmt = 117,          /* drop_index_stmt  */
  YYSYMBOL_attr_def_list = 118,            /* attr_def_list  */
  YYSYMBOL_attr_def = 119,                 /* attr_def  */
  YYSYMBOL_alias = 120,                    /* alias  */
  YYSYMBOL_opt_null = 121,                 /* opt_null  */
  YYSYMBOL_number = 122,                   /* number  */
  YYSYMBOL_type = 123,                     /* type  */
  YYSYMBOL_insert_stmt = 124,              /* insert_stmt  */
  YYSYMBOL_value_list = 125,               /* value_list  */
  YYSYMBOL_insert_value = 126,             /* insert_value  */
  YYSYMBOL_value = 127,                    /* value  */
  YYSYMBOL_storage_format = 128,           /* storage_format  */
  YYSYMBOL_double_list = 129,              /* double_list  */
  YYSYMBOL_float_number = 130,             /* float_number  */
  YYSYMBOL_delete_stmt = 131,              /* delete_stmt  */
  YYSYMBOL_update_stmt = 132,              /* update_stmt  */
  YYSYMBOL_update_kv_list = 133,           /* update_kv_list  */
  YYSYMBOL_create_table_select_stmt = 134, /* create_table_select_stmt  */
  YYSYMBOL_select_stmt = 135,              /* select_stmt  */
  YYSYMBOL_calc_stmt = 136,                /* calc_stmt  */
  YYSYMBOL_expression_list = 137,          /* expression_list  */
  YYSYMBOL_aggr_argument_list = 138,       /* aggr_argument_list  */
  YYSYMBOL_expression = 139,               /* expression  */
  YYSYMBOL_vector_func_type = 140,         /* vector_func_type  */
  YYSYMBOL_aggregate_expr = 141,           /* aggregate_expr  */
  YYSYMBOL_sub_query_expr = 142,           /* sub_query_expr  */
  YYSYMBOL_rel_attr = 143,                 /* rel_attr  */
  YYSYMBOL_rel_attr_list = 144,            /* rel_attr_list  */
  YYSYMBOL_relation = 145,                 /* relation  */
  YYSYMBOL_rel_list = 146,                 /* rel_list  */
  YYSYMBOL_inner_join_list = 147,          /* inner_join_list  */
  YYSYMBOL_inner_join_rel = 148,           /* inner_join_rel  */
  YYSYMBOL_where = 149,                    /* where  */
  YYSYMBOL_condition = 150,                /* condition  */
  YYSYMBOL_comp_op = 151,                  /* comp_op  */
  YYSYMBOL_exists_op = 152,                /* exists_op  */
  YYSYMBOL_group_by = 153,                 /* group_by  */
  YYSYMBOL_opt_having = 154,               /* opt_having  */
  YYSYMBOL_order_by = 155,                 /* order_by  */
  YYSYMBOL_opt_limit = 156,                /* opt_limit  */
  YYSYMBOL_order_by_list = 157,            /* order_by_list  */
  YYSYMBOL_order_unit = 158,               /* order_unit  */
  YYSYMBOL_order_op = 159,                 /* order_op  */
  YYSYMBOL_load_data_stmt = 160,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 161,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 162,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 163             /* opt_semicolon  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  85
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   375

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  97
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  67
/* YYNRULES -- Number of rules.  */
#define YYNRULES  169
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  342

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   345


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,    92,    90,     2,    91,     2,    93,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    95,     2,    96,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    94
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   287,   287,   295,   296,   297,   298,   299,   300,   301,
     302,   303,   304,   305,   306,   307,   308,   309,   310,   311,
     312,   313,   314,   315,   316,   320,   326,   331,   337,   343,
     349,   355,   376,   384,   409,   416,   422,   431,   452,   460,
     475,   497,   512,   515,   522,   525,   537,   540,   549,   561,
     564,   577,   601,   626,   629,   633,   640,   644,   648,   654,
     657,   658,   659,   660,   661,   662,   665,   678,   698,   701,
     711,   726,   730,   734,   748,   752,   758,   765,   768,   773,
     776,   780,   785,   788,   793,   806,   822,   829,   839,   843,
     850,   894,   904,   913,   922,   939,   942,   950,   960,   963,
     966,   969,   972,   981,   984,   989,   995,   998,  1001,  1004,
    1010,  1013,  1016,  1022,  1025,  1028,  1031,  1034,  1039,  1047,
    1052,  1059,  1068,  1071,  1085,  1090,  1100,  1120,  1123,  1137,
    1153,  1156,  1161,  1165,  1172,  1179,  1183,  1190,  1191,  1192,
    1193,  1194,  1195,  1196,  1197,  1198,  1199,  1200,  1204,  1205,
    1210,  1213,  1221,  1224,  1233,  1236,  1245,  1248,  1256,  1261,
    1269,  1277,  1285,  1288,  1292,  1299,  1312,  1320,  1330,  1331
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "SEMICOLON", "BY",
  "CREATE", "DROP", "GROUP", "ORDER", "ASC", "HAVING", "TABLE", "TABLES",
  "VIEW", "INDEX", "CALC", "SELECT", "DESC", "SHOW", "SYNC", "INSERT",
  "DELETE", "UPDATE", "INNER", "JOIN", "LBRACE", "RBRACE", "COMMA",
  "TRX_BEGIN", "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "STRING_T",
  "FLOAT_T", "VECTOR_T", "WITH_T", "DISTANCE_T", "TYPE_T", "IVFFLAT_T",
  "LISTS_T", "PROBES_T", "TEXT_T", "IS", "NOT", "NULL_T", "DATE_T", "HELP",
  "EXIT", "DOT", "INTO", "VALUES", "FROM", "WHERE", "AND", "OR", "SET",
  "ON", "AS", "LOAD", "DATA", "INFILE", "EXPLAIN", "STORAGE", "FORMAT",
  "EQ", "LT", "GT", "LE", "GE", "NE", "LIKE", "COUNT", "SUM", "AVG", "MAX",
  "MIN", "L2_DISTANCE", "COSINE_DISTANCE", "INNER_PRODUCT", "IN", "EXISTS",
  "VECTORS", "QUOTE", "UNIQUE", "LIMIT", "NUMBER", "FLOAT", "ID", "SSS",
  "DATE_STR", "'+'", "'-'", "'*'", "'/'", "UMINUS", "'['", "']'",
  "$accept", "commands", "command_wrapper", "exit_stmt", "help_stmt",
  "sync_stmt", "begin_stmt", "commit_stmt", "rollback_stmt",
  "create_table_stmt", "drop_table_stmt", "show_tables_stmt",
  "desc_table_stmt", "create_view_stmt", "drop_view_stmt",
  "create_index_stmt", "vector_index_with", "opt_unique",
  "view_brace_id_list", "idx_col_list", "drop_index_stmt", "attr_def_list",
  "attr_def", "alias", "opt_null", "number", "type", "insert_stmt",
  "value_list", "insert_value", "value", "storage_format", "double_list",
  "float_number", "delete_stmt", "update_stmt", "update_kv_list",
  "create_table_select_stmt", "select_stmt", "calc_stmt",
  "expression_list", "aggr_argument_list", "expression",
  "vector_func_type", "aggregate_expr", "sub_query_expr", "rel_attr",
  "rel_attr_list", "relation", "rel_list", "inner_join_list",
  "inner_join_rel", "where", "condition", "comp_op", "exists_op",
  "group_by", "opt_having", "order_by", "opt_limit", "order_by_list",
  "order_unit", "order_op", "load_data_stmt", "explain_stmt",
  "set_variable_stmt", "opt_semicolon", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-290)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     209,    -6,   144,   105,   105,   -79,    -1,  -290,   -27,   -33,
     -55,  -290,  -290,  -290,  -290,  -290,   -53,    45,   209,   114,
     113,  -290,  -290,  -290,  -290,  -290,  -290,  -290,  -290,  -290,
    -290,  -290,  -290,  -290,  -290,  -290,  -290,  -290,  -290,  -290,
    -290,  -290,  -290,    42,    58,   160,  -290,   170,    98,   111,
     112,     8,  -290,   181,   182,   188,   191,   192,  -290,  -290,
    -290,  -290,  -290,   175,  -290,  -290,   105,  -290,   -16,  -290,
    -290,   118,   215,  -290,  -290,  -290,   190,  -290,  -290,   161,
     164,   -31,   183,   193,  -290,  -290,  -290,  -290,     0,   232,
     171,   172,  -290,  -290,   204,   237,   239,   105,   105,   105,
     105,   105,    55,  -290,  -290,  -290,   -18,  -290,   179,  -290,
     105,   105,   105,   105,   241,   105,   194,    77,   -31,   214,
     -24,   195,   197,   262,  -290,  -290,   198,   222,   224,   226,
     200,  -290,  -290,   263,   118,   264,   265,   266,   267,  -290,
    -290,   -16,  -290,  -290,    39,    39,  -290,  -290,   105,    19,
    -290,   -31,  -290,   208,   269,   236,   216,  -290,   247,   201,
     274,  -290,   275,   262,   217,   218,  -290,  -290,   279,  -290,
    -290,  -290,  -290,  -290,  -290,   105,   280,    49,   281,   -24,
      48,  -290,   245,    -8,   299,  -290,  -290,  -290,  -290,  -290,
    -290,   116,   197,   285,   225,   287,  -290,   289,   290,   105,
      -3,   194,   292,  -290,   310,   208,   293,   291,   240,  -290,
     207,   100,   105,   105,   234,  -290,   235,   238,   282,  -290,
    -290,   274,   268,   275,  -290,   242,   244,  -290,  -290,  -290,
     194,   320,   315,   281,   277,   105,   302,  -290,   122,   -49,
    -290,   270,  -290,  -290,  -290,  -290,  -290,  -290,   105,    48,
      48,    78,    78,   271,  -290,  -290,   306,  -290,  -290,   276,
       1,  -290,   275,   275,   -31,   105,    48,   325,  -290,   309,
     291,    78,  -290,  -290,  -290,  -290,  -290,    78,  -290,   284,
     105,   122,   278,  -290,   312,   314,   288,  -290,   100,   337,
     259,   -24,  -290,    78,  -290,   258,   311,  -290,    48,   167,
     238,  -290,   291,  -290,   322,  -290,   100,   323,   129,  -290,
     324,  -290,   326,   313,   105,  -290,  -290,  -290,   167,  -290,
     294,    71,  -290,   316,   105,   328,    15,   317,   129,   295,
    -290,   125,   329,   318,   296,   238,   334,   327,   298,   238,
     338,  -290
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    42,     0,     0,     0,     0,     0,    27,     0,     0,
       0,    28,    29,    30,    26,    25,     0,     0,     0,     0,
     168,    24,    23,    16,    17,    18,    19,     8,     9,    10,
      11,    12,    13,    14,    15,     5,     7,     6,     4,     3,
      20,    21,    22,     0,     0,     0,    43,     0,     0,     0,
       0,     0,    76,     0,     0,     0,     0,     0,   110,   111,
     112,    71,    72,   119,    75,    73,     0,   109,    79,   104,
      92,    53,     0,   107,   108,   105,    91,    36,    35,     0,
       0,    53,     0,     0,   166,     1,   169,     2,     0,    44,
       0,     0,    34,    38,     0,     0,     0,    95,    95,    95,
      95,    95,     0,   103,    82,    83,     0,    80,     0,    54,
       0,     0,     0,     0,    93,     0,     0,     0,    53,     0,
       0,     0,     0,     0,    32,    89,     0,     0,     0,     0,
       0,   118,   102,     0,    53,     0,     0,     0,     0,   120,
     121,     0,    74,    55,    98,    99,   100,   101,     0,     0,
     124,    53,   127,     0,     0,   130,     0,   167,     0,     0,
      49,    88,    46,     0,     0,     0,    48,   113,    96,   114,
     115,   117,   116,    81,    94,     0,   125,   130,   122,     0,
       0,    84,     0,   130,     0,    60,    61,    62,    63,    64,
      65,    56,     0,     0,     0,     0,    37,     0,     0,     0,
       0,     0,     0,   128,   150,     0,     0,    68,     0,   148,
       0,   131,     0,     0,     0,    85,     0,     0,     0,    58,
      52,    49,    77,    46,    45,     0,     0,    97,   106,   126,
       0,     0,   152,   122,     0,     0,     0,   149,    56,     0,
     137,   138,   139,   140,   142,   143,   144,   146,     0,     0,
       0,   133,    86,     0,   165,    59,     0,    57,    50,     0,
      31,    47,    46,    46,    53,     0,     0,   154,   123,     0,
      68,    70,    66,   134,   145,   147,   141,   132,   135,   136,
       0,    56,     0,    33,     0,     0,     0,   151,   153,     0,
     156,     0,    69,    87,    51,     0,     0,    39,     0,     0,
       0,    90,    68,    78,     0,    40,   129,     0,   162,   155,
     158,   157,     0,     0,     0,   163,   164,   160,     0,    67,
       0,     0,   159,     0,     0,     0,     0,     0,   162,     0,
     161,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    41
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -290,  -290,   331,  -290,  -290,  -290,  -290,  -290,  -290,  -290,
    -290,  -290,  -290,  -290,  -290,  -290,  -290,  -290,  -290,  -196,
    -290,   142,   173,   -75,  -226,  -183,  -290,  -290,  -257,  -290,
    -119,  -290,  -290,   227,  -290,  -290,  -290,   106,   -48,  -290,
      -4,   121,   -62,  -289,  -290,  -290,  -151,   136,   140,   174,
    -290,  -290,  -109,  -235,  -290,  -290,  -290,  -290,  -290,  -290,
      53,  -290,    44,  -290,  -290,  -290,  -290
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,   305,    47,   127,   195,
      34,   193,   160,   114,   220,   256,   191,    35,   236,   270,
      69,   260,   106,   107,    36,    37,   183,   124,    38,    39,
      70,   133,    71,    72,    73,    74,    75,   206,   151,   152,
     177,   203,   181,   211,   248,   212,   232,   267,   290,   301,
     309,   310,   317,    40,    41,    42,    87
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      76,   157,   178,    95,   103,    43,   119,    44,    77,   141,
     307,    78,   273,   292,   278,   279,     4,     4,    80,   214,
      52,   274,    79,   228,     4,   122,   108,   261,    45,   307,
     275,   288,    81,    51,    82,   134,   134,   134,   134,   134,
     125,   328,   332,   155,   180,   312,   175,    96,   144,   145,
     146,   147,    52,   149,   233,   294,   109,   123,   123,   168,
     207,    61,    62,   306,    64,    65,   284,   285,   204,   104,
     105,    68,   202,    51,   215,   161,   176,    46,   142,    53,
      54,    55,    56,    57,    58,    59,    60,   110,   111,   112,
     113,   208,    52,    61,    62,    63,    64,    65,   324,    66,
      67,   180,   153,    68,    83,   110,   111,   112,   113,   110,
     111,   112,   113,   200,    85,   196,    86,   311,   210,    53,
      54,    55,    56,    57,    58,    59,    60,   154,   209,    88,
      51,   112,   113,    61,    62,    63,    64,    65,   315,    66,
      67,   217,   139,    68,   174,    89,   316,   140,   308,    52,
     251,   252,   336,   249,   250,    48,   340,    49,    50,   218,
     219,   110,   111,   112,   113,   218,   219,   308,   110,   111,
     112,   113,   302,   271,    90,   108,    53,    54,    55,    56,
      57,    58,    59,    60,    91,    92,   277,   210,   210,   286,
      61,    62,    63,    64,    65,   227,    66,    67,    93,    94,
      68,    58,    59,    60,   210,   109,    97,    98,   110,   111,
     112,   113,   125,    99,     1,     2,   100,   101,   293,   135,
     136,   137,   138,   102,     3,     4,     5,     6,     7,     8,
       9,    10,   185,   186,   187,   188,   210,    11,    12,    13,
     115,   116,   189,    58,    59,    60,   190,   120,   117,   238,
     239,   118,   321,   121,    63,    14,    15,   126,   128,   129,
     130,   287,   326,   131,    16,   132,   143,    17,   148,   156,
      18,   240,   241,   242,   243,   244,   245,   246,     4,   163,
     164,   150,   165,   158,   159,   162,   247,   166,   180,   167,
     169,   170,   171,   172,   179,    63,   184,   110,   111,   112,
     113,   192,   194,   182,   197,   198,   199,   201,   205,   213,
     216,   222,   223,   224,   225,   226,   230,   231,   235,   234,
     237,   253,   254,   255,   265,   266,   257,   269,   272,   262,
     259,   263,   281,   289,   291,   280,   276,   249,   296,   282,
     297,   299,   295,   300,   298,   303,   304,   313,   314,    84,
     320,   318,   319,   329,   325,   327,   333,   334,   323,   331,
     335,   337,   339,   258,   341,   221,   283,   338,   173,   268,
     264,   322,   330,     0,     0,   229
};

static const yytype_int16 yycheck[] =
{
       4,   120,   153,    51,    66,    11,    81,    13,    87,    27,
     299,    12,   238,   270,   249,   250,    16,    16,    51,    27,
      44,    70,    49,    26,    16,    25,    57,   223,    34,   318,
      79,   266,    87,    25,    87,    97,    98,    99,   100,   101,
      88,    26,   331,   118,    52,   302,    27,    51,   110,   111,
     112,   113,    44,   115,   205,   281,    87,    57,    57,   134,
     179,    85,    86,   298,    88,    89,   262,   263,   177,    85,
      86,    95,    23,    25,   183,   123,   151,    83,    96,    71,
      72,    73,    74,    75,    76,    77,    78,    90,    91,    92,
      93,    43,    44,    85,    86,    87,    88,    89,    27,    91,
      92,    52,    25,    95,    59,    90,    91,    92,    93,    90,
      91,    92,    93,   175,     0,   163,     3,   300,   180,    71,
      72,    73,    74,    75,    76,    77,    78,    50,    80,    87,
      25,    92,    93,    85,    86,    87,    88,    89,     9,    91,
      92,    25,    87,    95,   148,    87,    17,    92,   299,    44,
     212,   213,   335,    53,    54,    11,   339,    13,    14,    43,
      44,    90,    91,    92,    93,    43,    44,   318,    90,    91,
      92,    93,   291,   235,    14,    57,    71,    72,    73,    74,
      75,    76,    77,    78,    14,    87,   248,   249,   250,   264,
      85,    86,    87,    88,    89,   199,    91,    92,    87,    87,
      95,    76,    77,    78,   266,    87,    25,    25,    90,    91,
      92,    93,   260,    25,     5,     6,    25,    25,   280,    98,
      99,   100,   101,    48,    15,    16,    17,    18,    19,    20,
      21,    22,    31,    32,    33,    34,   298,    28,    29,    30,
      25,    51,    41,    76,    77,    78,    45,    64,    87,    42,
      43,    87,   314,    60,    87,    46,    47,    25,    87,    87,
      56,   265,   324,    26,    55,    26,    87,    58,    27,    55,
      61,    64,    65,    66,    67,    68,    69,    70,    16,    57,
      56,    87,    56,    88,    87,    87,    79,    87,    52,    26,
      26,    26,    26,    26,    25,    87,    49,    90,    91,    92,
      93,    27,    27,    87,    87,    87,    27,    27,    27,    64,
      11,    26,    87,    26,    25,    25,    24,     7,    27,    26,
      80,    87,    87,    85,     4,    10,    44,    50,    26,    87,
      62,    87,    26,     8,    25,    64,    66,    53,    26,    63,
      26,     4,    64,    84,    56,    87,    35,    25,    25,    18,
      37,    27,    26,    36,    38,    27,    27,    39,    64,    64,
      64,    27,    64,   221,    26,   192,   260,    40,   141,   233,
     230,   318,   328,    -1,    -1,   201
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     6,    15,    16,    17,    18,    19,    20,    21,
      22,    28,    29,    30,    46,    47,    55,    58,    61,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   117,   124,   131,   132,   135,   136,
     160,   161,   162,    11,    13,    34,    83,   114,    11,    13,
      14,    25,    44,    71,    72,    73,    74,    75,    76,    77,
      78,    85,    86,    87,    88,    89,    91,    92,    95,   127,
     137,   139,   140,   141,   142,   143,   137,    87,    12,    49,
      51,    87,    87,    59,    99,     0,     3,   163,    87,    87,
      14,    14,    87,    87,    87,   135,   137,    25,    25,    25,
      25,    25,    48,   139,    85,    86,   129,   130,    57,    87,
      90,    91,    92,    93,   120,    25,    51,    87,    87,   120,
      64,    60,    25,    57,   134,   135,    25,   115,    87,    87,
      56,    26,    26,   138,   139,   138,   138,   138,   138,    87,
      92,    27,    96,    87,   139,   139,   139,   139,    27,   139,
      87,   145,   146,    25,    50,   120,    55,   127,    88,    87,
     119,   135,    87,    57,    56,    56,    87,    26,   120,    26,
      26,    26,    26,   130,   137,    27,   120,   147,   143,    25,
      52,   149,    87,   133,    49,    31,    32,    33,    34,    41,
      45,   123,    27,   118,    27,   116,   135,    87,    87,    27,
     139,    27,    23,   148,   149,    27,   144,   127,    43,    80,
     139,   150,   152,    64,    27,   149,    11,    25,    43,    44,
     121,   119,    26,    87,    26,    25,    25,   137,    26,   146,
      24,     7,   153,   143,    26,    27,   125,    80,    42,    43,
      64,    65,    66,    67,    68,    69,    70,    79,   151,    53,
      54,   139,   139,    87,    87,    85,   122,    44,   118,    62,
     128,   116,    87,    87,   145,     4,    10,   154,   144,    50,
     126,   139,    26,   121,    70,    79,    66,   139,   150,   150,
      64,    26,    63,   134,   116,   116,   120,   137,   150,     8,
     155,    25,   125,   139,   121,    64,    26,    26,    56,     4,
      84,   156,   127,    87,    35,   113,   150,   140,   143,   157,
     158,   122,   125,    25,    25,     9,    17,   159,    27,    26,
      37,   139,   157,    64,    27,    38,   139,    27,    26,    36,
     159,    64,   140,    27,    39,    64,   122,    27,    40,    64,
     122,    26
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    97,    98,    99,    99,    99,    99,    99,    99,    99,
      99,    99,    99,    99,    99,    99,    99,    99,    99,    99,
      99,    99,    99,    99,    99,   100,   101,   102,   103,   104,
     105,   106,   106,   106,   107,   108,   109,   110,   111,   112,
     112,   113,   114,   114,   115,   115,   116,   116,   117,   118,
     118,   119,   119,   120,   120,   120,   121,   121,   121,   122,
     123,   123,   123,   123,   123,   123,   124,   124,   125,   125,
     126,   127,   127,   127,   127,   127,   127,   128,   128,   129,
     129,   129,   130,   130,   131,   132,   133,   133,   134,   134,
     135,   135,   136,   137,   137,   138,   138,   138,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     140,   140,   140,   141,   141,   141,   141,   141,   142,   143,
     143,   143,   144,   144,   145,   146,   146,   147,   147,   148,
     149,   149,   150,   150,   150,   150,   150,   151,   151,   151,
     151,   151,   151,   151,   151,   151,   151,   151,   152,   152,
     153,   153,   154,   154,   155,   155,   156,   156,   157,   157,
     158,   158,   159,   159,   159,   160,   161,   162,   163,   163
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     8,     4,     9,     3,     2,     2,     6,     3,    10,
      11,    18,     0,     1,     0,     4,     0,     3,     5,     0,
       3,     6,     3,     0,     1,     2,     0,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     8,    12,     0,     3,
       1,     1,     1,     1,     3,     1,     1,     0,     4,     0,
       1,     3,     1,     1,     5,     6,     3,     5,     2,     1,
      10,     2,     2,     2,     4,     0,     2,     4,     3,     3,
       3,     3,     3,     2,     1,     1,     6,     1,     1,     1,
       1,     1,     1,     4,     4,     4,     4,     4,     3,     1,
       3,     3,     0,     3,     1,     2,     4,     0,     2,     6,
       0,     2,     3,     2,     3,     3,     3,     1,     1,     1,
       1,     2,     1,     1,     1,     2,     1,     2,     1,     2,
       0,     3,     0,     2,     0,     3,     0,     2,     1,     3,
       2,     7,     0,     1,     1,     7,     2,     4,     0,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (&yylloc, sql_string, sql_result, scanner, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location, sql_string, sql_result, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  YY_USE (sql_string);
  YY_USE (sql_result);
  YY_USE (scanner);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, sql_string, sql_result, scanner);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]), sql_string, sql_result, scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, sql_string, sql_result, scanner); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  YY_USE (sql_string);
  YY_USE (sql_result);
  YY_USE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, &yylloc, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* commands: command_wrapper opt_semicolon  */
#line 288 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1962 "yacc_sql.cpp"
    break;

  case 25: /* exit_stmt: EXIT  */
#line 320 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1971 "yacc_sql.cpp"
    break;

  case 26: /* help_stmt: HELP  */
#line 326 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1979 "yacc_sql.cpp"
    break;

  case 27: /* sync_stmt: SYNC  */
#line 331 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1987 "yacc_sql.cpp"
    break;

  case 28: /* begin_stmt: TRX_BEGIN  */
#line 337 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1995 "yacc_sql.cpp"
    break;

  case 29: /* commit_stmt: TRX_COMMIT  */
#line 343 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 2003 "yacc_sql.cpp"
    break;

  case 30: /* rollback_stmt: TRX_ROLLBACK  */
#line 349 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 2011 "yacc_sql.cpp"
    break;

  case 31: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format  */
#line 356 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-5].string);
      free((yyvsp[-5].string));

      std::vector<AttrInfoSqlNode> *src_attrs = (yyvsp[-2].attr_infos);

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
        delete src_attrs;
      }
      create_table.attr_infos.emplace_back(*(yyvsp[-3].attr_info));
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete (yyvsp[-3].attr_info);
      if ((yyvsp[0].string) != nullptr) {
        create_table.storage_format = (yyvsp[0].string);
        free((yyvsp[0].string));
      }
    }
#line 2036 "yacc_sql.cpp"
    break;

  case 32: /* create_table_stmt: CREATE TABLE ID create_table_select_stmt  */
#line 377 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-1].string);
      free((yyvsp[-1].string));
      create_table.select_sql_node.reset((yyvsp[0].sql_node));
    }
#line 2048 "yacc_sql.cpp"
    break;

  case 33: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format create_table_select_stmt  */
#line 385 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-6].string);
      free((yyvsp[-6].string));

      std::vector<AttrInfoSqlNode> *src_attrs = (yyvsp[-3].attr_infos);

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
        delete src_attrs;
      }
      create_table.attr_infos.emplace_back(*(yyvsp[-4].attr_info));
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete (yyvsp[-4].attr_info);
      if ((yyvsp[-1].string) != nullptr) {
        create_table.storage_format = (yyvsp[-1].string);
        free((yyvsp[-1].string));
      } 
      create_table.select_sql_node.reset((yyvsp[0].sql_node));
    }
#line 2074 "yacc_sql.cpp"
    break;

  case 34: /* drop_table_stmt: DROP TABLE ID  */
#line 409 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2084 "yacc_sql.cpp"
    break;

  case 35: /* show_tables_stmt: SHOW TABLES  */
#line 416 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 2092 "yacc_sql.cpp"
    break;

  case 36: /* desc_table_stmt: DESC ID  */
#line 422 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2102 "yacc_sql.cpp"
    break;

  case 37: /* create_view_stmt: CREATE VIEW ID view_brace_id_list AS select_stmt  */
#line 432 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_VIEW);
      CreateViewSqlNode &create_view = (yyval.sql_node)->create_view;
      create_view.view_name = (yyvsp[-3].string);
      free((yyvsp[-3].string));
      if ((yyvsp[-2].id_list) != nullptr) {
        create_view.attr_ids.swap(*(yyvsp[-2].id_list));
        delete (yyvsp[-2].id_list);
      } 
      if((yyvsp[0].sql_node) != nullptr){
        create_view.select_stmt.reset((yyvsp[0].sql_node));
        create_view.select_sql = token_name(sql_string, &(yylsp[0]));
      }else{
        yyerror(&(yyloc), sql_string, sql_result, scanner, "error");
        YYERROR;
      }
    }
#line 2124 "yacc_sql.cpp"
    break;

  case 38: /* drop_view_stmt: DROP VIEW ID  */
#line 452 "yacc_sql.y"
                 {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_VIEW);
      (yyval.sql_node)->drop_view.view_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2134 "yacc_sql.cpp"
    break;

  case 39: /* create_index_stmt: CREATE opt_unique INDEX ID ON ID LBRACE ID idx_col_list RBRACE  */
#line 461 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.index_name = (yyvsp[-6].string);
      create_index.relation_name = (yyvsp[-4].string);
      create_index.unique = (yyvsp[-8].bools);
      create_index.attr_names.swap(*(yyvsp[-1].relation_list));
      create_index.attr_names.emplace_back((yyvsp[-2].string));
      std::reverse(create_index.attr_names.begin(), create_index.attr_names.end());
      free((yyvsp[-6].string));
      free((yyvsp[-4].string));
      free((yyvsp[-2].string));
      delete (yyvsp[-1].relation_list);
    }
#line 2153 "yacc_sql.cpp"
    break;

  case 40: /* create_index_stmt: CREATE VECTOR_T INDEX ID ON ID LBRACE ID idx_col_list RBRACE vector_index_with  */
#line 476 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.index_name = (yyvsp[-7].string);
      create_index.relation_name = (yyvsp[-5].string);
      create_index.unique = false;
      create_index.attr_names.swap(*(yyvsp[-2].relation_list));
      create_index.attr_names.emplace_back((yyvsp[-3].string));
      std::reverse(create_index.attr_names.begin(), create_index.attr_names.end());
      create_index.with = nullptr;
      if((yyvsp[0].vector_index_with)) {
        create_index.with = std::unique_ptr<VectorIndexWith>((yyvsp[0].vector_index_with));
      }
      free((yyvsp[-7].string));
      free((yyvsp[-5].string));
      free((yyvsp[-3].string));
      delete (yyvsp[-2].relation_list);
    }
#line 2176 "yacc_sql.cpp"
    break;

  case 41: /* vector_index_with: WITH_T LBRACE TYPE_T EQ IVFFLAT_T COMMA DISTANCE_T EQ vector_func_type COMMA LISTS_T EQ number COMMA PROBES_T EQ number RBRACE  */
#line 498 "yacc_sql.y"
    {
      VectorIndexWith *with = new VectorIndexWith();
      with->func_type = (yyvsp[-9].number);
      // type 只有 ivfflat
      with->type = 1;
      with->lists = (yyvsp[-5].number);
      with->probes = (yyvsp[-1].number);

      (yyval.vector_index_with) = with;
    }
#line 2191 "yacc_sql.cpp"
    break;

  case 42: /* opt_unique: %empty  */
#line 512 "yacc_sql.y"
    {
      (yyval.bools) = false;
    }
#line 2199 "yacc_sql.cpp"
    break;

  case 43: /* opt_unique: UNIQUE  */
#line 516 "yacc_sql.y"
    {
      (yyval.bools) = true;
    }
#line 2207 "yacc_sql.cpp"
    break;

  case 44: /* view_brace_id_list: %empty  */
#line 522 "yacc_sql.y"
    {
      (yyval.id_list) = nullptr;
    }
#line 2215 "yacc_sql.cpp"
    break;

  case 45: /* view_brace_id_list: LBRACE ID idx_col_list RBRACE  */
#line 525 "yacc_sql.y"
                                    {
      if ((yyvsp[-1].relation_list) == nullptr) {
        (yyval.id_list) = new std::vector<std::string>();
      } else {
        (yyval.id_list) = (yyvsp[-1].relation_list);
      }
      (yyval.id_list)->push_back((yyvsp[-2].string));
      free((yyvsp[-2].string));
      std::reverse((yyval.id_list)->begin(), (yyval.id_list)->end());
    }
#line 2230 "yacc_sql.cpp"
    break;

  case 46: /* idx_col_list: %empty  */
#line 537 "yacc_sql.y"
    {
      (yyval.relation_list) = new std::vector<std::string>;
    }
#line 2238 "yacc_sql.cpp"
    break;

  case 47: /* idx_col_list: COMMA ID idx_col_list  */
#line 541 "yacc_sql.y"
    {
      (yyval.relation_list) = (yyvsp[0].relation_list);
      (yyval.relation_list)->emplace_back((yyvsp[-1].string));
      free((yyvsp[-1].string));
    }
#line 2248 "yacc_sql.cpp"
    break;

  case 48: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 550 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2260 "yacc_sql.cpp"
    break;

  case 49: /* attr_def_list: %empty  */
#line 561 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2268 "yacc_sql.cpp"
    break;

  case 50: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 565 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2282 "yacc_sql.cpp"
    break;

  case 51: /* attr_def: ID type LBRACE number RBRACE opt_null  */
#line 578 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[0].bools) == true;
      (yyval.attr_info)->high_vector = false;
      (yyval.attr_info)->dim = 0;
      // 如果是 vector，那么这里的 length 代表的是数量
      if((yyvsp[-4].number) == static_cast<int>(AttrType::VECTORS)) {
        (yyval.attr_info)->dim = (yyvsp[-2].number);
        // 如果其设置的 dim 过大，设置 vector 存储规则与 text 相同
        if((yyvsp[-2].number) > VECTOR_HIGH_DIM) {
          (yyval.attr_info)->length += sizeof(uint64_t) + sizeof(int32_t);
          (yyval.attr_info)->high_vector = true;
        } else {
          (yyval.attr_info)->length += (yyvsp[-2].number) * sizeof(double);
        }
      } else {
        (yyval.attr_info)->length += (yyvsp[-2].number);
      }
      (yyval.attr_info)->nullable = (yyvsp[0].bools);
      free((yyvsp[-5].string));
    }
#line 2310 "yacc_sql.cpp"
    break;

  case 52: /* attr_def: ID type opt_null  */
#line 602 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      // 这块是 4 是因为 char 和 vector 需要用 ()
      (yyval.attr_info)->length = 4 + ((yyvsp[0].bools) == true);
      (yyval.attr_info)->high_vector = false;
      (yyval.attr_info)->dim = 0;
      // 如果是 date，应该为 sizeof(common::DateTime)
      if((yyval.attr_info)->type == AttrType::DATES) {
        (yyval.attr_info)->length = sizeof(common::DateTime) + ((yyvsp[0].bools) == true);
      }
      // 如果是 text，应该为 sizeof(uint64_t) + sizeof(int32_t)
      // 代表 text file 中 offset 和 text length
      else if((yyval.attr_info)->type == AttrType::TEXTS) {
        (yyval.attr_info)->length = sizeof(uint64_t) + sizeof(int32_t) + ((yyvsp[0].bools) == true);
      }
      (yyval.attr_info)->nullable = (yyvsp[0].bools);
      free((yyvsp[-2].string));
    }
#line 2335 "yacc_sql.cpp"
    break;

  case 53: /* alias: %empty  */
#line 626 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2343 "yacc_sql.cpp"
    break;

  case 54: /* alias: ID  */
#line 630 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2351 "yacc_sql.cpp"
    break;

  case 55: /* alias: AS ID  */
#line 634 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2359 "yacc_sql.cpp"
    break;

  case 56: /* opt_null: %empty  */
#line 640 "yacc_sql.y"
    {
      // 根据 primary-null.result 来看，默认是 not null
      (yyval.bools) = true;
    }
#line 2368 "yacc_sql.cpp"
    break;

  case 57: /* opt_null: NOT NULL_T  */
#line 645 "yacc_sql.y"
    {
      (yyval.bools) = false;
    }
#line 2376 "yacc_sql.cpp"
    break;

  case 58: /* opt_null: NULL_T  */
#line 649 "yacc_sql.y"
    {
      (yyval.bools) = true;
    }
#line 2384 "yacc_sql.cpp"
    break;

  case 59: /* number: NUMBER  */
#line 654 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2390 "yacc_sql.cpp"
    break;

  case 60: /* type: INT_T  */
#line 657 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::INTS); }
#line 2396 "yacc_sql.cpp"
    break;

  case 61: /* type: STRING_T  */
#line 658 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::CHARS); }
#line 2402 "yacc_sql.cpp"
    break;

  case 62: /* type: FLOAT_T  */
#line 659 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::FLOATS); }
#line 2408 "yacc_sql.cpp"
    break;

  case 63: /* type: VECTOR_T  */
#line 660 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::VECTORS); }
#line 2414 "yacc_sql.cpp"
    break;

  case 64: /* type: TEXT_T  */
#line 661 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::TEXTS); }
#line 2420 "yacc_sql.cpp"
    break;

  case 65: /* type: DATE_T  */
#line 662 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::DATES); }
#line 2426 "yacc_sql.cpp"
    break;

  case 66: /* insert_stmt: INSERT INTO ID VALUES LBRACE value value_list RBRACE  */
#line 666 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_INSERT);
      (yyval.sql_node)->insertion.relation_name = (yyvsp[-5].string);
      if ((yyvsp[-1].value_list) != nullptr) {
        (yyval.sql_node)->insertion.values.swap(*(yyvsp[-1].value_list));
        delete (yyvsp[-1].value_list);
      }
      (yyval.sql_node)->insertion.values.emplace_back(*(yyvsp[-2].value));
      std::reverse((yyval.sql_node)->insertion.values.begin(), (yyval.sql_node)->insertion.values.end());
      delete (yyvsp[-2].value);
      free((yyvsp[-5].string));
    }
#line 2443 "yacc_sql.cpp"
    break;

  case 67: /* insert_stmt: INSERT INTO ID LBRACE rel_attr rel_attr_list RBRACE VALUES LBRACE value value_list RBRACE  */
#line 679 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_INSERT);
      (yyval.sql_node)->insertion.relation_name = (yyvsp[-9].string);
      delete (yyvsp[-7].rel_attr);
      delete (yyvsp[-6].rel_attr_list);
      if ((yyvsp[-1].value_list) != nullptr) {
        (yyval.sql_node)->insertion.values.swap(*(yyvsp[-1].value_list));
        delete (yyvsp[-1].value_list);
      }
      (yyval.sql_node)->insertion.values.emplace_back(*(yyvsp[-2].value));
      std::reverse((yyval.sql_node)->insertion.values.begin(), (yyval.sql_node)->insertion.values.end());
      delete (yyvsp[-2].value);
      free((yyvsp[-9].string));
    }
#line 2462 "yacc_sql.cpp"
    break;

  case 68: /* value_list: %empty  */
#line 698 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2470 "yacc_sql.cpp"
    break;

  case 69: /* value_list: COMMA insert_value value_list  */
#line 701 "yacc_sql.y"
                                     { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2484 "yacc_sql.cpp"
    break;

  case 70: /* insert_value: expression  */
#line 712 "yacc_sql.y"
    {
      auto tmp = new Value();
      if(!ArithmeticExpr::exp2value((yyvsp[0].expression), tmp)) {
        delete (yyvsp[0].expression);
        delete tmp;
        yyerror(&(yyloc), sql_string, sql_result, scanner, "error");
        YYERROR;
      }
      delete (yyvsp[0].expression);
      (yyval.value) = tmp;
    }
#line 2500 "yacc_sql.cpp"
    break;

  case 71: /* value: NUMBER  */
#line 726 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2509 "yacc_sql.cpp"
    break;

  case 72: /* value: FLOAT  */
#line 730 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2518 "yacc_sql.cpp"
    break;

  case 73: /* value: DATE_STR  */
#line 734 "yacc_sql.y"
             {
      char *tmp = common::substr((yyvsp[0].string), 1, strlen((yyvsp[0].string))-2);
      std::string str(tmp);
      common::DateTime date_time(str);
      if(!common::DateTime::is_valid_date(str))
      {
        yyerror(&(yyloc),sql_string,sql_result,scanner,"date invaid",true);
        YYERROR;
      }else
      {
        (yyval.value) = new Value(date_time);
      }

    }
#line 2537 "yacc_sql.cpp"
    break;

  case 74: /* value: '[' double_list ']'  */
#line 749 "yacc_sql.y"
    {
      (yyval.value) = vec2val(sql_string, &(yyloc));
    }
#line 2545 "yacc_sql.cpp"
    break;

  case 75: /* value: SSS  */
#line 752 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2556 "yacc_sql.cpp"
    break;

  case 76: /* value: NULL_T  */
#line 758 "yacc_sql.y"
             {
      (yyval.value) = new Value();
      (yyval.value)->set_null();
    }
#line 2565 "yacc_sql.cpp"
    break;

  case 77: /* storage_format: %empty  */
#line 765 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2573 "yacc_sql.cpp"
    break;

  case 78: /* storage_format: STORAGE FORMAT EQ ID  */
#line 769 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2581 "yacc_sql.cpp"
    break;

  case 79: /* double_list: %empty  */
#line 773 "yacc_sql.y"
             {
      (yyval.double_list) = new std::vector<double>();
    }
#line 2589 "yacc_sql.cpp"
    break;

  case 80: /* double_list: float_number  */
#line 776 "yacc_sql.y"
                   {
      (yyval.double_list) = new std::vector<double>();
      (yyval.double_list)->emplace_back((yyvsp[0].float_number));
    }
#line 2598 "yacc_sql.cpp"
    break;

  case 81: /* double_list: double_list COMMA float_number  */
#line 780 "yacc_sql.y"
                                     {
      (yyval.double_list) = (yyvsp[-2].double_list);
      (yyval.double_list)->emplace_back((yyvsp[0].float_number));
    }
#line 2607 "yacc_sql.cpp"
    break;

  case 82: /* float_number: NUMBER  */
#line 785 "yacc_sql.y"
                     {
      (yyval.float_number) = (yyvsp[0].number);
    }
#line 2615 "yacc_sql.cpp"
    break;

  case 83: /* float_number: FLOAT  */
#line 788 "yacc_sql.y"
            {
      (yyval.float_number) = (yyvsp[0].floats);
    }
#line 2623 "yacc_sql.cpp"
    break;

  case 84: /* delete_stmt: DELETE FROM ID alias where  */
#line 794 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-2].string);
      if((yyvsp[-1].string) != nullptr){
      (yyval.sql_node)->deletion.relation_alias = (yyvsp[-1].string);
      }
      (yyval.sql_node)->deletion.conditions = (yyvsp[0].expression);
      free((yyvsp[-2].string));
      free((yyvsp[-1].string));
    }
#line 2638 "yacc_sql.cpp"
    break;

  case 85: /* update_stmt: UPDATE ID alias SET update_kv_list where  */
#line 807 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_UPDATE);
      (yyval.sql_node)->update.relation_name = (yyvsp[-4].string);
      if((yyvsp[-3].string) != nullptr){
        (yyval.sql_node)->update.relation_alias = (yyvsp[-3].string);
      }
      (yyval.sql_node)->update.attribute_name.swap((yyvsp[-1].kv_list)->attrs);
      (yyval.sql_node)->update.value.swap((yyvsp[-1].kv_list)->values);
      (yyval.sql_node)->update.conditions = (yyvsp[0].expression);
      free((yyvsp[-4].string));
      free((yyvsp[-3].string));
      delete((yyvsp[-1].kv_list));
    }
#line 2656 "yacc_sql.cpp"
    break;

  case 86: /* update_kv_list: ID EQ expression  */
#line 823 "yacc_sql.y"
    {
      (yyval.kv_list) = new KeyValueList{};
      (yyval.kv_list)->attrs.emplace_back((yyvsp[-2].string));
      (yyval.kv_list)->values.emplace_back((yyvsp[0].expression));
      free((yyvsp[-2].string));
    }
#line 2667 "yacc_sql.cpp"
    break;

  case 87: /* update_kv_list: update_kv_list COMMA ID EQ expression  */
#line 830 "yacc_sql.y"
    {
      (yyval.kv_list) = (yyvsp[-4].kv_list);
      (yyval.kv_list)->attrs.emplace_back((yyvsp[-2].string));
      (yyval.kv_list)->values.emplace_back((yyvsp[0].expression));
      free((yyvsp[-2].string));
    }
#line 2678 "yacc_sql.cpp"
    break;

  case 88: /* create_table_select_stmt: AS select_stmt  */
#line 840 "yacc_sql.y"
    {
      (yyval.sql_node) = (yyvsp[0].sql_node);
    }
#line 2686 "yacc_sql.cpp"
    break;

  case 89: /* create_table_select_stmt: select_stmt  */
#line 844 "yacc_sql.y"
    {
      (yyval.sql_node) = (yyvsp[0].sql_node);
    }
#line 2694 "yacc_sql.cpp"
    break;

  case 90: /* select_stmt: SELECT expression_list FROM rel_list inner_join_list where group_by opt_having order_by opt_limit  */
#line 851 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-8].expression_list) != nullptr) {
        (yyval.sql_node)->selection.expressions.swap(*(yyvsp[-8].expression_list));
        delete (yyvsp[-8].expression_list);
      }

      if ((yyvsp[-6].relation_list) != nullptr) {
        if((yyvsp[-5].inner_join) != nullptr && (yyvsp[-6].relation_list)->size() != 2){
          yyerror(&(yyloc),sql_string,sql_result,scanner,"inner join only support one table",true);
          delete (yyvsp[-6].relation_list);
          YYERROR;
        }
        (yyval.sql_node)->selection.relations.swap(*(yyvsp[-6].relation_list));
        delete (yyvsp[-6].relation_list);
      }

      if((yyvsp[-5].inner_join) != nullptr){
        (yyval.sql_node)->selection.inner_join.reset((yyvsp[-5].inner_join));
      }

      if ((yyvsp[-4].expression) != nullptr) {
        (yyval.sql_node)->selection.conditions.reset((yyvsp[-4].expression));
      }

      if ((yyvsp[-3].expression_list) != nullptr) {
        (yyval.sql_node)->selection.group_by.swap(*(yyvsp[-3].expression_list));
        delete (yyvsp[-3].expression_list);
      }

      if((yyvsp[-2].expression) != nullptr){
        (yyval.sql_node)->selection.having_conditions.reset((yyvsp[-2].expression));
      }

      if((yyvsp[-1].order_by_list) != nullptr){
        (yyval.sql_node)->selection.order_by.swap(*(yyvsp[-1].order_by_list));
        delete (yyvsp[-1].order_by_list);
      }

      if((yyvsp[0].limit) != nullptr){
        (yyval.sql_node)->selection.limit = std::unique_ptr<LimitSqlNode>((yyvsp[0].limit));
      }
    }
#line 2742 "yacc_sql.cpp"
    break;

  case 91: /* select_stmt: SELECT expression_list  */
#line 895 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2753 "yacc_sql.cpp"
    break;

  case 92: /* calc_stmt: CALC expression_list  */
#line 905 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2763 "yacc_sql.cpp"
    break;

  case 93: /* expression_list: expression alias  */
#line 914 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->emplace_back((yyvsp[-1].expression));
      if((yyvsp[0].string) != nullptr){
        (yyvsp[-1].expression)->set_alias((yyvsp[0].string));
        free((yyvsp[0].string));
      }
    }
#line 2776 "yacc_sql.cpp"
    break;

  case 94: /* expression_list: expression alias COMMA expression_list  */
#line 923 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      if((yyvsp[-2].string) != nullptr){
        (yyvsp[-3].expression)->set_alias((yyvsp[-2].string));
        free((yyvsp[-2].string));
      }
      (yyval.expression_list)->emplace((yyval.expression_list)->begin(), (yyvsp[-3].expression));
    }
#line 2793 "yacc_sql.cpp"
    break;

  case 95: /* aggr_argument_list: %empty  */
#line 939 "yacc_sql.y"
  {
    (yyval.expression) = nullptr;
  }
#line 2801 "yacc_sql.cpp"
    break;

  case 96: /* aggr_argument_list: expression alias  */
#line 943 "yacc_sql.y"
  {
    if((yyvsp[0].string) != nullptr){
      (yyvsp[-1].expression)->set_alias((yyvsp[0].string));
      free((yyvsp[0].string));
    }
    (yyval.expression) = (yyvsp[-1].expression);
  }
#line 2813 "yacc_sql.cpp"
    break;

  case 97: /* aggr_argument_list: expression alias COMMA expression_list  */
#line 951 "yacc_sql.y"
  {
    (yyval.expression) = nullptr;
    delete (yyvsp[-3].expression);
    free((yyvsp[-2].string));
    delete (yyvsp[0].expression_list);
  }
#line 2824 "yacc_sql.cpp"
    break;

  case 98: /* expression: expression '+' expression  */
#line 960 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2832 "yacc_sql.cpp"
    break;

  case 99: /* expression: expression '-' expression  */
#line 963 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2840 "yacc_sql.cpp"
    break;

  case 100: /* expression: expression '*' expression  */
#line 966 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2848 "yacc_sql.cpp"
    break;

  case 101: /* expression: expression '/' expression  */
#line 969 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2856 "yacc_sql.cpp"
    break;

  case 102: /* expression: LBRACE expression_list RBRACE  */
#line 972 "yacc_sql.y"
                                    {
      if ((yyvsp[-1].expression_list)->size() == 1) {
        (yyval.expression) = (yyvsp[-1].expression_list)->front().release();
      } else {
        (yyval.expression) = new ExprListExpr(std::move(*(yyvsp[-1].expression_list)));
      }
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[-1].expression_list);
    }
#line 2870 "yacc_sql.cpp"
    break;

  case 103: /* expression: '-' expression  */
#line 981 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2878 "yacc_sql.cpp"
    break;

  case 104: /* expression: value  */
#line 984 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2888 "yacc_sql.cpp"
    break;

  case 105: /* expression: rel_attr  */
#line 989 "yacc_sql.y"
               {
      RelAttrSqlNode *node = (yyvsp[0].rel_attr);
      (yyval.expression) = new UnboundFieldExpr(node->relation_name, node->attribute_name);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].rel_attr);
    }
#line 2899 "yacc_sql.cpp"
    break;

  case 106: /* expression: vector_func_type LBRACE expression COMMA expression RBRACE  */
#line 995 "yacc_sql.y"
                                                                 {
      (yyval.expression) = create_function_expression((FunctionExpr::Type)(yyvsp[-5].number), sql_string, (yyvsp[-3].expression), (yyvsp[-1].expression), &(yyloc));
    }
#line 2907 "yacc_sql.cpp"
    break;

  case 107: /* expression: aggregate_expr  */
#line 998 "yacc_sql.y"
                     {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 2915 "yacc_sql.cpp"
    break;

  case 108: /* expression: sub_query_expr  */
#line 1001 "yacc_sql.y"
                     {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 2923 "yacc_sql.cpp"
    break;

  case 109: /* expression: '*'  */
#line 1004 "yacc_sql.y"
          {
      (yyval.expression) = new StarExpr();
    }
#line 2931 "yacc_sql.cpp"
    break;

  case 110: /* vector_func_type: L2_DISTANCE  */
#line 1010 "yacc_sql.y"
                {
      (yyval.number) = static_cast<int>(FunctionExpr::Type::L2_DISTANCE);
    }
#line 2939 "yacc_sql.cpp"
    break;

  case 111: /* vector_func_type: COSINE_DISTANCE  */
#line 1013 "yacc_sql.y"
                      {
      (yyval.number) = static_cast<int>(FunctionExpr::Type::COSINE_DISTANCE);
    }
#line 2947 "yacc_sql.cpp"
    break;

  case 112: /* vector_func_type: INNER_PRODUCT  */
#line 1016 "yacc_sql.y"
                    {
      (yyval.number) = static_cast<int>(FunctionExpr::Type::INNER_PRODUCT);
    }
#line 2955 "yacc_sql.cpp"
    break;

  case 113: /* aggregate_expr: COUNT LBRACE aggr_argument_list RBRACE  */
#line 1022 "yacc_sql.y"
                                           {
      (yyval.expression) = create_aggregate_expression("count", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2963 "yacc_sql.cpp"
    break;

  case 114: /* aggregate_expr: SUM LBRACE aggr_argument_list RBRACE  */
#line 1025 "yacc_sql.y"
                                           {
      (yyval.expression) = create_aggregate_expression("sum", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2971 "yacc_sql.cpp"
    break;

  case 115: /* aggregate_expr: AVG LBRACE aggr_argument_list RBRACE  */
#line 1028 "yacc_sql.y"
                                           {
      (yyval.expression) = create_aggregate_expression("avg", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2979 "yacc_sql.cpp"
    break;

  case 116: /* aggregate_expr: MIN LBRACE aggr_argument_list RBRACE  */
#line 1031 "yacc_sql.y"
                                           {
      (yyval.expression) = create_aggregate_expression("min", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2987 "yacc_sql.cpp"
    break;

  case 117: /* aggregate_expr: MAX LBRACE aggr_argument_list RBRACE  */
#line 1034 "yacc_sql.y"
                                           {
      (yyval.expression) = create_aggregate_expression("max", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2995 "yacc_sql.cpp"
    break;

  case 118: /* sub_query_expr: LBRACE select_stmt RBRACE  */
#line 1040 "yacc_sql.y"
    {
      (yyval.expression) = new SubQueryExpr(std::move((yyvsp[-1].sql_node)->selection));
      delete (yyvsp[-1].sql_node);
    }
#line 3004 "yacc_sql.cpp"
    break;

  case 119: /* rel_attr: ID  */
#line 1047 "yacc_sql.y"
       {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 3014 "yacc_sql.cpp"
    break;

  case 120: /* rel_attr: ID DOT ID  */
#line 1052 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 3026 "yacc_sql.cpp"
    break;

  case 121: /* rel_attr: ID DOT '*'  */
#line 1059 "yacc_sql.y"
                 {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = "*";
      free((yyvsp[-2].string));
    }
#line 3037 "yacc_sql.cpp"
    break;

  case 122: /* rel_attr_list: %empty  */
#line 1068 "yacc_sql.y"
    {
      (yyval.rel_attr_list) = nullptr;
    }
#line 3045 "yacc_sql.cpp"
    break;

  case 123: /* rel_attr_list: COMMA rel_attr rel_attr_list  */
#line 1072 "yacc_sql.y"
    {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }
      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-1].rel_attr));
      delete (yyvsp[-1].rel_attr);
    }
#line 3059 "yacc_sql.cpp"
    break;

  case 124: /* relation: ID  */
#line 1085 "yacc_sql.y"
       {
      (yyval.string) = (yyvsp[0].string);
    }
#line 3067 "yacc_sql.cpp"
    break;

  case 125: /* rel_list: relation alias  */
#line 1090 "yacc_sql.y"
                  {
      (yyval.relation_list) = new std::vector<std::string>();
      (yyval.relation_list)->push_back((yyvsp[-1].string));
      if((yyvsp[0].string) != nullptr){
        (yyval.relation_list)->push_back((yyvsp[0].string)); //存在别名
      }else{
        (yyval.relation_list)->push_back(""); //别名为空
      }
      free((yyvsp[-1].string));
    }
#line 3082 "yacc_sql.cpp"
    break;

  case 126: /* rel_list: relation alias COMMA rel_list  */
#line 1100 "yacc_sql.y"
                                    { 
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new std::vector<std::string>;
      }

//Todo 改变遍历顺序
      if((yyvsp[-2].string) != nullptr){
        (yyval.relation_list)->insert((yyval.relation_list)->begin(), (yyvsp[-2].string)); 
      }else{
        (yyval.relation_list)->insert((yyval.relation_list)->begin(),"");
      }
      (yyval.relation_list)->insert((yyval.relation_list)->begin(), (yyvsp[-3].string));
      free((yyvsp[-3].string));
    }
#line 3103 "yacc_sql.cpp"
    break;

  case 127: /* inner_join_list: %empty  */
#line 1120 "yacc_sql.y"
    {
      (yyval.inner_join) = nullptr;
    }
#line 3111 "yacc_sql.cpp"
    break;

  case 128: /* inner_join_list: inner_join_list inner_join_rel  */
#line 1124 "yacc_sql.y"
    {
      if((yyvsp[-1].inner_join) == nullptr){
        (yyval.inner_join) = new InnerJoinSqlNode();
      }else{
        (yyval.inner_join) = (yyvsp[-1].inner_join);
      }
      (yyval.inner_join)->relations.emplace_back((yyvsp[0].inner_join_unit)->relation);
      (yyval.inner_join)->relations.emplace_back((yyvsp[0].inner_join_unit)->relation_alias);
      (yyval.inner_join)->conditions.emplace_back(std::move((yyvsp[0].inner_join_unit)->condition));
      delete (yyvsp[0].inner_join_unit);
    }
#line 3127 "yacc_sql.cpp"
    break;

  case 129: /* inner_join_rel: INNER JOIN relation alias ON condition  */
#line 1137 "yacc_sql.y"
                                          {
      (yyval.inner_join_unit) = new InnerJoinUnit((yyvsp[-3].string)); 
      if((yyvsp[-2].string) != nullptr){
        (yyval.inner_join_unit)->relation_alias = (yyvsp[-2].string);
        free((yyvsp[-2].string));
      }else{
        (yyval.inner_join_unit)->relation_alias = "";
      }
      (yyval.inner_join_unit)->condition.reset((yyvsp[0].expression)); 
      free((yyvsp[-3].string));
    }
#line 3143 "yacc_sql.cpp"
    break;

  case 130: /* where: %empty  */
#line 1153 "yacc_sql.y"
    {
      (yyval.expression) = nullptr;
    }
#line 3151 "yacc_sql.cpp"
    break;

  case 131: /* where: WHERE condition  */
#line 1156 "yacc_sql.y"
                      {
      (yyval.expression) = (yyvsp[0].expression);  
    }
#line 3159 "yacc_sql.cpp"
    break;

  case 132: /* condition: expression comp_op expression  */
#line 1162 "yacc_sql.y"
    {
      (yyval.expression) = new ComparisonExpr((yyvsp[-1].comp), (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 3167 "yacc_sql.cpp"
    break;

  case 133: /* condition: exists_op expression  */
#line 1166 "yacc_sql.y"
    {
      Value val;
      val.set_null();
      ValueExpr *value_expr = new ValueExpr(val);
      (yyval.expression) = new ComparisonExpr((yyvsp[-1].comp), value_expr, (yyvsp[0].expression));
    }
#line 3178 "yacc_sql.cpp"
    break;

  case 134: /* condition: expression IS opt_null  */
#line 1173 "yacc_sql.y"
    {
      Value val;
      val.set_null();
      ValueExpr *value_expr = new ValueExpr(val);
      (yyval.expression) = new ComparisonExpr((yyvsp[0].bools) ? IS_NULL : IS_NOT_NULL, (yyvsp[-2].expression), value_expr);
    }
#line 3189 "yacc_sql.cpp"
    break;

  case 135: /* condition: condition AND condition  */
#line 1180 "yacc_sql.y"
    {
      (yyval.expression) = new ConjunctionExpr(ConjunctionExpr::Type::AND, (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 3197 "yacc_sql.cpp"
    break;

  case 136: /* condition: condition OR condition  */
#line 1184 "yacc_sql.y"
    {
      (yyval.expression) = new ConjunctionExpr(ConjunctionExpr::Type::OR, (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 3205 "yacc_sql.cpp"
    break;

  case 137: /* comp_op: EQ  */
#line 1190 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 3211 "yacc_sql.cpp"
    break;

  case 138: /* comp_op: LT  */
#line 1191 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 3217 "yacc_sql.cpp"
    break;

  case 139: /* comp_op: GT  */
#line 1192 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3223 "yacc_sql.cpp"
    break;

  case 140: /* comp_op: LE  */
#line 1193 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3229 "yacc_sql.cpp"
    break;

  case 141: /* comp_op: LT GT  */
#line 1194 "yacc_sql.y"
            { (yyval.comp) = NOT_EQUAL; }
#line 3235 "yacc_sql.cpp"
    break;

  case 142: /* comp_op: GE  */
#line 1195 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3241 "yacc_sql.cpp"
    break;

  case 143: /* comp_op: NE  */
#line 1196 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3247 "yacc_sql.cpp"
    break;

  case 144: /* comp_op: LIKE  */
#line 1197 "yacc_sql.y"
           { (yyval.comp) = LIKE_OP; }
#line 3253 "yacc_sql.cpp"
    break;

  case 145: /* comp_op: NOT LIKE  */
#line 1198 "yacc_sql.y"
               { (yyval.comp) = NOT_LIKE_OP; }
#line 3259 "yacc_sql.cpp"
    break;

  case 146: /* comp_op: IN  */
#line 1199 "yacc_sql.y"
         { (yyval.comp) = IN_OP; }
#line 3265 "yacc_sql.cpp"
    break;

  case 147: /* comp_op: NOT IN  */
#line 1200 "yacc_sql.y"
             { (yyval.comp) = NOT_IN_OP; }
#line 3271 "yacc_sql.cpp"
    break;

  case 148: /* exists_op: EXISTS  */
#line 1204 "yacc_sql.y"
         { (yyval.comp) = EXISTS_OP; }
#line 3277 "yacc_sql.cpp"
    break;

  case 149: /* exists_op: NOT EXISTS  */
#line 1205 "yacc_sql.y"
               { (yyval.comp) = NOT_EXISTS_OP; }
#line 3283 "yacc_sql.cpp"
    break;

  case 150: /* group_by: %empty  */
#line 1210 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3291 "yacc_sql.cpp"
    break;

  case 151: /* group_by: GROUP BY expression_list  */
#line 1214 "yacc_sql.y"
    {
      (yyval.expression_list) = (yyvsp[0].expression_list);
    }
#line 3299 "yacc_sql.cpp"
    break;

  case 152: /* opt_having: %empty  */
#line 1221 "yacc_sql.y"
  {
    (yyval.expression) = nullptr;
  }
#line 3307 "yacc_sql.cpp"
    break;

  case 153: /* opt_having: HAVING condition  */
#line 1225 "yacc_sql.y"
  {
    (yyval.expression) = (yyvsp[0].expression);
  }
#line 3315 "yacc_sql.cpp"
    break;

  case 154: /* order_by: %empty  */
#line 1233 "yacc_sql.y"
    {
      (yyval.order_by_list) = nullptr;
    }
#line 3323 "yacc_sql.cpp"
    break;

  case 155: /* order_by: ORDER BY order_by_list  */
#line 1237 "yacc_sql.y"
    {
      (yyval.order_by_list) = (yyvsp[0].order_by_list);
      std::reverse((yyval.order_by_list)->begin(), (yyval.order_by_list)->end());
    }
#line 3332 "yacc_sql.cpp"
    break;

  case 156: /* opt_limit: %empty  */
#line 1245 "yacc_sql.y"
    {
      (yyval.limit) = nullptr;
    }
#line 3340 "yacc_sql.cpp"
    break;

  case 157: /* opt_limit: LIMIT number  */
#line 1249 "yacc_sql.y"
    {
      (yyval.limit) = new LimitSqlNode();
      (yyval.limit)->number = (yyvsp[0].number);
    }
#line 3349 "yacc_sql.cpp"
    break;

  case 158: /* order_by_list: order_unit  */
#line 1257 "yacc_sql.y"
    {
      (yyval.order_by_list) = new std::vector<std::unique_ptr<OrderBySqlNode>>();
      (yyval.order_by_list)->emplace_back((yyvsp[0].order_unit));
    }
#line 3358 "yacc_sql.cpp"
    break;

  case 159: /* order_by_list: order_unit COMMA order_by_list  */
#line 1262 "yacc_sql.y"
    {
      (yyval.order_by_list) = (yyvsp[0].order_by_list);
      (yyval.order_by_list)->emplace_back((yyvsp[-2].order_unit));
    }
#line 3367 "yacc_sql.cpp"
    break;

  case 160: /* order_unit: rel_attr order_op  */
#line 1270 "yacc_sql.y"
    {
      (yyval.order_unit) = new OrderBySqlNode;
      RelAttrSqlNode *node = (yyvsp[-1].rel_attr);
      (yyval.order_unit)->unbound_field = std::make_unique<UnboundFieldExpr>(node->relation_name, node->attribute_name);
      (yyval.order_unit)->order_op = (yyvsp[0].order_op);
      delete (yyvsp[-1].rel_attr);
    }
#line 3379 "yacc_sql.cpp"
    break;

  case 161: /* order_unit: vector_func_type LBRACE expression COMMA expression RBRACE order_op  */
#line 1277 "yacc_sql.y"
                                                                          {
      (yyval.order_unit) = new OrderBySqlNode;
      (yyval.order_unit)->unbound_field = std::unique_ptr<Expression>(create_function_expression((FunctionExpr::Type)(yyvsp[-6].number), sql_string, (yyvsp[-4].expression), (yyvsp[-2].expression), &(yyloc)));
      (yyval.order_unit)->order_op = (yyvsp[0].order_op);
    }
#line 3389 "yacc_sql.cpp"
    break;

  case 162: /* order_op: %empty  */
#line 1285 "yacc_sql.y"
    {
      (yyval.order_op) = OrderOp::ASC;
    }
#line 3397 "yacc_sql.cpp"
    break;

  case 163: /* order_op: ASC  */
#line 1289 "yacc_sql.y"
    {
      (yyval.order_op) = OrderOp::ASC;
    }
#line 3405 "yacc_sql.cpp"
    break;

  case 164: /* order_op: DESC  */
#line 1293 "yacc_sql.y"
    {
      (yyval.order_op) = OrderOp::DESC;
    }
#line 3413 "yacc_sql.cpp"
    break;

  case 165: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 1300 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3427 "yacc_sql.cpp"
    break;

  case 166: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1313 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3436 "yacc_sql.cpp"
    break;

  case 167: /* set_variable_stmt: SET ID EQ value  */
#line 1321 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3448 "yacc_sql.cpp"
    break;


#line 3452 "yacc_sql.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (&yylloc, sql_string, sql_result, scanner, yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, sql_string, sql_result, scanner, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 1333 "yacc_sql.y"

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

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
  YYSYMBOL_select_stmt = 134,              /* select_stmt  */
  YYSYMBOL_calc_stmt = 135,                /* calc_stmt  */
  YYSYMBOL_expression_list = 136,          /* expression_list  */
  YYSYMBOL_aggr_argument_list = 137,       /* aggr_argument_list  */
  YYSYMBOL_expression = 138,               /* expression  */
  YYSYMBOL_vector_func_type = 139,         /* vector_func_type  */
  YYSYMBOL_aggregate_expr = 140,           /* aggregate_expr  */
  YYSYMBOL_sub_query_expr = 141,           /* sub_query_expr  */
  YYSYMBOL_rel_attr = 142,                 /* rel_attr  */
  YYSYMBOL_rel_attr_list = 143,            /* rel_attr_list  */
  YYSYMBOL_relation = 144,                 /* relation  */
  YYSYMBOL_rel_list = 145,                 /* rel_list  */
  YYSYMBOL_inner_join_list = 146,          /* inner_join_list  */
  YYSYMBOL_inner_join_rel = 147,           /* inner_join_rel  */
  YYSYMBOL_where = 148,                    /* where  */
  YYSYMBOL_condition = 149,                /* condition  */
  YYSYMBOL_comp_op = 150,                  /* comp_op  */
  YYSYMBOL_exists_op = 151,                /* exists_op  */
  YYSYMBOL_group_by = 152,                 /* group_by  */
  YYSYMBOL_opt_having = 153,               /* opt_having  */
  YYSYMBOL_order_by = 154,                 /* order_by  */
  YYSYMBOL_opt_limit = 155,                /* opt_limit  */
  YYSYMBOL_order_by_list = 156,            /* order_by_list  */
  YYSYMBOL_order_unit = 157,               /* order_unit  */
  YYSYMBOL_order_op = 158,                 /* order_op  */
  YYSYMBOL_load_data_stmt = 159,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 160,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 161,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 162             /* opt_semicolon  */
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
#define YYLAST   365

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  97
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  66
/* YYNRULES -- Number of rules.  */
#define YYNRULES  165
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  337

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
       0,   286,   286,   294,   295,   296,   297,   298,   299,   300,
     301,   302,   303,   304,   305,   306,   307,   308,   309,   310,
     311,   312,   313,   314,   315,   319,   325,   330,   336,   342,
     348,   354,   378,   385,   391,   400,   421,   429,   444,   466,
     481,   484,   491,   494,   506,   509,   518,   530,   533,   546,
     570,   595,   598,   602,   609,   613,   617,   623,   626,   627,
     628,   629,   630,   631,   634,   647,   667,   670,   680,   695,
     699,   703,   717,   721,   727,   734,   737,   742,   745,   749,
     754,   757,   762,   775,   791,   798,   808,   852,   862,   871,
     880,   897,   900,   908,   918,   921,   924,   927,   930,   939,
     942,   947,   953,   956,   959,   962,   968,   971,   974,   980,
     983,   986,   989,   992,   997,  1005,  1010,  1017,  1026,  1029,
    1043,  1048,  1058,  1078,  1081,  1095,  1111,  1114,  1119,  1123,
    1130,  1137,  1141,  1148,  1149,  1150,  1151,  1152,  1153,  1154,
    1155,  1156,  1157,  1158,  1162,  1163,  1168,  1171,  1179,  1182,
    1191,  1194,  1203,  1206,  1214,  1219,  1227,  1235,  1243,  1246,
    1250,  1257,  1270,  1278,  1288,  1289
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
  "select_stmt", "calc_stmt", "expression_list", "aggr_argument_list",
  "expression", "vector_func_type", "aggregate_expr", "sub_query_expr",
  "rel_attr", "rel_attr_list", "relation", "rel_list", "inner_join_list",
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

#define YYPACT_NINF (-281)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     222,    -3,   155,   131,   131,   -78,    13,  -281,     9,    -9,
     -18,  -281,  -281,  -281,  -281,  -281,    -1,    25,   222,   138,
     148,  -281,  -281,  -281,  -281,  -281,  -281,  -281,  -281,  -281,
    -281,  -281,  -281,  -281,  -281,  -281,  -281,  -281,  -281,  -281,
    -281,  -281,  -281,    75,    84,   150,  -281,   160,    95,   100,
     102,   -10,  -281,   165,   185,   186,   187,   188,  -281,  -281,
    -281,  -281,  -281,   166,  -281,  -281,   131,  -281,   -63,  -281,
    -281,    52,   196,  -281,  -281,  -281,   173,  -281,  -281,   142,
     143,   -44,   161,   171,  -281,  -281,  -281,  -281,   208,   209,
     149,   158,  -281,  -281,   179,   221,   223,   131,   131,   131,
     131,   131,    37,  -281,  -281,  -281,   -23,  -281,   159,  -281,
     131,   131,   131,   131,   226,   131,   167,    77,   -44,   200,
      64,   168,   172,   174,   203,   210,   211,   177,  -281,  -281,
     239,    52,   244,   245,   246,   247,  -281,  -281,   -63,  -281,
    -281,    65,    65,  -281,  -281,   131,     8,  -281,   -44,  -281,
     189,   249,   227,   191,  -281,   232,   147,   248,   255,   275,
     205,   206,  -281,  -281,   267,  -281,  -281,  -281,  -281,  -281,
    -281,   131,   268,    -7,   269,    64,    45,  -281,   233,    76,
     287,  -281,  -281,  -281,  -281,  -281,  -281,   129,   172,   274,
     214,   276,  -281,   278,   279,   131,     0,   167,   281,  -281,
     299,   189,   282,   280,   229,  -281,   220,   107,   131,   131,
     228,  -281,   230,   231,   270,  -281,  -281,   248,   256,   255,
    -281,   234,   235,  -281,  -281,  -281,   167,   315,   310,   269,
     273,   131,   298,  -281,   133,    56,  -281,   259,  -281,  -281,
    -281,  -281,  -281,  -281,   131,    45,    45,   103,   103,   262,
    -281,  -281,   301,  -281,  -281,   265,  -281,  -281,   255,   255,
     -44,   131,    45,   321,  -281,   305,   280,   103,  -281,  -281,
    -281,  -281,  -281,   103,  -281,   283,   131,   133,   271,   306,
     307,   284,  -281,   107,   327,   250,    64,  -281,   103,  -281,
     251,   302,  -281,    45,   -58,   231,  -281,   280,  -281,   314,
    -281,   107,   316,   146,  -281,   317,  -281,   319,   309,   131,
    -281,  -281,  -281,   -58,  -281,   285,    14,  -281,   304,   131,
     320,     4,   312,   146,   286,  -281,    36,   324,   313,   289,
     231,   328,   303,   290,   231,   330,  -281
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    40,     0,     0,     0,     0,     0,    27,     0,     0,
       0,    28,    29,    30,    26,    25,     0,     0,     0,     0,
     164,    24,    23,    16,    17,    18,    19,     8,     9,    10,
      11,    12,    13,    14,    15,     5,     7,     6,     4,     3,
      20,    21,    22,     0,     0,     0,    41,     0,     0,     0,
       0,     0,    74,     0,     0,     0,     0,     0,   106,   107,
     108,    69,    70,   115,    73,    71,     0,   105,    77,   100,
      88,    51,     0,   103,   104,   101,    87,    34,    33,     0,
       0,    51,     0,     0,   162,     1,   165,     2,     0,    42,
       0,     0,    32,    36,     0,     0,     0,    91,    91,    91,
      91,    91,     0,    99,    80,    81,     0,    78,     0,    52,
       0,     0,     0,     0,    89,     0,     0,     0,    51,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   114,    98,
       0,    51,     0,     0,     0,     0,   116,   117,     0,    72,
      53,    94,    95,    96,    97,     0,     0,   120,    51,   123,
       0,     0,   126,     0,   163,     0,     0,    47,    44,     0,
       0,     0,    46,   109,    92,   110,   111,   113,   112,    79,
      90,     0,   121,   126,   118,     0,     0,    82,     0,   126,
       0,    58,    59,    60,    61,    62,    63,    54,     0,     0,
       0,     0,    35,     0,     0,     0,     0,     0,     0,   124,
     146,     0,     0,    66,     0,   144,     0,   127,     0,     0,
       0,    83,     0,     0,     0,    56,    50,    47,    75,    44,
      43,     0,     0,    93,   102,   122,     0,     0,   148,   118,
       0,     0,     0,   145,    54,     0,   133,   134,   135,   136,
     138,   139,   140,   142,     0,     0,     0,   129,    84,     0,
     161,    57,     0,    55,    48,     0,    31,    45,    44,    44,
      51,     0,     0,   150,   119,     0,    66,    68,    64,   130,
     141,   143,   137,   128,   131,   132,     0,    54,     0,     0,
       0,     0,   147,   149,     0,   152,     0,    67,    85,    49,
       0,     0,    37,     0,     0,     0,    86,    66,    76,     0,
      38,   125,     0,   158,   151,   154,   153,     0,     0,     0,
     159,   160,   156,     0,    65,     0,     0,   155,     0,     0,
       0,     0,     0,   158,     0,   157,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    39
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -281,  -281,   339,  -281,  -281,  -281,  -281,  -281,  -281,  -281,
    -281,  -281,  -281,  -281,  -281,  -281,  -281,  -281,  -281,  -187,
    -281,   141,   175,   -74,  -217,  -247,  -281,  -281,  -242,  -281,
    -119,  -281,  -281,   224,  -281,  -281,  -281,   -48,  -281,    -4,
      99,   -61,  -280,  -281,  -281,  -148,   130,   134,   164,  -281,
    -281,  -152,  -234,  -281,  -281,  -281,  -281,  -281,  -281,    51,
    -281,    42,  -281,  -281,  -281,  -281
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,   300,    47,   124,   191,
      34,   189,   157,   114,   216,   252,   187,    35,   232,   266,
      69,   256,   106,   107,    36,    37,   179,    38,    39,    70,
     130,    71,    72,    73,    74,    75,   202,   148,   149,   173,
     199,   177,   207,   244,   208,   228,   263,   285,   296,   304,
     305,   312,    40,    41,    42,    87
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      76,   154,   174,    95,   138,   103,     4,   119,    43,    77,
      44,   274,   275,   108,   302,    51,   198,   269,    58,    59,
      60,   200,   104,   105,   287,    78,   224,   211,   283,    63,
     323,    45,   257,   302,    52,   171,   131,   131,   131,   131,
     131,   319,    80,   109,   152,   176,   327,    96,   306,   141,
     142,   143,   144,   229,   146,   307,   203,   164,    79,   301,
     289,    53,    54,    55,    56,    57,    58,    59,    60,    81,
      51,   279,   280,   139,   172,    61,    62,    63,    64,    65,
      46,    66,    67,   331,    83,    68,    82,   335,   204,    52,
     110,   111,   112,   113,   110,   111,   112,   113,   110,   111,
     112,   113,   150,   210,   110,   111,   112,   113,    52,   108,
     196,   192,    58,    59,    60,   206,    53,    54,    55,    56,
      57,    58,    59,    60,   136,   205,   270,   151,   176,   137,
      61,    62,    63,    64,    65,   271,    66,    67,    85,   109,
      68,   170,   110,   111,   112,   113,   303,   247,   248,    61,
      62,    86,    64,    65,   213,   310,    51,   112,   113,    68,
     245,   246,    88,   311,    90,   303,    48,   297,    49,    50,
     267,    89,   214,   215,    91,    52,   214,   215,   181,   182,
     183,   184,    92,   273,   206,   206,   281,    93,   185,    94,
      97,   223,   186,   110,   111,   112,   113,   132,   133,   134,
     135,   206,    53,    54,    55,    56,    57,    58,    59,    60,
      98,    99,   100,   101,   102,   288,    61,    62,    63,    64,
      65,   115,    66,    67,   116,   120,    68,     1,     2,   117,
     118,   121,   206,   122,   123,   127,   125,     3,     4,     5,
       6,     7,     8,     9,    10,   126,   140,   128,   316,   129,
      11,    12,    13,   145,   147,   153,   155,   282,   321,   156,
     159,   158,   234,   235,   162,   163,   160,   161,    14,    15,
     165,   166,   167,   168,   175,   188,    63,    16,   178,   176,
      17,   180,   190,    18,   236,   237,   238,   239,   240,   241,
     242,     4,   193,   194,   195,   197,   201,   209,   212,   243,
     218,   219,   220,   221,   222,   226,   227,   231,   230,   233,
     110,   111,   112,   113,   253,   249,   251,   250,   255,   261,
     262,   258,   259,   265,   268,   272,   276,   277,   278,   284,
     286,   294,   291,   292,   295,   290,   245,   299,   298,   308,
     293,   309,   320,   333,   313,   314,   315,   322,   324,   318,
     326,   328,   329,   330,   334,   332,   336,    84,   254,   264,
     260,   225,   169,   217,   317,   325
};

static const yytype_int16 yycheck[] =
{
       4,   120,   150,    51,    27,    66,    16,    81,    11,    87,
      13,   245,   246,    57,   294,    25,    23,   234,    76,    77,
      78,   173,    85,    86,   266,    12,    26,   179,   262,    87,
      26,    34,   219,   313,    44,    27,    97,    98,    99,   100,
     101,    27,    51,    87,   118,    52,   326,    51,   295,   110,
     111,   112,   113,   201,   115,   297,   175,   131,    49,   293,
     277,    71,    72,    73,    74,    75,    76,    77,    78,    87,
      25,   258,   259,    96,   148,    85,    86,    87,    88,    89,
      83,    91,    92,   330,    59,    95,    87,   334,    43,    44,
      90,    91,    92,    93,    90,    91,    92,    93,    90,    91,
      92,    93,    25,    27,    90,    91,    92,    93,    44,    57,
     171,   159,    76,    77,    78,   176,    71,    72,    73,    74,
      75,    76,    77,    78,    87,    80,    70,    50,    52,    92,
      85,    86,    87,    88,    89,    79,    91,    92,     0,    87,
      95,   145,    90,    91,    92,    93,   294,   208,   209,    85,
      86,     3,    88,    89,    25,     9,    25,    92,    93,    95,
      53,    54,    87,    17,    14,   313,    11,   286,    13,    14,
     231,    87,    43,    44,    14,    44,    43,    44,    31,    32,
      33,    34,    87,   244,   245,   246,   260,    87,    41,    87,
      25,   195,    45,    90,    91,    92,    93,    98,    99,   100,
     101,   262,    71,    72,    73,    74,    75,    76,    77,    78,
      25,    25,    25,    25,    48,   276,    85,    86,    87,    88,
      89,    25,    91,    92,    51,    64,    95,     5,     6,    87,
      87,    60,   293,    25,    25,    56,    87,    15,    16,    17,
      18,    19,    20,    21,    22,    87,    87,    26,   309,    26,
      28,    29,    30,    27,    87,    55,    88,   261,   319,    87,
      57,    87,    42,    43,    87,    26,    56,    56,    46,    47,
      26,    26,    26,    26,    25,    27,    87,    55,    87,    52,
      58,    49,    27,    61,    64,    65,    66,    67,    68,    69,
      70,    16,    87,    87,    27,    27,    27,    64,    11,    79,
      26,    87,    26,    25,    25,    24,     7,    27,    26,    80,
      90,    91,    92,    93,    44,    87,    85,    87,    62,     4,
      10,    87,    87,    50,    26,    66,    64,    26,    63,     8,
      25,     4,    26,    26,    84,    64,    53,    35,    87,    25,
      56,    25,    38,    40,    27,    26,    37,    27,    36,    64,
      64,    27,    39,    64,    64,    27,    26,    18,   217,   229,
     226,   197,   138,   188,   313,   323
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     6,    15,    16,    17,    18,    19,    20,    21,
      22,    28,    29,    30,    46,    47,    55,    58,    61,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   117,   124,   131,   132,   134,   135,
     159,   160,   161,    11,    13,    34,    83,   114,    11,    13,
      14,    25,    44,    71,    72,    73,    74,    75,    76,    77,
      78,    85,    86,    87,    88,    89,    91,    92,    95,   127,
     136,   138,   139,   140,   141,   142,   136,    87,    12,    49,
      51,    87,    87,    59,    99,     0,     3,   162,    87,    87,
      14,    14,    87,    87,    87,   134,   136,    25,    25,    25,
      25,    25,    48,   138,    85,    86,   129,   130,    57,    87,
      90,    91,    92,    93,   120,    25,    51,    87,    87,   120,
      64,    60,    25,    25,   115,    87,    87,    56,    26,    26,
     137,   138,   137,   137,   137,   137,    87,    92,    27,    96,
      87,   138,   138,   138,   138,    27,   138,    87,   144,   145,
      25,    50,   120,    55,   127,    88,    87,   119,    87,    57,
      56,    56,    87,    26,   120,    26,    26,    26,    26,   130,
     136,    27,   120,   146,   142,    25,    52,   148,    87,   133,
      49,    31,    32,    33,    34,    41,    45,   123,    27,   118,
      27,   116,   134,    87,    87,    27,   138,    27,    23,   147,
     148,    27,   143,   127,    43,    80,   138,   149,   151,    64,
      27,   148,    11,    25,    43,    44,   121,   119,    26,    87,
      26,    25,    25,   136,    26,   145,    24,     7,   152,   142,
      26,    27,   125,    80,    42,    43,    64,    65,    66,    67,
      68,    69,    70,    79,   150,    53,    54,   138,   138,    87,
      87,    85,   122,    44,   118,    62,   128,   116,    87,    87,
     144,     4,    10,   153,   143,    50,   126,   138,    26,   121,
      70,    79,    66,   138,   149,   149,    64,    26,    63,   116,
     116,   120,   136,   149,     8,   154,    25,   125,   138,   121,
      64,    26,    26,    56,     4,    84,   155,   127,    87,    35,
     113,   149,   139,   142,   156,   157,   122,   125,    25,    25,
       9,    17,   158,    27,    26,    37,   138,   156,    64,    27,
      38,   138,    27,    26,    36,   158,    64,   139,    27,    39,
      64,   122,    27,    40,    64,   122,    26
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    97,    98,    99,    99,    99,    99,    99,    99,    99,
      99,    99,    99,    99,    99,    99,    99,    99,    99,    99,
      99,    99,    99,    99,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   112,   113,
     114,   114,   115,   115,   116,   116,   117,   118,   118,   119,
     119,   120,   120,   120,   121,   121,   121,   122,   123,   123,
     123,   123,   123,   123,   124,   124,   125,   125,   126,   127,
     127,   127,   127,   127,   127,   128,   128,   129,   129,   129,
     130,   130,   131,   132,   133,   133,   134,   134,   135,   136,
     136,   137,   137,   137,   138,   138,   138,   138,   138,   138,
     138,   138,   138,   138,   138,   138,   139,   139,   139,   140,
     140,   140,   140,   140,   141,   142,   142,   142,   143,   143,
     144,   145,   145,   146,   146,   147,   148,   148,   149,   149,
     149,   149,   149,   150,   150,   150,   150,   150,   150,   150,
     150,   150,   150,   150,   151,   151,   152,   152,   153,   153,
     154,   154,   155,   155,   156,   156,   157,   157,   158,   158,
     158,   159,   160,   161,   162,   162
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     8,     3,     2,     2,     6,     3,    10,    11,    18,
       0,     1,     0,     4,     0,     3,     5,     0,     3,     6,
       3,     0,     1,     2,     0,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     8,    12,     0,     3,     1,     1,
       1,     1,     3,     1,     1,     0,     4,     0,     1,     3,
       1,     1,     5,     6,     3,     5,    10,     2,     2,     2,
       4,     0,     2,     4,     3,     3,     3,     3,     3,     2,
       1,     1,     6,     1,     1,     1,     1,     1,     1,     4,
       4,     4,     4,     4,     3,     1,     3,     3,     0,     3,
       1,     2,     4,     0,     2,     6,     0,     2,     3,     2,
       3,     3,     3,     1,     1,     1,     1,     2,     1,     1,
       1,     2,     1,     2,     1,     2,     0,     3,     0,     2,
       0,     3,     0,     2,     1,     3,     2,     7,     0,     1,
       1,     7,     2,     4,     0,     1
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
#line 287 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1955 "yacc_sql.cpp"
    break;

  case 25: /* exit_stmt: EXIT  */
#line 319 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1964 "yacc_sql.cpp"
    break;

  case 26: /* help_stmt: HELP  */
#line 325 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1972 "yacc_sql.cpp"
    break;

  case 27: /* sync_stmt: SYNC  */
#line 330 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1980 "yacc_sql.cpp"
    break;

  case 28: /* begin_stmt: TRX_BEGIN  */
#line 336 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1988 "yacc_sql.cpp"
    break;

  case 29: /* commit_stmt: TRX_COMMIT  */
#line 342 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1996 "yacc_sql.cpp"
    break;

  case 30: /* rollback_stmt: TRX_ROLLBACK  */
#line 348 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 2004 "yacc_sql.cpp"
    break;

  case 31: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format  */
#line 355 "yacc_sql.y"
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
#line 2029 "yacc_sql.cpp"
    break;

  case 32: /* drop_table_stmt: DROP TABLE ID  */
#line 378 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2039 "yacc_sql.cpp"
    break;

  case 33: /* show_tables_stmt: SHOW TABLES  */
#line 385 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 2047 "yacc_sql.cpp"
    break;

  case 34: /* desc_table_stmt: DESC ID  */
#line 391 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2057 "yacc_sql.cpp"
    break;

  case 35: /* create_view_stmt: CREATE VIEW ID view_brace_id_list AS select_stmt  */
#line 401 "yacc_sql.y"
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
#line 2079 "yacc_sql.cpp"
    break;

  case 36: /* drop_view_stmt: DROP VIEW ID  */
#line 421 "yacc_sql.y"
                 {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_VIEW);
      (yyval.sql_node)->drop_view.view_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2089 "yacc_sql.cpp"
    break;

  case 37: /* create_index_stmt: CREATE opt_unique INDEX ID ON ID LBRACE ID idx_col_list RBRACE  */
#line 430 "yacc_sql.y"
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
#line 2108 "yacc_sql.cpp"
    break;

  case 38: /* create_index_stmt: CREATE VECTOR_T INDEX ID ON ID LBRACE ID idx_col_list RBRACE vector_index_with  */
#line 445 "yacc_sql.y"
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
#line 2131 "yacc_sql.cpp"
    break;

  case 39: /* vector_index_with: WITH_T LBRACE TYPE_T EQ IVFFLAT_T COMMA DISTANCE_T EQ vector_func_type COMMA LISTS_T EQ number COMMA PROBES_T EQ number RBRACE  */
#line 467 "yacc_sql.y"
    {
      VectorIndexWith *with = new VectorIndexWith();
      with->func_type = (yyvsp[-9].number);
      // type 只有 ivfflat
      with->type = 1;
      with->lists = (yyvsp[-5].number);
      with->probes = (yyvsp[-1].number);

      (yyval.vector_index_with) = with;
    }
#line 2146 "yacc_sql.cpp"
    break;

  case 40: /* opt_unique: %empty  */
#line 481 "yacc_sql.y"
    {
      (yyval.bools) = false;
    }
#line 2154 "yacc_sql.cpp"
    break;

  case 41: /* opt_unique: UNIQUE  */
#line 485 "yacc_sql.y"
    {
      (yyval.bools) = true;
    }
#line 2162 "yacc_sql.cpp"
    break;

  case 42: /* view_brace_id_list: %empty  */
#line 491 "yacc_sql.y"
    {
      (yyval.id_list) = nullptr;
    }
#line 2170 "yacc_sql.cpp"
    break;

  case 43: /* view_brace_id_list: LBRACE ID idx_col_list RBRACE  */
#line 494 "yacc_sql.y"
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
#line 2185 "yacc_sql.cpp"
    break;

  case 44: /* idx_col_list: %empty  */
#line 506 "yacc_sql.y"
    {
      (yyval.relation_list) = new std::vector<std::string>;
    }
#line 2193 "yacc_sql.cpp"
    break;

  case 45: /* idx_col_list: COMMA ID idx_col_list  */
#line 510 "yacc_sql.y"
    {
      (yyval.relation_list) = (yyvsp[0].relation_list);
      (yyval.relation_list)->emplace_back((yyvsp[-1].string));
      free((yyvsp[-1].string));
    }
#line 2203 "yacc_sql.cpp"
    break;

  case 46: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 519 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2215 "yacc_sql.cpp"
    break;

  case 47: /* attr_def_list: %empty  */
#line 530 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2223 "yacc_sql.cpp"
    break;

  case 48: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 534 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2237 "yacc_sql.cpp"
    break;

  case 49: /* attr_def: ID type LBRACE number RBRACE opt_null  */
#line 547 "yacc_sql.y"
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
#line 2265 "yacc_sql.cpp"
    break;

  case 50: /* attr_def: ID type opt_null  */
#line 571 "yacc_sql.y"
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
#line 2290 "yacc_sql.cpp"
    break;

  case 51: /* alias: %empty  */
#line 595 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2298 "yacc_sql.cpp"
    break;

  case 52: /* alias: ID  */
#line 599 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2306 "yacc_sql.cpp"
    break;

  case 53: /* alias: AS ID  */
#line 603 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2314 "yacc_sql.cpp"
    break;

  case 54: /* opt_null: %empty  */
#line 609 "yacc_sql.y"
    {
      // 根据 primary-null.result 来看，默认是 not null
      (yyval.bools) = true;
    }
#line 2323 "yacc_sql.cpp"
    break;

  case 55: /* opt_null: NOT NULL_T  */
#line 614 "yacc_sql.y"
    {
      (yyval.bools) = false;
    }
#line 2331 "yacc_sql.cpp"
    break;

  case 56: /* opt_null: NULL_T  */
#line 618 "yacc_sql.y"
    {
      (yyval.bools) = true;
    }
#line 2339 "yacc_sql.cpp"
    break;

  case 57: /* number: NUMBER  */
#line 623 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2345 "yacc_sql.cpp"
    break;

  case 58: /* type: INT_T  */
#line 626 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::INTS); }
#line 2351 "yacc_sql.cpp"
    break;

  case 59: /* type: STRING_T  */
#line 627 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::CHARS); }
#line 2357 "yacc_sql.cpp"
    break;

  case 60: /* type: FLOAT_T  */
#line 628 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::FLOATS); }
#line 2363 "yacc_sql.cpp"
    break;

  case 61: /* type: VECTOR_T  */
#line 629 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::VECTORS); }
#line 2369 "yacc_sql.cpp"
    break;

  case 62: /* type: TEXT_T  */
#line 630 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::TEXTS); }
#line 2375 "yacc_sql.cpp"
    break;

  case 63: /* type: DATE_T  */
#line 631 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::DATES); }
#line 2381 "yacc_sql.cpp"
    break;

  case 64: /* insert_stmt: INSERT INTO ID VALUES LBRACE value value_list RBRACE  */
#line 635 "yacc_sql.y"
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
#line 2398 "yacc_sql.cpp"
    break;

  case 65: /* insert_stmt: INSERT INTO ID LBRACE rel_attr rel_attr_list RBRACE VALUES LBRACE value value_list RBRACE  */
#line 648 "yacc_sql.y"
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
#line 2417 "yacc_sql.cpp"
    break;

  case 66: /* value_list: %empty  */
#line 667 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2425 "yacc_sql.cpp"
    break;

  case 67: /* value_list: COMMA insert_value value_list  */
#line 670 "yacc_sql.y"
                                     { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2439 "yacc_sql.cpp"
    break;

  case 68: /* insert_value: expression  */
#line 681 "yacc_sql.y"
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
#line 2455 "yacc_sql.cpp"
    break;

  case 69: /* value: NUMBER  */
#line 695 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2464 "yacc_sql.cpp"
    break;

  case 70: /* value: FLOAT  */
#line 699 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2473 "yacc_sql.cpp"
    break;

  case 71: /* value: DATE_STR  */
#line 703 "yacc_sql.y"
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
#line 2492 "yacc_sql.cpp"
    break;

  case 72: /* value: '[' double_list ']'  */
#line 718 "yacc_sql.y"
    {
      (yyval.value) = vec2val(sql_string, &(yyloc));
    }
#line 2500 "yacc_sql.cpp"
    break;

  case 73: /* value: SSS  */
#line 721 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2511 "yacc_sql.cpp"
    break;

  case 74: /* value: NULL_T  */
#line 727 "yacc_sql.y"
             {
      (yyval.value) = new Value();
      (yyval.value)->set_null();
    }
#line 2520 "yacc_sql.cpp"
    break;

  case 75: /* storage_format: %empty  */
#line 734 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2528 "yacc_sql.cpp"
    break;

  case 76: /* storage_format: STORAGE FORMAT EQ ID  */
#line 738 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2536 "yacc_sql.cpp"
    break;

  case 77: /* double_list: %empty  */
#line 742 "yacc_sql.y"
             {
      (yyval.double_list) = new std::vector<double>();
    }
#line 2544 "yacc_sql.cpp"
    break;

  case 78: /* double_list: float_number  */
#line 745 "yacc_sql.y"
                   {
      (yyval.double_list) = new std::vector<double>();
      (yyval.double_list)->emplace_back((yyvsp[0].float_number));
    }
#line 2553 "yacc_sql.cpp"
    break;

  case 79: /* double_list: double_list COMMA float_number  */
#line 749 "yacc_sql.y"
                                     {
      (yyval.double_list) = (yyvsp[-2].double_list);
      (yyval.double_list)->emplace_back((yyvsp[0].float_number));
    }
#line 2562 "yacc_sql.cpp"
    break;

  case 80: /* float_number: NUMBER  */
#line 754 "yacc_sql.y"
                     {
      (yyval.float_number) = (yyvsp[0].number);
    }
#line 2570 "yacc_sql.cpp"
    break;

  case 81: /* float_number: FLOAT  */
#line 757 "yacc_sql.y"
            {
      (yyval.float_number) = (yyvsp[0].floats);
    }
#line 2578 "yacc_sql.cpp"
    break;

  case 82: /* delete_stmt: DELETE FROM ID alias where  */
#line 763 "yacc_sql.y"
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
#line 2593 "yacc_sql.cpp"
    break;

  case 83: /* update_stmt: UPDATE ID alias SET update_kv_list where  */
#line 776 "yacc_sql.y"
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
#line 2611 "yacc_sql.cpp"
    break;

  case 84: /* update_kv_list: ID EQ expression  */
#line 792 "yacc_sql.y"
    {
      (yyval.kv_list) = new KeyValueList{};
      (yyval.kv_list)->attrs.emplace_back((yyvsp[-2].string));
      (yyval.kv_list)->values.emplace_back((yyvsp[0].expression));
      free((yyvsp[-2].string));
    }
#line 2622 "yacc_sql.cpp"
    break;

  case 85: /* update_kv_list: update_kv_list COMMA ID EQ expression  */
#line 799 "yacc_sql.y"
    {
      (yyval.kv_list) = (yyvsp[-4].kv_list);
      (yyval.kv_list)->attrs.emplace_back((yyvsp[-2].string));
      (yyval.kv_list)->values.emplace_back((yyvsp[0].expression));
      free((yyvsp[-2].string));
    }
#line 2633 "yacc_sql.cpp"
    break;

  case 86: /* select_stmt: SELECT expression_list FROM rel_list inner_join_list where group_by opt_having order_by opt_limit  */
#line 809 "yacc_sql.y"
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
#line 2681 "yacc_sql.cpp"
    break;

  case 87: /* select_stmt: SELECT expression_list  */
#line 853 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2692 "yacc_sql.cpp"
    break;

  case 88: /* calc_stmt: CALC expression_list  */
#line 863 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2702 "yacc_sql.cpp"
    break;

  case 89: /* expression_list: expression alias  */
#line 872 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->emplace_back((yyvsp[-1].expression));
      if((yyvsp[0].string) != nullptr){
        (yyvsp[-1].expression)->set_alias((yyvsp[0].string));
        free((yyvsp[0].string));
      }
    }
#line 2715 "yacc_sql.cpp"
    break;

  case 90: /* expression_list: expression alias COMMA expression_list  */
#line 881 "yacc_sql.y"
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
#line 2732 "yacc_sql.cpp"
    break;

  case 91: /* aggr_argument_list: %empty  */
#line 897 "yacc_sql.y"
  {
    (yyval.expression) = nullptr;
  }
#line 2740 "yacc_sql.cpp"
    break;

  case 92: /* aggr_argument_list: expression alias  */
#line 901 "yacc_sql.y"
  {
    if((yyvsp[0].string) != nullptr){
      (yyvsp[-1].expression)->set_alias((yyvsp[0].string));
      free((yyvsp[0].string));
    }
    (yyval.expression) = (yyvsp[-1].expression);
  }
#line 2752 "yacc_sql.cpp"
    break;

  case 93: /* aggr_argument_list: expression alias COMMA expression_list  */
#line 909 "yacc_sql.y"
  {
    (yyval.expression) = nullptr;
    delete (yyvsp[-3].expression);
    free((yyvsp[-2].string));
    delete (yyvsp[0].expression_list);
  }
#line 2763 "yacc_sql.cpp"
    break;

  case 94: /* expression: expression '+' expression  */
#line 918 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2771 "yacc_sql.cpp"
    break;

  case 95: /* expression: expression '-' expression  */
#line 921 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2779 "yacc_sql.cpp"
    break;

  case 96: /* expression: expression '*' expression  */
#line 924 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2787 "yacc_sql.cpp"
    break;

  case 97: /* expression: expression '/' expression  */
#line 927 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2795 "yacc_sql.cpp"
    break;

  case 98: /* expression: LBRACE expression_list RBRACE  */
#line 930 "yacc_sql.y"
                                    {
      if ((yyvsp[-1].expression_list)->size() == 1) {
        (yyval.expression) = (yyvsp[-1].expression_list)->front().release();
      } else {
        (yyval.expression) = new ExprListExpr(std::move(*(yyvsp[-1].expression_list)));
      }
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[-1].expression_list);
    }
#line 2809 "yacc_sql.cpp"
    break;

  case 99: /* expression: '-' expression  */
#line 939 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2817 "yacc_sql.cpp"
    break;

  case 100: /* expression: value  */
#line 942 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2827 "yacc_sql.cpp"
    break;

  case 101: /* expression: rel_attr  */
#line 947 "yacc_sql.y"
               {
      RelAttrSqlNode *node = (yyvsp[0].rel_attr);
      (yyval.expression) = new UnboundFieldExpr(node->relation_name, node->attribute_name);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].rel_attr);
    }
#line 2838 "yacc_sql.cpp"
    break;

  case 102: /* expression: vector_func_type LBRACE expression COMMA expression RBRACE  */
#line 953 "yacc_sql.y"
                                                                 {
      (yyval.expression) = create_function_expression((FunctionExpr::Type)(yyvsp[-5].number), sql_string, (yyvsp[-3].expression), (yyvsp[-1].expression), &(yyloc));
    }
#line 2846 "yacc_sql.cpp"
    break;

  case 103: /* expression: aggregate_expr  */
#line 956 "yacc_sql.y"
                     {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 2854 "yacc_sql.cpp"
    break;

  case 104: /* expression: sub_query_expr  */
#line 959 "yacc_sql.y"
                     {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 2862 "yacc_sql.cpp"
    break;

  case 105: /* expression: '*'  */
#line 962 "yacc_sql.y"
          {
      (yyval.expression) = new StarExpr();
    }
#line 2870 "yacc_sql.cpp"
    break;

  case 106: /* vector_func_type: L2_DISTANCE  */
#line 968 "yacc_sql.y"
                {
      (yyval.number) = static_cast<int>(FunctionExpr::Type::L2_DISTANCE);
    }
#line 2878 "yacc_sql.cpp"
    break;

  case 107: /* vector_func_type: COSINE_DISTANCE  */
#line 971 "yacc_sql.y"
                      {
      (yyval.number) = static_cast<int>(FunctionExpr::Type::COSINE_DISTANCE);
    }
#line 2886 "yacc_sql.cpp"
    break;

  case 108: /* vector_func_type: INNER_PRODUCT  */
#line 974 "yacc_sql.y"
                    {
      (yyval.number) = static_cast<int>(FunctionExpr::Type::INNER_PRODUCT);
    }
#line 2894 "yacc_sql.cpp"
    break;

  case 109: /* aggregate_expr: COUNT LBRACE aggr_argument_list RBRACE  */
#line 980 "yacc_sql.y"
                                           {
      (yyval.expression) = create_aggregate_expression("count", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2902 "yacc_sql.cpp"
    break;

  case 110: /* aggregate_expr: SUM LBRACE aggr_argument_list RBRACE  */
#line 983 "yacc_sql.y"
                                           {
      (yyval.expression) = create_aggregate_expression("sum", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2910 "yacc_sql.cpp"
    break;

  case 111: /* aggregate_expr: AVG LBRACE aggr_argument_list RBRACE  */
#line 986 "yacc_sql.y"
                                           {
      (yyval.expression) = create_aggregate_expression("avg", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2918 "yacc_sql.cpp"
    break;

  case 112: /* aggregate_expr: MIN LBRACE aggr_argument_list RBRACE  */
#line 989 "yacc_sql.y"
                                           {
      (yyval.expression) = create_aggregate_expression("min", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2926 "yacc_sql.cpp"
    break;

  case 113: /* aggregate_expr: MAX LBRACE aggr_argument_list RBRACE  */
#line 992 "yacc_sql.y"
                                           {
      (yyval.expression) = create_aggregate_expression("max", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2934 "yacc_sql.cpp"
    break;

  case 114: /* sub_query_expr: LBRACE select_stmt RBRACE  */
#line 998 "yacc_sql.y"
    {
      (yyval.expression) = new SubQueryExpr(std::move((yyvsp[-1].sql_node)->selection));
      delete (yyvsp[-1].sql_node);
    }
#line 2943 "yacc_sql.cpp"
    break;

  case 115: /* rel_attr: ID  */
#line 1005 "yacc_sql.y"
       {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2953 "yacc_sql.cpp"
    break;

  case 116: /* rel_attr: ID DOT ID  */
#line 1010 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2965 "yacc_sql.cpp"
    break;

  case 117: /* rel_attr: ID DOT '*'  */
#line 1017 "yacc_sql.y"
                 {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = "*";
      free((yyvsp[-2].string));
    }
#line 2976 "yacc_sql.cpp"
    break;

  case 118: /* rel_attr_list: %empty  */
#line 1026 "yacc_sql.y"
    {
      (yyval.rel_attr_list) = nullptr;
    }
#line 2984 "yacc_sql.cpp"
    break;

  case 119: /* rel_attr_list: COMMA rel_attr rel_attr_list  */
#line 1030 "yacc_sql.y"
    {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }
      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-1].rel_attr));
      delete (yyvsp[-1].rel_attr);
    }
#line 2998 "yacc_sql.cpp"
    break;

  case 120: /* relation: ID  */
#line 1043 "yacc_sql.y"
       {
      (yyval.string) = (yyvsp[0].string);
    }
#line 3006 "yacc_sql.cpp"
    break;

  case 121: /* rel_list: relation alias  */
#line 1048 "yacc_sql.y"
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
#line 3021 "yacc_sql.cpp"
    break;

  case 122: /* rel_list: relation alias COMMA rel_list  */
#line 1058 "yacc_sql.y"
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
#line 3042 "yacc_sql.cpp"
    break;

  case 123: /* inner_join_list: %empty  */
#line 1078 "yacc_sql.y"
    {
      (yyval.inner_join) = nullptr;
    }
#line 3050 "yacc_sql.cpp"
    break;

  case 124: /* inner_join_list: inner_join_list inner_join_rel  */
#line 1082 "yacc_sql.y"
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
#line 3066 "yacc_sql.cpp"
    break;

  case 125: /* inner_join_rel: INNER JOIN relation alias ON condition  */
#line 1095 "yacc_sql.y"
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
#line 3082 "yacc_sql.cpp"
    break;

  case 126: /* where: %empty  */
#line 1111 "yacc_sql.y"
    {
      (yyval.expression) = nullptr;
    }
#line 3090 "yacc_sql.cpp"
    break;

  case 127: /* where: WHERE condition  */
#line 1114 "yacc_sql.y"
                      {
      (yyval.expression) = (yyvsp[0].expression);  
    }
#line 3098 "yacc_sql.cpp"
    break;

  case 128: /* condition: expression comp_op expression  */
#line 1120 "yacc_sql.y"
    {
      (yyval.expression) = new ComparisonExpr((yyvsp[-1].comp), (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 3106 "yacc_sql.cpp"
    break;

  case 129: /* condition: exists_op expression  */
#line 1124 "yacc_sql.y"
    {
      Value val;
      val.set_null();
      ValueExpr *value_expr = new ValueExpr(val);
      (yyval.expression) = new ComparisonExpr((yyvsp[-1].comp), value_expr, (yyvsp[0].expression));
    }
#line 3117 "yacc_sql.cpp"
    break;

  case 130: /* condition: expression IS opt_null  */
#line 1131 "yacc_sql.y"
    {
      Value val;
      val.set_null();
      ValueExpr *value_expr = new ValueExpr(val);
      (yyval.expression) = new ComparisonExpr((yyvsp[0].bools) ? IS_NULL : IS_NOT_NULL, (yyvsp[-2].expression), value_expr);
    }
#line 3128 "yacc_sql.cpp"
    break;

  case 131: /* condition: condition AND condition  */
#line 1138 "yacc_sql.y"
    {
      (yyval.expression) = new ConjunctionExpr(ConjunctionExpr::Type::AND, (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 3136 "yacc_sql.cpp"
    break;

  case 132: /* condition: condition OR condition  */
#line 1142 "yacc_sql.y"
    {
      (yyval.expression) = new ConjunctionExpr(ConjunctionExpr::Type::OR, (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 3144 "yacc_sql.cpp"
    break;

  case 133: /* comp_op: EQ  */
#line 1148 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 3150 "yacc_sql.cpp"
    break;

  case 134: /* comp_op: LT  */
#line 1149 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 3156 "yacc_sql.cpp"
    break;

  case 135: /* comp_op: GT  */
#line 1150 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3162 "yacc_sql.cpp"
    break;

  case 136: /* comp_op: LE  */
#line 1151 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3168 "yacc_sql.cpp"
    break;

  case 137: /* comp_op: LT GT  */
#line 1152 "yacc_sql.y"
            { (yyval.comp) = NOT_EQUAL; }
#line 3174 "yacc_sql.cpp"
    break;

  case 138: /* comp_op: GE  */
#line 1153 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3180 "yacc_sql.cpp"
    break;

  case 139: /* comp_op: NE  */
#line 1154 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3186 "yacc_sql.cpp"
    break;

  case 140: /* comp_op: LIKE  */
#line 1155 "yacc_sql.y"
           { (yyval.comp) = LIKE_OP; }
#line 3192 "yacc_sql.cpp"
    break;

  case 141: /* comp_op: NOT LIKE  */
#line 1156 "yacc_sql.y"
               { (yyval.comp) = NOT_LIKE_OP; }
#line 3198 "yacc_sql.cpp"
    break;

  case 142: /* comp_op: IN  */
#line 1157 "yacc_sql.y"
         { (yyval.comp) = IN_OP; }
#line 3204 "yacc_sql.cpp"
    break;

  case 143: /* comp_op: NOT IN  */
#line 1158 "yacc_sql.y"
             { (yyval.comp) = NOT_IN_OP; }
#line 3210 "yacc_sql.cpp"
    break;

  case 144: /* exists_op: EXISTS  */
#line 1162 "yacc_sql.y"
         { (yyval.comp) = EXISTS_OP; }
#line 3216 "yacc_sql.cpp"
    break;

  case 145: /* exists_op: NOT EXISTS  */
#line 1163 "yacc_sql.y"
               { (yyval.comp) = NOT_EXISTS_OP; }
#line 3222 "yacc_sql.cpp"
    break;

  case 146: /* group_by: %empty  */
#line 1168 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3230 "yacc_sql.cpp"
    break;

  case 147: /* group_by: GROUP BY expression_list  */
#line 1172 "yacc_sql.y"
    {
      (yyval.expression_list) = (yyvsp[0].expression_list);
    }
#line 3238 "yacc_sql.cpp"
    break;

  case 148: /* opt_having: %empty  */
#line 1179 "yacc_sql.y"
  {
    (yyval.expression) = nullptr;
  }
#line 3246 "yacc_sql.cpp"
    break;

  case 149: /* opt_having: HAVING condition  */
#line 1183 "yacc_sql.y"
  {
    (yyval.expression) = (yyvsp[0].expression);
  }
#line 3254 "yacc_sql.cpp"
    break;

  case 150: /* order_by: %empty  */
#line 1191 "yacc_sql.y"
    {
      (yyval.order_by_list) = nullptr;
    }
#line 3262 "yacc_sql.cpp"
    break;

  case 151: /* order_by: ORDER BY order_by_list  */
#line 1195 "yacc_sql.y"
    {
      (yyval.order_by_list) = (yyvsp[0].order_by_list);
      std::reverse((yyval.order_by_list)->begin(), (yyval.order_by_list)->end());
    }
#line 3271 "yacc_sql.cpp"
    break;

  case 152: /* opt_limit: %empty  */
#line 1203 "yacc_sql.y"
    {
      (yyval.limit) = nullptr;
    }
#line 3279 "yacc_sql.cpp"
    break;

  case 153: /* opt_limit: LIMIT number  */
#line 1207 "yacc_sql.y"
    {
      (yyval.limit) = new LimitSqlNode();
      (yyval.limit)->number = (yyvsp[0].number);
    }
#line 3288 "yacc_sql.cpp"
    break;

  case 154: /* order_by_list: order_unit  */
#line 1215 "yacc_sql.y"
    {
      (yyval.order_by_list) = new std::vector<std::unique_ptr<OrderBySqlNode>>();
      (yyval.order_by_list)->emplace_back((yyvsp[0].order_unit));
    }
#line 3297 "yacc_sql.cpp"
    break;

  case 155: /* order_by_list: order_unit COMMA order_by_list  */
#line 1220 "yacc_sql.y"
    {
      (yyval.order_by_list) = (yyvsp[0].order_by_list);
      (yyval.order_by_list)->emplace_back((yyvsp[-2].order_unit));
    }
#line 3306 "yacc_sql.cpp"
    break;

  case 156: /* order_unit: rel_attr order_op  */
#line 1228 "yacc_sql.y"
    {
      (yyval.order_unit) = new OrderBySqlNode;
      RelAttrSqlNode *node = (yyvsp[-1].rel_attr);
      (yyval.order_unit)->unbound_field = std::make_unique<UnboundFieldExpr>(node->relation_name, node->attribute_name);
      (yyval.order_unit)->order_op = (yyvsp[0].order_op);
      delete (yyvsp[-1].rel_attr);
    }
#line 3318 "yacc_sql.cpp"
    break;

  case 157: /* order_unit: vector_func_type LBRACE expression COMMA expression RBRACE order_op  */
#line 1235 "yacc_sql.y"
                                                                          {
      (yyval.order_unit) = new OrderBySqlNode;
      (yyval.order_unit)->unbound_field = std::unique_ptr<Expression>(create_function_expression((FunctionExpr::Type)(yyvsp[-6].number), sql_string, (yyvsp[-4].expression), (yyvsp[-2].expression), &(yyloc)));
      (yyval.order_unit)->order_op = (yyvsp[0].order_op);
    }
#line 3328 "yacc_sql.cpp"
    break;

  case 158: /* order_op: %empty  */
#line 1243 "yacc_sql.y"
    {
      (yyval.order_op) = OrderOp::ASC;
    }
#line 3336 "yacc_sql.cpp"
    break;

  case 159: /* order_op: ASC  */
#line 1247 "yacc_sql.y"
    {
      (yyval.order_op) = OrderOp::ASC;
    }
#line 3344 "yacc_sql.cpp"
    break;

  case 160: /* order_op: DESC  */
#line 1251 "yacc_sql.y"
    {
      (yyval.order_op) = OrderOp::DESC;
    }
#line 3352 "yacc_sql.cpp"
    break;

  case 161: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 1258 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3366 "yacc_sql.cpp"
    break;

  case 162: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1271 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3375 "yacc_sql.cpp"
    break;

  case 163: /* set_variable_stmt: SET ID EQ value  */
#line 1279 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3387 "yacc_sql.cpp"
    break;


#line 3391 "yacc_sql.cpp"

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

#line 1291 "yacc_sql.y"

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

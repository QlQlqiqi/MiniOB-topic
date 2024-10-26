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


#line 148 "yacc_sql.cpp"

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
  YYSYMBOL_INDEX = 13,                     /* INDEX  */
  YYSYMBOL_CALC = 14,                      /* CALC  */
  YYSYMBOL_SELECT = 15,                    /* SELECT  */
  YYSYMBOL_DESC = 16,                      /* DESC  */
  YYSYMBOL_SHOW = 17,                      /* SHOW  */
  YYSYMBOL_SYNC = 18,                      /* SYNC  */
  YYSYMBOL_INSERT = 19,                    /* INSERT  */
  YYSYMBOL_DELETE = 20,                    /* DELETE  */
  YYSYMBOL_UPDATE = 21,                    /* UPDATE  */
  YYSYMBOL_INNER = 22,                     /* INNER  */
  YYSYMBOL_JOIN = 23,                      /* JOIN  */
  YYSYMBOL_LBRACE = 24,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 25,                    /* RBRACE  */
  YYSYMBOL_COMMA = 26,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 27,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 28,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 29,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 30,                     /* INT_T  */
  YYSYMBOL_STRING_T = 31,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 32,                   /* FLOAT_T  */
  YYSYMBOL_VECTOR_T = 33,                  /* VECTOR_T  */
  YYSYMBOL_IS = 34,                        /* IS  */
  YYSYMBOL_NOT = 35,                       /* NOT  */
  YYSYMBOL_NULL_T = 36,                    /* NULL_T  */
  YYSYMBOL_DATE_T = 37,                    /* DATE_T  */
  YYSYMBOL_HELP = 38,                      /* HELP  */
  YYSYMBOL_EXIT = 39,                      /* EXIT  */
  YYSYMBOL_DOT = 40,                       /* DOT  */
  YYSYMBOL_INTO = 41,                      /* INTO  */
  YYSYMBOL_VALUES = 42,                    /* VALUES  */
  YYSYMBOL_FROM = 43,                      /* FROM  */
  YYSYMBOL_WHERE = 44,                     /* WHERE  */
  YYSYMBOL_AND = 45,                       /* AND  */
  YYSYMBOL_OR = 46,                        /* OR  */
  YYSYMBOL_SET = 47,                       /* SET  */
  YYSYMBOL_ON = 48,                        /* ON  */
  YYSYMBOL_LOAD = 49,                      /* LOAD  */
  YYSYMBOL_DATA = 50,                      /* DATA  */
  YYSYMBOL_INFILE = 51,                    /* INFILE  */
  YYSYMBOL_EXPLAIN = 52,                   /* EXPLAIN  */
  YYSYMBOL_STORAGE = 53,                   /* STORAGE  */
  YYSYMBOL_FORMAT = 54,                    /* FORMAT  */
  YYSYMBOL_EQ = 55,                        /* EQ  */
  YYSYMBOL_LT = 56,                        /* LT  */
  YYSYMBOL_GT = 57,                        /* GT  */
  YYSYMBOL_LE = 58,                        /* LE  */
  YYSYMBOL_GE = 59,                        /* GE  */
  YYSYMBOL_NE = 60,                        /* NE  */
  YYSYMBOL_LIKE = 61,                      /* LIKE  */
  YYSYMBOL_COUNT = 62,                     /* COUNT  */
  YYSYMBOL_SUM = 63,                       /* SUM  */
  YYSYMBOL_AVG = 64,                       /* AVG  */
  YYSYMBOL_MAX = 65,                       /* MAX  */
  YYSYMBOL_MIN = 66,                       /* MIN  */
  YYSYMBOL_L2_DISTANCE = 67,               /* L2_DISTANCE  */
  YYSYMBOL_COSINE_DISTANCE = 68,           /* COSINE_DISTANCE  */
  YYSYMBOL_INNER_PRODUCT = 69,             /* INNER_PRODUCT  */
  YYSYMBOL_IN = 70,                        /* IN  */
  YYSYMBOL_EXISTS = 71,                    /* EXISTS  */
  YYSYMBOL_VECTORS = 72,                   /* VECTORS  */
  YYSYMBOL_QUOTE = 73,                     /* QUOTE  */
  YYSYMBOL_UNIQUE = 74,                    /* UNIQUE  */
  YYSYMBOL_NUMBER = 75,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 76,                     /* FLOAT  */
  YYSYMBOL_ID = 77,                        /* ID  */
  YYSYMBOL_SSS = 78,                       /* SSS  */
  YYSYMBOL_DATE_STR = 79,                  /* DATE_STR  */
  YYSYMBOL_80_ = 80,                       /* '+'  */
  YYSYMBOL_81_ = 81,                       /* '-'  */
  YYSYMBOL_82_ = 82,                       /* '*'  */
  YYSYMBOL_83_ = 83,                       /* '/'  */
  YYSYMBOL_UMINUS = 84,                    /* UMINUS  */
  YYSYMBOL_85_ = 85,                       /* '['  */
  YYSYMBOL_86_ = 86,                       /* ']'  */
  YYSYMBOL_YYACCEPT = 87,                  /* $accept  */
  YYSYMBOL_commands = 88,                  /* commands  */
  YYSYMBOL_command_wrapper = 89,           /* command_wrapper  */
  YYSYMBOL_exit_stmt = 90,                 /* exit_stmt  */
  YYSYMBOL_help_stmt = 91,                 /* help_stmt  */
  YYSYMBOL_sync_stmt = 92,                 /* sync_stmt  */
  YYSYMBOL_begin_stmt = 93,                /* begin_stmt  */
  YYSYMBOL_commit_stmt = 94,               /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 95,             /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 96,           /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 97,          /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 98,           /* desc_table_stmt  */
  YYSYMBOL_create_index_stmt = 99,         /* create_index_stmt  */
  YYSYMBOL_opt_unique = 100,               /* opt_unique  */
  YYSYMBOL_idx_col_list = 101,             /* idx_col_list  */
  YYSYMBOL_drop_index_stmt = 102,          /* drop_index_stmt  */
  YYSYMBOL_create_table_stmt = 103,        /* create_table_stmt  */
  YYSYMBOL_attr_def_list = 104,            /* attr_def_list  */
  YYSYMBOL_attr_def = 105,                 /* attr_def  */
  YYSYMBOL_opt_null = 106,                 /* opt_null  */
  YYSYMBOL_number = 107,                   /* number  */
  YYSYMBOL_type = 108,                     /* type  */
  YYSYMBOL_insert_stmt = 109,              /* insert_stmt  */
  YYSYMBOL_value_list = 110,               /* value_list  */
  YYSYMBOL_insert_value = 111,             /* insert_value  */
  YYSYMBOL_value = 112,                    /* value  */
  YYSYMBOL_storage_format = 113,           /* storage_format  */
  YYSYMBOL_double_list = 114,              /* double_list  */
  YYSYMBOL_float_number = 115,             /* float_number  */
  YYSYMBOL_delete_stmt = 116,              /* delete_stmt  */
  YYSYMBOL_update_stmt = 117,              /* update_stmt  */
  YYSYMBOL_update_kv_list = 118,           /* update_kv_list  */
  YYSYMBOL_select_stmt = 119,              /* select_stmt  */
  YYSYMBOL_calc_stmt = 120,                /* calc_stmt  */
  YYSYMBOL_expression_list = 121,          /* expression_list  */
  YYSYMBOL_group_by_expression_list = 122, /* group_by_expression_list  */
  YYSYMBOL_expression = 123,               /* expression  */
  YYSYMBOL_aggregate_expr = 124,           /* aggregate_expr  */
  YYSYMBOL_sub_query_expr = 125,           /* sub_query_expr  */
  YYSYMBOL_rel_attr = 126,                 /* rel_attr  */
  YYSYMBOL_relation = 127,                 /* relation  */
  YYSYMBOL_rel_list = 128,                 /* rel_list  */
  YYSYMBOL_inner_join_list = 129,          /* inner_join_list  */
  YYSYMBOL_inner_join_rel = 130,           /* inner_join_rel  */
  YYSYMBOL_where = 131,                    /* where  */
  YYSYMBOL_condition = 132,                /* condition  */
  YYSYMBOL_comp_op = 133,                  /* comp_op  */
  YYSYMBOL_exists_op = 134,                /* exists_op  */
  YYSYMBOL_group_by = 135,                 /* group_by  */
  YYSYMBOL_opt_having = 136,               /* opt_having  */
  YYSYMBOL_order_by = 137,                 /* order_by  */
  YYSYMBOL_order_by_list = 138,            /* order_by_list  */
  YYSYMBOL_order_unit = 139,               /* order_unit  */
  YYSYMBOL_order_op = 140,                 /* order_op  */
  YYSYMBOL_load_data_stmt = 141,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 142,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 143,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 144             /* opt_semicolon  */
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
#define YYFINAL  79
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   310

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  87
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  58
/* YYNRULES -- Number of rules.  */
#define YYNRULES  145
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  272

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   335


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
       2,     2,    82,    80,     2,    81,     2,    83,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    85,     2,    86,     2,     2,     2,     2,     2,     2,
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
      75,    76,    77,    78,    79,    84
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   264,   264,   272,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   295,   301,   306,   312,   318,   324,   330,
     337,   343,   351,   369,   372,   379,   382,   391,   401,   425,
     428,   441,   456,   473,   477,   481,   487,   490,   491,   492,
     493,   494,   497,   514,   517,   527,   542,   546,   550,   564,
     568,   574,   581,   584,   589,   592,   596,   601,   604,   609,
     618,   630,   638,   649,   689,   699,   708,   713,   726,   729,
     735,   742,   745,   748,   751,   754,   763,   766,   771,   777,
     780,   783,   786,   789,   792,   798,   801,   804,   807,   810,
     815,   823,   828,   838,   843,   848,   862,   865,   878,   888,
     891,   896,   900,   907,   914,   918,   925,   926,   927,   928,
     929,   930,   931,   932,   933,   934,   935,   939,   940,   945,
     948,   956,   959,   967,   970,   978,   983,   990,   999,  1002,
    1006,  1012,  1025,  1033,  1043,  1044
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
  "INDEX", "CALC", "SELECT", "DESC", "SHOW", "SYNC", "INSERT", "DELETE",
  "UPDATE", "INNER", "JOIN", "LBRACE", "RBRACE", "COMMA", "TRX_BEGIN",
  "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "STRING_T", "FLOAT_T", "VECTOR_T",
  "IS", "NOT", "NULL_T", "DATE_T", "HELP", "EXIT", "DOT", "INTO", "VALUES",
  "FROM", "WHERE", "AND", "OR", "SET", "ON", "LOAD", "DATA", "INFILE",
  "EXPLAIN", "STORAGE", "FORMAT", "EQ", "LT", "GT", "LE", "GE", "NE",
  "LIKE", "COUNT", "SUM", "AVG", "MAX", "MIN", "L2_DISTANCE",
  "COSINE_DISTANCE", "INNER_PRODUCT", "IN", "EXISTS", "VECTORS", "QUOTE",
  "UNIQUE", "NUMBER", "FLOAT", "ID", "SSS", "DATE_STR", "'+'", "'-'",
  "'*'", "'/'", "UMINUS", "'['", "']'", "$accept", "commands",
  "command_wrapper", "exit_stmt", "help_stmt", "sync_stmt", "begin_stmt",
  "commit_stmt", "rollback_stmt", "drop_table_stmt", "show_tables_stmt",
  "desc_table_stmt", "create_index_stmt", "opt_unique", "idx_col_list",
  "drop_index_stmt", "create_table_stmt", "attr_def_list", "attr_def",
  "opt_null", "number", "type", "insert_stmt", "value_list",
  "insert_value", "value", "storage_format", "double_list", "float_number",
  "delete_stmt", "update_stmt", "update_kv_list", "select_stmt",
  "calc_stmt", "expression_list", "group_by_expression_list", "expression",
  "aggregate_expr", "sub_query_expr", "rel_attr", "relation", "rel_list",
  "inner_join_list", "inner_join_rel", "where", "condition", "comp_op",
  "exists_op", "group_by", "opt_having", "order_by", "order_by_list",
  "order_unit", "order_op", "load_data_stmt", "explain_stmt",
  "set_variable_stmt", "opt_semicolon", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-248)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     238,    -8,     2,   145,   145,   -36,     5,  -248,   -16,    12,
     -18,  -248,  -248,  -248,  -248,  -248,   -12,    19,   238,    89,
      78,  -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,
    -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,
    -248,    28,  -248,   113,    55,    56,    46,  -248,   105,   106,
     115,   119,   121,   123,   129,   130,  -248,  -248,   117,  -248,
    -248,   145,  -248,   -27,  -248,  -248,    21,  -248,  -248,  -248,
     116,  -248,  -248,    88,    90,   111,   118,   124,  -248,  -248,
    -248,  -248,   142,    91,  -248,   122,   146,   147,   145,   145,
     145,   145,   145,   145,   145,   145,    97,  -248,  -248,  -248,
     -22,  -248,   145,   145,   145,   145,   145,    99,   136,   135,
     126,   -25,   114,   127,   152,   140,  -248,  -248,   168,    36,
     169,   193,   194,   200,    54,    81,   151,  -248,   -27,  -248,
    -248,   -26,   -26,  -248,  -248,  -248,   180,  -248,   204,   120,
    -248,   174,   -20,  -248,   205,    53,   219,   170,  -248,  -248,
     145,  -248,  -248,  -248,  -248,   145,   145,   145,  -248,    99,
     -17,   -25,   177,  -248,   181,    22,   145,   -25,   172,  -248,
     239,  -248,  -248,  -248,  -248,  -248,   -14,   127,   235,   244,
    -248,    -9,    -5,    11,  -248,   246,  -248,   263,   245,  -248,
      52,   -52,  -248,   215,  -248,  -248,  -248,  -248,  -248,  -248,
     145,   120,   120,   -43,  -248,   218,   197,   203,   243,  -248,
    -248,   219,   222,   206,  -248,  -248,  -248,    99,   276,   271,
     145,   257,  -248,  -248,  -248,  -248,   -43,  -248,   241,   -25,
    -248,  -248,   259,  -248,  -248,   234,  -248,   265,   247,   145,
     120,   281,   245,   -43,  -248,  -248,    52,   237,   216,   269,
     120,  -248,    22,   292,  -248,  -248,  -248,   220,   265,  -248,
      22,   221,  -248,  -248,     3,  -248,   273,  -248,  -248,  -248,
     221,  -248
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    33,     0,     0,     0,     0,     0,    25,     0,     0,
       0,    26,    27,    28,    24,    23,     0,     0,     0,     0,
     144,    22,    21,    14,    15,    16,    17,     9,    10,    11,
      12,    13,     8,     5,     7,     6,     4,     3,    18,    19,
      20,     0,    34,     0,     0,     0,     0,    61,     0,     0,
       0,     0,     0,     0,     0,     0,    56,    57,   101,    60,
      58,     0,    94,    64,    87,    75,    76,    89,    93,    88,
      74,    31,    30,     0,     0,     0,     0,     0,   142,     1,
     145,     2,     0,     0,    29,     0,     0,     0,    78,    78,
      78,    78,    78,     0,     0,     0,     0,    86,    67,    68,
       0,    65,     0,     0,     0,     0,     0,     0,     0,   109,
       0,     0,     0,     0,     0,     0,   100,    85,     0,    80,
       0,     0,     0,     0,     0,     0,     0,   102,     0,    59,
      77,    81,    82,    83,    84,   103,   104,   106,     0,     0,
      69,     0,   109,   143,     0,     0,    39,     0,    37,    95,
       0,    96,    97,    99,    98,     0,     0,     0,    66,     0,
     109,     0,     0,   127,     0,   110,     0,     0,     0,    70,
       0,    47,    48,    49,    50,    51,    43,     0,     0,     0,
      79,     0,     0,     0,   105,     0,   107,   129,    53,   128,
      43,     0,   116,   117,   118,   119,   121,   122,   123,   125,
       0,     0,     0,   112,    71,     0,     0,     0,     0,    45,
      42,    39,    62,     0,    90,    91,    92,     0,     0,   131,
       0,     0,   113,   124,   126,   120,   111,   114,   115,     0,
     141,    46,     0,    44,    40,     0,    38,    35,     0,     0,
       0,   133,    53,    55,    52,    72,    43,     0,     0,     0,
       0,   130,   132,     0,    73,    54,    41,     0,    35,    32,
     108,     0,    63,    36,   138,   134,   135,   139,   140,   137,
       0,   136
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -248,  -248,   282,  -248,  -248,  -248,  -248,  -248,  -248,  -248,
    -248,  -248,  -248,  -248,    43,  -248,  -248,    92,   125,  -183,
    -248,  -248,  -248,    62,  -248,  -109,  -248,  -248,   178,  -248,
    -248,  -248,   261,  -248,    -4,    60,   -60,  -248,  -248,  -247,
      93,   149,  -248,  -248,  -134,  -102,  -248,  -248,  -248,  -248,
    -248,    35,  -248,  -248,  -248,  -248,  -248,  -248
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    43,   249,    31,    32,   178,   146,   210,
     232,   176,    33,   221,   242,    64,   236,   100,   101,    34,
      35,   142,    36,    37,    65,   118,    66,    67,    68,    69,
     136,   137,   160,   186,   140,   165,   200,   166,   219,   241,
     254,   265,   266,   269,    38,    39,    40,    81
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      70,    97,   143,    41,   128,   185,   168,   222,   169,   223,
     207,    47,   267,    44,   264,    45,   214,    72,   224,   268,
     215,   208,   209,   264,   139,    73,   187,   139,   119,   119,
     119,   119,   119,   124,   125,   126,   216,   103,   104,   105,
     106,    71,    87,   131,   132,   133,   134,   102,    98,    99,
      56,    57,   188,    59,    60,    74,   105,   106,   204,    75,
      63,     4,   150,   256,   129,    76,    42,   201,   202,    77,
      46,   103,   104,   105,   106,   103,   104,   105,   106,   164,
     155,    80,    47,   171,   172,   173,   174,   208,   209,    79,
     175,   103,   104,   105,   106,   181,   182,   183,   130,   227,
     228,   103,   104,   105,   106,    82,   203,   156,    48,    49,
      50,    51,    52,    53,    54,    55,   103,   104,   105,   106,
     245,    56,    57,    58,    59,    60,    83,    61,    62,    88,
      89,    63,    84,    85,   103,   104,   105,   106,   252,    90,
     226,   164,   164,    91,    46,    92,   180,    93,   260,   120,
     121,   122,   123,    94,    95,   162,    47,    96,   110,   107,
     243,   103,   104,   105,   106,   108,   113,   109,   114,    46,
     115,   116,   117,   111,   127,   112,   135,   157,   138,   139,
     164,    47,    48,    49,    50,    51,    52,    53,    54,    55,
     164,   163,   144,   149,   151,    56,    57,    58,    59,    60,
     147,    61,    62,   141,   145,    63,   159,    48,    49,    50,
      51,    52,    53,    54,    55,   190,   191,   148,   152,   153,
      56,    57,    58,    59,    60,   154,    61,    62,   161,   167,
      63,   103,   104,   105,   106,   251,   192,   193,   194,   195,
     196,   197,   198,     1,     2,   177,   170,   179,   189,   205,
     206,   199,     3,     4,     5,     6,     7,     8,     9,    10,
     212,   103,   104,   105,   106,    11,    12,    13,   213,   217,
     218,   220,   225,   229,   230,   235,    14,    15,   231,   233,
     239,   240,   244,   237,   246,    16,   201,    17,   247,   253,
      18,   248,   257,   258,   259,   250,   261,   262,    58,   270,
      78,   263,   211,   234,   255,   271,   158,    86,   184,     0,
     238
};

static const yytype_int16 yycheck[] =
{
       4,    61,   111,    11,    26,    22,    26,   190,   142,    61,
      24,    36,     9,    11,   261,    13,    25,    12,    70,    16,
      25,    35,    36,   270,    44,    41,   160,    44,    88,    89,
      90,    91,    92,    93,    94,    95,    25,    80,    81,    82,
      83,    77,    46,   103,   104,   105,   106,    26,    75,    76,
      75,    76,   161,    78,    79,    43,    82,    83,   167,    77,
      85,    15,    26,   246,    86,    77,    74,    45,    46,    50,
      24,    80,    81,    82,    83,    80,    81,    82,    83,   139,
      26,     3,    36,    30,    31,    32,    33,    35,    36,     0,
      37,    80,    81,    82,    83,   155,   156,   157,   102,   201,
     202,    80,    81,    82,    83,    77,   166,    26,    62,    63,
      64,    65,    66,    67,    68,    69,    80,    81,    82,    83,
     229,    75,    76,    77,    78,    79,    13,    81,    82,    24,
      24,    85,    77,    77,    80,    81,    82,    83,   240,    24,
     200,   201,   202,    24,    24,    24,   150,    24,   250,    89,
      90,    91,    92,    24,    24,    35,    36,    40,    47,    43,
     220,    80,    81,    82,    83,    77,    24,    77,    77,    24,
      48,    25,    25,    55,    77,    51,    77,    26,    42,    44,
     240,    36,    62,    63,    64,    65,    66,    67,    68,    69,
     250,    71,    78,    25,    25,    75,    76,    77,    78,    79,
      48,    81,    82,    77,    77,    85,    26,    62,    63,    64,
      65,    66,    67,    68,    69,    34,    35,    77,    25,    25,
      75,    76,    77,    78,    79,    25,    81,    82,    24,    55,
      85,    80,    81,    82,    83,   239,    55,    56,    57,    58,
      59,    60,    61,     5,     6,    26,    41,    77,    71,    77,
      11,    70,    14,    15,    16,    17,    18,    19,    20,    21,
      25,    80,    81,    82,    83,    27,    28,    29,    24,    23,
       7,    26,    57,    55,    77,    53,    38,    39,    75,    36,
       4,    10,    25,    77,    25,    47,    45,    49,    54,     8,
      52,    26,    55,    77,    25,    48,     4,    77,    77,    26,
      18,   258,   177,   211,   242,   270,   128,    46,   159,    -1,
     217
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     6,    14,    15,    16,    17,    18,    19,    20,
      21,    27,    28,    29,    38,    39,    47,    49,    52,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   102,   103,   109,   116,   117,   119,   120,   141,   142,
     143,    11,    74,   100,    11,    13,    24,    36,    62,    63,
      64,    65,    66,    67,    68,    69,    75,    76,    77,    78,
      79,    81,    82,    85,   112,   121,   123,   124,   125,   126,
     121,    77,    12,    41,    43,    77,    77,    50,    89,     0,
       3,   144,    77,    13,    77,    77,   119,   121,    24,    24,
      24,    24,    24,    24,    24,    24,    40,   123,    75,    76,
     114,   115,    26,    80,    81,    82,    83,    43,    77,    77,
      47,    55,    51,    24,    77,    48,    25,    25,   122,   123,
     122,   122,   122,   122,   123,   123,   123,    77,    26,    86,
     121,   123,   123,   123,   123,    77,   127,   128,    42,    44,
     131,    77,   118,   112,    78,    77,   105,    48,    77,    25,
      26,    25,    25,    25,    25,    26,    26,    26,   115,    26,
     129,    24,    35,    71,   123,   132,   134,    55,    26,   131,
      41,    30,    31,    32,    33,    37,   108,    26,   104,    77,
     121,   123,   123,   123,   128,    22,   130,   131,   112,    71,
      34,    35,    55,    56,    57,    58,    59,    60,    61,    70,
     133,    45,    46,   123,   112,    77,    11,    24,    35,    36,
     106,   105,    25,    24,    25,    25,    25,    23,     7,   135,
      26,   110,   106,    61,    70,    57,   123,   132,   132,    55,
      77,    75,   107,    36,   104,    53,   113,    77,   127,     4,
      10,   136,   111,   123,    25,   112,    25,    54,    26,   101,
      48,   121,   132,     8,   137,   110,   106,    55,    77,    25,
     132,     4,    77,   101,   126,   138,   139,     9,    16,   140,
      26,   138
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    87,    88,    89,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   100,   101,   101,   102,   103,   104,
     104,   105,   105,   106,   106,   106,   107,   108,   108,   108,
     108,   108,   109,   110,   110,   111,   112,   112,   112,   112,
     112,   112,   113,   113,   114,   114,   114,   115,   115,   116,
     117,   118,   118,   119,   119,   120,   121,   121,   122,   122,
     122,   123,   123,   123,   123,   123,   123,   123,   123,   123,
     123,   123,   123,   123,   123,   124,   124,   124,   124,   124,
     125,   126,   126,   127,   128,   128,   129,   129,   130,   131,
     131,   132,   132,   132,   132,   132,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   134,   134,   135,
     135,   136,   136,   137,   137,   138,   138,   139,   140,   140,
     140,   141,   142,   143,   144,   144
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       2,     2,    10,     0,     1,     0,     3,     5,     8,     0,
       3,     6,     3,     0,     2,     1,     1,     1,     1,     1,
       1,     1,     8,     0,     3,     1,     1,     1,     1,     3,
       1,     1,     0,     4,     0,     1,     3,     1,     1,     4,
       5,     3,     5,     9,     2,     2,     1,     3,     0,     3,
       1,     3,     3,     3,     3,     3,     2,     1,     1,     1,
       6,     6,     6,     1,     1,     4,     4,     4,     4,     4,
       3,     1,     3,     1,     1,     3,     0,     2,     5,     0,
       2,     3,     2,     3,     3,     3,     1,     1,     1,     1,
       2,     1,     1,     1,     2,     1,     2,     1,     2,     0,
       3,     0,     2,     0,     3,     1,     3,     2,     0,     1,
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
#line 265 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1895 "yacc_sql.cpp"
    break;

  case 23: /* exit_stmt: EXIT  */
#line 295 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1904 "yacc_sql.cpp"
    break;

  case 24: /* help_stmt: HELP  */
#line 301 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1912 "yacc_sql.cpp"
    break;

  case 25: /* sync_stmt: SYNC  */
#line 306 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1920 "yacc_sql.cpp"
    break;

  case 26: /* begin_stmt: TRX_BEGIN  */
#line 312 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1928 "yacc_sql.cpp"
    break;

  case 27: /* commit_stmt: TRX_COMMIT  */
#line 318 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1936 "yacc_sql.cpp"
    break;

  case 28: /* rollback_stmt: TRX_ROLLBACK  */
#line 324 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1944 "yacc_sql.cpp"
    break;

  case 29: /* drop_table_stmt: DROP TABLE ID  */
#line 330 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1954 "yacc_sql.cpp"
    break;

  case 30: /* show_tables_stmt: SHOW TABLES  */
#line 337 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1962 "yacc_sql.cpp"
    break;

  case 31: /* desc_table_stmt: DESC ID  */
#line 343 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1972 "yacc_sql.cpp"
    break;

  case 32: /* create_index_stmt: CREATE opt_unique INDEX ID ON ID LBRACE ID idx_col_list RBRACE  */
#line 352 "yacc_sql.y"
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
#line 1991 "yacc_sql.cpp"
    break;

  case 33: /* opt_unique: %empty  */
#line 369 "yacc_sql.y"
    {
      (yyval.bools) = false;
    }
#line 1999 "yacc_sql.cpp"
    break;

  case 34: /* opt_unique: UNIQUE  */
#line 373 "yacc_sql.y"
    {
      (yyval.bools) = true;
    }
#line 2007 "yacc_sql.cpp"
    break;

  case 35: /* idx_col_list: %empty  */
#line 379 "yacc_sql.y"
    {
      (yyval.relation_list) = new std::vector<std::string>;
    }
#line 2015 "yacc_sql.cpp"
    break;

  case 36: /* idx_col_list: COMMA ID idx_col_list  */
#line 383 "yacc_sql.y"
    {
      (yyval.relation_list) = (yyvsp[0].relation_list);
      (yyval.relation_list)->emplace_back((yyvsp[-1].string));
      free((yyvsp[-1].string));
    }
#line 2025 "yacc_sql.cpp"
    break;

  case 37: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 392 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2037 "yacc_sql.cpp"
    break;

  case 38: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format  */
#line 402 "yacc_sql.y"
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
#line 2062 "yacc_sql.cpp"
    break;

  case 39: /* attr_def_list: %empty  */
#line 425 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2070 "yacc_sql.cpp"
    break;

  case 40: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 429 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2084 "yacc_sql.cpp"
    break;

  case 41: /* attr_def: ID type LBRACE number RBRACE opt_null  */
#line 442 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[0].bools) == true;
      // 如果是 vector，那么这里的 length 代表的是数量
      if((yyvsp[-4].number) == static_cast<int>(AttrType::VECTORS)) {
        (yyval.attr_info)->length += (yyvsp[-2].number) * sizeof(double);
      } else {
        (yyval.attr_info)->length += (yyvsp[-2].number);
      }
      (yyval.attr_info)->nullable = (yyvsp[0].bools);
      free((yyvsp[-5].string));
    }
#line 2103 "yacc_sql.cpp"
    break;

  case 42: /* attr_def: ID type opt_null  */
#line 457 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      // 这块是 4 是因为 char 和 vector 需要用 ()
      (yyval.attr_info)->length = 4 + ((yyvsp[0].bools) == true);
      // 如果是 date，应该为 sizeof(common::DateTime)
      if((yyval.attr_info)->type == AttrType::DATES) {
        (yyval.attr_info)->length = sizeof(common::DateTime) + ((yyvsp[0].bools) == true);
      }
      (yyval.attr_info)->nullable = (yyvsp[0].bools);
      free((yyvsp[-2].string));
    }
#line 2121 "yacc_sql.cpp"
    break;

  case 43: /* opt_null: %empty  */
#line 473 "yacc_sql.y"
    {
      // 根据 primary-null.result 来看，默认是 not null
      (yyval.bools) = false;
    }
#line 2130 "yacc_sql.cpp"
    break;

  case 44: /* opt_null: NOT NULL_T  */
#line 478 "yacc_sql.y"
    {
      (yyval.bools) = false;
    }
#line 2138 "yacc_sql.cpp"
    break;

  case 45: /* opt_null: NULL_T  */
#line 482 "yacc_sql.y"
    {
      (yyval.bools) = true;
    }
#line 2146 "yacc_sql.cpp"
    break;

  case 46: /* number: NUMBER  */
#line 487 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2152 "yacc_sql.cpp"
    break;

  case 47: /* type: INT_T  */
#line 490 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::INTS); }
#line 2158 "yacc_sql.cpp"
    break;

  case 48: /* type: STRING_T  */
#line 491 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::CHARS); }
#line 2164 "yacc_sql.cpp"
    break;

  case 49: /* type: FLOAT_T  */
#line 492 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::FLOATS); }
#line 2170 "yacc_sql.cpp"
    break;

  case 50: /* type: VECTOR_T  */
#line 493 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::VECTORS); }
#line 2176 "yacc_sql.cpp"
    break;

  case 51: /* type: DATE_T  */
#line 494 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::DATES); }
#line 2182 "yacc_sql.cpp"
    break;

  case 52: /* insert_stmt: INSERT INTO ID VALUES LBRACE value value_list RBRACE  */
#line 498 "yacc_sql.y"
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
#line 2199 "yacc_sql.cpp"
    break;

  case 53: /* value_list: %empty  */
#line 514 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2207 "yacc_sql.cpp"
    break;

  case 54: /* value_list: COMMA insert_value value_list  */
#line 517 "yacc_sql.y"
                                     { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2221 "yacc_sql.cpp"
    break;

  case 55: /* insert_value: expression  */
#line 528 "yacc_sql.y"
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
#line 2237 "yacc_sql.cpp"
    break;

  case 56: /* value: NUMBER  */
#line 542 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2246 "yacc_sql.cpp"
    break;

  case 57: /* value: FLOAT  */
#line 546 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2255 "yacc_sql.cpp"
    break;

  case 58: /* value: DATE_STR  */
#line 550 "yacc_sql.y"
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
#line 2274 "yacc_sql.cpp"
    break;

  case 59: /* value: '[' double_list ']'  */
#line 565 "yacc_sql.y"
    {
      (yyval.value) = vec2val(sql_string, &(yyloc));
    }
#line 2282 "yacc_sql.cpp"
    break;

  case 60: /* value: SSS  */
#line 568 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2293 "yacc_sql.cpp"
    break;

  case 61: /* value: NULL_T  */
#line 574 "yacc_sql.y"
             {
      (yyval.value) = new Value();
      (yyval.value)->set_null();
    }
#line 2302 "yacc_sql.cpp"
    break;

  case 62: /* storage_format: %empty  */
#line 581 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2310 "yacc_sql.cpp"
    break;

  case 63: /* storage_format: STORAGE FORMAT EQ ID  */
#line 585 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2318 "yacc_sql.cpp"
    break;

  case 64: /* double_list: %empty  */
#line 589 "yacc_sql.y"
             {
      (yyval.double_list) = new std::vector<double>();
    }
#line 2326 "yacc_sql.cpp"
    break;

  case 65: /* double_list: float_number  */
#line 592 "yacc_sql.y"
                   {
      (yyval.double_list) = new std::vector<double>();
      (yyval.double_list)->emplace_back((yyvsp[0].float_number));
    }
#line 2335 "yacc_sql.cpp"
    break;

  case 66: /* double_list: double_list COMMA float_number  */
#line 596 "yacc_sql.y"
                                     {
      (yyval.double_list) = (yyvsp[-2].double_list);
      (yyval.double_list)->emplace_back((yyvsp[0].float_number));
    }
#line 2344 "yacc_sql.cpp"
    break;

  case 67: /* float_number: NUMBER  */
#line 601 "yacc_sql.y"
                     {
      (yyval.float_number) = (yyvsp[0].number);
    }
#line 2352 "yacc_sql.cpp"
    break;

  case 68: /* float_number: FLOAT  */
#line 604 "yacc_sql.y"
            {
      (yyval.float_number) = (yyvsp[0].floats);
    }
#line 2360 "yacc_sql.cpp"
    break;

  case 69: /* delete_stmt: DELETE FROM ID where  */
#line 610 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      (yyval.sql_node)->deletion.conditions = (yyvsp[0].expression);
      free((yyvsp[-1].string));
    }
#line 2371 "yacc_sql.cpp"
    break;

  case 70: /* update_stmt: UPDATE ID SET update_kv_list where  */
#line 619 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_UPDATE);
      (yyval.sql_node)->update.relation_name = (yyvsp[-3].string);
      (yyval.sql_node)->update.attribute_name.swap((yyvsp[-1].kv_list)->attrs);
      (yyval.sql_node)->update.value.swap((yyvsp[-1].kv_list)->values);
      (yyval.sql_node)->update.conditions = (yyvsp[0].expression);
      free((yyvsp[-3].string));
      delete((yyvsp[-1].kv_list));
    }
#line 2385 "yacc_sql.cpp"
    break;

  case 71: /* update_kv_list: ID EQ value  */
#line 631 "yacc_sql.y"
    {
      (yyval.kv_list) = new KeyValueList{};
      (yyval.kv_list)->attrs.emplace_back((yyvsp[-2].string));
      (yyval.kv_list)->values.emplace_back(*(yyvsp[0].value));
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 2397 "yacc_sql.cpp"
    break;

  case 72: /* update_kv_list: update_kv_list COMMA ID EQ value  */
#line 639 "yacc_sql.y"
    {
      (yyval.kv_list) = (yyvsp[-4].kv_list);
      (yyval.kv_list)->attrs.emplace_back((yyvsp[-2].string));
      (yyval.kv_list)->values.emplace_back(*(yyvsp[0].value));
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 2409 "yacc_sql.cpp"
    break;

  case 73: /* select_stmt: SELECT expression_list FROM rel_list inner_join_list where group_by opt_having order_by  */
#line 650 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-7].expression_list) != nullptr) {
        (yyval.sql_node)->selection.expressions.swap(*(yyvsp[-7].expression_list));
        delete (yyvsp[-7].expression_list);
      }

      if ((yyvsp[-5].relation_list) != nullptr) {
        if((yyvsp[-4].inner_join) != nullptr && (yyvsp[-5].relation_list)->size() != 1){
          yyerror(&(yyloc),sql_string,sql_result,scanner,"inner join only support one table",true);
          delete (yyvsp[-5].relation_list);
          YYERROR;
        }
        (yyval.sql_node)->selection.relations.swap(*(yyvsp[-5].relation_list));
        delete (yyvsp[-5].relation_list);
      }

      if((yyvsp[-4].inner_join) != nullptr){
        (yyval.sql_node)->selection.inner_join.reset((yyvsp[-4].inner_join));
      }

      if ((yyvsp[-3].expression) != nullptr) {
        (yyval.sql_node)->selection.conditions.reset((yyvsp[-3].expression));
      }

      if ((yyvsp[-2].expression_list) != nullptr) {
        (yyval.sql_node)->selection.group_by.swap(*(yyvsp[-2].expression_list));
        delete (yyvsp[-2].expression_list);
      }

      if((yyvsp[-1].expression) != nullptr){
        (yyval.sql_node)->selection.having_conditions.reset((yyvsp[-1].expression));
      }

      if((yyvsp[0].order_by_list) != nullptr){
        (yyval.sql_node)->selection.order_by.swap(*(yyvsp[0].order_by_list));
        delete (yyvsp[0].order_by_list);
      }
    }
#line 2453 "yacc_sql.cpp"
    break;

  case 74: /* select_stmt: SELECT expression_list  */
#line 690 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2464 "yacc_sql.cpp"
    break;

  case 75: /* calc_stmt: CALC expression_list  */
#line 700 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2474 "yacc_sql.cpp"
    break;

  case 76: /* expression_list: expression  */
#line 709 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2483 "yacc_sql.cpp"
    break;

  case 77: /* expression_list: expression COMMA expression_list  */
#line 714 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->emplace((yyval.expression_list)->begin(), (yyvsp[-2].expression));
    }
#line 2496 "yacc_sql.cpp"
    break;

  case 78: /* group_by_expression_list: %empty  */
#line 726 "yacc_sql.y"
  {
    (yyval.expression) = nullptr;
  }
#line 2504 "yacc_sql.cpp"
    break;

  case 79: /* group_by_expression_list: expression COMMA expression_list  */
#line 730 "yacc_sql.y"
  {
    (yyval.expression) = nullptr;
    delete (yyvsp[-2].expression);
    delete (yyvsp[0].expression_list);
  }
#line 2514 "yacc_sql.cpp"
    break;

  case 80: /* group_by_expression_list: expression  */
#line 736 "yacc_sql.y"
  {
    (yyval.expression) = (yyvsp[0].expression);
  }
#line 2522 "yacc_sql.cpp"
    break;

  case 81: /* expression: expression '+' expression  */
#line 742 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2530 "yacc_sql.cpp"
    break;

  case 82: /* expression: expression '-' expression  */
#line 745 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2538 "yacc_sql.cpp"
    break;

  case 83: /* expression: expression '*' expression  */
#line 748 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2546 "yacc_sql.cpp"
    break;

  case 84: /* expression: expression '/' expression  */
#line 751 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2554 "yacc_sql.cpp"
    break;

  case 85: /* expression: LBRACE expression_list RBRACE  */
#line 754 "yacc_sql.y"
                                    {
      if ((yyvsp[-1].expression_list)->size() == 1) {
        (yyval.expression) = (yyvsp[-1].expression_list)->front().release();
      } else {
        (yyval.expression) = new ExprListExpr(std::move(*(yyvsp[-1].expression_list)));
      }
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[-1].expression_list);
    }
#line 2568 "yacc_sql.cpp"
    break;

  case 86: /* expression: '-' expression  */
#line 763 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2576 "yacc_sql.cpp"
    break;

  case 87: /* expression: value  */
#line 766 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2586 "yacc_sql.cpp"
    break;

  case 88: /* expression: rel_attr  */
#line 771 "yacc_sql.y"
               {
      RelAttrSqlNode *node = (yyvsp[0].rel_attr);
      (yyval.expression) = new UnboundFieldExpr(node->relation_name, node->attribute_name);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].rel_attr);
    }
#line 2597 "yacc_sql.cpp"
    break;

  case 89: /* expression: aggregate_expr  */
#line 777 "yacc_sql.y"
                     {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 2605 "yacc_sql.cpp"
    break;

  case 90: /* expression: L2_DISTANCE LBRACE expression COMMA expression RBRACE  */
#line 780 "yacc_sql.y"
                                                            {
      (yyval.expression) = create_function_expression(FunctionExpr::Type::L2_DISTANCE, sql_string, (yyvsp[-3].expression), (yyvsp[-1].expression), &(yyloc));
    }
#line 2613 "yacc_sql.cpp"
    break;

  case 91: /* expression: COSINE_DISTANCE LBRACE expression COMMA expression RBRACE  */
#line 783 "yacc_sql.y"
                                                                {
      (yyval.expression) = create_function_expression(FunctionExpr::Type::COSINE_DISTANCE, sql_string, (yyvsp[-3].expression), (yyvsp[-1].expression), &(yyloc));
    }
#line 2621 "yacc_sql.cpp"
    break;

  case 92: /* expression: INNER_PRODUCT LBRACE expression COMMA expression RBRACE  */
#line 786 "yacc_sql.y"
                                                              {
      (yyval.expression) = create_function_expression(FunctionExpr::Type::INNER_PRODUCT, sql_string, (yyvsp[-3].expression), (yyvsp[-1].expression), &(yyloc));
    }
#line 2629 "yacc_sql.cpp"
    break;

  case 93: /* expression: sub_query_expr  */
#line 789 "yacc_sql.y"
                     {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 2637 "yacc_sql.cpp"
    break;

  case 94: /* expression: '*'  */
#line 792 "yacc_sql.y"
          {
      (yyval.expression) = new StarExpr();
    }
#line 2645 "yacc_sql.cpp"
    break;

  case 95: /* aggregate_expr: COUNT LBRACE group_by_expression_list RBRACE  */
#line 798 "yacc_sql.y"
                                                 {
      (yyval.expression) = create_aggregate_expression("count", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2653 "yacc_sql.cpp"
    break;

  case 96: /* aggregate_expr: SUM LBRACE group_by_expression_list RBRACE  */
#line 801 "yacc_sql.y"
                                                 {
      (yyval.expression) = create_aggregate_expression("sum", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2661 "yacc_sql.cpp"
    break;

  case 97: /* aggregate_expr: AVG LBRACE group_by_expression_list RBRACE  */
#line 804 "yacc_sql.y"
                                                 {
      (yyval.expression) = create_aggregate_expression("avg", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2669 "yacc_sql.cpp"
    break;

  case 98: /* aggregate_expr: MIN LBRACE group_by_expression_list RBRACE  */
#line 807 "yacc_sql.y"
                                                 {
      (yyval.expression) = create_aggregate_expression("min", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2677 "yacc_sql.cpp"
    break;

  case 99: /* aggregate_expr: MAX LBRACE group_by_expression_list RBRACE  */
#line 810 "yacc_sql.y"
                                                 {
      (yyval.expression) = create_aggregate_expression("max", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2685 "yacc_sql.cpp"
    break;

  case 100: /* sub_query_expr: LBRACE select_stmt RBRACE  */
#line 816 "yacc_sql.y"
    {
      (yyval.expression) = new SubQueryExpr(std::move((yyvsp[-1].sql_node)->selection));
      delete (yyvsp[-1].sql_node);
    }
#line 2694 "yacc_sql.cpp"
    break;

  case 101: /* rel_attr: ID  */
#line 823 "yacc_sql.y"
       {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2704 "yacc_sql.cpp"
    break;

  case 102: /* rel_attr: ID DOT ID  */
#line 828 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2716 "yacc_sql.cpp"
    break;

  case 103: /* relation: ID  */
#line 838 "yacc_sql.y"
       {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2724 "yacc_sql.cpp"
    break;

  case 104: /* rel_list: relation  */
#line 843 "yacc_sql.y"
             {
      (yyval.relation_list) = new std::vector<std::string>();
      (yyval.relation_list)->push_back((yyvsp[0].string));
      free((yyvsp[0].string));
    }
#line 2734 "yacc_sql.cpp"
    break;

  case 105: /* rel_list: relation COMMA rel_list  */
#line 848 "yacc_sql.y"
                              {
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new std::vector<std::string>;
      }

      (yyval.relation_list)->insert((yyval.relation_list)->begin(), (yyvsp[-2].string));
      free((yyvsp[-2].string));
    }
#line 2749 "yacc_sql.cpp"
    break;

  case 106: /* inner_join_list: %empty  */
#line 862 "yacc_sql.y"
    {
      (yyval.inner_join) = nullptr;
    }
#line 2757 "yacc_sql.cpp"
    break;

  case 107: /* inner_join_list: inner_join_list inner_join_rel  */
#line 866 "yacc_sql.y"
    {
      if((yyvsp[-1].inner_join) == nullptr){
        (yyval.inner_join) = new InnerJoinSqlNode();
      }else{
        (yyval.inner_join) = (yyvsp[-1].inner_join);
      }
      (yyval.inner_join)->relations.emplace_back((yyvsp[0].inner_join_unit)->relation);
      (yyval.inner_join)->conditions.emplace_back(std::move((yyvsp[0].inner_join_unit)->condition));
      delete (yyvsp[0].inner_join_unit);
    }
#line 2772 "yacc_sql.cpp"
    break;

  case 108: /* inner_join_rel: INNER JOIN relation ON condition  */
#line 878 "yacc_sql.y"
                                    {
      (yyval.inner_join_unit) = new InnerJoinUnit((yyvsp[-2].string)); 
      (yyval.inner_join_unit)->condition.reset((yyvsp[0].expression)); 
      free((yyvsp[-2].string));
    }
#line 2782 "yacc_sql.cpp"
    break;

  case 109: /* where: %empty  */
#line 888 "yacc_sql.y"
    {
      (yyval.expression) = nullptr;
    }
#line 2790 "yacc_sql.cpp"
    break;

  case 110: /* where: WHERE condition  */
#line 891 "yacc_sql.y"
                      {
      (yyval.expression) = (yyvsp[0].expression);  
    }
#line 2798 "yacc_sql.cpp"
    break;

  case 111: /* condition: expression comp_op expression  */
#line 897 "yacc_sql.y"
    {
      (yyval.expression) = new ComparisonExpr((yyvsp[-1].comp), (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 2806 "yacc_sql.cpp"
    break;

  case 112: /* condition: exists_op expression  */
#line 901 "yacc_sql.y"
    {
      Value val;
      val.set_null();
      ValueExpr *value_expr = new ValueExpr(val);
      (yyval.expression) = new ComparisonExpr((yyvsp[-1].comp), value_expr, (yyvsp[0].expression));
    }
#line 2817 "yacc_sql.cpp"
    break;

  case 113: /* condition: expression IS opt_null  */
#line 908 "yacc_sql.y"
    {
      Value val;
      val.set_null();
      ValueExpr *value_expr = new ValueExpr(val);
      (yyval.expression) = new ComparisonExpr((yyvsp[0].bools) ? IS_NULL : IS_NOT_NULL, (yyvsp[-2].expression), value_expr);
    }
#line 2828 "yacc_sql.cpp"
    break;

  case 114: /* condition: condition AND condition  */
#line 915 "yacc_sql.y"
    {
      (yyval.expression) = new ConjunctionExpr(ConjunctionExpr::Type::AND, (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 2836 "yacc_sql.cpp"
    break;

  case 115: /* condition: condition OR condition  */
#line 919 "yacc_sql.y"
    {
      (yyval.expression) = new ConjunctionExpr(ConjunctionExpr::Type::OR, (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 2844 "yacc_sql.cpp"
    break;

  case 116: /* comp_op: EQ  */
#line 925 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 2850 "yacc_sql.cpp"
    break;

  case 117: /* comp_op: LT  */
#line 926 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 2856 "yacc_sql.cpp"
    break;

  case 118: /* comp_op: GT  */
#line 927 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 2862 "yacc_sql.cpp"
    break;

  case 119: /* comp_op: LE  */
#line 928 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 2868 "yacc_sql.cpp"
    break;

  case 120: /* comp_op: LT GT  */
#line 929 "yacc_sql.y"
            { (yyval.comp) = NOT_EQUAL; }
#line 2874 "yacc_sql.cpp"
    break;

  case 121: /* comp_op: GE  */
#line 930 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 2880 "yacc_sql.cpp"
    break;

  case 122: /* comp_op: NE  */
#line 931 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 2886 "yacc_sql.cpp"
    break;

  case 123: /* comp_op: LIKE  */
#line 932 "yacc_sql.y"
           { (yyval.comp) = LIKE_OP; }
#line 2892 "yacc_sql.cpp"
    break;

  case 124: /* comp_op: NOT LIKE  */
#line 933 "yacc_sql.y"
               { (yyval.comp) = NOT_LIKE_OP; }
#line 2898 "yacc_sql.cpp"
    break;

  case 125: /* comp_op: IN  */
#line 934 "yacc_sql.y"
         { (yyval.comp) = IN_OP; }
#line 2904 "yacc_sql.cpp"
    break;

  case 126: /* comp_op: NOT IN  */
#line 935 "yacc_sql.y"
             { (yyval.comp) = NOT_IN_OP; }
#line 2910 "yacc_sql.cpp"
    break;

  case 127: /* exists_op: EXISTS  */
#line 939 "yacc_sql.y"
         { (yyval.comp) = EXISTS_OP; }
#line 2916 "yacc_sql.cpp"
    break;

  case 128: /* exists_op: NOT EXISTS  */
#line 940 "yacc_sql.y"
               { (yyval.comp) = NOT_EXISTS_OP; }
#line 2922 "yacc_sql.cpp"
    break;

  case 129: /* group_by: %empty  */
#line 945 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 2930 "yacc_sql.cpp"
    break;

  case 130: /* group_by: GROUP BY expression_list  */
#line 949 "yacc_sql.y"
    {
      (yyval.expression_list) = (yyvsp[0].expression_list);
    }
#line 2938 "yacc_sql.cpp"
    break;

  case 131: /* opt_having: %empty  */
#line 956 "yacc_sql.y"
  {
    (yyval.expression) = nullptr;
  }
#line 2946 "yacc_sql.cpp"
    break;

  case 132: /* opt_having: HAVING condition  */
#line 960 "yacc_sql.y"
  {
    (yyval.expression) = (yyvsp[0].expression);
  }
#line 2954 "yacc_sql.cpp"
    break;

  case 133: /* order_by: %empty  */
#line 967 "yacc_sql.y"
    {
      (yyval.order_by_list) = nullptr;
    }
#line 2962 "yacc_sql.cpp"
    break;

  case 134: /* order_by: ORDER BY order_by_list  */
#line 971 "yacc_sql.y"
    {
      (yyval.order_by_list) = (yyvsp[0].order_by_list);
      std::reverse((yyval.order_by_list)->begin(), (yyval.order_by_list)->end());
    }
#line 2971 "yacc_sql.cpp"
    break;

  case 135: /* order_by_list: order_unit  */
#line 979 "yacc_sql.y"
    {
      (yyval.order_by_list) = new std::vector<std::unique_ptr<OrderBySqlNode>>();
      (yyval.order_by_list)->emplace_back((yyvsp[0].order_unit));
    }
#line 2980 "yacc_sql.cpp"
    break;

  case 136: /* order_by_list: order_unit COMMA order_by_list  */
#line 984 "yacc_sql.y"
    {
      (yyval.order_by_list) = (yyvsp[0].order_by_list);
      (yyval.order_by_list)->emplace_back((yyvsp[-2].order_unit));
    }
#line 2989 "yacc_sql.cpp"
    break;

  case 137: /* order_unit: rel_attr order_op  */
#line 991 "yacc_sql.y"
    {
      (yyval.order_unit) = new OrderBySqlNode;
      RelAttrSqlNode *node = (yyvsp[-1].rel_attr);
      (yyval.order_unit)->unbound_field = std::make_unique<UnboundFieldExpr>(node->relation_name, node->attribute_name);
      (yyval.order_unit)->order_op = (yyvsp[0].order_op);
      delete (yyvsp[-1].rel_attr);
    }
#line 3001 "yacc_sql.cpp"
    break;

  case 138: /* order_op: %empty  */
#line 999 "yacc_sql.y"
    {
      (yyval.order_op) = OrderOp::ASC;
    }
#line 3009 "yacc_sql.cpp"
    break;

  case 139: /* order_op: ASC  */
#line 1003 "yacc_sql.y"
    {
      (yyval.order_op) = OrderOp::ASC;
    }
#line 3017 "yacc_sql.cpp"
    break;

  case 140: /* order_op: DESC  */
#line 1007 "yacc_sql.y"
    {
      (yyval.order_op) = OrderOp::DESC;
    }
#line 3025 "yacc_sql.cpp"
    break;

  case 141: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 1013 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3039 "yacc_sql.cpp"
    break;

  case 142: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1026 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3048 "yacc_sql.cpp"
    break;

  case 143: /* set_variable_stmt: SET ID EQ value  */
#line 1034 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3060 "yacc_sql.cpp"
    break;


#line 3064 "yacc_sql.cpp"

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

#line 1046 "yacc_sql.y"

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

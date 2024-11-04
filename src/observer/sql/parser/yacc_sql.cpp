/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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
    INDEX = 268,
    CALC = 269,
    SELECT = 270,
    DESC = 271,
    SHOW = 272,
    SYNC = 273,
    INSERT = 274,
    DELETE = 275,
    UPDATE = 276,
    INNER = 277,
    JOIN = 278,
    LBRACE = 279,
    RBRACE = 280,
    COMMA = 281,
    TRX_BEGIN = 282,
    TRX_COMMIT = 283,
    TRX_ROLLBACK = 284,
    INT_T = 285,
    STRING_T = 286,
    FLOAT_T = 287,
    VECTOR_T = 288,
    TEXT_T = 289,
    IS = 290,
    NOT = 291,
    NULL_T = 292,
    DATE_T = 293,
    HELP = 294,
    EXIT = 295,
    DOT = 296,
    INTO = 297,
    VALUES = 298,
    FROM = 299,
    WHERE = 300,
    AND = 301,
    OR = 302,
    SET = 303,
    ON = 304,
    AS = 305,
    LOAD = 306,
    DATA = 307,
    INFILE = 308,
    EXPLAIN = 309,
    STORAGE = 310,
    FORMAT = 311,
    EQ = 312,
    LT = 313,
    GT = 314,
    LE = 315,
    GE = 316,
    NE = 317,
    LIKE = 318,
    COUNT = 319,
    SUM = 320,
    AVG = 321,
    MAX = 322,
    MIN = 323,
    L2_DISTANCE = 324,
    COSINE_DISTANCE = 325,
    INNER_PRODUCT = 326,
    IN = 327,
    EXISTS = 328,
    VECTORS = 329,
    QUOTE = 330,
    UNIQUE = 331,
    NUMBER = 332,
    FLOAT = 333,
    ID = 334,
    SSS = 335,
    DATE_STR = 336,
    UMINUS = 337
  };
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

#line 309 "yacc_sql.cpp"

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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


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
#define YYLAST   319

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  89
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  59
/* YYNRULES -- Number of rules.  */
#define YYNRULES  150
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  283

#define YYUNDEFTOK  2
#define YYMAXUTOK   337


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,    84,    82,     2,    83,     2,    85,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    87,     2,    88,     2,     2,     2,     2,     2,     2,
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
      75,    76,    77,    78,    79,    80,    81,    86
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   268,   268,   276,   277,   278,   279,   280,   281,   282,
     283,   284,   285,   286,   287,   288,   289,   290,   291,   292,
     293,   294,   295,   299,   305,   310,   316,   322,   328,   334,
     341,   347,   355,   373,   376,   383,   386,   395,   405,   429,
     432,   445,   469,   494,   497,   501,   508,   512,   516,   522,
     525,   526,   527,   528,   529,   530,   533,   550,   553,   563,
     578,   582,   586,   600,   604,   610,   617,   620,   625,   628,
     632,   637,   640,   645,   658,   674,   681,   691,   731,   741,
     750,   759,   776,   779,   787,   797,   800,   803,   806,   809,
     818,   821,   826,   832,   835,   838,   841,   844,   847,   853,
     856,   859,   862,   865,   870,   878,   883,   890,   899,   904,
     914,   934,   937,   951,   967,   970,   975,   979,   986,   993,
     997,  1004,  1005,  1006,  1007,  1008,  1009,  1010,  1011,  1012,
    1013,  1014,  1018,  1019,  1024,  1027,  1035,  1038,  1046,  1049,
    1057,  1062,  1069,  1078,  1081,  1085,  1091,  1104,  1112,  1122,
    1123
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SEMICOLON", "BY", "CREATE", "DROP",
  "GROUP", "ORDER", "ASC", "HAVING", "TABLE", "TABLES", "INDEX", "CALC",
  "SELECT", "DESC", "SHOW", "SYNC", "INSERT", "DELETE", "UPDATE", "INNER",
  "JOIN", "LBRACE", "RBRACE", "COMMA", "TRX_BEGIN", "TRX_COMMIT",
  "TRX_ROLLBACK", "INT_T", "STRING_T", "FLOAT_T", "VECTOR_T", "TEXT_T",
  "IS", "NOT", "NULL_T", "DATE_T", "HELP", "EXIT", "DOT", "INTO", "VALUES",
  "FROM", "WHERE", "AND", "OR", "SET", "ON", "AS", "LOAD", "DATA",
  "INFILE", "EXPLAIN", "STORAGE", "FORMAT", "EQ", "LT", "GT", "LE", "GE",
  "NE", "LIKE", "COUNT", "SUM", "AVG", "MAX", "MIN", "L2_DISTANCE",
  "COSINE_DISTANCE", "INNER_PRODUCT", "IN", "EXISTS", "VECTORS", "QUOTE",
  "UNIQUE", "NUMBER", "FLOAT", "ID", "SSS", "DATE_STR", "'+'", "'-'",
  "'*'", "'/'", "UMINUS", "'['", "']'", "$accept", "commands",
  "command_wrapper", "exit_stmt", "help_stmt", "sync_stmt", "begin_stmt",
  "commit_stmt", "rollback_stmt", "drop_table_stmt", "show_tables_stmt",
  "desc_table_stmt", "create_index_stmt", "opt_unique", "idx_col_list",
  "drop_index_stmt", "create_table_stmt", "attr_def_list", "attr_def",
  "alias", "opt_null", "number", "type", "insert_stmt", "value_list",
  "insert_value", "value", "storage_format", "double_list", "float_number",
  "delete_stmt", "update_stmt", "update_kv_list", "select_stmt",
  "calc_stmt", "expression_list", "aggr_argument_list", "expression",
  "aggregate_expr", "sub_query_expr", "rel_attr", "relation", "rel_list",
  "inner_join_list", "inner_join_rel", "where", "condition", "comp_op",
  "exists_op", "group_by", "opt_having", "order_by", "order_by_list",
  "order_unit", "order_op", "load_data_stmt", "explain_stmt",
  "set_variable_stmt", "opt_semicolon", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,    43,    45,    42,    47,   337,    91,    93
};
# endif

#define YYPACT_NINF (-257)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     230,    -1,     7,   121,   121,   -55,    14,  -257,     8,    34,
      16,  -257,  -257,  -257,  -257,  -257,    19,    41,   230,   106,
     109,  -257,  -257,  -257,  -257,  -257,  -257,  -257,  -257,  -257,
    -257,  -257,  -257,  -257,  -257,  -257,  -257,  -257,  -257,  -257,
    -257,    63,  -257,   133,    73,    83,   -10,  -257,   147,   149,
     150,   151,   157,   159,   171,   173,  -257,  -257,   141,  -257,
    -257,   121,  -257,   -12,  -257,  -257,    82,  -257,  -257,  -257,
     162,  -257,  -257,   124,   128,   -39,   152,   160,  -257,  -257,
    -257,  -257,   186,   132,  -257,   165,   197,   203,   121,   121,
     121,   121,   121,   121,   121,   121,   -40,  -257,  -257,  -257,
     -25,  -257,   153,  -257,   121,   121,   121,   121,   207,   155,
     195,   -39,   181,    76,   172,   174,   190,   175,  -257,  -257,
     231,    82,   235,   236,   237,   238,    26,    36,    66,  -257,
    -257,   -12,  -257,  -257,     6,     6,  -257,  -257,   121,  -257,
     -39,  -257,   240,   210,   187,  -257,   223,   193,   241,   189,
    -257,  -257,   245,  -257,  -257,  -257,  -257,   121,   121,   121,
    -257,  -257,   246,   -16,    76,    60,  -257,   216,    -7,   263,
    -257,  -257,  -257,  -257,  -257,  -257,   -20,   174,   250,   252,
     121,    -3,     3,    20,   155,   254,  -257,   272,   256,   212,
    -257,   158,   113,   121,   121,   201,  -257,   204,   209,   251,
    -257,  -257,   241,   232,   211,  -257,  -257,  -257,  -257,  -257,
     155,   285,   281,   121,   267,  -257,    86,   -51,  -257,   234,
    -257,  -257,  -257,  -257,  -257,  -257,   121,    60,    60,    32,
      32,   239,  -257,  -257,   269,  -257,  -257,   242,  -257,   271,
     -39,   121,    60,   287,   256,    32,  -257,  -257,  -257,  -257,
    -257,    32,  -257,   253,   121,    86,   243,   222,   277,   255,
    -257,   113,   299,  -257,  -257,    32,  -257,   226,   271,  -257,
      60,   227,  -257,  -257,   113,    67,  -257,   282,  -257,  -257,
    -257,   227,  -257
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    33,     0,     0,     0,     0,     0,    25,     0,     0,
       0,    26,    27,    28,    24,    23,     0,     0,     0,     0,
     149,    22,    21,    14,    15,    16,    17,     9,    10,    11,
      12,    13,     8,     5,     7,     6,     4,     3,    18,    19,
      20,     0,    34,     0,     0,     0,     0,    65,     0,     0,
       0,     0,     0,     0,     0,     0,    60,    61,   105,    64,
      62,     0,    98,    68,    91,    79,    43,    96,    97,    92,
      78,    31,    30,     0,     0,    43,     0,     0,   147,     1,
     150,     2,     0,     0,    29,     0,     0,     0,    82,    82,
      82,    82,    82,     0,     0,     0,     0,    90,    71,    72,
       0,    69,     0,    44,     0,     0,     0,     0,    80,     0,
       0,    43,     0,     0,     0,     0,     0,     0,   104,    89,
       0,    43,     0,     0,     0,     0,     0,     0,     0,   106,
     107,     0,    63,    45,    85,    86,    87,    88,     0,   108,
      43,   111,     0,   114,     0,   148,     0,     0,    39,     0,
      37,    99,    83,   100,   101,   103,   102,     0,     0,     0,
      70,    81,   109,   114,     0,     0,    73,     0,   114,     0,
      50,    51,    52,    53,    54,    55,    46,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   112,   134,    57,     0,
     132,     0,   115,     0,     0,     0,    74,     0,     0,     0,
      48,    42,    39,    66,     0,    84,    93,    94,    95,   110,
       0,     0,   136,     0,     0,   133,    46,     0,   121,   122,
     123,   124,   126,   127,   128,   130,     0,     0,     0,   117,
      75,     0,   146,    49,     0,    47,    40,     0,    38,    35,
      43,     0,     0,   138,    57,    59,    56,   118,   129,   131,
     125,   116,   119,   120,     0,    46,     0,     0,     0,     0,
     135,   137,     0,    77,    58,    76,    41,     0,    35,    32,
       0,     0,    67,    36,   113,   143,   139,   140,   144,   145,
     142,     0,   141
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -257,  -257,   289,  -257,  -257,  -257,  -257,  -257,  -257,  -257,
    -257,  -257,  -257,  -257,    42,  -257,  -257,   107,   134,   -68,
    -214,  -257,  -257,  -257,    68,  -257,  -100,  -257,  -257,   182,
    -257,  -257,  -257,   268,  -257,    -4,    88,   -58,  -257,  -257,
    -256,   105,   135,  -257,  -257,   -74,  -219,  -257,  -257,  -257,
    -257,  -257,    35,  -257,  -257,  -257,  -257,  -257,  -257
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    43,   258,    31,    32,   178,   148,   108,
     201,   234,   176,    33,   214,   244,    64,   238,   100,   101,
      34,    35,   168,    36,    37,    65,   120,    66,    67,    68,
      69,   140,   141,   163,   186,   166,   192,   226,   193,   212,
     243,   263,   276,   277,   280,    38,    39,    40,    81
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      70,   131,   247,    97,   198,     4,   185,   112,   252,   253,
      41,   102,   248,   145,    46,   275,   199,   200,    44,   195,
      45,   249,   206,   261,    71,   275,    72,    47,   207,   165,
     121,   121,   121,   121,   121,   126,   127,   128,   165,   129,
     103,   266,    87,   143,   130,   208,   134,   135,   136,   137,
      73,   274,   157,   152,    48,    49,    50,    51,    52,    53,
      54,    55,   158,   132,   188,    98,    99,    56,    57,    58,
      59,    60,   162,    61,    62,    42,   278,    63,    74,   104,
     105,   106,   107,   279,    46,   104,   105,   106,   107,   187,
     106,   107,   159,    77,   196,    75,   189,    47,    76,   181,
     182,   183,   104,   105,   106,   107,    79,   191,   104,   105,
     106,   107,    80,    47,   104,   105,   106,   107,   104,   105,
     106,   107,   199,   200,    48,    49,    50,    51,    52,    53,
      54,    55,   102,   190,   161,   229,   230,    56,    57,    58,
      59,    60,    82,    61,    62,    46,    83,    63,   104,   105,
     106,   107,    84,    56,    57,   245,    59,    60,    47,   227,
     228,   103,    85,    63,   104,   105,   106,   107,   251,   191,
     191,    88,   259,    89,    90,    91,   205,   122,   123,   124,
     125,    92,    96,    93,   191,    48,    49,    50,    51,    52,
      53,    54,    55,   216,   217,    94,   265,    95,    56,    57,
      58,    59,    60,   110,    61,    62,   109,   111,    63,   113,
     115,   116,   191,   114,   117,   218,   219,   220,   221,   222,
     223,   224,   118,   170,   171,   172,   173,   174,   119,   144,
     225,   175,   133,   138,   139,     1,     2,   260,   142,   149,
     104,   105,   106,   107,     3,     4,     5,     6,     7,     8,
       9,    10,   146,   147,   150,   165,   151,    11,    12,    13,
     153,   154,   155,   156,   164,   169,   167,   177,   179,    14,
      15,   180,   184,   194,   197,   203,   204,   210,    16,   211,
     231,    17,   213,   232,    18,   215,   233,   237,   235,   241,
     239,   242,   246,   250,   255,   262,   254,   257,   256,   227,
     267,   268,   269,   271,   270,   272,    58,    78,   281,   236,
     273,   202,   264,   160,    86,   240,   282,     0,     0,   209
};

static const yytype_int16 yycheck[] =
{
       4,    26,   216,    61,    24,    15,    22,    75,   227,   228,
      11,    50,    63,   113,    24,   271,    36,    37,    11,    26,
      13,    72,    25,   242,    79,   281,    12,    37,    25,    45,
      88,    89,    90,    91,    92,    93,    94,    95,    45,    79,
      79,   255,    46,   111,    84,    25,   104,   105,   106,   107,
      42,   270,    26,   121,    64,    65,    66,    67,    68,    69,
      70,    71,    26,    88,   164,    77,    78,    77,    78,    79,
      80,    81,   140,    83,    84,    76,     9,    87,    44,    82,
      83,    84,    85,    16,    24,    82,    83,    84,    85,   163,
      84,    85,    26,    52,   168,    79,    36,    37,    79,   157,
     158,   159,    82,    83,    84,    85,     0,   165,    82,    83,
      84,    85,     3,    37,    82,    83,    84,    85,    82,    83,
      84,    85,    36,    37,    64,    65,    66,    67,    68,    69,
      70,    71,    50,    73,   138,   193,   194,    77,    78,    79,
      80,    81,    79,    83,    84,    24,    13,    87,    82,    83,
      84,    85,    79,    77,    78,   213,    80,    81,    37,    46,
      47,    79,    79,    87,    82,    83,    84,    85,   226,   227,
     228,    24,   240,    24,    24,    24,   180,    89,    90,    91,
      92,    24,    41,    24,   242,    64,    65,    66,    67,    68,
      69,    70,    71,    35,    36,    24,   254,    24,    77,    78,
      79,    80,    81,    79,    83,    84,    44,    79,    87,    57,
      24,    79,   270,    53,    49,    57,    58,    59,    60,    61,
      62,    63,    25,    30,    31,    32,    33,    34,    25,    48,
      72,    38,    79,    26,    79,     5,     6,   241,    43,    49,
      82,    83,    84,    85,    14,    15,    16,    17,    18,    19,
      20,    21,    80,    79,    79,    45,    25,    27,    28,    29,
      25,    25,    25,    25,    24,    42,    79,    26,    79,    39,
      40,    26,    26,    57,    11,    25,    24,    23,    48,     7,
      79,    51,    26,    79,    54,    73,    77,    55,    37,     4,
      79,    10,    25,    59,    25,     8,    57,    26,    56,    46,
      57,    79,    25,     4,    49,    79,    79,    18,    26,   202,
     268,   177,   244,   131,    46,   210,   281,    -1,    -1,   184
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     6,    14,    15,    16,    17,    18,    19,    20,
      21,    27,    28,    29,    39,    40,    48,    51,    54,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   104,   105,   112,   119,   120,   122,   123,   144,   145,
     146,    11,    76,   102,    11,    13,    24,    37,    64,    65,
      66,    67,    68,    69,    70,    71,    77,    78,    79,    80,
      81,    83,    84,    87,   115,   124,   126,   127,   128,   129,
     124,    79,    12,    42,    44,    79,    79,    52,    91,     0,
       3,   147,    79,    13,    79,    79,   122,   124,    24,    24,
      24,    24,    24,    24,    24,    24,    41,   126,    77,    78,
     117,   118,    50,    79,    82,    83,    84,    85,   108,    44,
      79,    79,   108,    57,    53,    24,    79,    49,    25,    25,
     125,   126,   125,   125,   125,   125,   126,   126,   126,    79,
      84,    26,    88,    79,   126,   126,   126,   126,    26,    79,
     130,   131,    43,   108,    48,   115,    80,    79,   107,    49,
      79,    25,   108,    25,    25,    25,    25,    26,    26,    26,
     118,   124,   108,   132,    24,    45,   134,    79,   121,    42,
      30,    31,    32,    33,    34,    38,   111,    26,   106,    79,
      26,   126,   126,   126,    26,    22,   133,   134,   115,    36,
      73,   126,   135,   137,    57,    26,   134,    11,    24,    36,
      37,   109,   107,    25,    24,   124,    25,    25,    25,   131,
      23,     7,   138,    26,   113,    73,    35,    36,    57,    58,
      59,    60,    61,    62,    63,    72,   136,    46,    47,   126,
     126,    79,    79,    77,   110,    37,   106,    55,   116,    79,
     130,     4,    10,   139,   114,   126,    25,   109,    63,    72,
      59,   126,   135,   135,    57,    25,    56,    26,   103,   108,
     124,   135,     8,   140,   113,   126,   109,    57,    79,    25,
      49,     4,    79,   103,   135,   129,   141,   142,     9,    16,
     143,    26,   141
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    89,    90,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   102,   103,   103,   104,   105,   106,
     106,   107,   107,   108,   108,   108,   109,   109,   109,   110,
     111,   111,   111,   111,   111,   111,   112,   113,   113,   114,
     115,   115,   115,   115,   115,   115,   116,   116,   117,   117,
     117,   118,   118,   119,   120,   121,   121,   122,   122,   123,
     124,   124,   125,   125,   125,   126,   126,   126,   126,   126,
     126,   126,   126,   126,   126,   126,   126,   126,   126,   127,
     127,   127,   127,   127,   128,   129,   129,   129,   130,   131,
     131,   132,   132,   133,   134,   134,   135,   135,   135,   135,
     135,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   137,   137,   138,   138,   139,   139,   140,   140,
     141,   141,   142,   143,   143,   143,   144,   145,   146,   147,
     147
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       2,     2,    10,     0,     1,     0,     3,     5,     8,     0,
       3,     6,     3,     0,     1,     2,     0,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     8,     0,     3,     1,
       1,     1,     1,     3,     1,     1,     0,     4,     0,     1,
       3,     1,     1,     5,     6,     3,     5,     9,     2,     2,
       2,     4,     0,     2,     4,     3,     3,     3,     3,     3,
       2,     1,     1,     6,     6,     6,     1,     1,     1,     4,
       4,     4,     4,     4,     3,     1,     3,     3,     1,     2,
       4,     0,     2,     6,     0,     2,     3,     2,     3,     3,
       3,     1,     1,     1,     1,     2,     1,     1,     1,     2,
       1,     2,     1,     2,     0,     3,     0,     2,     0,     3,
       1,     3,     2,     0,     1,     1,     7,     2,     4,     0,
       1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

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

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location, sql_string, sql_result, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  YYUSE (sql_string);
  YYUSE (sql_result);
  YYUSE (scanner);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yytype, yyvaluep, yylocationp, sql_string, sql_result, scanner);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
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
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       , sql_string, sql_result, scanner);
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
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
#  endif
# endif

# ifndef yytnamerr
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
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
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
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
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
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
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
          yyp += yytnamerr (yyp, yyarg[yyi++]);
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
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (sql_string);
  YYUSE (sql_result);
  YYUSE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
/* The lookahead symbol.  */
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
    int yynerrs;

    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
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

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
# undef YYSTACK_RELOCATE
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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex (&yylval, &yylloc, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
  case 2:
#line 269 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1837 "yacc_sql.cpp"
    break;

  case 23:
#line 299 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1846 "yacc_sql.cpp"
    break;

  case 24:
#line 305 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1854 "yacc_sql.cpp"
    break;

  case 25:
#line 310 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1862 "yacc_sql.cpp"
    break;

  case 26:
#line 316 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1870 "yacc_sql.cpp"
    break;

  case 27:
#line 322 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1878 "yacc_sql.cpp"
    break;

  case 28:
#line 328 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1886 "yacc_sql.cpp"
    break;

  case 29:
#line 334 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1896 "yacc_sql.cpp"
    break;

  case 30:
#line 341 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1904 "yacc_sql.cpp"
    break;

  case 31:
#line 347 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1914 "yacc_sql.cpp"
    break;

  case 32:
#line 356 "yacc_sql.y"
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
#line 1933 "yacc_sql.cpp"
    break;

  case 33:
#line 373 "yacc_sql.y"
    {
      (yyval.bools) = false;
    }
#line 1941 "yacc_sql.cpp"
    break;

  case 34:
#line 377 "yacc_sql.y"
    {
      (yyval.bools) = true;
    }
#line 1949 "yacc_sql.cpp"
    break;

  case 35:
#line 383 "yacc_sql.y"
    {
      (yyval.relation_list) = new std::vector<std::string>;
    }
#line 1957 "yacc_sql.cpp"
    break;

  case 36:
#line 387 "yacc_sql.y"
    {
      (yyval.relation_list) = (yyvsp[0].relation_list);
      (yyval.relation_list)->emplace_back((yyvsp[-1].string));
      free((yyvsp[-1].string));
    }
#line 1967 "yacc_sql.cpp"
    break;

  case 37:
#line 396 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 1979 "yacc_sql.cpp"
    break;

  case 38:
#line 406 "yacc_sql.y"
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
#line 2004 "yacc_sql.cpp"
    break;

  case 39:
#line 429 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2012 "yacc_sql.cpp"
    break;

  case 40:
#line 433 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2026 "yacc_sql.cpp"
    break;

  case 41:
#line 446 "yacc_sql.y"
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
#line 2054 "yacc_sql.cpp"
    break;

  case 42:
#line 470 "yacc_sql.y"
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
#line 2079 "yacc_sql.cpp"
    break;

  case 43:
#line 494 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2087 "yacc_sql.cpp"
    break;

  case 44:
#line 498 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2095 "yacc_sql.cpp"
    break;

  case 45:
#line 502 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2103 "yacc_sql.cpp"
    break;

  case 46:
#line 508 "yacc_sql.y"
    {
      // 根据 primary-null.result 来看，默认是 not null
      (yyval.bools) = true;
    }
#line 2112 "yacc_sql.cpp"
    break;

  case 47:
#line 513 "yacc_sql.y"
    {
      (yyval.bools) = false;
    }
#line 2120 "yacc_sql.cpp"
    break;

  case 48:
#line 517 "yacc_sql.y"
    {
      (yyval.bools) = true;
    }
#line 2128 "yacc_sql.cpp"
    break;

  case 49:
#line 522 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2134 "yacc_sql.cpp"
    break;

  case 50:
#line 525 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::INTS); }
#line 2140 "yacc_sql.cpp"
    break;

  case 51:
#line 526 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::CHARS); }
#line 2146 "yacc_sql.cpp"
    break;

  case 52:
#line 527 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::FLOATS); }
#line 2152 "yacc_sql.cpp"
    break;

  case 53:
#line 528 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::VECTORS); }
#line 2158 "yacc_sql.cpp"
    break;

  case 54:
#line 529 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::TEXTS); }
#line 2164 "yacc_sql.cpp"
    break;

  case 55:
#line 530 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::DATES); }
#line 2170 "yacc_sql.cpp"
    break;

  case 56:
#line 534 "yacc_sql.y"
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
#line 2187 "yacc_sql.cpp"
    break;

  case 57:
#line 550 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2195 "yacc_sql.cpp"
    break;

  case 58:
#line 553 "yacc_sql.y"
                                     { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2209 "yacc_sql.cpp"
    break;

  case 59:
#line 564 "yacc_sql.y"
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
#line 2225 "yacc_sql.cpp"
    break;

  case 60:
#line 578 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2234 "yacc_sql.cpp"
    break;

  case 61:
#line 582 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2243 "yacc_sql.cpp"
    break;

  case 62:
#line 586 "yacc_sql.y"
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
#line 2262 "yacc_sql.cpp"
    break;

  case 63:
#line 601 "yacc_sql.y"
    {
      (yyval.value) = vec2val(sql_string, &(yyloc));
    }
#line 2270 "yacc_sql.cpp"
    break;

  case 64:
#line 604 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2281 "yacc_sql.cpp"
    break;

  case 65:
#line 610 "yacc_sql.y"
             {
      (yyval.value) = new Value();
      (yyval.value)->set_null();
    }
#line 2290 "yacc_sql.cpp"
    break;

  case 66:
#line 617 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2298 "yacc_sql.cpp"
    break;

  case 67:
#line 621 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2306 "yacc_sql.cpp"
    break;

  case 68:
#line 625 "yacc_sql.y"
             {
      (yyval.double_list) = new std::vector<double>();
    }
#line 2314 "yacc_sql.cpp"
    break;

  case 69:
#line 628 "yacc_sql.y"
                   {
      (yyval.double_list) = new std::vector<double>();
      (yyval.double_list)->emplace_back((yyvsp[0].float_number));
    }
#line 2323 "yacc_sql.cpp"
    break;

  case 70:
#line 632 "yacc_sql.y"
                                     {
      (yyval.double_list) = (yyvsp[-2].double_list);
      (yyval.double_list)->emplace_back((yyvsp[0].float_number));
    }
#line 2332 "yacc_sql.cpp"
    break;

  case 71:
#line 637 "yacc_sql.y"
                     {
      (yyval.float_number) = (yyvsp[0].number);
    }
#line 2340 "yacc_sql.cpp"
    break;

  case 72:
#line 640 "yacc_sql.y"
            {
      (yyval.float_number) = (yyvsp[0].floats);
    }
#line 2348 "yacc_sql.cpp"
    break;

  case 73:
#line 646 "yacc_sql.y"
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
#line 2363 "yacc_sql.cpp"
    break;

  case 74:
#line 659 "yacc_sql.y"
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
#line 2381 "yacc_sql.cpp"
    break;

  case 75:
#line 675 "yacc_sql.y"
    {
      (yyval.kv_list) = new KeyValueList{};
      (yyval.kv_list)->attrs.emplace_back((yyvsp[-2].string));
      (yyval.kv_list)->values.emplace_back((yyvsp[0].expression));
      free((yyvsp[-2].string));
    }
#line 2392 "yacc_sql.cpp"
    break;

  case 76:
#line 682 "yacc_sql.y"
    {
      (yyval.kv_list) = (yyvsp[-4].kv_list);
      (yyval.kv_list)->attrs.emplace_back((yyvsp[-2].string));
      (yyval.kv_list)->values.emplace_back((yyvsp[0].expression));
      free((yyvsp[-2].string));
    }
#line 2403 "yacc_sql.cpp"
    break;

  case 77:
#line 692 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-7].expression_list) != nullptr) {
        (yyval.sql_node)->selection.expressions.swap(*(yyvsp[-7].expression_list));
        delete (yyvsp[-7].expression_list);
      }

      if ((yyvsp[-5].relation_list) != nullptr) {
        if((yyvsp[-4].inner_join) != nullptr && (yyvsp[-5].relation_list)->size() != 2){
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
#line 2447 "yacc_sql.cpp"
    break;

  case 78:
#line 732 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2458 "yacc_sql.cpp"
    break;

  case 79:
#line 742 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2468 "yacc_sql.cpp"
    break;

  case 80:
#line 751 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->emplace_back((yyvsp[-1].expression));
      if((yyvsp[0].string) != nullptr){
        (yyvsp[-1].expression)->set_alias((yyvsp[0].string));
        free((yyvsp[0].string));
      }
    }
#line 2481 "yacc_sql.cpp"
    break;

  case 81:
#line 760 "yacc_sql.y"
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
#line 2498 "yacc_sql.cpp"
    break;

  case 82:
#line 776 "yacc_sql.y"
  {
    (yyval.expression) = nullptr;
  }
#line 2506 "yacc_sql.cpp"
    break;

  case 83:
#line 780 "yacc_sql.y"
  {
    if((yyvsp[0].string) != nullptr){
      (yyvsp[-1].expression)->set_alias((yyvsp[0].string));
      free((yyvsp[0].string));
    }
    (yyval.expression) = (yyvsp[-1].expression);
  }
#line 2518 "yacc_sql.cpp"
    break;

  case 84:
#line 788 "yacc_sql.y"
  {
    (yyval.expression) = nullptr;
    delete (yyvsp[-3].expression);
    free((yyvsp[-2].string));
    delete (yyvsp[0].expression_list);
  }
#line 2529 "yacc_sql.cpp"
    break;

  case 85:
#line 797 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2537 "yacc_sql.cpp"
    break;

  case 86:
#line 800 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2545 "yacc_sql.cpp"
    break;

  case 87:
#line 803 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2553 "yacc_sql.cpp"
    break;

  case 88:
#line 806 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2561 "yacc_sql.cpp"
    break;

  case 89:
#line 809 "yacc_sql.y"
                                    {
      if ((yyvsp[-1].expression_list)->size() == 1) {
        (yyval.expression) = (yyvsp[-1].expression_list)->front().release();
      } else {
        (yyval.expression) = new ExprListExpr(std::move(*(yyvsp[-1].expression_list)));
      }
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[-1].expression_list);
    }
#line 2575 "yacc_sql.cpp"
    break;

  case 90:
#line 818 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2583 "yacc_sql.cpp"
    break;

  case 91:
#line 821 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2593 "yacc_sql.cpp"
    break;

  case 92:
#line 826 "yacc_sql.y"
               {
      RelAttrSqlNode *node = (yyvsp[0].rel_attr);
      (yyval.expression) = new UnboundFieldExpr(node->relation_name, node->attribute_name);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].rel_attr);
    }
#line 2604 "yacc_sql.cpp"
    break;

  case 93:
#line 832 "yacc_sql.y"
                                                            {
      (yyval.expression) = create_function_expression(FunctionExpr::Type::L2_DISTANCE, sql_string, (yyvsp[-3].expression), (yyvsp[-1].expression), &(yyloc));
    }
#line 2612 "yacc_sql.cpp"
    break;

  case 94:
#line 835 "yacc_sql.y"
                                                                {
      (yyval.expression) = create_function_expression(FunctionExpr::Type::COSINE_DISTANCE, sql_string, (yyvsp[-3].expression), (yyvsp[-1].expression), &(yyloc));
    }
#line 2620 "yacc_sql.cpp"
    break;

  case 95:
#line 838 "yacc_sql.y"
                                                              {
      (yyval.expression) = create_function_expression(FunctionExpr::Type::INNER_PRODUCT, sql_string, (yyvsp[-3].expression), (yyvsp[-1].expression), &(yyloc));
    }
#line 2628 "yacc_sql.cpp"
    break;

  case 96:
#line 841 "yacc_sql.y"
                     {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 2636 "yacc_sql.cpp"
    break;

  case 97:
#line 844 "yacc_sql.y"
                     {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 2644 "yacc_sql.cpp"
    break;

  case 98:
#line 847 "yacc_sql.y"
          {
      (yyval.expression) = new StarExpr();
    }
#line 2652 "yacc_sql.cpp"
    break;

  case 99:
#line 853 "yacc_sql.y"
                                           {
      (yyval.expression) = create_aggregate_expression("count", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2660 "yacc_sql.cpp"
    break;

  case 100:
#line 856 "yacc_sql.y"
                                           {
      (yyval.expression) = create_aggregate_expression("sum", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2668 "yacc_sql.cpp"
    break;

  case 101:
#line 859 "yacc_sql.y"
                                           {
      (yyval.expression) = create_aggregate_expression("avg", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2676 "yacc_sql.cpp"
    break;

  case 102:
#line 862 "yacc_sql.y"
                                           {
      (yyval.expression) = create_aggregate_expression("min", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2684 "yacc_sql.cpp"
    break;

  case 103:
#line 865 "yacc_sql.y"
                                           {
      (yyval.expression) = create_aggregate_expression("max", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2692 "yacc_sql.cpp"
    break;

  case 104:
#line 871 "yacc_sql.y"
    {
      (yyval.expression) = new SubQueryExpr(std::move((yyvsp[-1].sql_node)->selection));
      delete (yyvsp[-1].sql_node);
    }
#line 2701 "yacc_sql.cpp"
    break;

  case 105:
#line 878 "yacc_sql.y"
       {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2711 "yacc_sql.cpp"
    break;

  case 106:
#line 883 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2723 "yacc_sql.cpp"
    break;

  case 107:
#line 890 "yacc_sql.y"
                 {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = "*";
      free((yyvsp[-2].string));
    }
#line 2734 "yacc_sql.cpp"
    break;

  case 108:
#line 899 "yacc_sql.y"
       {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2742 "yacc_sql.cpp"
    break;

  case 109:
#line 904 "yacc_sql.y"
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
#line 2757 "yacc_sql.cpp"
    break;

  case 110:
#line 914 "yacc_sql.y"
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
#line 2778 "yacc_sql.cpp"
    break;

  case 111:
#line 934 "yacc_sql.y"
    {
      (yyval.inner_join) = nullptr;
    }
#line 2786 "yacc_sql.cpp"
    break;

  case 112:
#line 938 "yacc_sql.y"
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
#line 2802 "yacc_sql.cpp"
    break;

  case 113:
#line 951 "yacc_sql.y"
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
#line 2818 "yacc_sql.cpp"
    break;

  case 114:
#line 967 "yacc_sql.y"
    {
      (yyval.expression) = nullptr;
    }
#line 2826 "yacc_sql.cpp"
    break;

  case 115:
#line 970 "yacc_sql.y"
                      {
      (yyval.expression) = (yyvsp[0].expression);  
    }
#line 2834 "yacc_sql.cpp"
    break;

  case 116:
#line 976 "yacc_sql.y"
    {
      (yyval.expression) = new ComparisonExpr((yyvsp[-1].comp), (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 2842 "yacc_sql.cpp"
    break;

  case 117:
#line 980 "yacc_sql.y"
    {
      Value val;
      val.set_null();
      ValueExpr *value_expr = new ValueExpr(val);
      (yyval.expression) = new ComparisonExpr((yyvsp[-1].comp), value_expr, (yyvsp[0].expression));
    }
#line 2853 "yacc_sql.cpp"
    break;

  case 118:
#line 987 "yacc_sql.y"
    {
      Value val;
      val.set_null();
      ValueExpr *value_expr = new ValueExpr(val);
      (yyval.expression) = new ComparisonExpr((yyvsp[0].bools) ? IS_NULL : IS_NOT_NULL, (yyvsp[-2].expression), value_expr);
    }
#line 2864 "yacc_sql.cpp"
    break;

  case 119:
#line 994 "yacc_sql.y"
    {
      (yyval.expression) = new ConjunctionExpr(ConjunctionExpr::Type::AND, (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 2872 "yacc_sql.cpp"
    break;

  case 120:
#line 998 "yacc_sql.y"
    {
      (yyval.expression) = new ConjunctionExpr(ConjunctionExpr::Type::OR, (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 2880 "yacc_sql.cpp"
    break;

  case 121:
#line 1004 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 2886 "yacc_sql.cpp"
    break;

  case 122:
#line 1005 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 2892 "yacc_sql.cpp"
    break;

  case 123:
#line 1006 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 2898 "yacc_sql.cpp"
    break;

  case 124:
#line 1007 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 2904 "yacc_sql.cpp"
    break;

  case 125:
#line 1008 "yacc_sql.y"
            { (yyval.comp) = NOT_EQUAL; }
#line 2910 "yacc_sql.cpp"
    break;

  case 126:
#line 1009 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 2916 "yacc_sql.cpp"
    break;

  case 127:
#line 1010 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 2922 "yacc_sql.cpp"
    break;

  case 128:
#line 1011 "yacc_sql.y"
           { (yyval.comp) = LIKE_OP; }
#line 2928 "yacc_sql.cpp"
    break;

  case 129:
#line 1012 "yacc_sql.y"
               { (yyval.comp) = NOT_LIKE_OP; }
#line 2934 "yacc_sql.cpp"
    break;

  case 130:
#line 1013 "yacc_sql.y"
         { (yyval.comp) = IN_OP; }
#line 2940 "yacc_sql.cpp"
    break;

  case 131:
#line 1014 "yacc_sql.y"
             { (yyval.comp) = NOT_IN_OP; }
#line 2946 "yacc_sql.cpp"
    break;

  case 132:
#line 1018 "yacc_sql.y"
         { (yyval.comp) = EXISTS_OP; }
#line 2952 "yacc_sql.cpp"
    break;

  case 133:
#line 1019 "yacc_sql.y"
               { (yyval.comp) = NOT_EXISTS_OP; }
#line 2958 "yacc_sql.cpp"
    break;

  case 134:
#line 1024 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 2966 "yacc_sql.cpp"
    break;

  case 135:
#line 1028 "yacc_sql.y"
    {
      (yyval.expression_list) = (yyvsp[0].expression_list);
    }
#line 2974 "yacc_sql.cpp"
    break;

  case 136:
#line 1035 "yacc_sql.y"
  {
    (yyval.expression) = nullptr;
  }
#line 2982 "yacc_sql.cpp"
    break;

  case 137:
#line 1039 "yacc_sql.y"
  {
    (yyval.expression) = (yyvsp[0].expression);
  }
#line 2990 "yacc_sql.cpp"
    break;

  case 138:
#line 1046 "yacc_sql.y"
    {
      (yyval.order_by_list) = nullptr;
    }
#line 2998 "yacc_sql.cpp"
    break;

  case 139:
#line 1050 "yacc_sql.y"
    {
      (yyval.order_by_list) = (yyvsp[0].order_by_list);
      std::reverse((yyval.order_by_list)->begin(), (yyval.order_by_list)->end());
    }
#line 3007 "yacc_sql.cpp"
    break;

  case 140:
#line 1058 "yacc_sql.y"
    {
      (yyval.order_by_list) = new std::vector<std::unique_ptr<OrderBySqlNode>>();
      (yyval.order_by_list)->emplace_back((yyvsp[0].order_unit));
    }
#line 3016 "yacc_sql.cpp"
    break;

  case 141:
#line 1063 "yacc_sql.y"
    {
      (yyval.order_by_list) = (yyvsp[0].order_by_list);
      (yyval.order_by_list)->emplace_back((yyvsp[-2].order_unit));
    }
#line 3025 "yacc_sql.cpp"
    break;

  case 142:
#line 1070 "yacc_sql.y"
    {
      (yyval.order_unit) = new OrderBySqlNode;
      RelAttrSqlNode *node = (yyvsp[-1].rel_attr);
      (yyval.order_unit)->unbound_field = std::make_unique<UnboundFieldExpr>(node->relation_name, node->attribute_name);
      (yyval.order_unit)->order_op = (yyvsp[0].order_op);
      delete (yyvsp[-1].rel_attr);
    }
#line 3037 "yacc_sql.cpp"
    break;

  case 143:
#line 1078 "yacc_sql.y"
    {
      (yyval.order_op) = OrderOp::ASC;
    }
#line 3045 "yacc_sql.cpp"
    break;

  case 144:
#line 1082 "yacc_sql.y"
    {
      (yyval.order_op) = OrderOp::ASC;
    }
#line 3053 "yacc_sql.cpp"
    break;

  case 145:
#line 1086 "yacc_sql.y"
    {
      (yyval.order_op) = OrderOp::DESC;
    }
#line 3061 "yacc_sql.cpp"
    break;

  case 146:
#line 1092 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3075 "yacc_sql.cpp"
    break;

  case 147:
#line 1105 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3084 "yacc_sql.cpp"
    break;

  case 148:
#line 1113 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3096 "yacc_sql.cpp"
    break;


#line 3100 "yacc_sql.cpp"

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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

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
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (&yylloc, sql_string, sql_result, scanner, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (&yylloc, sql_string, sql_result, scanner, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, sql_string, sql_result, scanner, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
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
                  yystos[+*yyssp], yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 1125 "yacc_sql.y"

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

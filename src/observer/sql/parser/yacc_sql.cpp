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


#line 147 "yacc_sql.cpp"

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
    TABLE = 265,
    TABLES = 266,
    INDEX = 267,
    CALC = 268,
    SELECT = 269,
    DESC = 270,
    SHOW = 271,
    SYNC = 272,
    INSERT = 273,
    DELETE = 274,
    UPDATE = 275,
    INNER = 276,
    JOIN = 277,
    LBRACE = 278,
    RBRACE = 279,
    COMMA = 280,
    TRX_BEGIN = 281,
    TRX_COMMIT = 282,
    TRX_ROLLBACK = 283,
    INT_T = 284,
    STRING_T = 285,
    FLOAT_T = 286,
    VECTOR_T = 287,
    IS = 288,
    NOT = 289,
    NULL_T = 290,
    DATE_T = 291,
    HELP = 292,
    EXIT = 293,
    DOT = 294,
    INTO = 295,
    VALUES = 296,
    FROM = 297,
    WHERE = 298,
    AND = 299,
    OR = 300,
    SET = 301,
    ON = 302,
    LOAD = 303,
    DATA = 304,
    INFILE = 305,
    EXPLAIN = 306,
    STORAGE = 307,
    FORMAT = 308,
    EQ = 309,
    LT = 310,
    GT = 311,
    LE = 312,
    GE = 313,
    NE = 314,
    LIKE = 315,
    COUNT = 316,
    SUM = 317,
    AVG = 318,
    MAX = 319,
    MIN = 320,
    L2_DISTANCE = 321,
    COSINE_DISTANCE = 322,
    INNER_PRODUCT = 323,
    IN = 324,
    EXISTS = 325,
    VECTORS = 326,
    QUOTE = 327,
    NUMBER = 328,
    FLOAT = 329,
    ID = 330,
    SSS = 331,
    DATE_STR = 332,
    UMINUS = 333
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 162 "yacc_sql.y"

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

#line 303 "yacc_sql.cpp"

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
typedef yytype_uint8 yy_state_t;

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
#define YYFINAL  77
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   280

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  85
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  52
/* YYNRULES -- Number of rules.  */
#define YYNRULES  133
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  252

#define YYUNDEFTOK  2
#define YYMAXUTOK   333


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
       2,     2,    80,    78,     2,    79,     2,    81,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    83,     2,    84,     2,     2,     2,     2,     2,     2,
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
      75,    76,    77,    82
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   255,   255,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   286,   292,   297,   303,   309,   315,   321,
     328,   334,   342,   356,   366,   390,   393,   406,   421,   434,
     438,   442,   448,   451,   452,   453,   454,   455,   458,   475,
     478,   488,   503,   507,   511,   525,   529,   535,   542,   545,
     550,   553,   557,   562,   565,   570,   579,   591,   627,   637,
     646,   651,   664,   667,   673,   680,   683,   686,   689,   692,
     696,   699,   704,   710,   713,   716,   719,   722,   725,   728,
     731,   734,   737,   743,   751,   756,   766,   771,   776,   790,
     793,   806,   816,   819,   824,   828,   835,   839,   846,   847,
     848,   849,   850,   851,   852,   853,   854,   855,   856,   861,
     864,   873,   876,   884,   889,   896,   905,   908,   912,   918,
     931,   939,   949,   950
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SEMICOLON", "BY", "CREATE", "DROP",
  "GROUP", "ORDER", "ASC", "TABLE", "TABLES", "INDEX", "CALC", "SELECT",
  "DESC", "SHOW", "SYNC", "INSERT", "DELETE", "UPDATE", "INNER", "JOIN",
  "LBRACE", "RBRACE", "COMMA", "TRX_BEGIN", "TRX_COMMIT", "TRX_ROLLBACK",
  "INT_T", "STRING_T", "FLOAT_T", "VECTOR_T", "IS", "NOT", "NULL_T",
  "DATE_T", "HELP", "EXIT", "DOT", "INTO", "VALUES", "FROM", "WHERE",
  "AND", "OR", "SET", "ON", "LOAD", "DATA", "INFILE", "EXPLAIN", "STORAGE",
  "FORMAT", "EQ", "LT", "GT", "LE", "GE", "NE", "LIKE", "COUNT", "SUM",
  "AVG", "MAX", "MIN", "L2_DISTANCE", "COSINE_DISTANCE", "INNER_PRODUCT",
  "IN", "EXISTS", "VECTORS", "QUOTE", "NUMBER", "FLOAT", "ID", "SSS",
  "DATE_STR", "'+'", "'-'", "'*'", "'/'", "UMINUS", "'['", "']'",
  "$accept", "commands", "command_wrapper", "exit_stmt", "help_stmt",
  "sync_stmt", "begin_stmt", "commit_stmt", "rollback_stmt",
  "drop_table_stmt", "show_tables_stmt", "desc_table_stmt",
  "create_index_stmt", "drop_index_stmt", "create_table_stmt",
  "attr_def_list", "attr_def", "opt_null", "number", "type", "insert_stmt",
  "value_list", "insert_value", "value", "storage_format", "double_list",
  "float_number", "delete_stmt", "update_stmt", "select_stmt", "calc_stmt",
  "expression_list", "group_by_expression_list", "expression",
  "sub_query_expr", "rel_attr", "relation", "rel_list", "inner_join_list",
  "inner_join_rel", "where", "condition", "comp_op", "group_by",
  "order_by", "order_by_list", "order_unit", "order_op", "load_data_stmt",
  "explain_stmt", "set_variable_stmt", "opt_semicolon", YY_NULLPTR
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
     325,   326,   327,   328,   329,   330,   331,   332,    43,    45,
      42,    47,   333,    91,    93
};
# endif

#define YYPACT_NINF (-230)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     216,    12,    16,    55,    55,   -63,    14,  -230,   -25,   -13,
     -36,  -230,  -230,  -230,  -230,  -230,   -34,     3,   216,    91,
      51,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,
    -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,
    -230,    17,    19,    28,    36,     0,  -230,    89,    92,   114,
     116,   118,   122,   123,   127,  -230,  -230,    56,  -230,  -230,
      55,  -230,   -37,  -230,  -230,    77,  -230,  -230,   100,  -230,
    -230,    39,    95,   117,   110,   121,  -230,  -230,  -230,  -230,
     149,   126,  -230,   129,   155,     6,    55,    55,    55,    55,
      55,    55,    55,    55,   107,  -230,  -230,  -230,   -15,  -230,
      55,    55,    55,    55,    55,   133,   142,   148,   134,   101,
     109,   135,   136,   137,  -230,  -230,   166,    88,   189,   190,
     191,   193,   108,   115,   119,  -230,   -37,  -230,  -230,    -9,
      -9,  -230,  -230,  -230,   194,  -230,   195,    55,  -230,   169,
    -230,   180,     2,   212,   215,  -230,  -230,    55,  -230,  -230,
    -230,  -230,    55,    55,    55,  -230,   133,   -16,   101,   147,
      37,   101,   229,  -230,  -230,  -230,  -230,  -230,   -17,   135,
     217,   165,  -230,    26,    46,    73,  -230,   223,  -230,   239,
     222,    54,   -49,  -230,   192,  -230,  -230,  -230,  -230,  -230,
    -230,    55,    55,    55,   148,   174,   177,   220,  -230,  -230,
     212,   199,   228,  -230,  -230,  -230,   133,   252,   249,    55,
     234,  -230,  -230,  -230,  -230,    20,  -230,   219,  -230,  -230,
    -230,   235,  -230,  -230,   207,  -230,  -230,   214,    55,   261,
    -230,   222,    20,  -230,    54,   218,    55,  -230,   196,  -230,
    -230,   198,    37,     4,  -230,   241,  -230,  -230,  -230,  -230,
     196,  -230
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    25,     0,     0,
       0,    26,    27,    28,    24,    23,     0,     0,     0,     0,
     132,    22,    21,    14,    15,    16,    17,     9,    10,    11,
      12,    13,     8,     5,     7,     6,     4,     3,    18,    19,
      20,     0,     0,     0,     0,     0,    57,     0,     0,     0,
       0,     0,     0,     0,     0,    52,    53,    94,    56,    54,
       0,    92,    60,    81,    69,    70,    91,    82,    68,    31,
      30,     0,     0,     0,     0,     0,   130,     1,   133,     2,
       0,     0,    29,     0,     0,     0,    72,    72,    72,    72,
      72,     0,     0,     0,     0,    80,    63,    64,     0,    61,
       0,     0,     0,     0,     0,     0,     0,   102,     0,     0,
       0,     0,     0,     0,    93,    79,     0,    74,     0,     0,
       0,     0,     0,     0,     0,    95,     0,    55,    71,    75,
      76,    77,    78,    96,    97,    99,     0,     0,    65,     0,
     131,     0,     0,    35,     0,    33,    86,     0,    87,    88,
      90,    89,     0,     0,     0,    62,     0,   102,     0,     0,
     103,     0,     0,    43,    44,    45,    46,    47,    39,     0,
       0,     0,    73,     0,     0,     0,    98,     0,   100,   119,
      49,    39,     0,   108,   109,   110,   111,   113,   114,   115,
     117,     0,     0,     0,   102,     0,     0,     0,    41,    38,
      35,    58,     0,    83,    84,    85,     0,     0,   121,     0,
       0,   105,   116,   118,   112,   104,   106,   107,    66,   129,
      42,     0,    40,    36,     0,    34,    32,     0,     0,     0,
      67,    49,    51,    48,    39,     0,     0,   120,     0,    50,
      37,     0,   101,   126,   122,   123,    59,   127,   128,   125,
       0,   124
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -230,  -230,   250,  -230,  -230,  -230,  -230,  -230,  -230,  -230,
    -230,  -230,  -230,  -230,  -230,    69,   105,  -179,  -230,  -230,
    -230,    44,  -230,  -105,  -230,  -230,   144,  -230,  -230,   231,
    -230,    -4,    72,   -44,  -230,  -229,    71,   124,  -230,  -230,
    -154,  -185,  -230,  -230,  -230,    29,  -230,  -230,  -230,  -230,
    -230,  -230
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,   170,   143,   199,   221,   168,
      33,   210,   231,    63,   225,    98,    99,    34,    35,    36,
      37,    64,   116,    65,    66,    67,   134,   135,   157,   178,
     138,   160,   191,   208,   230,   244,   245,   249,    38,    39,
      40,    79
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      68,    85,   211,   179,   140,   177,   196,   216,   217,   243,
     126,   212,    69,   247,     4,    71,    95,   197,   198,   248,
     213,   243,    41,    45,    42,    70,    43,   137,    44,    72,
     115,   163,   164,   165,   166,    46,    96,    97,   167,    73,
     218,    74,   117,   117,   117,   117,   117,   122,   123,   124,
     203,   242,    75,   180,    78,   240,   194,   129,   130,   131,
     132,    47,    48,    49,    50,    51,    52,    53,    54,   127,
     204,   103,   104,    55,    56,    57,    58,    59,    45,    60,
      61,   192,   193,    62,   101,   102,   103,   104,   197,   198,
      46,    77,    80,   159,    81,    94,   128,   205,   101,   102,
     103,   104,   100,    82,   101,   102,   103,   104,   173,   174,
     175,    83,    86,   147,   106,    87,    47,    48,    49,    50,
      51,    52,    53,    54,   101,   102,   103,   104,    55,    56,
      57,    58,    59,   152,    60,    61,    46,    88,    62,    89,
     153,    90,   105,   172,   154,    91,    92,   215,   159,   159,
      93,   101,   102,   103,   104,   101,   102,   103,   104,   118,
     119,   120,   121,   108,   109,   232,   101,   102,   103,   104,
     107,   110,   111,   112,    55,    56,   113,    58,    59,   114,
     181,   182,   125,   136,    62,   141,   101,   102,   103,   104,
     146,   137,   159,   101,   102,   103,   104,   101,   102,   103,
     104,   183,   184,   185,   186,   187,   188,   189,   133,   139,
     142,   144,   145,   148,   149,   150,   190,   151,   158,   156,
     162,     1,     2,   161,   237,   101,   102,   103,   104,     3,
       4,     5,     6,     7,     8,     9,    10,   169,   171,   195,
     202,   201,    11,    12,    13,   206,   207,   209,   214,   219,
     220,   224,   226,    14,    15,   222,   228,   229,   233,   234,
     235,   236,    16,   192,    17,   238,   250,    18,    76,   223,
     155,    57,   241,   246,   200,   239,    84,   227,     0,   251,
     176
};

static const yytype_int16 yycheck[] =
{
       4,    45,   181,   157,   109,    21,    23,   192,   193,   238,
      25,    60,    75,     9,    14,    40,    60,    34,    35,    15,
      69,   250,    10,    23,    12,    11,    10,    43,    12,    42,
      24,    29,    30,    31,    32,    35,    73,    74,    36,    75,
     194,    75,    86,    87,    88,    89,    90,    91,    92,    93,
      24,   236,    49,   158,     3,   234,   161,   101,   102,   103,
     104,    61,    62,    63,    64,    65,    66,    67,    68,    84,
      24,    80,    81,    73,    74,    75,    76,    77,    23,    79,
      80,    44,    45,    83,    78,    79,    80,    81,    34,    35,
      35,     0,    75,   137,    75,    39,   100,    24,    78,    79,
      80,    81,    25,    75,    78,    79,    80,    81,   152,   153,
     154,    75,    23,    25,    75,    23,    61,    62,    63,    64,
      65,    66,    67,    68,    78,    79,    80,    81,    73,    74,
      75,    76,    77,    25,    79,    80,    35,    23,    83,    23,
      25,    23,    42,   147,    25,    23,    23,   191,   192,   193,
      23,    78,    79,    80,    81,    78,    79,    80,    81,    87,
      88,    89,    90,    46,    54,   209,    78,    79,    80,    81,
      75,    50,    23,    47,    73,    74,    47,    76,    77,    24,
      33,    34,    75,    41,    83,    76,    78,    79,    80,    81,
      24,    43,   236,    78,    79,    80,    81,    78,    79,    80,
      81,    54,    55,    56,    57,    58,    59,    60,    75,    75,
      75,    75,    75,    24,    24,    24,    69,    24,    23,    25,
      40,     5,     6,    54,   228,    78,    79,    80,    81,    13,
      14,    15,    16,    17,    18,    19,    20,    25,    23,    10,
      75,    24,    26,    27,    28,    22,     7,    25,    56,    75,
      73,    52,    24,    37,    38,    35,     4,     8,    24,    24,
      53,    47,    46,    44,    48,     4,    25,    51,    18,   200,
     126,    75,    54,    75,   169,   231,    45,   206,    -1,   250,
     156
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     6,    13,    14,    15,    16,    17,    18,    19,
      20,    26,    27,    28,    37,    38,    46,    48,    51,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   105,   112,   113,   114,   115,   133,   134,
     135,    10,    12,    10,    12,    23,    35,    61,    62,    63,
      64,    65,    66,    67,    68,    73,    74,    75,    76,    77,
      79,    80,    83,   108,   116,   118,   119,   120,   116,    75,
      11,    40,    42,    75,    75,    49,    87,     0,     3,   136,
      75,    75,    75,    75,   114,   118,    23,    23,    23,    23,
      23,    23,    23,    23,    39,   118,    73,    74,   110,   111,
      25,    78,    79,    80,    81,    42,    75,    75,    46,    54,
      50,    23,    47,    47,    24,    24,   117,   118,   117,   117,
     117,   117,   118,   118,   118,    75,    25,    84,   116,   118,
     118,   118,   118,    75,   121,   122,    41,    43,   125,    75,
     108,    76,    75,   101,    75,    75,    24,    25,    24,    24,
      24,    24,    25,    25,    25,   111,    25,   123,    23,   118,
     126,    54,    40,    29,    30,    31,    32,    36,   104,    25,
     100,    23,   116,   118,   118,   118,   122,    21,   124,   125,
     108,    33,    34,    54,    55,    56,    57,    58,    59,    60,
      69,   127,    44,    45,   108,    10,    23,    34,    35,   102,
     101,    24,    75,    24,    24,    24,    22,     7,   128,    25,
     106,   102,    60,    69,    56,   118,   126,   126,   125,    75,
      73,   103,    35,   100,    52,   109,    24,   121,     4,     8,
     129,   107,   118,    24,    24,    53,    47,   116,     4,   106,
     102,    54,   126,   120,   130,   131,    75,     9,    15,   132,
      25,   130
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    85,    86,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   100,   101,   101,   102,
     102,   102,   103,   104,   104,   104,   104,   104,   105,   106,
     106,   107,   108,   108,   108,   108,   108,   108,   109,   109,
     110,   110,   110,   111,   111,   112,   113,   114,   114,   115,
     116,   116,   117,   117,   117,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   119,   120,   120,   121,   122,   122,   123,
     123,   124,   125,   125,   126,   126,   126,   126,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   128,
     128,   129,   129,   130,   130,   131,   132,   132,   132,   133,
     134,   135,   136,   136
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       2,     2,     8,     5,     8,     0,     3,     6,     3,     0,
       2,     1,     1,     1,     1,     1,     1,     1,     8,     0,
       3,     1,     1,     1,     1,     3,     1,     1,     0,     4,
       0,     1,     3,     1,     1,     4,     7,     8,     2,     2,
       1,     3,     0,     3,     1,     3,     3,     3,     3,     3,
       2,     1,     1,     6,     6,     6,     4,     4,     4,     4,
       4,     1,     1,     3,     1,     3,     1,     1,     3,     0,
       2,     5,     0,     2,     3,     3,     3,     3,     1,     1,
       1,     1,     2,     1,     1,     1,     2,     1,     2,     0,
       3,     0,     3,     1,     3,     2,     0,     1,     1,     7,
       2,     4,     0,     1
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
#line 256 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1808 "yacc_sql.cpp"
    break;

  case 23:
#line 286 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1817 "yacc_sql.cpp"
    break;

  case 24:
#line 292 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1825 "yacc_sql.cpp"
    break;

  case 25:
#line 297 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1833 "yacc_sql.cpp"
    break;

  case 26:
#line 303 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1841 "yacc_sql.cpp"
    break;

  case 27:
#line 309 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1849 "yacc_sql.cpp"
    break;

  case 28:
#line 315 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1857 "yacc_sql.cpp"
    break;

  case 29:
#line 321 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1867 "yacc_sql.cpp"
    break;

  case 30:
#line 328 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1875 "yacc_sql.cpp"
    break;

  case 31:
#line 334 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1885 "yacc_sql.cpp"
    break;

  case 32:
#line 343 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.index_name = (yyvsp[-5].string);
      create_index.relation_name = (yyvsp[-3].string);
      create_index.attribute_name = (yyvsp[-1].string);
      free((yyvsp[-5].string));
      free((yyvsp[-3].string));
      free((yyvsp[-1].string));
    }
#line 1900 "yacc_sql.cpp"
    break;

  case 33:
#line 357 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 1912 "yacc_sql.cpp"
    break;

  case 34:
#line 367 "yacc_sql.y"
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
#line 1937 "yacc_sql.cpp"
    break;

  case 35:
#line 390 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 1945 "yacc_sql.cpp"
    break;

  case 36:
#line 394 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 1959 "yacc_sql.cpp"
    break;

  case 37:
#line 407 "yacc_sql.y"
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
#line 1978 "yacc_sql.cpp"
    break;

  case 38:
#line 422 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      // 这块是 4 是因为 char 和 vector 需要用 ()
      (yyval.attr_info)->length = 4 + ((yyvsp[0].bools) == true);
      (yyval.attr_info)->nullable = (yyvsp[0].bools);
      free((yyvsp[-2].string));
    }
#line 1992 "yacc_sql.cpp"
    break;

  case 39:
#line 434 "yacc_sql.y"
    {
      // 根据 primary-null.result 来看，默认是 not null
      (yyval.bools) = false;
    }
#line 2001 "yacc_sql.cpp"
    break;

  case 40:
#line 439 "yacc_sql.y"
    {
      (yyval.bools) = false;
    }
#line 2009 "yacc_sql.cpp"
    break;

  case 41:
#line 443 "yacc_sql.y"
    {
      (yyval.bools) = true;
    }
#line 2017 "yacc_sql.cpp"
    break;

  case 42:
#line 448 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2023 "yacc_sql.cpp"
    break;

  case 43:
#line 451 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::INTS); }
#line 2029 "yacc_sql.cpp"
    break;

  case 44:
#line 452 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::CHARS); }
#line 2035 "yacc_sql.cpp"
    break;

  case 45:
#line 453 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::FLOATS); }
#line 2041 "yacc_sql.cpp"
    break;

  case 46:
#line 454 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::VECTORS); }
#line 2047 "yacc_sql.cpp"
    break;

  case 47:
#line 455 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::DATES); }
#line 2053 "yacc_sql.cpp"
    break;

  case 48:
#line 459 "yacc_sql.y"
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
#line 2070 "yacc_sql.cpp"
    break;

  case 49:
#line 475 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2078 "yacc_sql.cpp"
    break;

  case 50:
#line 478 "yacc_sql.y"
                                     { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2092 "yacc_sql.cpp"
    break;

  case 51:
#line 489 "yacc_sql.y"
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
#line 2108 "yacc_sql.cpp"
    break;

  case 52:
#line 503 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2117 "yacc_sql.cpp"
    break;

  case 53:
#line 507 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2126 "yacc_sql.cpp"
    break;

  case 54:
#line 511 "yacc_sql.y"
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
#line 2145 "yacc_sql.cpp"
    break;

  case 55:
#line 526 "yacc_sql.y"
    {
      (yyval.value) = vec2val(sql_string, &(yyloc));
    }
#line 2153 "yacc_sql.cpp"
    break;

  case 56:
#line 529 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2164 "yacc_sql.cpp"
    break;

  case 57:
#line 535 "yacc_sql.y"
             {
      (yyval.value) = new Value();
      (yyval.value)->set_null();
    }
#line 2173 "yacc_sql.cpp"
    break;

  case 58:
#line 542 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2181 "yacc_sql.cpp"
    break;

  case 59:
#line 546 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2189 "yacc_sql.cpp"
    break;

  case 60:
#line 550 "yacc_sql.y"
             {
      (yyval.double_list) = new std::vector<double>();
    }
#line 2197 "yacc_sql.cpp"
    break;

  case 61:
#line 553 "yacc_sql.y"
                   {
      (yyval.double_list) = new std::vector<double>();
      (yyval.double_list)->emplace_back((yyvsp[0].float_number));
    }
#line 2206 "yacc_sql.cpp"
    break;

  case 62:
#line 557 "yacc_sql.y"
                                     {
      (yyval.double_list) = (yyvsp[-2].double_list);
      (yyval.double_list)->emplace_back((yyvsp[0].float_number));
    }
#line 2215 "yacc_sql.cpp"
    break;

  case 63:
#line 562 "yacc_sql.y"
                     {
      (yyval.float_number) = (yyvsp[0].number);
    }
#line 2223 "yacc_sql.cpp"
    break;

  case 64:
#line 565 "yacc_sql.y"
            {
      (yyval.float_number) = (yyvsp[0].floats);
    }
#line 2231 "yacc_sql.cpp"
    break;

  case 65:
#line 571 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      (yyval.sql_node)->deletion.conditions = (yyvsp[0].expression);
      free((yyvsp[-1].string));
    }
#line 2242 "yacc_sql.cpp"
    break;

  case 66:
#line 580 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_UPDATE);
      (yyval.sql_node)->update.relation_name = (yyvsp[-5].string);
      (yyval.sql_node)->update.attribute_name = (yyvsp[-3].string);
      (yyval.sql_node)->update.value = *(yyvsp[-1].value);
      (yyval.sql_node)->update.conditions = (yyvsp[0].expression);
      free((yyvsp[-5].string));
      free((yyvsp[-3].string));
    }
#line 2256 "yacc_sql.cpp"
    break;

  case 67:
#line 592 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-6].expression_list) != nullptr) {
        (yyval.sql_node)->selection.expressions.swap(*(yyvsp[-6].expression_list));
        delete (yyvsp[-6].expression_list);
      }

      if ((yyvsp[-4].relation_list) != nullptr) {
        if((yyvsp[-3].inner_join) != nullptr && (yyvsp[-4].relation_list)->size() != 1){
          yyerror(&(yyloc),sql_string,sql_result,scanner,"inner join only support one table",true);
          delete (yyvsp[-4].relation_list);
          YYERROR;
        }
        (yyval.sql_node)->selection.relations.swap(*(yyvsp[-4].relation_list));
        delete (yyvsp[-4].relation_list);
      }

      if((yyvsp[-3].inner_join) != nullptr){
        (yyval.sql_node)->selection.inner_join.reset((yyvsp[-3].inner_join));
      }

      if ((yyvsp[-2].expression) != nullptr) {
        (yyval.sql_node)->selection.conditions.reset((yyvsp[-2].expression));
      }

      if ((yyvsp[-1].expression_list) != nullptr) {
        (yyval.sql_node)->selection.group_by.swap(*(yyvsp[-1].expression_list));
        delete (yyvsp[-1].expression_list);
      }

      if((yyvsp[0].order_by_list) != nullptr){
        (yyval.sql_node)->selection.order_by.swap(*(yyvsp[0].order_by_list));
        delete (yyvsp[0].order_by_list);
      }
    }
#line 2296 "yacc_sql.cpp"
    break;

  case 68:
#line 628 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2307 "yacc_sql.cpp"
    break;

  case 69:
#line 638 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2317 "yacc_sql.cpp"
    break;

  case 70:
#line 647 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2326 "yacc_sql.cpp"
    break;

  case 71:
#line 652 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->emplace((yyval.expression_list)->begin(), (yyvsp[-2].expression));
    }
#line 2339 "yacc_sql.cpp"
    break;

  case 72:
#line 664 "yacc_sql.y"
  {
    (yyval.expression) = nullptr;
  }
#line 2347 "yacc_sql.cpp"
    break;

  case 73:
#line 668 "yacc_sql.y"
  {
    (yyval.expression) = nullptr;
    delete (yyvsp[-2].expression);
    delete (yyvsp[0].expression_list);
  }
#line 2357 "yacc_sql.cpp"
    break;

  case 74:
#line 674 "yacc_sql.y"
  {
    (yyval.expression) = (yyvsp[0].expression);
  }
#line 2365 "yacc_sql.cpp"
    break;

  case 75:
#line 680 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2373 "yacc_sql.cpp"
    break;

  case 76:
#line 683 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2381 "yacc_sql.cpp"
    break;

  case 77:
#line 686 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2389 "yacc_sql.cpp"
    break;

  case 78:
#line 689 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2397 "yacc_sql.cpp"
    break;

  case 79:
#line 692 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2406 "yacc_sql.cpp"
    break;

  case 80:
#line 696 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2414 "yacc_sql.cpp"
    break;

  case 81:
#line 699 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2424 "yacc_sql.cpp"
    break;

  case 82:
#line 704 "yacc_sql.y"
               {
      RelAttrSqlNode *node = (yyvsp[0].rel_attr);
      (yyval.expression) = new UnboundFieldExpr(node->relation_name, node->attribute_name);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].rel_attr);
    }
#line 2435 "yacc_sql.cpp"
    break;

  case 83:
#line 710 "yacc_sql.y"
                                                            {
      (yyval.expression) = create_function_expression(FunctionExpr::Type::L2_DISTANCE, sql_string, (yyvsp[-3].expression), (yyvsp[-1].expression), &(yyloc));
    }
#line 2443 "yacc_sql.cpp"
    break;

  case 84:
#line 713 "yacc_sql.y"
                                                                {
      (yyval.expression) = create_function_expression(FunctionExpr::Type::COSINE_DISTANCE, sql_string, (yyvsp[-3].expression), (yyvsp[-1].expression), &(yyloc));
    }
#line 2451 "yacc_sql.cpp"
    break;

  case 85:
#line 716 "yacc_sql.y"
                                                              {
      (yyval.expression) = create_function_expression(FunctionExpr::Type::INNER_PRODUCT, sql_string, (yyvsp[-3].expression), (yyvsp[-1].expression), &(yyloc));
    }
#line 2459 "yacc_sql.cpp"
    break;

  case 86:
#line 719 "yacc_sql.y"
                                                   {
      (yyval.expression) = create_aggregate_expression("count", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2467 "yacc_sql.cpp"
    break;

  case 87:
#line 722 "yacc_sql.y"
                                                 {
      (yyval.expression) = create_aggregate_expression("sum", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2475 "yacc_sql.cpp"
    break;

  case 88:
#line 725 "yacc_sql.y"
                                                 {
      (yyval.expression) = create_aggregate_expression("avg", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2483 "yacc_sql.cpp"
    break;

  case 89:
#line 728 "yacc_sql.y"
                                                 {
      (yyval.expression) = create_aggregate_expression("min", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2491 "yacc_sql.cpp"
    break;

  case 90:
#line 731 "yacc_sql.y"
                                                 {
      (yyval.expression) = create_aggregate_expression("max", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2499 "yacc_sql.cpp"
    break;

  case 91:
#line 734 "yacc_sql.y"
                     {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 2507 "yacc_sql.cpp"
    break;

  case 92:
#line 737 "yacc_sql.y"
          {
      (yyval.expression) = new StarExpr();
    }
#line 2515 "yacc_sql.cpp"
    break;

  case 93:
#line 744 "yacc_sql.y"
    {
      (yyval.expression) = new SubQueryExpr(std::move((yyvsp[-1].sql_node)->selection));
      delete (yyvsp[-1].sql_node);
    }
#line 2524 "yacc_sql.cpp"
    break;

  case 94:
#line 751 "yacc_sql.y"
       {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2534 "yacc_sql.cpp"
    break;

  case 95:
#line 756 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2546 "yacc_sql.cpp"
    break;

  case 96:
#line 766 "yacc_sql.y"
       {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2554 "yacc_sql.cpp"
    break;

  case 97:
#line 771 "yacc_sql.y"
             {
      (yyval.relation_list) = new std::vector<std::string>();
      (yyval.relation_list)->push_back((yyvsp[0].string));
      free((yyvsp[0].string));
    }
#line 2564 "yacc_sql.cpp"
    break;

  case 98:
#line 776 "yacc_sql.y"
                              {
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new std::vector<std::string>;
      }

      (yyval.relation_list)->insert((yyval.relation_list)->begin(), (yyvsp[-2].string));
      free((yyvsp[-2].string));
    }
#line 2579 "yacc_sql.cpp"
    break;

  case 99:
#line 790 "yacc_sql.y"
    {
      (yyval.inner_join) = nullptr;
    }
#line 2587 "yacc_sql.cpp"
    break;

  case 100:
#line 794 "yacc_sql.y"
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
#line 2602 "yacc_sql.cpp"
    break;

  case 101:
#line 806 "yacc_sql.y"
                                    {
      (yyval.inner_join_unit) = new InnerJoinUnit((yyvsp[-2].string)); 
      (yyval.inner_join_unit)->condition.reset((yyvsp[0].expression)); 
      free((yyvsp[-2].string));
    }
#line 2612 "yacc_sql.cpp"
    break;

  case 102:
#line 816 "yacc_sql.y"
    {
      (yyval.expression) = nullptr;
    }
#line 2620 "yacc_sql.cpp"
    break;

  case 103:
#line 819 "yacc_sql.y"
                      {
      (yyval.expression) = (yyvsp[0].expression);  
    }
#line 2628 "yacc_sql.cpp"
    break;

  case 104:
#line 825 "yacc_sql.y"
    {
      (yyval.expression) = new ComparisonExpr((yyvsp[-1].comp), (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 2636 "yacc_sql.cpp"
    break;

  case 105:
#line 829 "yacc_sql.y"
    {
      Value val;
      val.set_null();
      ValueExpr *value_expr = new ValueExpr(val);
      (yyval.expression) = new ComparisonExpr((yyvsp[0].bools) ? IS_NULL : IS_NOT_NULL, (yyvsp[-2].expression), value_expr);
    }
#line 2647 "yacc_sql.cpp"
    break;

  case 106:
#line 836 "yacc_sql.y"
    {
      (yyval.expression) = new ConjunctionExpr(ConjunctionExpr::Type::AND, (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 2655 "yacc_sql.cpp"
    break;

  case 107:
#line 840 "yacc_sql.y"
    {
      (yyval.expression) = new ConjunctionExpr(ConjunctionExpr::Type::OR, (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 2663 "yacc_sql.cpp"
    break;

  case 108:
#line 846 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 2669 "yacc_sql.cpp"
    break;

  case 109:
#line 847 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 2675 "yacc_sql.cpp"
    break;

  case 110:
#line 848 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 2681 "yacc_sql.cpp"
    break;

  case 111:
#line 849 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 2687 "yacc_sql.cpp"
    break;

  case 112:
#line 850 "yacc_sql.y"
            { (yyval.comp) = NOT_EQUAL; }
#line 2693 "yacc_sql.cpp"
    break;

  case 113:
#line 851 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 2699 "yacc_sql.cpp"
    break;

  case 114:
#line 852 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 2705 "yacc_sql.cpp"
    break;

  case 115:
#line 853 "yacc_sql.y"
           { (yyval.comp) = LIKE_OP; }
#line 2711 "yacc_sql.cpp"
    break;

  case 116:
#line 854 "yacc_sql.y"
               { (yyval.comp) = NOT_LIKE_OP; }
#line 2717 "yacc_sql.cpp"
    break;

  case 117:
#line 855 "yacc_sql.y"
         { (yyval.comp) = IN_OP; }
#line 2723 "yacc_sql.cpp"
    break;

  case 118:
#line 856 "yacc_sql.y"
             { (yyval.comp) = NOT_IN_OP; }
#line 2729 "yacc_sql.cpp"
    break;

  case 119:
#line 861 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 2737 "yacc_sql.cpp"
    break;

  case 120:
#line 865 "yacc_sql.y"
    {
      (yyval.expression_list) = (yyvsp[0].expression_list);
    }
#line 2745 "yacc_sql.cpp"
    break;

  case 121:
#line 873 "yacc_sql.y"
    {
      (yyval.order_by_list) = nullptr;
    }
#line 2753 "yacc_sql.cpp"
    break;

  case 122:
#line 877 "yacc_sql.y"
    {
      (yyval.order_by_list) = (yyvsp[0].order_by_list);
      std::reverse((yyval.order_by_list)->begin(), (yyval.order_by_list)->end());
    }
#line 2762 "yacc_sql.cpp"
    break;

  case 123:
#line 885 "yacc_sql.y"
    {
      (yyval.order_by_list) = new std::vector<std::unique_ptr<OrderBySqlNode>>();
      (yyval.order_by_list)->emplace_back((yyvsp[0].order_unit));
    }
#line 2771 "yacc_sql.cpp"
    break;

  case 124:
#line 890 "yacc_sql.y"
    {
      (yyval.order_by_list) = (yyvsp[0].order_by_list);
      (yyval.order_by_list)->emplace_back((yyvsp[-2].order_unit));
    }
#line 2780 "yacc_sql.cpp"
    break;

  case 125:
#line 897 "yacc_sql.y"
    {
      (yyval.order_unit) = new OrderBySqlNode;
      RelAttrSqlNode *node = (yyvsp[-1].rel_attr);
      (yyval.order_unit)->unbound_field = std::make_unique<UnboundFieldExpr>(node->relation_name, node->attribute_name);
      (yyval.order_unit)->order_op = (yyvsp[0].order_op);
      delete (yyvsp[-1].rel_attr);
    }
#line 2792 "yacc_sql.cpp"
    break;

  case 126:
#line 905 "yacc_sql.y"
    {
      (yyval.order_op) = OrderOp::ASC;
    }
#line 2800 "yacc_sql.cpp"
    break;

  case 127:
#line 909 "yacc_sql.y"
    {
      (yyval.order_op) = OrderOp::ASC;
    }
#line 2808 "yacc_sql.cpp"
    break;

  case 128:
#line 913 "yacc_sql.y"
    {
      (yyval.order_op) = OrderOp::DESC;
    }
#line 2816 "yacc_sql.cpp"
    break;

  case 129:
#line 919 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 2830 "yacc_sql.cpp"
    break;

  case 130:
#line 932 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 2839 "yacc_sql.cpp"
    break;

  case 131:
#line 940 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 2851 "yacc_sql.cpp"
    break;


#line 2855 "yacc_sql.cpp"

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
#line 952 "yacc_sql.y"

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

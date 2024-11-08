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

#line 320 "yacc_sql.cpp"

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
#define YYFINAL  85
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   377

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  97
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  67
/* YYNRULES -- Number of rules.  */
#define YYNRULES  170
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  343

#define YYUNDEFTOK  2
#define YYMAXUTOK   345


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
    1269,  1277,  1285,  1288,  1292,  1299,  1312,  1320,  1328,  1338,
    1339
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SEMICOLON", "BY", "CREATE", "DROP",
  "GROUP", "ORDER", "ASC", "HAVING", "TABLE", "TABLES", "VIEW", "INDEX",
  "CALC", "SELECT", "DESC", "SHOW", "SYNC", "INSERT", "DELETE", "UPDATE",
  "INNER", "JOIN", "LBRACE", "RBRACE", "COMMA", "TRX_BEGIN", "TRX_COMMIT",
  "TRX_ROLLBACK", "INT_T", "STRING_T", "FLOAT_T", "VECTOR_T", "WITH_T",
  "DISTANCE_T", "TYPE_T", "IVFFLAT_T", "LISTS_T", "PROBES_T", "TEXT_T",
  "IS", "NOT", "NULL_T", "DATE_T", "HELP", "EXIT", "DOT", "INTO", "VALUES",
  "FROM", "WHERE", "AND", "OR", "SET", "ON", "AS", "LOAD", "DATA",
  "INFILE", "EXPLAIN", "STORAGE", "FORMAT", "EQ", "LT", "GT", "LE", "GE",
  "NE", "LIKE", "COUNT", "SUM", "AVG", "MAX", "MIN", "L2_DISTANCE",
  "COSINE_DISTANCE", "INNER_PRODUCT", "IN", "EXISTS", "VECTORS", "QUOTE",
  "UNIQUE", "LIMIT", "NUMBER", "FLOAT", "ID", "SSS", "DATE_STR", "'+'",
  "'-'", "'*'", "'/'", "UMINUS", "'['", "']'", "$accept", "commands",
  "command_wrapper", "exit_stmt", "help_stmt", "sync_stmt", "begin_stmt",
  "commit_stmt", "rollback_stmt", "create_table_stmt", "drop_table_stmt",
  "show_tables_stmt", "desc_table_stmt", "create_view_stmt",
  "drop_view_stmt", "create_index_stmt", "vector_index_with", "opt_unique",
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
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
      43,    45,    42,    47,   345,    91,    93
};
# endif

#define YYPACT_NINF (-289)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     249,    -2,   209,   153,   153,   -64,    14,  -289,    62,    64,
      37,  -289,  -289,  -289,  -289,  -289,    85,    58,   249,   149,
     174,  -289,  -289,  -289,  -289,  -289,  -289,  -289,  -289,  -289,
    -289,  -289,  -289,  -289,  -289,  -289,  -289,  -289,  -289,  -289,
    -289,  -289,  -289,   124,   125,   165,  -289,   190,   134,   145,
     146,    -3,  -289,   210,   211,   218,   221,   222,  -289,  -289,
    -289,  -289,  -289,   186,  -289,  -289,   153,  -289,    19,  -289,
    -289,    10,   224,  -289,  -289,  -289,   199,  -289,  -289,   164,
     170,   -42,   -57,   192,  -289,  -289,  -289,  -289,   109,   231,
     171,   172,  -289,  -289,   204,   235,   246,   153,   153,   153,
     153,   153,    26,  -289,  -289,  -289,   -17,  -289,   187,  -289,
     153,   153,   153,   153,   248,   153,   189,    87,   -42,   225,
     -30,  -289,   185,   194,   266,  -289,  -289,   196,   227,   229,
     230,   200,  -289,  -289,   262,    10,   263,   264,   265,   267,
    -289,  -289,    19,  -289,  -289,    46,    46,  -289,  -289,   153,
      30,  -289,   -42,  -289,   205,   269,   245,   212,  -289,   251,
     169,   271,  -289,   274,   266,   215,   216,  -289,  -289,   278,
    -289,  -289,  -289,  -289,  -289,  -289,   153,   279,   113,   281,
     -30,    55,  -289,   247,   -19,   298,  -289,  -289,  -289,  -289,
    -289,  -289,   132,   194,   286,   226,   288,  -289,   290,   291,
     153,     3,   189,   293,  -289,   311,   205,   294,   292,   241,
    -289,   116,   110,   153,   153,   236,  -289,   237,   240,   282,
    -289,  -289,   271,   260,   274,  -289,   242,   243,  -289,  -289,
    -289,   189,   323,   318,   281,   283,   153,   305,  -289,   155,
     -54,  -289,   268,  -289,  -289,  -289,  -289,  -289,  -289,   153,
      55,    55,   101,   101,   272,  -289,  -289,   306,  -289,  -289,
     275,   -11,  -289,   274,   274,   -42,   153,    55,   327,  -289,
     312,   292,   101,  -289,  -289,  -289,  -289,  -289,   101,  -289,
     287,   153,   155,   277,  -289,   313,   316,   289,  -289,   110,
     339,   270,   -30,  -289,   101,  -289,   257,   314,  -289,    55,
      84,   240,  -289,   292,  -289,   321,  -289,   110,   322,    11,
    -289,   324,  -289,   326,   319,   153,  -289,  -289,  -289,    84,
    -289,   284,    63,  -289,   315,   153,   328,    16,   325,    11,
     295,  -289,    92,   330,   329,   296,   240,   331,   310,   299,
     240,   336,  -289
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    42,     0,     0,     0,     0,     0,    27,     0,     0,
       0,    28,    29,    30,    26,    25,     0,     0,     0,     0,
     169,    24,    23,    16,    17,    18,    19,     8,     9,    10,
      11,    12,    13,    14,    15,     5,     7,     6,     4,     3,
      20,    21,    22,     0,     0,     0,    43,     0,     0,     0,
       0,     0,    76,     0,     0,     0,     0,     0,   110,   111,
     112,    71,    72,   119,    75,    73,     0,   109,    79,   104,
      92,    53,     0,   107,   108,   105,    91,    36,    35,     0,
       0,    53,     0,     0,   166,     1,   170,     2,     0,    44,
       0,     0,    34,    38,     0,     0,     0,    95,    95,    95,
      95,    95,     0,   103,    82,    83,     0,    80,     0,    54,
       0,     0,     0,     0,    93,     0,     0,     0,    53,     0,
       0,   168,     0,     0,     0,    32,    89,     0,     0,     0,
       0,     0,   118,   102,     0,    53,     0,     0,     0,     0,
     120,   121,     0,    74,    55,    98,    99,   100,   101,     0,
       0,   124,    53,   127,     0,     0,   130,     0,   167,     0,
       0,    49,    88,    46,     0,     0,     0,    48,   113,    96,
     114,   115,   117,   116,    81,    94,     0,   125,   130,   122,
       0,     0,    84,     0,   130,     0,    60,    61,    62,    63,
      64,    65,    56,     0,     0,     0,     0,    37,     0,     0,
       0,     0,     0,     0,   128,   150,     0,     0,    68,     0,
     148,     0,   131,     0,     0,     0,    85,     0,     0,     0,
      58,    52,    49,    77,    46,    45,     0,     0,    97,   106,
     126,     0,     0,   152,   122,     0,     0,     0,   149,    56,
       0,   137,   138,   139,   140,   142,   143,   144,   146,     0,
       0,     0,   133,    86,     0,   165,    59,     0,    57,    50,
       0,    31,    47,    46,    46,    53,     0,     0,   154,   123,
       0,    68,    70,    66,   134,   145,   147,   141,   132,   135,
     136,     0,    56,     0,    33,     0,     0,     0,   151,   153,
       0,   156,     0,    69,    87,    51,     0,     0,    39,     0,
       0,     0,    90,    68,    78,     0,    40,   129,     0,   162,
     155,   158,   157,     0,     0,     0,   163,   164,   160,     0,
      67,     0,     0,   159,     0,     0,     0,     0,     0,   162,
       0,   161,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    41
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -289,  -289,   346,  -289,  -289,  -289,  -289,  -289,  -289,  -289,
    -289,  -289,  -289,  -289,  -289,  -289,  -289,  -289,  -289,  -200,
    -289,   143,   173,   -75,  -220,  -249,  -289,  -289,  -193,  -289,
    -119,  -289,  -289,   228,  -289,  -289,  -289,   106,   -48,  -289,
      -4,   117,   -62,  -288,  -289,  -289,  -152,   135,   140,   175,
    -289,  -289,  -157,  -233,  -289,  -289,  -289,  -289,  -289,  -289,
      53,  -289,    44,  -289,  -289,  -289,  -289
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,   306,    47,   128,   196,
      34,   194,   161,   114,   221,   257,   192,    35,   237,   271,
      69,   261,   106,   107,    36,    37,   184,   125,    38,    39,
      70,   134,    71,    72,    73,    74,    75,   207,   152,   153,
     178,   204,   182,   212,   249,   213,   233,   268,   291,   302,
     310,   311,   318,    40,    41,    42,    87
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      76,   158,   179,    95,   103,     4,   119,   120,   215,    43,
     142,    44,   308,     4,    52,   108,   275,   279,   280,   274,
     316,   205,    51,    77,   262,   276,    78,   216,   317,   229,
     121,   308,    45,   181,   289,   135,   135,   135,   135,   135,
     126,    52,   329,   156,   333,   109,   124,    96,   145,   146,
     147,   148,   312,   150,   234,    61,    62,   176,    64,    65,
     169,   208,   295,   285,   286,    68,   307,   108,    53,    54,
      55,    56,    57,    58,    59,    60,   162,   177,   293,   143,
      51,    46,    61,    62,    63,    64,    65,   337,    66,    67,
     325,   341,    68,   110,   111,   112,   113,   109,   209,    52,
     110,   111,   112,   113,   104,   105,   110,   111,   112,   113,
     313,    79,   154,   140,   201,    80,   197,    83,   141,   211,
     110,   111,   112,   113,    81,     4,    53,    54,    55,    56,
      57,    58,    59,    60,   123,   210,   203,   155,   112,   113,
      61,    62,    63,    64,    65,   175,    66,    67,   309,    85,
      68,   252,   253,   110,   111,   112,   113,   218,   239,   240,
      58,    59,    60,   250,   251,   181,   124,   309,    58,    59,
      60,    63,    82,   303,   272,   219,   220,    86,    51,    90,
     241,   242,   243,   244,   245,   246,   247,   278,   211,   211,
     287,   110,   111,   112,   113,   248,   228,    52,   219,   220,
     186,   187,   188,   189,    91,   211,   110,   111,   112,   113,
     190,    88,    89,   126,   191,   136,   137,   138,   139,   294,
      48,    92,    49,    50,    53,    54,    55,    56,    57,    58,
      59,    60,    93,    94,   102,    97,    98,   211,    61,    62,
      63,    64,    65,    99,    66,    67,   100,   101,    68,   115,
     116,   117,   122,   322,     1,     2,   127,   118,   129,   130,
     131,   132,   288,   327,     3,     4,     5,     6,     7,     8,
       9,    10,   133,   159,   144,   149,   151,    11,    12,    13,
     157,   160,     4,   163,   164,   165,   166,   167,   168,   170,
     171,   172,    63,   173,   180,    14,    15,   181,   193,   183,
     185,   195,   198,   199,    16,   200,   202,    17,   206,   217,
      18,   214,   223,   224,   225,   226,   227,   231,   232,   236,
     235,   238,   260,   254,   255,   256,   258,   266,   267,   263,
     264,   273,   282,   270,   277,   290,   281,   292,   283,   297,
     250,   296,   298,   300,   304,   299,   314,   315,   324,   305,
     339,   319,   320,   326,   301,   328,   321,   334,   338,   332,
     336,   330,   342,   340,    84,   259,   222,   284,   335,   269,
     174,   265,   323,   331,     0,     0,     0,   230
};

static const yytype_int16 yycheck[] =
{
       4,   120,   154,    51,    66,    16,    81,    64,    27,    11,
      27,    13,   300,    16,    44,    57,    70,   250,   251,   239,
       9,   178,    25,    87,   224,    79,    12,   184,    17,    26,
      87,   319,    34,    52,   267,    97,    98,    99,   100,   101,
      88,    44,    26,   118,   332,    87,    57,    51,   110,   111,
     112,   113,   301,   115,   206,    85,    86,    27,    88,    89,
     135,   180,   282,   263,   264,    95,   299,    57,    71,    72,
      73,    74,    75,    76,    77,    78,   124,   152,   271,    96,
      25,    83,    85,    86,    87,    88,    89,   336,    91,    92,
      27,   340,    95,    90,    91,    92,    93,    87,    43,    44,
      90,    91,    92,    93,    85,    86,    90,    91,    92,    93,
     303,    49,    25,    87,   176,    51,   164,    59,    92,   181,
      90,    91,    92,    93,    87,    16,    71,    72,    73,    74,
      75,    76,    77,    78,    25,    80,    23,    50,    92,    93,
      85,    86,    87,    88,    89,   149,    91,    92,   300,     0,
      95,   213,   214,    90,    91,    92,    93,    25,    42,    43,
      76,    77,    78,    53,    54,    52,    57,   319,    76,    77,
      78,    87,    87,   292,   236,    43,    44,     3,    25,    14,
      64,    65,    66,    67,    68,    69,    70,   249,   250,   251,
     265,    90,    91,    92,    93,    79,   200,    44,    43,    44,
      31,    32,    33,    34,    14,   267,    90,    91,    92,    93,
      41,    87,    87,   261,    45,    98,    99,   100,   101,   281,
      11,    87,    13,    14,    71,    72,    73,    74,    75,    76,
      77,    78,    87,    87,    48,    25,    25,   299,    85,    86,
      87,    88,    89,    25,    91,    92,    25,    25,    95,    25,
      51,    87,    60,   315,     5,     6,    25,    87,    87,    87,
      56,    26,   266,   325,    15,    16,    17,    18,    19,    20,
      21,    22,    26,    88,    87,    27,    87,    28,    29,    30,
      55,    87,    16,    87,    57,    56,    56,    87,    26,    26,
      26,    26,    87,    26,    25,    46,    47,    52,    27,    87,
      49,    27,    87,    87,    55,    27,    27,    58,    27,    11,
      61,    64,    26,    87,    26,    25,    25,    24,     7,    27,
      26,    80,    62,    87,    87,    85,    44,     4,    10,    87,
      87,    26,    26,    50,    66,     8,    64,    25,    63,    26,
      53,    64,    26,     4,    87,    56,    25,    25,    64,    35,
      40,    27,    26,    38,    84,    27,    37,    27,    27,    64,
      64,    36,    26,    64,    18,   222,   193,   261,    39,   234,
     142,   231,   319,   329,    -1,    -1,    -1,   202
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
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
      64,    87,    60,    25,    57,   134,   135,    25,   115,    87,
      87,    56,    26,    26,   138,   139,   138,   138,   138,   138,
      87,    92,    27,    96,    87,   139,   139,   139,   139,    27,
     139,    87,   145,   146,    25,    50,   120,    55,   127,    88,
      87,   119,   135,    87,    57,    56,    56,    87,    26,   120,
      26,    26,    26,    26,   130,   137,    27,   120,   147,   143,
      25,    52,   149,    87,   133,    49,    31,    32,    33,    34,
      41,    45,   123,    27,   118,    27,   116,   135,    87,    87,
      27,   139,    27,    23,   148,   149,    27,   144,   127,    43,
      80,   139,   150,   152,    64,    27,   149,    11,    25,    43,
      44,   121,   119,    26,    87,    26,    25,    25,   137,    26,
     146,    24,     7,   153,   143,    26,    27,   125,    80,    42,
      43,    64,    65,    66,    67,    68,    69,    70,    79,   151,
      53,    54,   139,   139,    87,    87,    85,   122,    44,   118,
      62,   128,   116,    87,    87,   145,     4,    10,   154,   144,
      50,   126,   139,    26,   121,    70,    79,    66,   139,   150,
     150,    64,    26,    63,   134,   116,   116,   120,   137,   150,
       8,   155,    25,   125,   139,   121,    64,    26,    26,    56,
       4,    84,   156,   127,    87,    35,   113,   150,   140,   143,
     157,   158,   122,   125,    25,    25,     9,    17,   159,    27,
      26,    37,   139,   157,    64,    27,    38,   139,    27,    26,
      36,   159,    64,   140,    27,    39,    64,   122,    27,    40,
      64,   122,    26
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
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
     158,   158,   159,   159,   159,   160,   161,   162,   162,   163,
     163
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
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
       2,     7,     0,     1,     1,     7,     2,     4,     3,     0,
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
#line 288 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1892 "yacc_sql.cpp"
    break;

  case 25:
#line 320 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1901 "yacc_sql.cpp"
    break;

  case 26:
#line 326 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1909 "yacc_sql.cpp"
    break;

  case 27:
#line 331 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1917 "yacc_sql.cpp"
    break;

  case 28:
#line 337 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1925 "yacc_sql.cpp"
    break;

  case 29:
#line 343 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1933 "yacc_sql.cpp"
    break;

  case 30:
#line 349 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1941 "yacc_sql.cpp"
    break;

  case 31:
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
#line 1966 "yacc_sql.cpp"
    break;

  case 32:
#line 377 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-1].string);
      free((yyvsp[-1].string));
      create_table.select_sql_node.reset((yyvsp[0].sql_node));
    }
#line 1978 "yacc_sql.cpp"
    break;

  case 33:
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
#line 2004 "yacc_sql.cpp"
    break;

  case 34:
#line 409 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2014 "yacc_sql.cpp"
    break;

  case 35:
#line 416 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 2022 "yacc_sql.cpp"
    break;

  case 36:
#line 422 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2032 "yacc_sql.cpp"
    break;

  case 37:
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
#line 2054 "yacc_sql.cpp"
    break;

  case 38:
#line 452 "yacc_sql.y"
                 {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_VIEW);
      (yyval.sql_node)->drop_view.view_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2064 "yacc_sql.cpp"
    break;

  case 39:
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
#line 2083 "yacc_sql.cpp"
    break;

  case 40:
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
#line 2106 "yacc_sql.cpp"
    break;

  case 41:
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
#line 2121 "yacc_sql.cpp"
    break;

  case 42:
#line 512 "yacc_sql.y"
    {
      (yyval.bools) = false;
    }
#line 2129 "yacc_sql.cpp"
    break;

  case 43:
#line 516 "yacc_sql.y"
    {
      (yyval.bools) = true;
    }
#line 2137 "yacc_sql.cpp"
    break;

  case 44:
#line 522 "yacc_sql.y"
    {
      (yyval.id_list) = nullptr;
    }
#line 2145 "yacc_sql.cpp"
    break;

  case 45:
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
#line 2160 "yacc_sql.cpp"
    break;

  case 46:
#line 537 "yacc_sql.y"
    {
      (yyval.relation_list) = new std::vector<std::string>;
    }
#line 2168 "yacc_sql.cpp"
    break;

  case 47:
#line 541 "yacc_sql.y"
    {
      (yyval.relation_list) = (yyvsp[0].relation_list);
      (yyval.relation_list)->emplace_back((yyvsp[-1].string));
      free((yyvsp[-1].string));
    }
#line 2178 "yacc_sql.cpp"
    break;

  case 48:
#line 550 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2190 "yacc_sql.cpp"
    break;

  case 49:
#line 561 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2198 "yacc_sql.cpp"
    break;

  case 50:
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
#line 2212 "yacc_sql.cpp"
    break;

  case 51:
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
#line 2240 "yacc_sql.cpp"
    break;

  case 52:
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
#line 2265 "yacc_sql.cpp"
    break;

  case 53:
#line 626 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2273 "yacc_sql.cpp"
    break;

  case 54:
#line 630 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2281 "yacc_sql.cpp"
    break;

  case 55:
#line 634 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2289 "yacc_sql.cpp"
    break;

  case 56:
#line 640 "yacc_sql.y"
    {
      // 根据 primary-null.result 来看，默认是 not null
      (yyval.bools) = true;
    }
#line 2298 "yacc_sql.cpp"
    break;

  case 57:
#line 645 "yacc_sql.y"
    {
      (yyval.bools) = false;
    }
#line 2306 "yacc_sql.cpp"
    break;

  case 58:
#line 649 "yacc_sql.y"
    {
      (yyval.bools) = true;
    }
#line 2314 "yacc_sql.cpp"
    break;

  case 59:
#line 654 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2320 "yacc_sql.cpp"
    break;

  case 60:
#line 657 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::INTS); }
#line 2326 "yacc_sql.cpp"
    break;

  case 61:
#line 658 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::CHARS); }
#line 2332 "yacc_sql.cpp"
    break;

  case 62:
#line 659 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::FLOATS); }
#line 2338 "yacc_sql.cpp"
    break;

  case 63:
#line 660 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::VECTORS); }
#line 2344 "yacc_sql.cpp"
    break;

  case 64:
#line 661 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::TEXTS); }
#line 2350 "yacc_sql.cpp"
    break;

  case 65:
#line 662 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::DATES); }
#line 2356 "yacc_sql.cpp"
    break;

  case 66:
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
#line 2373 "yacc_sql.cpp"
    break;

  case 67:
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
#line 2392 "yacc_sql.cpp"
    break;

  case 68:
#line 698 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2400 "yacc_sql.cpp"
    break;

  case 69:
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
#line 2414 "yacc_sql.cpp"
    break;

  case 70:
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
#line 2430 "yacc_sql.cpp"
    break;

  case 71:
#line 726 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2439 "yacc_sql.cpp"
    break;

  case 72:
#line 730 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2448 "yacc_sql.cpp"
    break;

  case 73:
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
#line 2467 "yacc_sql.cpp"
    break;

  case 74:
#line 749 "yacc_sql.y"
    {
      (yyval.value) = vec2val(sql_string, &(yyloc));
    }
#line 2475 "yacc_sql.cpp"
    break;

  case 75:
#line 752 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2486 "yacc_sql.cpp"
    break;

  case 76:
#line 758 "yacc_sql.y"
             {
      (yyval.value) = new Value();
      (yyval.value)->set_null();
    }
#line 2495 "yacc_sql.cpp"
    break;

  case 77:
#line 765 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2503 "yacc_sql.cpp"
    break;

  case 78:
#line 769 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2511 "yacc_sql.cpp"
    break;

  case 79:
#line 773 "yacc_sql.y"
             {
      (yyval.double_list) = new std::vector<double>();
    }
#line 2519 "yacc_sql.cpp"
    break;

  case 80:
#line 776 "yacc_sql.y"
                   {
      (yyval.double_list) = new std::vector<double>();
      (yyval.double_list)->emplace_back((yyvsp[0].float_number));
    }
#line 2528 "yacc_sql.cpp"
    break;

  case 81:
#line 780 "yacc_sql.y"
                                     {
      (yyval.double_list) = (yyvsp[-2].double_list);
      (yyval.double_list)->emplace_back((yyvsp[0].float_number));
    }
#line 2537 "yacc_sql.cpp"
    break;

  case 82:
#line 785 "yacc_sql.y"
                     {
      (yyval.float_number) = (yyvsp[0].number);
    }
#line 2545 "yacc_sql.cpp"
    break;

  case 83:
#line 788 "yacc_sql.y"
            {
      (yyval.float_number) = (yyvsp[0].floats);
    }
#line 2553 "yacc_sql.cpp"
    break;

  case 84:
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
#line 2568 "yacc_sql.cpp"
    break;

  case 85:
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
#line 2586 "yacc_sql.cpp"
    break;

  case 86:
#line 823 "yacc_sql.y"
    {
      (yyval.kv_list) = new KeyValueList{};
      (yyval.kv_list)->attrs.emplace_back((yyvsp[-2].string));
      (yyval.kv_list)->values.emplace_back((yyvsp[0].expression));
      free((yyvsp[-2].string));
    }
#line 2597 "yacc_sql.cpp"
    break;

  case 87:
#line 830 "yacc_sql.y"
    {
      (yyval.kv_list) = (yyvsp[-4].kv_list);
      (yyval.kv_list)->attrs.emplace_back((yyvsp[-2].string));
      (yyval.kv_list)->values.emplace_back((yyvsp[0].expression));
      free((yyvsp[-2].string));
    }
#line 2608 "yacc_sql.cpp"
    break;

  case 88:
#line 840 "yacc_sql.y"
    {
      (yyval.sql_node) = (yyvsp[0].sql_node);
    }
#line 2616 "yacc_sql.cpp"
    break;

  case 89:
#line 844 "yacc_sql.y"
    {
      (yyval.sql_node) = (yyvsp[0].sql_node);
    }
#line 2624 "yacc_sql.cpp"
    break;

  case 90:
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
#line 2672 "yacc_sql.cpp"
    break;

  case 91:
#line 895 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2683 "yacc_sql.cpp"
    break;

  case 92:
#line 905 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2693 "yacc_sql.cpp"
    break;

  case 93:
#line 914 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->emplace_back((yyvsp[-1].expression));
      if((yyvsp[0].string) != nullptr){
        (yyvsp[-1].expression)->set_alias((yyvsp[0].string));
        free((yyvsp[0].string));
      }
    }
#line 2706 "yacc_sql.cpp"
    break;

  case 94:
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
#line 2723 "yacc_sql.cpp"
    break;

  case 95:
#line 939 "yacc_sql.y"
  {
    (yyval.expression) = nullptr;
  }
#line 2731 "yacc_sql.cpp"
    break;

  case 96:
#line 943 "yacc_sql.y"
  {
    if((yyvsp[0].string) != nullptr){
      (yyvsp[-1].expression)->set_alias((yyvsp[0].string));
      free((yyvsp[0].string));
    }
    (yyval.expression) = (yyvsp[-1].expression);
  }
#line 2743 "yacc_sql.cpp"
    break;

  case 97:
#line 951 "yacc_sql.y"
  {
    (yyval.expression) = nullptr;
    delete (yyvsp[-3].expression);
    free((yyvsp[-2].string));
    delete (yyvsp[0].expression_list);
  }
#line 2754 "yacc_sql.cpp"
    break;

  case 98:
#line 960 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2762 "yacc_sql.cpp"
    break;

  case 99:
#line 963 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2770 "yacc_sql.cpp"
    break;

  case 100:
#line 966 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2778 "yacc_sql.cpp"
    break;

  case 101:
#line 969 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2786 "yacc_sql.cpp"
    break;

  case 102:
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
#line 2800 "yacc_sql.cpp"
    break;

  case 103:
#line 981 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2808 "yacc_sql.cpp"
    break;

  case 104:
#line 984 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2818 "yacc_sql.cpp"
    break;

  case 105:
#line 989 "yacc_sql.y"
               {
      RelAttrSqlNode *node = (yyvsp[0].rel_attr);
      (yyval.expression) = new UnboundFieldExpr(node->relation_name, node->attribute_name);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].rel_attr);
    }
#line 2829 "yacc_sql.cpp"
    break;

  case 106:
#line 995 "yacc_sql.y"
                                                                 {
      (yyval.expression) = create_function_expression((FunctionExpr::Type)(yyvsp[-5].number), sql_string, (yyvsp[-3].expression), (yyvsp[-1].expression), &(yyloc));
    }
#line 2837 "yacc_sql.cpp"
    break;

  case 107:
#line 998 "yacc_sql.y"
                     {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 2845 "yacc_sql.cpp"
    break;

  case 108:
#line 1001 "yacc_sql.y"
                     {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 2853 "yacc_sql.cpp"
    break;

  case 109:
#line 1004 "yacc_sql.y"
          {
      (yyval.expression) = new StarExpr();
    }
#line 2861 "yacc_sql.cpp"
    break;

  case 110:
#line 1010 "yacc_sql.y"
                {
      (yyval.number) = static_cast<int>(FunctionExpr::Type::L2_DISTANCE);
    }
#line 2869 "yacc_sql.cpp"
    break;

  case 111:
#line 1013 "yacc_sql.y"
                      {
      (yyval.number) = static_cast<int>(FunctionExpr::Type::COSINE_DISTANCE);
    }
#line 2877 "yacc_sql.cpp"
    break;

  case 112:
#line 1016 "yacc_sql.y"
                    {
      (yyval.number) = static_cast<int>(FunctionExpr::Type::INNER_PRODUCT);
    }
#line 2885 "yacc_sql.cpp"
    break;

  case 113:
#line 1022 "yacc_sql.y"
                                           {
      (yyval.expression) = create_aggregate_expression("count", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2893 "yacc_sql.cpp"
    break;

  case 114:
#line 1025 "yacc_sql.y"
                                           {
      (yyval.expression) = create_aggregate_expression("sum", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2901 "yacc_sql.cpp"
    break;

  case 115:
#line 1028 "yacc_sql.y"
                                           {
      (yyval.expression) = create_aggregate_expression("avg", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2909 "yacc_sql.cpp"
    break;

  case 116:
#line 1031 "yacc_sql.y"
                                           {
      (yyval.expression) = create_aggregate_expression("min", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2917 "yacc_sql.cpp"
    break;

  case 117:
#line 1034 "yacc_sql.y"
                                           {
      (yyval.expression) = create_aggregate_expression("max", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2925 "yacc_sql.cpp"
    break;

  case 118:
#line 1040 "yacc_sql.y"
    {
      (yyval.expression) = new SubQueryExpr(std::move((yyvsp[-1].sql_node)->selection));
      delete (yyvsp[-1].sql_node);
    }
#line 2934 "yacc_sql.cpp"
    break;

  case 119:
#line 1047 "yacc_sql.y"
       {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2944 "yacc_sql.cpp"
    break;

  case 120:
#line 1052 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2956 "yacc_sql.cpp"
    break;

  case 121:
#line 1059 "yacc_sql.y"
                 {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = "*";
      free((yyvsp[-2].string));
    }
#line 2967 "yacc_sql.cpp"
    break;

  case 122:
#line 1068 "yacc_sql.y"
    {
      (yyval.rel_attr_list) = nullptr;
    }
#line 2975 "yacc_sql.cpp"
    break;

  case 123:
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
#line 2989 "yacc_sql.cpp"
    break;

  case 124:
#line 1085 "yacc_sql.y"
       {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2997 "yacc_sql.cpp"
    break;

  case 125:
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
#line 3012 "yacc_sql.cpp"
    break;

  case 126:
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
#line 3033 "yacc_sql.cpp"
    break;

  case 127:
#line 1120 "yacc_sql.y"
    {
      (yyval.inner_join) = nullptr;
    }
#line 3041 "yacc_sql.cpp"
    break;

  case 128:
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
#line 3057 "yacc_sql.cpp"
    break;

  case 129:
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
#line 3073 "yacc_sql.cpp"
    break;

  case 130:
#line 1153 "yacc_sql.y"
    {
      (yyval.expression) = nullptr;
    }
#line 3081 "yacc_sql.cpp"
    break;

  case 131:
#line 1156 "yacc_sql.y"
                      {
      (yyval.expression) = (yyvsp[0].expression);  
    }
#line 3089 "yacc_sql.cpp"
    break;

  case 132:
#line 1162 "yacc_sql.y"
    {
      (yyval.expression) = new ComparisonExpr((yyvsp[-1].comp), (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 3097 "yacc_sql.cpp"
    break;

  case 133:
#line 1166 "yacc_sql.y"
    {
      Value val;
      val.set_null();
      ValueExpr *value_expr = new ValueExpr(val);
      (yyval.expression) = new ComparisonExpr((yyvsp[-1].comp), value_expr, (yyvsp[0].expression));
    }
#line 3108 "yacc_sql.cpp"
    break;

  case 134:
#line 1173 "yacc_sql.y"
    {
      Value val;
      val.set_null();
      ValueExpr *value_expr = new ValueExpr(val);
      (yyval.expression) = new ComparisonExpr((yyvsp[0].bools) ? IS_NULL : IS_NOT_NULL, (yyvsp[-2].expression), value_expr);
    }
#line 3119 "yacc_sql.cpp"
    break;

  case 135:
#line 1180 "yacc_sql.y"
    {
      (yyval.expression) = new ConjunctionExpr(ConjunctionExpr::Type::AND, (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 3127 "yacc_sql.cpp"
    break;

  case 136:
#line 1184 "yacc_sql.y"
    {
      (yyval.expression) = new ConjunctionExpr(ConjunctionExpr::Type::OR, (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 3135 "yacc_sql.cpp"
    break;

  case 137:
#line 1190 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 3141 "yacc_sql.cpp"
    break;

  case 138:
#line 1191 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 3147 "yacc_sql.cpp"
    break;

  case 139:
#line 1192 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3153 "yacc_sql.cpp"
    break;

  case 140:
#line 1193 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3159 "yacc_sql.cpp"
    break;

  case 141:
#line 1194 "yacc_sql.y"
            { (yyval.comp) = NOT_EQUAL; }
#line 3165 "yacc_sql.cpp"
    break;

  case 142:
#line 1195 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3171 "yacc_sql.cpp"
    break;

  case 143:
#line 1196 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3177 "yacc_sql.cpp"
    break;

  case 144:
#line 1197 "yacc_sql.y"
           { (yyval.comp) = LIKE_OP; }
#line 3183 "yacc_sql.cpp"
    break;

  case 145:
#line 1198 "yacc_sql.y"
               { (yyval.comp) = NOT_LIKE_OP; }
#line 3189 "yacc_sql.cpp"
    break;

  case 146:
#line 1199 "yacc_sql.y"
         { (yyval.comp) = IN_OP; }
#line 3195 "yacc_sql.cpp"
    break;

  case 147:
#line 1200 "yacc_sql.y"
             { (yyval.comp) = NOT_IN_OP; }
#line 3201 "yacc_sql.cpp"
    break;

  case 148:
#line 1204 "yacc_sql.y"
         { (yyval.comp) = EXISTS_OP; }
#line 3207 "yacc_sql.cpp"
    break;

  case 149:
#line 1205 "yacc_sql.y"
               { (yyval.comp) = NOT_EXISTS_OP; }
#line 3213 "yacc_sql.cpp"
    break;

  case 150:
#line 1210 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3221 "yacc_sql.cpp"
    break;

  case 151:
#line 1214 "yacc_sql.y"
    {
      (yyval.expression_list) = (yyvsp[0].expression_list);
    }
#line 3229 "yacc_sql.cpp"
    break;

  case 152:
#line 1221 "yacc_sql.y"
  {
    (yyval.expression) = nullptr;
  }
#line 3237 "yacc_sql.cpp"
    break;

  case 153:
#line 1225 "yacc_sql.y"
  {
    (yyval.expression) = (yyvsp[0].expression);
  }
#line 3245 "yacc_sql.cpp"
    break;

  case 154:
#line 1233 "yacc_sql.y"
    {
      (yyval.order_by_list) = nullptr;
    }
#line 3253 "yacc_sql.cpp"
    break;

  case 155:
#line 1237 "yacc_sql.y"
    {
      (yyval.order_by_list) = (yyvsp[0].order_by_list);
      std::reverse((yyval.order_by_list)->begin(), (yyval.order_by_list)->end());
    }
#line 3262 "yacc_sql.cpp"
    break;

  case 156:
#line 1245 "yacc_sql.y"
    {
      (yyval.limit) = nullptr;
    }
#line 3270 "yacc_sql.cpp"
    break;

  case 157:
#line 1249 "yacc_sql.y"
    {
      (yyval.limit) = new LimitSqlNode();
      (yyval.limit)->number = (yyvsp[0].number);
    }
#line 3279 "yacc_sql.cpp"
    break;

  case 158:
#line 1257 "yacc_sql.y"
    {
      (yyval.order_by_list) = new std::vector<std::unique_ptr<OrderBySqlNode>>();
      (yyval.order_by_list)->emplace_back((yyvsp[0].order_unit));
    }
#line 3288 "yacc_sql.cpp"
    break;

  case 159:
#line 1262 "yacc_sql.y"
    {
      (yyval.order_by_list) = (yyvsp[0].order_by_list);
      (yyval.order_by_list)->emplace_back((yyvsp[-2].order_unit));
    }
#line 3297 "yacc_sql.cpp"
    break;

  case 160:
#line 1270 "yacc_sql.y"
    {
      (yyval.order_unit) = new OrderBySqlNode;
      RelAttrSqlNode *node = (yyvsp[-1].rel_attr);
      (yyval.order_unit)->unbound_field = std::make_unique<UnboundFieldExpr>(node->relation_name, node->attribute_name);
      (yyval.order_unit)->order_op = (yyvsp[0].order_op);
      delete (yyvsp[-1].rel_attr);
    }
#line 3309 "yacc_sql.cpp"
    break;

  case 161:
#line 1277 "yacc_sql.y"
                                                                          {
      (yyval.order_unit) = new OrderBySqlNode;
      (yyval.order_unit)->unbound_field = std::unique_ptr<Expression>(create_function_expression((FunctionExpr::Type)(yyvsp[-6].number), sql_string, (yyvsp[-4].expression), (yyvsp[-2].expression), &(yyloc)));
      (yyval.order_unit)->order_op = (yyvsp[0].order_op);
    }
#line 3319 "yacc_sql.cpp"
    break;

  case 162:
#line 1285 "yacc_sql.y"
    {
      (yyval.order_op) = OrderOp::ASC;
    }
#line 3327 "yacc_sql.cpp"
    break;

  case 163:
#line 1289 "yacc_sql.y"
    {
      (yyval.order_op) = OrderOp::ASC;
    }
#line 3335 "yacc_sql.cpp"
    break;

  case 164:
#line 1293 "yacc_sql.y"
    {
      (yyval.order_op) = OrderOp::DESC;
    }
#line 3343 "yacc_sql.cpp"
    break;

  case 165:
#line 1300 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3357 "yacc_sql.cpp"
    break;

  case 166:
#line 1313 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3366 "yacc_sql.cpp"
    break;

  case 167:
#line 1321 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3378 "yacc_sql.cpp"
    break;

  case 168:
#line 1328 "yacc_sql.y"
                {
      // ann benchmark 三次握手后会发送这个命令
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-1].string);
      (yyval.sql_node)->set_variable.str_val = (yyvsp[0].string);
      free((yyvsp[-1].string));
      free((yyvsp[0].string));
    }
#line 3391 "yacc_sql.cpp"
    break;


#line 3395 "yacc_sql.cpp"

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
#line 1341 "yacc_sql.y"

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

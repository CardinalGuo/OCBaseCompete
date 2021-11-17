/* A Bison parser, made by GNU Bison 3.3.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2019 Free Software Foundation,
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
#define YYBISON_VERSION "3.3.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "yacc_sql.y" /* yacc.c:337  */


#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.tab.h"
#include "sql/parser/lex.yy.h"
// #include "common/log/log.h" // 包含C++中的头文件

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct ParserContext {
  Query * ssql;
  size_t select_length;
  size_t condition_length;
  size_t from_length;
  size_t value_length;
  Value values[MAX_NUM];
  
  size_t value_lengths[MAX_INSERT_RECORD];
  size_t record_length;
  Value record_values[MAX_INSERT_RECORD][MAX_NUM];
  
  Condition conditions[MAX_NUM];
  CompOp comp;
	char id[MAX_NUM];
    
    
  size_t select_num;
  
  size_t select_max;
  size_t select_stack[MAX_NUM];
  size_t select_stack_index;
  
  size_t condition_total_num;
    //size_t condition_composite_num[MAX_NUM];
  Condition_Composite condition_composites[MAX_NUM];
  
  Expression exp_array[MAX_NUM * 2];
  size_t exp_num;
  
} ParserContext;

//获取子串
char *substr(const char *s,int n1,int n2)/*从s中提取下标为n1~n2的字符组成一个新字符串，然后返回这个新串的首地址*/
{
  char *sp = malloc(sizeof(char) * (n2 - n1 + 2));
  int i, j = 0;
  for (i = n1; i <= n2; i++) {
    sp[j++] = s[i];
  }
  sp[j] = 0;
  return sp;
}

void yyerror(yyscan_t scanner, const char *str)
{
  ParserContext *context = (ParserContext *)(yyget_extra(scanner));
  query_reset(context->ssql);
  context->ssql->flag = SCF_ERROR;
  context->condition_length = 0;
  context->from_length = 0;
  context->select_length = 0;
  context->value_length = 0;
  context->exp_num = 0;
  context->ssql->sstr.insertion.value_num = 0;
  context->ssql->sstr.errors = "parse failed";
  printf("parse sql failed. error=%s", str);
}

ParserContext *get_context(yyscan_t scanner)
{
  return (ParserContext *)yyget_extra(scanner);
}

#define CONTEXT get_context(scanner)


#line 149 "yacc_sql.tab.c" /* yacc.c:337  */
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
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "yacc_sql.tab.h".  */
#ifndef YY_YY_YACC_SQL_TAB_H_INCLUDED
# define YY_YY_YACC_SQL_TAB_H_INCLUDED
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
    EQ = 258,
    NE = 259,
    LT = 260,
    GT = 261,
    GE = 262,
    LE = 263,
    ADD = 264,
    SUB = 265,
    STAR = 266,
    DIV = 267,
    SEMICOLON = 268,
    CREATE = 269,
    DROP = 270,
    TABLE = 271,
    TABLES = 272,
    INDEX = 273,
    SELECT = 274,
    DESC = 275,
    ASC = 276,
    SHOW = 277,
    SYNC = 278,
    INSERT = 279,
    DELETE = 280,
    UPDATE = 281,
    LBRACE = 282,
    RBRACE = 283,
    COMMA = 284,
    TRX_BEGIN = 285,
    TRX_COMMIT = 286,
    TRX_ROLLBACK = 287,
    INT_T = 288,
    STRING_T = 289,
    FLOAT_T = 290,
    DATE = 291,
    HELP = 292,
    EXIT = 293,
    DOT = 294,
    INTO = 295,
    VALUES = 296,
    FROM = 297,
    WHERE = 298,
    AND = 299,
    SET = 300,
    ON = 301,
    LOAD = 302,
    DATA = 303,
    NULLABLE = 304,
    NULLL = 305,
    INNER = 306,
    JOIN = 307,
    GROUP = 308,
    ORDER = 309,
    BY = 310,
    MAX = 311,
    MIN = 312,
    AVG = 313,
    COUNT = 314,
    IN = 315,
    NOT = 316,
    INFILE = 317,
    NUMBER = 318,
    FLOAT = 319,
    ID = 320,
    PATH = 321,
    SSS = 322,
    STRING_V = 323
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 158 "yacc_sql.y" /* yacc.c:352  */

  struct _Attr *attr;
  struct _Condition *condition1;
  struct _Value *value1;
  struct _Condition_Composite *Condition_Composite1;
  struct _Selects *selects1;
  struct _Expression *expression1;
  char *string;
  int number;
  int comOp;
  float floats;
	char *position;

#line 275 "yacc_sql.tab.c" /* yacc.c:352  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (void *scanner);

#endif /* !YY_YY_YACC_SQL_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   335

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  69
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  52
/* YYNRULES -- Number of rules.  */
#define YYNRULES  135
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  284

#define YYUNDEFTOK  2
#define YYMAXUTOK   323

/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  ((unsigned) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      65,    66,    67,    68
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   192,   192,   194,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   218,   223,   228,   234,   240,   246,   252,   258,   264,
     271,   279,   286,   295,   297,   301,   312,   325,   328,   329,
     330,   331,   334,   343,   359,   360,   364,   370,   372,   377,
     380,   383,   387,   393,   403,   412,   414,   418,   420,   425,
     446,   466,   486,   508,   529,   550,   570,   571,   577,   583,
     591,   599,   607,   615,   623,   631,   640,   645,   652,   659,
     666,   673,   680,   687,   694,   704,   714,   719,   720,   723,
     726,   727,   730,   734,   735,   738,   741,   744,   747,   750,
     755,   756,   759,   762,   765,   768,   771,   775,   776,   781,
     782,   787,   788,   793,   796,   802,   803,   810,   816,   818,
     823,   824,   832,   840,   849,   859,   873,   890,   891,   892,
     893,   894,   895,   896,   897,   901
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "EQ", "NE", "LT", "GT", "GE", "LE",
  "ADD", "SUB", "STAR", "DIV", "SEMICOLON", "CREATE", "DROP", "TABLE",
  "TABLES", "INDEX", "SELECT", "DESC", "ASC", "SHOW", "SYNC", "INSERT",
  "DELETE", "UPDATE", "LBRACE", "RBRACE", "COMMA", "TRX_BEGIN",
  "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "STRING_T", "FLOAT_T", "DATE",
  "HELP", "EXIT", "DOT", "INTO", "VALUES", "FROM", "WHERE", "AND", "SET",
  "ON", "LOAD", "DATA", "NULLABLE", "NULLL", "INNER", "JOIN", "GROUP",
  "ORDER", "BY", "MAX", "MIN", "AVG", "COUNT", "IN", "NOT", "INFILE",
  "NUMBER", "FLOAT", "ID", "PATH", "SSS", "STRING_V", "$accept",
  "commands", "command", "exit", "help", "sync", "begin", "commit",
  "rollback", "drop_table", "show_tables", "desc_table", "create_index",
  "drop_index", "create_table", "attr_def_list", "attr_def", "number",
  "type", "ID_get", "insert", "record_list", "record", "value_list",
  "value", "delete", "update", "where_old", "condition_list_old",
  "condition_old", "expression_list_add", "expression_list", "expression",
  "select", "select_main", "group_list_add", "group_list",
  "order_list_add", "order_list", "join_add_know", "join_list_add",
  "rel_list_add", "rel_list", "join_condition_list_add",
  "join_condition_list", "where", "where_condition_list_add",
  "where_condition_list", "condition_select_know", "condition", "comOp",
  "load_data", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323
};
# endif

#define YYPACT_NINF -230

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-230)))

#define YYTABLE_NINF -108

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -230,   158,  -230,    39,    67,    77,   -60,    -6,     7,    16,
      -9,     5,    64,    69,    73,    74,    76,    53,  -230,  -230,
    -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,
    -230,  -230,  -230,  -230,  -230,  -230,    40,    54,    61,    62,
    -230,    77,    63,   104,   110,   111,  -230,  -230,    79,  -230,
      97,     6,   132,   140,   146,  -230,    99,   106,   124,  -230,
    -230,  -230,  -230,  -230,   112,   152,   139,   184,   186,    87,
      77,    77,    77,    77,    -7,   133,    77,    77,    77,    77,
      77,  -230,  -230,  -230,  -230,   162,   161,   143,   142,   151,
     153,  -230,  -230,  -230,   138,   203,   214,   218,  -230,  -230,
     -19,   176,    41,    -3,   222,  -230,     6,   209,    43,   224,
     235,   199,  -230,   215,   230,   216,  -230,  -230,  -230,  -230,
     191,   217,  -230,    98,   194,  -230,    50,   232,  -230,  -230,
    -230,    42,  -230,    34,   223,  -230,    50,   252,   151,   242,
    -230,  -230,  -230,  -230,   244,   207,   245,   208,    65,    19,
    -230,    77,   231,   221,   225,   248,   209,   265,  -230,  -230,
    -230,  -230,  -230,  -230,   219,  -230,   220,   185,   190,    43,
    -230,   161,   226,   215,   268,   227,   254,  -230,   237,  -230,
      98,   257,    98,  -230,   228,   233,  -230,    50,   258,   232,
    -230,    34,  -230,  -230,  -230,   250,  -230,   223,   274,   279,
    -230,  -230,  -230,   266,   282,    98,   182,    77,    34,   231,
      25,   234,   248,  -230,  -230,   195,   236,  -230,  -230,  -230,
    -230,  -230,   -44,   253,   270,    77,  -230,   238,   239,  -230,
     131,  -230,   261,  -230,  -230,   255,   240,  -230,    98,  -230,
    -230,   182,    30,   267,   273,   273,   241,   243,  -230,   246,
    -230,   263,   253,   247,  -230,  -230,  -230,  -230,   212,    91,
    -230,    98,  -230,   267,   273,   273,   249,  -230,   273,   273,
    -230,   -44,  -230,  -230,  -230,   147,  -230,  -230,  -230,   273,
     273,  -230,  -230,  -230
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,    20,
      19,    14,    15,    16,    17,     9,    10,    11,    12,    13,
       8,     5,     7,     6,     4,    18,     0,     0,     0,     0,
      70,     0,     0,     0,     0,     0,    73,    74,    71,    75,
       0,    66,     0,     0,     0,    23,     0,     0,     0,    24,
      25,    26,    22,    21,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    68,    85,    29,    28,     0,    55,     0,     0,     0,
       0,    27,    31,    76,     0,     0,     0,     0,    69,    72,
     111,   118,    77,    78,    79,    80,    66,     0,     0,     0,
       0,     0,    42,    33,     0,     0,    82,    83,    84,    81,
       0,     0,   113,     0,    90,    67,     0,    44,    52,    49,
      50,     0,    51,     0,    57,    53,     0,     0,     0,     0,
      38,    39,    40,    41,    36,     0,   111,     0,     0,     0,
     119,     0,   120,     0,   100,    47,     0,     0,   127,   132,
     128,   129,   131,   130,     0,   133,     0,     0,     0,     0,
      56,    55,     0,    33,     0,     0,     0,   112,     0,   123,
       0,     0,     0,   122,     0,     0,    86,     0,     0,    44,
      43,     0,   134,    61,    59,    62,    60,    57,     0,     0,
      34,    32,    37,     0,     0,     0,   124,     0,     0,   120,
      87,     0,    47,    46,    45,     0,     0,    58,    54,   135,
      35,    30,   109,   115,     0,     0,   121,     0,     0,    91,
      93,    48,     0,    63,    64,     0,     0,   114,     0,   117,
     125,   126,    87,    87,    93,    93,     0,     0,   106,     0,
     108,     0,   115,     0,    89,    92,   104,   102,    93,    93,
      65,     0,   116,    87,    93,    93,     0,    97,    93,    93,
     105,   109,    88,    99,    95,    93,   103,   101,   110,    93,
      93,    96,    98,    94
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,
    -230,  -230,  -230,  -230,  -230,   137,   175,  -230,  -230,  -230,
    -230,   126,   160,   105,  -124,  -230,  -230,   148,   121,   154,
     229,  -230,    -5,  -230,  -145,  -229,  -230,   -58,  -230,  -230,
      49,   178,  -230,    70,    60,  -230,   116,  -230,   149,  -122,
    -130,  -230
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,   139,   113,   203,   144,   114,
      31,   157,   127,   188,   133,    32,    33,   109,   170,   134,
      81,    50,   149,    34,    52,   229,   154,   248,   186,   236,
     237,   122,   101,   239,   222,   124,   183,   150,   151,   223,
     167,    35
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      51,   152,   155,   168,    98,    53,   181,   235,    78,    79,
     120,    54,   171,   254,   255,    76,    77,    78,    79,   180,
      55,  -107,   158,   159,   160,   161,   162,   163,    76,    77,
      78,    79,   121,    57,   272,    80,    69,   158,   159,   160,
     161,   162,   163,   194,   196,   158,   159,   160,   161,   162,
     163,    77,    78,    79,   227,    36,    56,    37,    99,   227,
     209,   215,   224,   212,   228,    94,    95,    96,    97,   253,
      58,   102,   103,   104,   105,   106,    40,    59,   225,   165,
     166,   164,    60,    38,   179,    39,    61,    62,    40,    63,
      70,   233,    41,   128,   165,   166,    76,    77,    78,    79,
     128,    64,   165,   166,    41,    65,   129,   130,   131,    40,
     132,   268,   269,   129,   130,    93,   252,   132,    74,    66,
     246,    42,    43,    44,    45,   148,    67,    68,    46,    47,
      48,    71,    49,    42,    43,    44,    45,    72,    73,    75,
      46,    47,    48,    69,    49,    82,    51,    76,    77,    78,
      79,   244,   245,    83,    42,    43,    44,    45,     2,    84,
     246,    46,    47,    48,    85,    49,   116,   279,   280,    87,
     247,    86,     3,     4,    88,   206,   246,     5,     6,    89,
       7,     8,     9,    10,    11,    90,   256,   257,    12,    13,
      14,    76,    77,    78,    79,    15,    16,    91,   100,    92,
     267,   270,    51,   107,   108,    17,   273,   274,   110,   111,
     276,   277,    76,    77,    78,    79,   112,   281,   115,   123,
     241,   282,   283,    76,    77,    78,    79,    76,    77,    78,
      79,   117,   264,   265,    79,   128,   126,   135,   136,   137,
     128,   246,   118,   145,   138,   128,   119,   153,   129,   130,
     193,   266,   132,   129,   130,   195,   146,   132,   129,   130,
     232,   156,   132,   140,   141,   142,   143,   169,   172,   147,
     174,   175,   176,   178,   120,   182,   184,   187,   190,   185,
     192,   201,   204,   205,   191,   208,   213,   218,   211,   216,
     202,   199,   219,   210,   220,   221,   227,   238,   240,   230,
     249,   234,   246,   242,   243,   251,   258,   250,   259,   261,
     200,   260,   263,   173,   275,   214,   189,   231,   217,   198,
     278,   271,   262,   197,   177,   226,     0,     0,     0,   207,
       0,     0,     0,     0,     0,   125
};

static const yytype_int16 yycheck[] =
{
       5,   123,   126,   133,    11,    65,   151,    51,    11,    12,
      29,    17,   136,   242,   243,     9,    10,    11,    12,   149,
      13,    65,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    51,    42,   263,    29,    41,     3,     4,     5,
       6,     7,     8,   167,   168,     3,     4,     5,     6,     7,
       8,    10,    11,    12,    29,    16,    40,    18,    65,    29,
     182,   191,   207,   187,    39,    70,    71,    72,    73,    39,
      65,    76,    77,    78,    79,    80,    11,    13,   208,    60,
      61,    39,    13,    16,    19,    18,    13,    13,    11,    13,
      27,   215,    27,    50,    60,    61,     9,    10,    11,    12,
      50,    48,    60,    61,    27,    65,    63,    64,    65,    11,
      67,    20,    21,    63,    64,    28,   238,    67,    39,    65,
      29,    56,    57,    58,    59,    27,    65,    65,    63,    64,
      65,    27,    67,    56,    57,    58,    59,    27,    27,    42,
      63,    64,    65,   148,    67,    13,   151,     9,    10,    11,
      12,    20,    21,    13,    56,    57,    58,    59,     0,    13,
      29,    63,    64,    65,    65,    67,    28,    20,    21,    45,
      39,    65,    14,    15,    62,   180,    29,    19,    20,    27,
      22,    23,    24,    25,    26,    46,   244,   245,    30,    31,
      32,     9,    10,    11,    12,    37,    38,    13,    65,    13,
     258,   259,   207,    41,    43,    47,   264,   265,    65,    67,
     268,   269,     9,    10,    11,    12,    65,   275,    65,    43,
     225,   279,   280,     9,    10,    11,    12,     9,    10,    11,
      12,    28,    20,    21,    12,    50,    27,    13,     3,    40,
      50,    29,    28,    27,    29,    50,    28,    53,    63,    64,
      65,    39,    67,    63,    64,    65,    65,    67,    63,    64,
      65,    29,    67,    33,    34,    35,    36,    44,    16,    52,
      28,    27,    65,    65,    29,    44,    55,    29,    13,    54,
      60,    13,    28,    46,    65,    28,    28,    13,    55,    39,
      63,    65,    13,    65,    28,    13,    29,    44,    28,    65,
      39,    65,    29,    65,    65,    65,    65,    52,    65,    46,
     173,    65,    65,   138,    65,   189,   156,   212,   197,   171,
     271,   261,   252,   169,   146,   209,    -1,    -1,    -1,   180,
      -1,    -1,    -1,    -1,    -1,   106
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    70,     0,    14,    15,    19,    20,    22,    23,    24,
      25,    26,    30,    31,    32,    37,    38,    47,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    89,    94,    95,   102,   120,    16,    18,    16,    18,
      11,    27,    56,    57,    58,    59,    63,    64,    65,    67,
     100,   101,   103,    65,    17,    13,    40,    42,    65,    13,
      13,    13,    13,    13,    48,    65,    65,    65,    65,   101,
      27,    27,    27,    27,    39,    42,     9,    10,    11,    12,
      29,    99,    13,    13,    13,    65,    65,    45,    62,    27,
      46,    13,    13,    28,   101,   101,   101,   101,    11,    65,
      65,   111,   101,   101,   101,   101,   101,    41,    43,    96,
      65,    67,    65,    85,    88,    65,    28,    28,    28,    28,
      29,    51,   110,    43,   114,    99,    27,    91,    50,    63,
      64,    65,    67,    93,    98,    13,     3,    40,    29,    84,
      33,    34,    35,    36,    87,    27,    65,    52,    27,   101,
     116,   117,   118,    53,   105,    93,    29,    90,     3,     4,
       5,     6,     7,     8,    39,    60,    61,   119,   119,    44,
      97,    93,    16,    85,    28,    27,    65,   110,    65,    19,
     119,   103,    44,   115,    55,    54,   107,    29,    92,    91,
      13,    65,    60,    65,    93,    65,    93,    98,    96,    65,
      84,    13,    63,    86,    28,    46,   101,   117,    28,   118,
      65,    55,    93,    28,    90,   119,    39,    97,    13,    13,
      28,    13,   113,   118,   103,   119,   115,    29,    39,   104,
      65,    92,    65,    93,    65,    51,   108,   109,    44,   112,
      28,   101,    65,    65,    20,    21,    29,    39,   106,    39,
      52,    65,   118,    39,   104,   104,   106,   106,    65,    65,
      65,    46,   112,    65,    20,    21,    39,   106,    20,    21,
     106,   113,   104,   106,   106,    65,   106,   106,   109,    20,
      21,   106,   106,   106
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    69,    70,    70,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    84,    85,    85,    86,    87,    87,
      87,    87,    88,    89,    90,    90,    91,    92,    92,    93,
      93,    93,    93,    94,    95,    96,    96,    97,    97,    98,
      98,    98,    98,    98,    98,    98,    99,    99,   100,   101,
     101,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   102,   103,   104,   104,   104,
     105,   105,   105,   106,   106,   106,   106,   106,   106,   106,
     107,   107,   107,   107,   107,   107,   107,   108,   108,   109,
     109,   110,   110,   111,   111,   112,   112,   113,   114,   114,
     115,   115,   116,   117,   118,   118,   118,   119,   119,   119,
     119,   119,   119,   119,   119,   120
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     2,     2,     2,     4,     3,     3,
       9,     4,     8,     0,     3,     5,     2,     1,     1,     1,
       1,     1,     1,     7,     0,     3,     4,     0,     3,     1,
       1,     1,     1,     5,     8,     0,     3,     0,     3,     3,
       3,     3,     3,     5,     5,     7,     0,     3,     2,     3,
       1,     1,     3,     1,     1,     1,     3,     3,     3,     3,
       3,     4,     4,     4,     4,     3,     6,     0,     5,     3,
       0,     4,     6,     0,     6,     4,     5,     3,     6,     4,
       0,     7,     5,     7,     5,     6,     4,     0,     2,     0,
       5,     0,     3,     2,     7,     0,     3,     2,     0,     2,
       0,     3,     2,     2,     3,     5,     5,     1,     1,     1,
       1,     1,     1,     1,     2,     8
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
        yyerror (scanner, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, void *scanner)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (scanner);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, void *scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep, scanner);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule, void *scanner)
{
  unsigned long yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              , scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, scanner); \
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
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
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
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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

  if (! yyres)
    return yystrlen (yystr);

  return (YYSIZE_T) (yystpcpy (yyres, yystr) - yyres);
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
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
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
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
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
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
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
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, void *scanner)
{
  YYUSE (yyvaluep);
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
yyparse (void *scanner)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yynewstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  *yyssp = (yytype_int16) yystate;

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = (YYSIZE_T) (yyssp - yyss + 1);

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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
      yychar = yylex (&yylval, scanner);
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 21:
#line 218 "yacc_sql.y" /* yacc.c:1652  */
    {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1593 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 22:
#line 223 "yacc_sql.y" /* yacc.c:1652  */
    {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1601 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 23:
#line 228 "yacc_sql.y" /* yacc.c:1652  */
    {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1609 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 24:
#line 234 "yacc_sql.y" /* yacc.c:1652  */
    {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1617 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 25:
#line 240 "yacc_sql.y" /* yacc.c:1652  */
    {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1625 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 26:
#line 246 "yacc_sql.y" /* yacc.c:1652  */
    {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1633 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 27:
#line 252 "yacc_sql.y" /* yacc.c:1652  */
    {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1642 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 28:
#line 258 "yacc_sql.y" /* yacc.c:1652  */
    {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1650 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 29:
#line 264 "yacc_sql.y" /* yacc.c:1652  */
    {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1659 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 30:
#line 272 "yacc_sql.y" /* yacc.c:1652  */
    {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-6].string), (yyvsp[-4].string), (yyvsp[-2].string));
		}
#line 1668 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 31:
#line 280 "yacc_sql.y" /* yacc.c:1652  */
    {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1677 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 32:
#line 287 "yacc_sql.y" /* yacc.c:1652  */
    {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1689 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 34:
#line 297 "yacc_sql.y" /* yacc.c:1652  */
    {    }
#line 1695 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 35:
#line 302 "yacc_sql.y" /* yacc.c:1652  */
    {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-3].number), (yyvsp[-1].number));
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name =(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type = $2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length = $4;
			CONTEXT->value_length++;
		}
#line 1710 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 36:
#line 313 "yacc_sql.y" /* yacc.c:1652  */
    {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[0].number), 4);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
			CONTEXT->value_length++;
		}
#line 1725 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 37:
#line 325 "yacc_sql.y" /* yacc.c:1652  */
    {(yyval.number) = (yyvsp[0].number);}
#line 1731 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 38:
#line 328 "yacc_sql.y" /* yacc.c:1652  */
    { (yyval.number)=INTS; }
#line 1737 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 39:
#line 329 "yacc_sql.y" /* yacc.c:1652  */
    { (yyval.number)=CHARS; }
#line 1743 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 40:
#line 330 "yacc_sql.y" /* yacc.c:1652  */
    { (yyval.number)=FLOATS; }
#line 1749 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 41:
#line 331 "yacc_sql.y" /* yacc.c:1652  */
    {(yyval.number)=DATES;}
#line 1755 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 42:
#line 335 "yacc_sql.y" /* yacc.c:1652  */
    {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1764 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 43:
#line 344 "yacc_sql.y" /* yacc.c:1652  */
    {
			// CONTEXT->values[CONTEXT->value_length++] = *$6;

			CONTEXT->ssql->flag=SCF_INSERT;//"insert";
			// CONTEXT->ssql->sstr.insertion.relation_name = $3;
			// CONTEXT->ssql->sstr.insertion.value_num = CONTEXT->value_length;
			// for(i = 0; i < CONTEXT->value_length; i++){
			// 	CONTEXT->ssql->sstr.insertion.values[i] = CONTEXT->values[i];
      // }
			inserts_record_init(&CONTEXT->ssql->sstr.insertion, (yyvsp[-4].string), CONTEXT->record_values, CONTEXT->record_length, CONTEXT->value_lengths);

      //临时变量清零
      CONTEXT->value_length=0;
    }
#line 1783 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 45:
#line 360 "yacc_sql.y" /* yacc.c:1652  */
    {
    }
#line 1790 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 46:
#line 364 "yacc_sql.y" /* yacc.c:1652  */
    {
        CONTEXT->value_lengths[CONTEXT->record_length] = CONTEXT->value_length;
        record_init_from_values(&CONTEXT->record_values[CONTEXT->record_length++], CONTEXT->values, CONTEXT->value_length);
        CONTEXT->value_length = 0;
      }
#line 1800 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 48:
#line 372 "yacc_sql.y" /* yacc.c:1652  */
    { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1808 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 49:
#line 377 "yacc_sql.y" /* yacc.c:1652  */
    {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 1816 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 50:
#line 380 "yacc_sql.y" /* yacc.c:1652  */
    {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 1824 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 51:
#line 383 "yacc_sql.y" /* yacc.c:1652  */
    {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		}
#line 1833 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 52:
#line 387 "yacc_sql.y" /* yacc.c:1652  */
    {
        value_init_NULL(&CONTEXT->values[CONTEXT->value_length++], "GAY");
    }
#line 1841 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 53:
#line 394 "yacc_sql.y" /* yacc.c:1652  */
    {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 1853 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 54:
#line 404 "yacc_sql.y" /* yacc.c:1652  */
    {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
#line 1865 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 56:
#line 414 "yacc_sql.y" /* yacc.c:1652  */
    {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 1873 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 58:
#line 420 "yacc_sql.y" /* yacc.c:1652  */
    {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 1881 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 59:
#line 426 "yacc_sql.y" /* yacc.c:1652  */
    {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, (yyvsp[-1].comOp), 1, &left_attr, NULL, 0, NULL, right_value);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$ = ( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name = NULL;
			// $$->left_attr.attribute_name= $1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 0;
			// $$->right_attr.relation_name = NULL;
			// $$->right_attr.attribute_name = NULL;
			// $$->right_value = *$3;

		}
#line 1906 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 60:
#line 447 "yacc_sql.y" /* yacc.c:1652  */
    {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, (yyvsp[-1].comOp), 0, NULL, left_value, 0, NULL, right_value);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$ = ( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 0;
			// $$->right_attr.relation_name = NULL;
			// $$->right_attr.attribute_name = NULL;
			// $$->right_value = *$3;

		}
#line 1930 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 61:
#line 467 "yacc_sql.y" /* yacc.c:1652  */
    {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, (yyvsp[-1].comOp), 1, &left_attr, NULL, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;

		}
#line 1954 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 62:
#line 487 "yacc_sql.y" /* yacc.c:1652  */
    {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, (yyvsp[-1].comOp), 0, NULL, left_value, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;

			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp=CONTEXT->comp;
			
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;
		
		}
#line 1980 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 63:
#line 509 "yacc_sql.y" /* yacc.c:1652  */
    {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, (yyvsp[-1].comOp), 1, &left_attr, NULL, 0, NULL, right_value);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;

			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp=CONTEXT->comp;
			// $$->right_is_attr = 0;   //属性值
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=NULL;
			// $$->right_value =*$5;			
							
    }
#line 2005 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 64:
#line 530 "yacc_sql.y" /* yacc.c:1652  */
    {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, (yyvsp[-3].comOp), 0, NULL, left_value, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;//属性值
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;//属性
			// $$->right_attr.relation_name = $3;
			// $$->right_attr.attribute_name = $5;
									
    }
#line 2030 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 65:
#line 551 "yacc_sql.y" /* yacc.c:1652  */
    {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, (yyvsp[-3].comOp), 1, &left_attr, NULL, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;		//属性
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;		//属性
			// $$->right_attr.relation_name=$5;
			// $$->right_attr.attribute_name=$7;
    }
#line 2053 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 67:
#line 572 "yacc_sql.y" /* yacc.c:1652  */
    {
        selects_append_attribute(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num], (yyvsp[-1].expression1));
    }
#line 2061 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 68:
#line 578 "yacc_sql.y" /* yacc.c:1652  */
    {
        selects_append_attribute(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num], (yyvsp[-1].expression1));
    }
#line 2069 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 69:
#line 583 "yacc_sql.y" /* yacc.c:1652  */
    {
        RelAttr attr;
        relation_attr_init(&attr, (yyvsp[-2].string), "*");
        Expression exp_leaf;
        expression_init_leaf_attr(&exp_leaf, &attr);
        CONTEXT->exp_array[CONTEXT->exp_num++] = exp_leaf;
        (yyval.expression1) = &CONTEXT->exp_array[CONTEXT->exp_num - 1];
    }
#line 2082 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 70:
#line 591 "yacc_sql.y" /* yacc.c:1652  */
    {
        RelAttr attr;
        relation_attr_init(&attr, NULL, "*");
        Expression exp_leaf;
        expression_init_leaf_attr(&exp_leaf, &attr);
        CONTEXT->exp_array[CONTEXT->exp_num++] = exp_leaf;
        (yyval.expression1) = &CONTEXT->exp_array[CONTEXT->exp_num - 1];
    }
#line 2095 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 71:
#line 599 "yacc_sql.y" /* yacc.c:1652  */
    {
        RelAttr attr;
        relation_attr_init(&attr, NULL, (yyvsp[0].string));
        Expression exp_leaf;
        expression_init_leaf_attr(&exp_leaf, &attr);
        CONTEXT->exp_array[CONTEXT->exp_num++] = exp_leaf;
        (yyval.expression1) = &CONTEXT->exp_array[CONTEXT->exp_num - 1];
    }
#line 2108 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 72:
#line 607 "yacc_sql.y" /* yacc.c:1652  */
    {
        RelAttr attr;
        relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
        Expression exp_leaf;
        expression_init_leaf_attr(&exp_leaf, &attr);
        CONTEXT->exp_array[CONTEXT->exp_num++] = exp_leaf;
        (yyval.expression1) = &CONTEXT->exp_array[CONTEXT->exp_num - 1];
    }
#line 2121 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 73:
#line 615 "yacc_sql.y" /* yacc.c:1652  */
    {
        value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
        Value *value = &CONTEXT->values[CONTEXT->value_length - 1];
        Expression exp_leaf;
        expression_init_leaf(&exp_leaf, value);
        CONTEXT->exp_array[CONTEXT->exp_num++] = exp_leaf;
        (yyval.expression1) = &CONTEXT->exp_array[CONTEXT->exp_num - 1];
    }
#line 2134 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 74:
#line 623 "yacc_sql.y" /* yacc.c:1652  */
    {
        value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
        Value *value = &CONTEXT->values[CONTEXT->value_length - 1];
        Expression exp_leaf;
        expression_init_leaf(&exp_leaf, value);
        CONTEXT->exp_array[CONTEXT->exp_num++] = exp_leaf;
        (yyval.expression1) = &CONTEXT->exp_array[CONTEXT->exp_num - 1];
    }
#line 2147 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 75:
#line 631 "yacc_sql.y" /* yacc.c:1652  */
    {
        (yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
        value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
        Value *value = &CONTEXT->values[CONTEXT->value_length - 1];
        Expression exp_leaf;
        expression_init_leaf(&exp_leaf, value);
        CONTEXT->exp_array[CONTEXT->exp_num++] = exp_leaf;
        (yyval.expression1) = &CONTEXT->exp_array[CONTEXT->exp_num - 1];
    }
#line 2161 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 76:
#line 640 "yacc_sql.y" /* yacc.c:1652  */
    {
    
        (yyval.expression1) = (yyvsp[-1].expression1);
        //show_expression(&CONTEXT->exp_array[(CONTEXT->exp_num) - 1]);
    }
#line 2171 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 77:
#line 645 "yacc_sql.y" /* yacc.c:1652  */
    {
        Expression exp_node;
        expression_init_node(&exp_node, (yyvsp[-2].expression1), (yyvsp[0].expression1), CAL_ADD);
        CONTEXT->exp_array[CONTEXT->exp_num++] = exp_node;
        (yyval.expression1) = &CONTEXT->exp_array[CONTEXT->exp_num - 1];
        
    }
#line 2183 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 78:
#line 652 "yacc_sql.y" /* yacc.c:1652  */
    {
        Expression exp_node;
        expression_init_node(&exp_node, (yyvsp[-2].expression1), (yyvsp[0].expression1), CAL_SUB);
        CONTEXT->exp_array[CONTEXT->exp_num++] = exp_node;
        (yyval.expression1) = &CONTEXT->exp_array[CONTEXT->exp_num - 1];
        //show_expression(&CONTEXT->exp_array[(CONTEXT->exp_num) - 1]);
    }
#line 2195 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 79:
#line 659 "yacc_sql.y" /* yacc.c:1652  */
    {
        Expression exp_node;
        expression_init_node(&exp_node, (yyvsp[-2].expression1), (yyvsp[0].expression1), CAL_MUL);
        CONTEXT->exp_array[CONTEXT->exp_num++] = exp_node;
        (yyval.expression1) = &CONTEXT->exp_array[CONTEXT->exp_num - 1];
        //show_expression(&CONTEXT->exp_array[(CONTEXT->exp_num) - 1]);
    }
#line 2207 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 80:
#line 666 "yacc_sql.y" /* yacc.c:1652  */
    {
        Expression exp_node;
        expression_init_node(&exp_node, (yyvsp[-2].expression1), (yyvsp[0].expression1), CAL_DIV);
        CONTEXT->exp_array[CONTEXT->exp_num++] = exp_node;
        (yyval.expression1) = &CONTEXT->exp_array[CONTEXT->exp_num - 1];
        //show_expression(&CONTEXT->exp_array[(CONTEXT->exp_num) - 1]);
    }
#line 2219 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 81:
#line 673 "yacc_sql.y" /* yacc.c:1652  */
    {
        Expression exp_node;
        expression_init_node(&exp_node, (yyvsp[-1].expression1), NULL, CAL_COUNT);
        CONTEXT->exp_array[CONTEXT->exp_num++] = exp_node;
        (yyval.expression1) = &CONTEXT->exp_array[CONTEXT->exp_num - 1];
        //show_expression(&CONTEXT->exp_array[(CONTEXT->exp_num) - 1]);
    }
#line 2231 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 82:
#line 680 "yacc_sql.y" /* yacc.c:1652  */
    {
        Expression exp_node;
        expression_init_node(&exp_node, (yyvsp[-1].expression1), NULL, CAL_MAX);
        CONTEXT->exp_array[CONTEXT->exp_num++] = exp_node;
        (yyval.expression1) = &CONTEXT->exp_array[CONTEXT->exp_num - 1];
        //show_expression(&CONTEXT->exp_array[(CONTEXT->exp_num) - 1]);
    }
#line 2243 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 83:
#line 687 "yacc_sql.y" /* yacc.c:1652  */
    {
        Expression exp_node;
        expression_init_node(&exp_node, (yyvsp[-1].expression1), NULL, CAL_MIN);
        CONTEXT->exp_array[CONTEXT->exp_num++] = exp_node;
        (yyval.expression1) = &CONTEXT->exp_array[CONTEXT->exp_num - 1];
        //show_expression(&CONTEXT->exp_array[(CONTEXT->exp_num) - 1]);
    }
#line 2255 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 84:
#line 694 "yacc_sql.y" /* yacc.c:1652  */
    {
        Expression exp_node;
        expression_init_node(&exp_node, (yyvsp[-1].expression1), NULL, CAL_AVG);
        CONTEXT->exp_array[CONTEXT->exp_num++] = exp_node;
        (yyval.expression1) = &CONTEXT->exp_array[CONTEXT->exp_num - 1];
        //show_expression(&CONTEXT->exp_array[(CONTEXT->exp_num) - 1]);
    }
#line 2267 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 85:
#line 704 "yacc_sql.y" /* yacc.c:1652  */
    {
        CONTEXT->ssql->flag=SCF_SELECT;
        
        //CONTEXT->condition_length=0;
        //CONTEXT->from_length=0;
        //CONTEXT->select_length=0;
        //CONTEXT->value_length = 0;
    }
#line 2280 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 86:
#line 715 "yacc_sql.y" /* yacc.c:1652  */
    {
        (yyval.selects1) = &CONTEXT->ssql->sstr.selection[CONTEXT->select_num];
    }
#line 2288 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 88:
#line 720 "yacc_sql.y" /* yacc.c:1652  */
    {
        group_by_append_relattr(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num].group_by, (yyvsp[-3].string), (yyvsp[-1].string));
    }
#line 2296 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 89:
#line 723 "yacc_sql.y" /* yacc.c:1652  */
    {
        group_by_append_relattr(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num].group_by, NULL, (yyvsp[-1].string));
    }
#line 2304 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 91:
#line 727 "yacc_sql.y" /* yacc.c:1652  */
    {
        group_by_append_relattr(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num].group_by, NULL, (yyvsp[-1].string));
    }
#line 2312 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 92:
#line 730 "yacc_sql.y" /* yacc.c:1652  */
    {
        group_by_append_relattr(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num].group_by, (yyvsp[-3].string), (yyvsp[-1].string));
    }
#line 2320 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 94:
#line 735 "yacc_sql.y" /* yacc.c:1652  */
    {
        order_by_append_relattr(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num].order_by, (yyvsp[-4].string), (yyvsp[-2].string), 1);
    }
#line 2328 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 95:
#line 738 "yacc_sql.y" /* yacc.c:1652  */
    {
        order_by_append_relattr(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num].order_by, NULL, (yyvsp[-2].string), 1);
    }
#line 2336 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 96:
#line 741 "yacc_sql.y" /* yacc.c:1652  */
    {
        order_by_append_relattr(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num].order_by, (yyvsp[-3].string), (yyvsp[-1].string), 1);
    }
#line 2344 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 97:
#line 744 "yacc_sql.y" /* yacc.c:1652  */
    {
        order_by_append_relattr(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num].order_by, NULL, (yyvsp[-1].string), 1);
    }
#line 2352 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 98:
#line 747 "yacc_sql.y" /* yacc.c:1652  */
    {
        order_by_append_relattr(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num].order_by, (yyvsp[-4].string), (yyvsp[-2].string), 0);
    }
#line 2360 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 99:
#line 750 "yacc_sql.y" /* yacc.c:1652  */
    {
        order_by_append_relattr(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num].order_by, NULL, (yyvsp[-2].string), 0);
    }
#line 2368 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 101:
#line 756 "yacc_sql.y" /* yacc.c:1652  */
    {
        order_by_append_relattr(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num].order_by, (yyvsp[-4].string), (yyvsp[-2].string), 1);
    }
#line 2376 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 102:
#line 759 "yacc_sql.y" /* yacc.c:1652  */
    {
        order_by_append_relattr(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num].order_by, NULL, (yyvsp[-2].string), 1);
    }
#line 2384 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 103:
#line 762 "yacc_sql.y" /* yacc.c:1652  */
    {
        order_by_append_relattr(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num].order_by, (yyvsp[-4].string), (yyvsp[-2].string), 0);
    }
#line 2392 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 104:
#line 765 "yacc_sql.y" /* yacc.c:1652  */
    {
        order_by_append_relattr(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num].order_by, NULL, (yyvsp[-2].string), 0);
    }
#line 2400 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 105:
#line 768 "yacc_sql.y" /* yacc.c:1652  */
    {
        order_by_append_relattr(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num].order_by, (yyvsp[-3].string), (yyvsp[-1].string), 1);
    }
#line 2408 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 106:
#line 771 "yacc_sql.y" /* yacc.c:1652  */
    {
        order_by_append_relattr(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num].order_by, NULL, (yyvsp[-1].string), 1);
    }
#line 2416 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 108:
#line 777 "yacc_sql.y" /* yacc.c:1652  */
    {
        select_join_num_change(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num],1);
    }
#line 2424 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 110:
#line 783 "yacc_sql.y" /* yacc.c:1652  */
    {
        select_join_append_relation(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num], (yyvsp[-3].string));
        select_join_num_change(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num],0);
    }
#line 2433 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 112:
#line 788 "yacc_sql.y" /* yacc.c:1652  */
    {	
        selects_append_relation(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num], (yyvsp[-1].string));
    }
#line 2441 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 113:
#line 793 "yacc_sql.y" /* yacc.c:1652  */
    {
        selects_append_relation(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num], (yyvsp[-1].string));
    }
#line 2449 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 114:
#line 796 "yacc_sql.y" /* yacc.c:1652  */
    {
        selects_append_relation(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num], (yyvsp[-6].string));
        select_join_append_relation(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num], (yyvsp[-3].string));
    }
#line 2458 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 116:
#line 804 "yacc_sql.y" /* yacc.c:1652  */
    {
        select_join_append_condition(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num], (yyvsp[-1].Condition_Composite1));
    }
#line 2466 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 117:
#line 811 "yacc_sql.y" /* yacc.c:1652  */
    {
        select_join_append_condition(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num], (yyvsp[-1].Condition_Composite1));
    }
#line 2474 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 119:
#line 819 "yacc_sql.y" /* yacc.c:1652  */
    {	
        
    }
#line 2482 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 121:
#line 825 "yacc_sql.y" /* yacc.c:1652  */
    {
        select_append_condition(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num], (yyvsp[-1].Condition_Composite1));
        //show_condition(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num]);
    }
#line 2491 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 122:
#line 833 "yacc_sql.y" /* yacc.c:1652  */
    {
        show_select_num(CONTEXT->select_num);
        select_append_condition(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num], (yyvsp[-1].Condition_Composite1));
        //show_condition(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num]);
    }
#line 2501 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 123:
#line 841 "yacc_sql.y" /* yacc.c:1652  */
    {
        //show_select_num(CONTEXT->select_num);
        CONTEXT->select_stack[CONTEXT->select_stack_index++] = CONTEXT->select_num;
        CONTEXT->select_max++;
        CONTEXT->select_num = CONTEXT->select_max;
    }
#line 2512 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 124:
#line 850 "yacc_sql.y" /* yacc.c:1652  */
    {
        Condition_Composite condition_composite;
        condition_exp_exp_init(&condition_composite, (yyvsp[-2].expression1), (yyvsp[0].expression1), (yyvsp[-1].comOp));
        CONTEXT->condition_composites[CONTEXT->condition_total_num++] = condition_composite;
        
        //CONTEXT->condition_composite_num[CONTEXT->select_num]++;
        
        (yyval.Condition_Composite1) = &CONTEXT->condition_composites[CONTEXT->condition_total_num - 1];
    }
#line 2526 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 125:
#line 860 "yacc_sql.y" /* yacc.c:1652  */
    {
        CONTEXT->select_stack_index--;
        CONTEXT->select_num = CONTEXT->select_stack[CONTEXT->select_stack_index];
        
        show_select_num(CONTEXT->select_num);
        Condition_Composite condition_composite;
        condition_exp_select_init(&condition_composite, (yyvsp[-4].expression1), (yyvsp[-1].selects1), (yyvsp[-3].comOp));
        CONTEXT->condition_composites[CONTEXT->condition_total_num++] = condition_composite;
        
        //CONTEXT->condition_composite_num[CONTEXT->select_num]++;
        
        (yyval.Condition_Composite1) = &CONTEXT->condition_composites[CONTEXT->condition_total_num - 1];
    }
#line 2544 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 126:
#line 874 "yacc_sql.y" /* yacc.c:1652  */
    {
        CONTEXT->select_stack_index--;
        CONTEXT->select_num = CONTEXT->select_stack[CONTEXT->select_stack_index];
        
        show_select_num(CONTEXT->select_num);
        Condition_Composite condition_composite;
        condition_select_exe_init(&condition_composite, (yyvsp[-3].selects1), (yyvsp[0].expression1), (yyvsp[-1].comOp));
        CONTEXT->condition_composites[CONTEXT->condition_total_num++] = condition_composite;
        
        //CONTEXT->condition_composite_num[CONTEXT->select_num]++;
        
        (yyval.Condition_Composite1) = &CONTEXT->condition_composites[CONTEXT->condition_total_num - 1];
    }
#line 2562 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 127:
#line 890 "yacc_sql.y" /* yacc.c:1652  */
    { (yyval.comOp) = EQUAL_TO; }
#line 2568 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 128:
#line 891 "yacc_sql.y" /* yacc.c:1652  */
    { (yyval.comOp) = LESS_THAN; }
#line 2574 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 129:
#line 892 "yacc_sql.y" /* yacc.c:1652  */
    { (yyval.comOp) = GREAT_THAN; }
#line 2580 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 130:
#line 893 "yacc_sql.y" /* yacc.c:1652  */
    { (yyval.comOp) = LESS_EQUAL; }
#line 2586 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 131:
#line 894 "yacc_sql.y" /* yacc.c:1652  */
    { (yyval.comOp) = GREAT_EQUAL; }
#line 2592 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 132:
#line 895 "yacc_sql.y" /* yacc.c:1652  */
    { (yyval.comOp) = NOT_EQUAL; }
#line 2598 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 133:
#line 896 "yacc_sql.y" /* yacc.c:1652  */
    {(yyval.comOp) = ATTR_IN;}
#line 2604 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 134:
#line 897 "yacc_sql.y" /* yacc.c:1652  */
    {(yyval.comOp) = ATTR_NOT_IN;}
#line 2610 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 135:
#line 902 "yacc_sql.y" /* yacc.c:1652  */
    {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2619 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;


#line 2623 "yacc_sql.tab.c" /* yacc.c:1652  */
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
      yyerror (scanner, YY_("syntax error"));
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
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
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
        yyerror (scanner, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



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
                      yytoken, &yylval, scanner);
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


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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
  yyerror (scanner, YY_("memory exhausted"));
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
                  yytoken, &yylval, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, scanner);
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
#line 908 "yacc_sql.y" /* yacc.c:1918  */


//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, Query *sqls){
	ParserContext context;
	memset(&context, 0, sizeof(context));

	yyscan_t scanner;
	yylex_init_extra(&context, &scanner);
	context.ssql = sqls;
	scan_string(s, scanner);
	int result = yyparse(scanner);
	yylex_destroy(scanner);
	return result;
}

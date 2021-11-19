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
  
  Expression exp_array[MAX_NUM * 5];
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
    UMINUS = 268,
    SEMICOLON = 269,
    CREATE = 270,
    DROP = 271,
    TABLE = 272,
    TABLES = 273,
    INDEX = 274,
    UNIQUE = 275,
    SELECT = 276,
    DESC = 277,
    ASC = 278,
    SHOW = 279,
    SYNC = 280,
    INSERT = 281,
    DELETE = 282,
    UPDATE = 283,
    LBRACE = 284,
    RBRACE = 285,
    COMMA = 286,
    TRX_BEGIN = 287,
    TRX_COMMIT = 288,
    TRX_ROLLBACK = 289,
    INT_T = 290,
    STRING_T = 291,
    FLOAT_T = 292,
    DATE = 293,
    HELP = 294,
    EXIT = 295,
    DOT = 296,
    INTO = 297,
    VALUES = 298,
    TEXT = 299,
    FROM = 300,
    WHERE = 301,
    AND = 302,
    SET = 303,
    ON = 304,
    LOAD = 305,
    DATA = 306,
    NULLABLE = 307,
    NULLL = 308,
    INNER = 309,
    JOIN = 310,
    GROUP = 311,
    ORDER = 312,
    BY = 313,
    MAX = 314,
    MIN = 315,
    AVG = 316,
    COUNT = 317,
    IN = 318,
    NOT = 319,
    INFILE = 320,
    IS = 321,
    NUMBER = 322,
    FLOAT = 323,
    ID = 324,
    PATH = 325,
    SSS = 326,
    STRING_V = 327
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 163 "yacc_sql.y" /* yacc.c:352  */

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

#line 279 "yacc_sql.tab.c" /* yacc.c:352  */
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
#define YYLAST   376

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  73
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  53
/* YYNRULES -- Number of rules.  */
#define YYNRULES  150
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  315

#define YYUNDEFTOK  2
#define YYMAXUTOK   327

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
      65,    66,    67,    68,    69,    70,    71,    72
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   197,   197,   199,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   223,   228,   233,   239,   245,   251,   257,   263,   269,
     275,   279,   285,   290,   298,   305,   314,   316,   320,   327,
     335,   343,   354,   357,   358,   359,   360,   361,   364,   373,
     389,   390,   394,   400,   402,   407,   410,   413,   416,   419,
     423,   429,   439,   448,   450,   454,   456,   461,   482,   502,
     522,   544,   565,   586,   606,   607,   613,   619,   627,   635,
     643,   651,   659,   667,   675,   683,   691,   700,   707,   715,
     722,   729,   736,   743,   750,   757,   764,   774,   784,   789,
     790,   793,   796,   797,   800,   804,   805,   808,   811,   814,
     817,   820,   825,   826,   829,   832,   835,   838,   841,   845,
     846,   851,   852,   857,   858,   863,   866,   872,   873,   880,
     886,   888,   893,   894,   902,   910,   919,   929,   943,   957,
     977,   978,   979,   980,   981,   982,   983,   984,   985,   986,
     990
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "EQ", "NE", "LT", "GT", "GE", "LE",
  "ADD", "SUB", "STAR", "DIV", "UMINUS", "SEMICOLON", "CREATE", "DROP",
  "TABLE", "TABLES", "INDEX", "UNIQUE", "SELECT", "DESC", "ASC", "SHOW",
  "SYNC", "INSERT", "DELETE", "UPDATE", "LBRACE", "RBRACE", "COMMA",
  "TRX_BEGIN", "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "STRING_T",
  "FLOAT_T", "DATE", "HELP", "EXIT", "DOT", "INTO", "VALUES", "TEXT",
  "FROM", "WHERE", "AND", "SET", "ON", "LOAD", "DATA", "NULLABLE", "NULLL",
  "INNER", "JOIN", "GROUP", "ORDER", "BY", "MAX", "MIN", "AVG", "COUNT",
  "IN", "NOT", "INFILE", "IS", "NUMBER", "FLOAT", "ID", "PATH", "SSS",
  "STRING_V", "$accept", "commands", "command", "exit", "help", "sync",
  "begin", "commit", "rollback", "drop_table", "show_tables", "desc_table",
  "index_attr_list", "create_index", "drop_index", "create_table",
  "attr_def_list", "attr_def", "number", "type", "ID_get", "insert",
  "record_list", "record", "value_list", "value", "delete", "update",
  "where_old", "condition_list_old", "condition_old",
  "expression_list_add", "expression_list", "expression", "select",
  "select_main", "group_list_add", "group_list", "order_list_add",
  "order_list", "join_add_know", "join_list_add", "rel_list_add",
  "rel_list", "join_condition_list_add", "join_condition_list", "where",
  "where_condition_list_add", "where_condition_list",
  "condition_select_know", "condition", "comOp", "load_data", YY_NULLPTR
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
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327
};
# endif

#define YYPACT_NINF -258

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-258)))

#define YYTABLE_NINF -120

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -258,   204,  -258,   115,    -6,    94,   -52,    17,    71,    48,
      58,    24,    95,    99,   135,   137,   138,    78,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,    90,   106,   139,   112,
     114,   -20,  -258,    94,  -258,   162,   165,   168,   172,  -258,
    -258,   145,  -258,   158,    85,   191,   192,   195,  -258,   141,
     143,   170,  -258,  -258,  -258,  -258,  -258,   148,   210,   196,
     171,   227,   232,    94,  -258,  -258,   157,    94,    94,    94,
      94,    -4,   188,    94,    94,    94,    94,    94,  -258,  -258,
    -258,  -258,   215,   221,   199,   198,   218,   219,   242,  -258,
    -258,   205,  -258,   212,   252,   263,   267,  -258,  -258,    35,
     244,    39,     9,   282,  -258,    85,   266,    -7,   284,   293,
     259,  -258,   269,   248,   273,   234,  -258,  -258,  -258,  -258,
    -258,   235,   250,  -258,   111,   251,  -258,   140,   275,    75,
    -258,  -258,  -258,    36,  -258,    51,   261,  -258,   140,   292,
     218,   280,  -258,  -258,  -258,  -258,  -258,   -19,   243,   285,
     286,   246,    77,    20,  -258,    94,   264,   255,   262,   287,
     266,   302,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
     253,  -258,   257,   260,    57,   121,    -7,  -258,   221,   254,
     269,   307,   265,  -258,   272,   295,   297,   243,  -258,   279,
    -258,   111,   299,   111,  -258,   268,   276,  -258,   140,   300,
     275,  -258,    51,  -258,  -258,  -258,  -258,   290,  -258,   261,
     319,   321,  -258,  -258,  -258,   306,  -258,   243,   324,   309,
     111,   241,    94,    51,   264,   -23,   271,   287,  -258,  -258,
     131,   274,  -258,  -258,  -258,  -258,  -258,  -258,   327,   -35,
     298,   312,   111,  -258,   277,   278,  -258,   154,  -258,   303,
    -258,  -258,  -258,   294,   281,  -258,   111,  -258,  -258,   241,
      94,    60,   317,   320,   320,   283,   288,  -258,   289,  -258,
     304,   298,   325,   291,  -258,  -258,  -258,  -258,   258,    89,
    -258,   111,  -258,  -258,   317,   320,   320,   296,  -258,   320,
     320,  -258,   -35,  -258,  -258,  -258,    96,  -258,  -258,  -258,
     320,   320,  -258,  -258,  -258
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
       0,     0,    78,     0,    82,     0,     0,     0,     0,    81,
      83,    79,    86,     0,    74,     0,     0,     0,    23,     0,
       0,     0,    24,    25,    26,    22,    21,     0,     0,     0,
       0,     0,     0,     0,    84,    85,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    76,    97,
      29,    28,     0,    63,     0,     0,     0,     0,     0,    27,
      34,     0,    87,     0,     0,     0,     0,    77,    80,   123,
     130,    89,    90,    91,    92,    74,     0,     0,     0,     0,
       0,    48,    36,     0,     0,     0,    88,    94,    95,    96,
      93,     0,     0,   125,     0,   102,    75,     0,    50,     0,
      60,    55,    56,     0,    59,     0,    65,    61,     0,     0,
       0,     0,    43,    44,    45,    46,    47,    41,     0,     0,
     123,     0,     0,     0,   131,     0,   132,     0,   112,    53,
       0,     0,    57,    58,   140,   145,   141,   142,   144,   143,
       0,   146,     0,   148,     0,     0,     0,    64,    63,     0,
      36,     0,     0,    40,     0,    30,     0,     0,   124,     0,
     135,     0,     0,     0,   134,     0,     0,    98,     0,     0,
      50,    49,     0,   147,   149,    69,    67,    70,    68,    65,
       0,     0,    37,    35,    42,     0,    39,     0,     0,     0,
       0,   136,     0,     0,   132,    99,     0,    53,    52,    51,
       0,     0,    66,    62,   150,    38,    31,    32,     0,   121,
     127,     0,     0,   133,     0,     0,   103,   105,    54,     0,
      71,    72,    33,     0,     0,   126,     0,   129,   137,   138,
       0,    99,    99,   105,   105,     0,     0,   118,     0,   120,
       0,   127,     0,     0,   101,   104,   116,   114,   105,   105,
      73,     0,   128,   139,    99,   105,   105,     0,   109,   105,
     105,   117,   121,   100,   111,   107,   105,   115,   113,   122,
     105,   105,   108,   110,   106
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -191,  -258,  -258,  -258,   164,   206,  -258,  -258,
    -258,  -258,   149,   193,   124,  -132,  -258,  -258,   174,   147,
     178,   256,  -258,    -5,  -258,  -163,  -257,  -258,   -40,  -258,
    -258,    65,   208,  -258,    88,    79,  -258,   142,  -258,  -189,
    -133,  -141,  -258
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,   196,    28,    29,    30,   151,   122,   225,   157,
     123,    31,   171,   138,   209,   145,    32,    33,   118,   187,
     146,    88,    53,   163,    34,    55,   256,   168,   277,   207,
     264,   265,   133,   110,   267,   249,   135,   204,   164,   165,
     250,   184,    35
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      54,   166,   202,   139,   185,   169,   229,   107,   254,    73,
     192,    39,   232,    40,   284,   285,   188,    56,   255,   263,
      85,    86,   201,   174,   175,   176,   177,   178,   179,    83,
      84,    85,    86,   193,  -119,    57,   246,   303,    76,   174,
     175,   176,   177,   178,   179,   194,   140,    74,    75,    84,
      85,    86,   216,   218,   174,   175,   176,   177,   178,   179,
     141,   142,   143,   270,   144,   108,   131,   139,   101,   251,
     234,   240,   103,   104,   105,   106,   237,   180,   111,   112,
     113,   114,   115,   181,   182,    58,   183,    41,    42,   132,
      59,   254,   252,    61,    83,    84,    85,    86,   200,   181,
     182,   283,   183,    60,    41,    42,    43,   282,   260,    62,
     140,   299,   300,    63,   181,   182,    87,   183,   310,   311,
     275,    41,    42,    43,   141,   142,   215,   275,   144,    67,
      44,   139,    36,   281,    37,    38,    45,    46,    47,    48,
     162,   139,   172,   173,    49,    50,    51,    44,    52,    64,
     139,    65,    66,    45,    46,    47,    48,    76,    70,    68,
      54,    49,    50,    51,    44,    52,    83,    84,    85,    86,
      45,    46,    47,    48,   140,    69,   273,   274,    49,    50,
      51,    71,    52,    72,   140,   275,    81,   102,   141,   142,
     217,    77,   144,   140,    78,   276,   231,    79,   141,   142,
     259,    80,   144,    82,     2,    89,    90,   141,   142,    91,
      92,   144,    93,    95,    83,    84,    85,    86,    94,     3,
       4,    83,    84,    85,    86,     5,     6,    54,     7,     8,
       9,    10,    11,   286,   287,   126,    12,    13,    14,    96,
      98,    99,   127,    15,    16,    97,   100,   269,   298,   301,
      83,    84,    85,    86,    17,   304,   305,   109,   116,   307,
     308,    83,    84,    85,    86,    54,   312,   117,   119,   120,
     313,   314,    83,    84,    85,    86,    83,    84,    85,    86,
     295,   296,   128,   152,   153,   154,   155,   121,   124,   275,
     134,   125,   156,   129,    86,   137,   148,   130,   147,   297,
     150,   149,   158,   159,   160,   161,   170,   167,   186,   189,
     191,   203,   195,   205,   197,   199,   211,   131,   208,   206,
     213,   223,   212,   221,   214,   226,   227,   228,   230,   233,
     238,   241,   224,   243,   236,   244,   245,   235,   247,   248,
     257,   262,   268,   261,   278,   266,   271,   272,   254,   279,
     280,   275,   288,   291,   222,   293,   190,   289,   290,   239,
     294,   258,   220,   210,   219,   306,   242,   309,   198,   292,
     302,   136,     0,     0,     0,     0,   253
};

static const yytype_int16 yycheck[] =
{
       5,   134,   165,    10,   145,   137,   197,    11,    31,    29,
      29,    17,   201,    19,   271,   272,   148,    69,    41,    54,
      11,    12,   163,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    52,    69,    18,   227,   294,    43,     3,
       4,     5,     6,     7,     8,    64,    53,    67,    68,    10,
      11,    12,   184,   185,     3,     4,     5,     6,     7,     8,
      67,    68,    69,   252,    71,    69,    31,    10,    73,   232,
     203,   212,    77,    78,    79,    80,   208,    41,    83,    84,
      85,    86,    87,    63,    64,    14,    66,    10,    11,    54,
      42,    31,   233,    69,     9,    10,    11,    12,    21,    63,
      64,    41,    66,    45,    10,    11,    29,   270,   240,    14,
      53,    22,    23,    14,    63,    64,    31,    66,    22,    23,
      31,    10,    11,    29,    67,    68,    69,    31,    71,    51,
      53,    10,    17,   266,    19,    20,    59,    60,    61,    62,
      29,    10,    67,    68,    67,    68,    69,    53,    71,    14,
      10,    14,    14,    59,    60,    61,    62,   162,    19,    69,
     165,    67,    68,    69,    53,    71,     9,    10,    11,    12,
      59,    60,    61,    62,    53,    69,    22,    23,    67,    68,
      69,    69,    71,    69,    53,    31,    41,    30,    67,    68,
      69,    29,    71,    53,    29,    41,   201,    29,    67,    68,
      69,    29,    71,    45,     0,    14,    14,    67,    68,    14,
      69,    71,    69,    65,     9,    10,    11,    12,    48,    15,
      16,     9,    10,    11,    12,    21,    22,   232,    24,    25,
      26,    27,    28,   273,   274,    30,    32,    33,    34,    29,
      69,    14,    30,    39,    40,    49,    14,   252,   288,   289,
       9,    10,    11,    12,    50,   295,   296,    69,    43,   299,
     300,     9,    10,    11,    12,   270,   306,    46,    69,    71,
     310,   311,     9,    10,    11,    12,     9,    10,    11,    12,
      22,    23,    30,    35,    36,    37,    38,    69,    69,    31,
      46,    49,    44,    30,    12,    29,     3,    30,    14,    41,
      31,    42,    29,    69,    69,    55,    31,    56,    47,    17,
      30,    47,    69,    58,    29,    69,    14,    31,    31,    57,
      63,    14,    69,    69,    64,    53,    31,    30,    49,    30,
      30,    41,    67,    14,    58,    14,    30,    69,    14,    30,
      69,    14,    30,    69,    41,    47,    69,    69,    31,    55,
      69,    31,    69,    49,   190,    30,   150,    69,    69,   210,
      69,   237,   188,   170,   186,    69,   219,   302,   160,   281,
     291,   115,    -1,    -1,    -1,    -1,   234
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    74,     0,    15,    16,    21,    22,    24,    25,    26,
      27,    28,    32,    33,    34,    39,    40,    50,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    86,    87,
      88,    94,    99,   100,   107,   125,    17,    19,    20,    17,
      19,    10,    11,    29,    53,    59,    60,    61,    62,    67,
      68,    69,    71,   105,   106,   108,    69,    18,    14,    42,
      45,    69,    14,    14,    14,    14,    14,    51,    69,    69,
      19,    69,    69,    29,    67,    68,   106,    29,    29,    29,
      29,    41,    45,     9,    10,    11,    12,    31,   104,    14,
      14,    14,    69,    69,    48,    65,    29,    49,    69,    14,
      14,   106,    30,   106,   106,   106,   106,    11,    69,    69,
     116,   106,   106,   106,   106,   106,    43,    46,   101,    69,
      71,    69,    90,    93,    69,    49,    30,    30,    30,    30,
      30,    31,    54,   115,    46,   119,   104,    29,    96,    10,
      53,    67,    68,    69,    71,    98,   103,    14,     3,    42,
      31,    89,    35,    36,    37,    38,    44,    92,    29,    69,
      69,    55,    29,   106,   121,   122,   123,    56,   110,    98,
      31,    95,    67,    68,     3,     4,     5,     6,     7,     8,
      41,    63,    64,    66,   124,   124,    47,   102,    98,    17,
      90,    30,    29,    52,    64,    69,    85,    29,   115,    69,
      21,   124,   108,    47,   120,    58,    57,   112,    31,    97,
      96,    14,    69,    63,    64,    69,    98,    69,    98,   103,
     101,    69,    89,    14,    67,    91,    53,    31,    30,    85,
      49,   106,   122,    30,   123,    69,    58,    98,    30,    95,
     124,    41,   102,    14,    14,    30,    85,    14,    30,   118,
     123,   108,   124,   120,    31,    41,   109,    69,    97,    69,
      98,    69,    14,    54,   113,   114,    47,   117,    30,   106,
     122,    69,    69,    22,    23,    31,    41,   111,    41,    55,
      69,   123,   108,    41,   109,   109,   111,   111,    69,    69,
      69,    49,   117,    30,    69,    22,    23,    41,   111,    22,
      23,   111,   118,   109,   111,   111,    69,   111,   111,   114,
      22,    23,   111,   111,   111
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    73,    74,    74,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    85,    86,    86,    87,    88,    89,    89,    90,    90,
      90,    90,    91,    92,    92,    92,    92,    92,    93,    94,
      95,    95,    96,    97,    97,    98,    98,    98,    98,    98,
      98,    99,   100,   101,   101,   102,   102,   103,   103,   103,
     103,   103,   103,   103,   104,   104,   105,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   107,   108,   109,
     109,   109,   110,   110,   110,   111,   111,   111,   111,   111,
     111,   111,   112,   112,   112,   112,   112,   112,   112,   113,
     113,   114,   114,   115,   115,   116,   116,   117,   117,   118,
     119,   119,   120,   120,   121,   122,   123,   123,   123,   123,
     124,   124,   124,   124,   124,   124,   124,   124,   124,   124,
     125
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     2,     2,     2,     4,     3,     3,
       1,     3,     9,    10,     4,     8,     0,     3,     5,     4,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     7,
       0,     3,     4,     0,     3,     1,     1,     2,     2,     1,
       1,     5,     8,     0,     3,     0,     3,     3,     3,     3,
       3,     5,     5,     7,     0,     3,     2,     3,     1,     1,
       3,     1,     1,     1,     2,     2,     1,     3,     4,     3,
       3,     3,     3,     4,     4,     4,     4,     3,     6,     0,
       5,     3,     0,     4,     6,     0,     6,     4,     5,     3,
       6,     4,     0,     7,     5,     7,     5,     6,     4,     0,
       2,     0,     5,     0,     3,     2,     7,     0,     3,     2,
       0,     2,     0,     3,     2,     2,     3,     5,     5,     7,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     2,
       8
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
#line 223 "yacc_sql.y" /* yacc.c:1652  */
    {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1621 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 22:
#line 228 "yacc_sql.y" /* yacc.c:1652  */
    {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1629 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 23:
#line 233 "yacc_sql.y" /* yacc.c:1652  */
    {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1637 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 24:
#line 239 "yacc_sql.y" /* yacc.c:1652  */
    {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1645 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 25:
#line 245 "yacc_sql.y" /* yacc.c:1652  */
    {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1653 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 26:
#line 251 "yacc_sql.y" /* yacc.c:1652  */
    {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1661 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 27:
#line 257 "yacc_sql.y" /* yacc.c:1652  */
    {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1670 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 28:
#line 263 "yacc_sql.y" /* yacc.c:1652  */
    {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1678 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 29:
#line 269 "yacc_sql.y" /* yacc.c:1652  */
    {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1687 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 30:
#line 276 "yacc_sql.y" /* yacc.c:1652  */
    {
        create_index_append_attr(&CONTEXT->ssql->sstr.create_index, (yyvsp[0].string));
    }
#line 1695 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 31:
#line 280 "yacc_sql.y" /* yacc.c:1652  */
    {
        create_index_append_attr(&CONTEXT->ssql->sstr.create_index, (yyvsp[-2].string));
    }
#line 1703 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 32:
#line 286 "yacc_sql.y" /* yacc.c:1652  */
    {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-6].string), (yyvsp[-4].string), 0);
		}
#line 1712 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 33:
#line 291 "yacc_sql.y" /* yacc.c:1652  */
    {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-6].string), (yyvsp[-4].string), 1);
		}
#line 1721 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 34:
#line 299 "yacc_sql.y" /* yacc.c:1652  */
    {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1730 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 35:
#line 306 "yacc_sql.y" /* yacc.c:1652  */
    {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1742 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 37:
#line 316 "yacc_sql.y" /* yacc.c:1652  */
    {    }
#line 1748 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 38:
#line 321 "yacc_sql.y" /* yacc.c:1652  */
    {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-3].number), (yyvsp[-1].number), 0);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
#line 1759 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 39:
#line 328 "yacc_sql.y" /* yacc.c:1652  */
    {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-2].number), 4, 0);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			
			CONTEXT->value_length++;
		}
#line 1771 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 40:
#line 336 "yacc_sql.y" /* yacc.c:1652  */
    {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-1].number), 4, 1);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			
			CONTEXT->value_length++;
		}
#line 1783 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 41:
#line 344 "yacc_sql.y" /* yacc.c:1652  */
    {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[0].number),4, 0);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			
			CONTEXT->value_length++;
		}
#line 1795 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 42:
#line 354 "yacc_sql.y" /* yacc.c:1652  */
    {(yyval.number) = (yyvsp[0].number);}
#line 1801 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 43:
#line 357 "yacc_sql.y" /* yacc.c:1652  */
    { (yyval.number)=INTS; }
#line 1807 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 44:
#line 358 "yacc_sql.y" /* yacc.c:1652  */
    { (yyval.number)=CHARS; }
#line 1813 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 45:
#line 359 "yacc_sql.y" /* yacc.c:1652  */
    { (yyval.number)=FLOATS; }
#line 1819 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 46:
#line 360 "yacc_sql.y" /* yacc.c:1652  */
    {(yyval.number)=DATES;}
#line 1825 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 47:
#line 361 "yacc_sql.y" /* yacc.c:1652  */
    {(yyval.number)=TEXTS;}
#line 1831 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 48:
#line 365 "yacc_sql.y" /* yacc.c:1652  */
    {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1840 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 49:
#line 374 "yacc_sql.y" /* yacc.c:1652  */
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
#line 1859 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 51:
#line 390 "yacc_sql.y" /* yacc.c:1652  */
    {
    }
#line 1866 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 52:
#line 394 "yacc_sql.y" /* yacc.c:1652  */
    {
        CONTEXT->value_lengths[CONTEXT->record_length] = CONTEXT->value_length;
        record_init_from_values(&CONTEXT->record_values[CONTEXT->record_length++], CONTEXT->values, CONTEXT->value_length);
        CONTEXT->value_length = 0;
      }
#line 1876 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 54:
#line 402 "yacc_sql.y" /* yacc.c:1652  */
    { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1884 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 55:
#line 407 "yacc_sql.y" /* yacc.c:1652  */
    {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 1892 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 56:
#line 410 "yacc_sql.y" /* yacc.c:1652  */
    {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 1900 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 57:
#line 413 "yacc_sql.y" /* yacc.c:1652  */
    {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], -(yyvsp[0].number));
		}
#line 1908 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 58:
#line 416 "yacc_sql.y" /* yacc.c:1652  */
    {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], -(yyvsp[0].floats));
		}
#line 1916 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 59:
#line 419 "yacc_sql.y" /* yacc.c:1652  */
    {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		}
#line 1925 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 60:
#line 423 "yacc_sql.y" /* yacc.c:1652  */
    {
        value_init_NULL(&CONTEXT->values[CONTEXT->value_length++], "GAY");
    }
#line 1933 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 61:
#line 430 "yacc_sql.y" /* yacc.c:1652  */
    {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 1945 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 62:
#line 440 "yacc_sql.y" /* yacc.c:1652  */
    {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
#line 1957 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 64:
#line 450 "yacc_sql.y" /* yacc.c:1652  */
    {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 1965 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 66:
#line 456 "yacc_sql.y" /* yacc.c:1652  */
    {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 1973 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 67:
#line 462 "yacc_sql.y" /* yacc.c:1652  */
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
#line 1998 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 68:
#line 483 "yacc_sql.y" /* yacc.c:1652  */
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
#line 2022 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 69:
#line 503 "yacc_sql.y" /* yacc.c:1652  */
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
#line 2046 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 70:
#line 523 "yacc_sql.y" /* yacc.c:1652  */
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
#line 2072 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 71:
#line 545 "yacc_sql.y" /* yacc.c:1652  */
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
#line 2097 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 72:
#line 566 "yacc_sql.y" /* yacc.c:1652  */
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
#line 2122 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 73:
#line 587 "yacc_sql.y" /* yacc.c:1652  */
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
#line 2145 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 75:
#line 608 "yacc_sql.y" /* yacc.c:1652  */
    {
        selects_append_attribute(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num], (yyvsp[-1].expression1));
    }
#line 2153 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 76:
#line 614 "yacc_sql.y" /* yacc.c:1652  */
    {
        selects_append_attribute(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num], (yyvsp[-1].expression1));
    }
#line 2161 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 77:
#line 619 "yacc_sql.y" /* yacc.c:1652  */
    {
        RelAttr attr;
        relation_attr_init(&attr, (yyvsp[-2].string), "*");
        Expression exp_leaf;
        expression_init_leaf_attr(&exp_leaf, &attr);
        CONTEXT->exp_array[CONTEXT->exp_num++] = exp_leaf;
        (yyval.expression1) = &CONTEXT->exp_array[CONTEXT->exp_num - 1];
    }
#line 2174 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 78:
#line 627 "yacc_sql.y" /* yacc.c:1652  */
    {
        RelAttr attr;
        relation_attr_init(&attr, NULL, "*");
        Expression exp_leaf;
        expression_init_leaf_attr(&exp_leaf, &attr);
        CONTEXT->exp_array[CONTEXT->exp_num++] = exp_leaf;
        (yyval.expression1) = &CONTEXT->exp_array[CONTEXT->exp_num - 1];
    }
#line 2187 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 79:
#line 635 "yacc_sql.y" /* yacc.c:1652  */
    {
        RelAttr attr;
        relation_attr_init(&attr, NULL, (yyvsp[0].string));
        Expression exp_leaf;
        expression_init_leaf_attr(&exp_leaf, &attr);
        CONTEXT->exp_array[CONTEXT->exp_num++] = exp_leaf;
        (yyval.expression1) = &CONTEXT->exp_array[CONTEXT->exp_num - 1];
    }
#line 2200 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 80:
#line 643 "yacc_sql.y" /* yacc.c:1652  */
    {
        RelAttr attr;
        relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
        Expression exp_leaf;
        expression_init_leaf_attr(&exp_leaf, &attr);
        CONTEXT->exp_array[CONTEXT->exp_num++] = exp_leaf;
        (yyval.expression1) = &CONTEXT->exp_array[CONTEXT->exp_num - 1];
    }
#line 2213 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 81:
#line 651 "yacc_sql.y" /* yacc.c:1652  */
    {
        value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
        Value *value = &CONTEXT->values[CONTEXT->value_length - 1];
        Expression exp_leaf;
        expression_init_leaf(&exp_leaf, value);
        CONTEXT->exp_array[CONTEXT->exp_num++] = exp_leaf;
        (yyval.expression1) = &CONTEXT->exp_array[CONTEXT->exp_num - 1];
    }
#line 2226 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 82:
#line 659 "yacc_sql.y" /* yacc.c:1652  */
    {
        value_init_NULL(&CONTEXT->values[CONTEXT->value_length++], "gay");
        Value *value = &CONTEXT->values[CONTEXT->value_length - 1];
        Expression exp_leaf;
        expression_init_leaf(&exp_leaf, value);
        CONTEXT->exp_array[CONTEXT->exp_num++] = exp_leaf;
        (yyval.expression1) = &CONTEXT->exp_array[CONTEXT->exp_num - 1];
    }
#line 2239 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 83:
#line 667 "yacc_sql.y" /* yacc.c:1652  */
    {
        value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
        Value *value = &CONTEXT->values[CONTEXT->value_length - 1];
        Expression exp_leaf;
        expression_init_leaf(&exp_leaf, value);
        CONTEXT->exp_array[CONTEXT->exp_num++] = exp_leaf;
        (yyval.expression1) = &CONTEXT->exp_array[CONTEXT->exp_num - 1];
    }
#line 2252 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 84:
#line 675 "yacc_sql.y" /* yacc.c:1652  */
    {
        value_init_integer(&CONTEXT->values[CONTEXT->value_length++], -(yyvsp[0].number));
        Value *value = &CONTEXT->values[CONTEXT->value_length - 1];
        Expression exp_leaf;
        expression_init_leaf(&exp_leaf, value);
        CONTEXT->exp_array[CONTEXT->exp_num++] = exp_leaf;
        (yyval.expression1) = &CONTEXT->exp_array[CONTEXT->exp_num - 1];
    }
#line 2265 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 85:
#line 683 "yacc_sql.y" /* yacc.c:1652  */
    {
        value_init_float(&CONTEXT->values[CONTEXT->value_length++], -(yyvsp[0].floats));
        Value *value = &CONTEXT->values[CONTEXT->value_length - 1];
        Expression exp_leaf;
        expression_init_leaf(&exp_leaf, value);
        CONTEXT->exp_array[CONTEXT->exp_num++] = exp_leaf;
        (yyval.expression1) = &CONTEXT->exp_array[CONTEXT->exp_num - 1];
    }
#line 2278 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 86:
#line 691 "yacc_sql.y" /* yacc.c:1652  */
    {
        (yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
        value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
        Value *value = &CONTEXT->values[CONTEXT->value_length - 1];
        Expression exp_leaf;
        expression_init_leaf(&exp_leaf, value);
        CONTEXT->exp_array[CONTEXT->exp_num++] = exp_leaf;
        (yyval.expression1) = &CONTEXT->exp_array[CONTEXT->exp_num - 1];
    }
#line 2292 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 87:
#line 700 "yacc_sql.y" /* yacc.c:1652  */
    {
        Expression exp_node;
        expression_init_node(&exp_node, (yyvsp[-1].expression1),NULL,CAL_SELF);
        CONTEXT->exp_array[CONTEXT->exp_num++] = exp_node;
        (yyval.expression1) = &CONTEXT->exp_array[CONTEXT->exp_num - 1];
        //show_expression(&CONTEXT->exp_array[(CONTEXT->exp_num) - 1]);
    }
#line 2304 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 88:
#line 707 "yacc_sql.y" /* yacc.c:1652  */
    {
    
        Expression exp_node;
        expression_init_node(&exp_node, (yyvsp[-1].expression1),NULL,CAL_MINUS);
        CONTEXT->exp_array[CONTEXT->exp_num++] = exp_node;
        (yyval.expression1) = &CONTEXT->exp_array[CONTEXT->exp_num - 1];
        //show_expression(&CONTEXT->exp_array[(CONTEXT->exp_num) - 1]);
    }
#line 2317 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 89:
#line 715 "yacc_sql.y" /* yacc.c:1652  */
    {
        Expression exp_node;
        expression_init_node(&exp_node, (yyvsp[-2].expression1), (yyvsp[0].expression1), CAL_ADD);
        CONTEXT->exp_array[CONTEXT->exp_num++] = exp_node;
        (yyval.expression1) = &CONTEXT->exp_array[CONTEXT->exp_num - 1];
        
    }
#line 2329 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 90:
#line 722 "yacc_sql.y" /* yacc.c:1652  */
    {
        Expression exp_node;
        expression_init_node(&exp_node, (yyvsp[-2].expression1), (yyvsp[0].expression1), CAL_SUB);
        CONTEXT->exp_array[CONTEXT->exp_num++] = exp_node;
        (yyval.expression1) = &CONTEXT->exp_array[CONTEXT->exp_num - 1];
        //show_expression(&CONTEXT->exp_array[(CONTEXT->exp_num) - 1]);
    }
#line 2341 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 91:
#line 729 "yacc_sql.y" /* yacc.c:1652  */
    {
        Expression exp_node;
        expression_init_node(&exp_node, (yyvsp[-2].expression1), (yyvsp[0].expression1), CAL_MUL);
        CONTEXT->exp_array[CONTEXT->exp_num++] = exp_node;
        (yyval.expression1) = &CONTEXT->exp_array[CONTEXT->exp_num - 1];
        //show_expression(&CONTEXT->exp_array[(CONTEXT->exp_num) - 1]);
    }
#line 2353 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 92:
#line 736 "yacc_sql.y" /* yacc.c:1652  */
    {
        Expression exp_node;
        expression_init_node(&exp_node, (yyvsp[-2].expression1), (yyvsp[0].expression1), CAL_DIV);
        CONTEXT->exp_array[CONTEXT->exp_num++] = exp_node;
        (yyval.expression1) = &CONTEXT->exp_array[CONTEXT->exp_num - 1];
        //show_expression(&CONTEXT->exp_array[(CONTEXT->exp_num) - 1]);
    }
#line 2365 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 93:
#line 743 "yacc_sql.y" /* yacc.c:1652  */
    {
        Expression exp_node;
        expression_init_node(&exp_node, (yyvsp[-1].expression1), NULL, CAL_COUNT);
        CONTEXT->exp_array[CONTEXT->exp_num++] = exp_node;
        (yyval.expression1) = &CONTEXT->exp_array[CONTEXT->exp_num - 1];
        //show_expression(&CONTEXT->exp_array[(CONTEXT->exp_num) - 1]);
    }
#line 2377 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 94:
#line 750 "yacc_sql.y" /* yacc.c:1652  */
    {
        Expression exp_node;
        expression_init_node(&exp_node, (yyvsp[-1].expression1), NULL, CAL_MAX);
        CONTEXT->exp_array[CONTEXT->exp_num++] = exp_node;
        (yyval.expression1) = &CONTEXT->exp_array[CONTEXT->exp_num - 1];
        //show_expression(&CONTEXT->exp_array[(CONTEXT->exp_num) - 1]);
    }
#line 2389 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 95:
#line 757 "yacc_sql.y" /* yacc.c:1652  */
    {
        Expression exp_node;
        expression_init_node(&exp_node, (yyvsp[-1].expression1), NULL, CAL_MIN);
        CONTEXT->exp_array[CONTEXT->exp_num++] = exp_node;
        (yyval.expression1) = &CONTEXT->exp_array[CONTEXT->exp_num - 1];
        //show_expression(&CONTEXT->exp_array[(CONTEXT->exp_num) - 1]);
    }
#line 2401 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 96:
#line 764 "yacc_sql.y" /* yacc.c:1652  */
    {
        Expression exp_node;
        expression_init_node(&exp_node, (yyvsp[-1].expression1), NULL, CAL_AVG);
        CONTEXT->exp_array[CONTEXT->exp_num++] = exp_node;
        (yyval.expression1) = &CONTEXT->exp_array[CONTEXT->exp_num - 1];
        //show_expression(&CONTEXT->exp_array[(CONTEXT->exp_num) - 1]);
    }
#line 2413 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 97:
#line 774 "yacc_sql.y" /* yacc.c:1652  */
    {
        CONTEXT->ssql->flag=SCF_SELECT;
        
        //CONTEXT->condition_length=0;
        //CONTEXT->from_length=0;
        //CONTEXT->select_length=0;
        //CONTEXT->value_length = 0;
    }
#line 2426 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 98:
#line 785 "yacc_sql.y" /* yacc.c:1652  */
    {
        (yyval.selects1) = &CONTEXT->ssql->sstr.selection[CONTEXT->select_num];
    }
#line 2434 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 100:
#line 790 "yacc_sql.y" /* yacc.c:1652  */
    {
        group_by_append_relattr(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num].group_by, (yyvsp[-3].string), (yyvsp[-1].string));
    }
#line 2442 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 101:
#line 793 "yacc_sql.y" /* yacc.c:1652  */
    {
        group_by_append_relattr(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num].group_by, NULL, (yyvsp[-1].string));
    }
#line 2450 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 103:
#line 797 "yacc_sql.y" /* yacc.c:1652  */
    {
        group_by_append_relattr(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num].group_by, NULL, (yyvsp[-1].string));
    }
#line 2458 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 104:
#line 800 "yacc_sql.y" /* yacc.c:1652  */
    {
        group_by_append_relattr(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num].group_by, (yyvsp[-3].string), (yyvsp[-1].string));
    }
#line 2466 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 106:
#line 805 "yacc_sql.y" /* yacc.c:1652  */
    {
        order_by_append_relattr(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num].order_by, (yyvsp[-4].string), (yyvsp[-2].string), 1);
    }
#line 2474 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 107:
#line 808 "yacc_sql.y" /* yacc.c:1652  */
    {
        order_by_append_relattr(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num].order_by, NULL, (yyvsp[-2].string), 1);
    }
#line 2482 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 108:
#line 811 "yacc_sql.y" /* yacc.c:1652  */
    {
        order_by_append_relattr(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num].order_by, (yyvsp[-3].string), (yyvsp[-1].string), 1);
    }
#line 2490 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 109:
#line 814 "yacc_sql.y" /* yacc.c:1652  */
    {
        order_by_append_relattr(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num].order_by, NULL, (yyvsp[-1].string), 1);
    }
#line 2498 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 110:
#line 817 "yacc_sql.y" /* yacc.c:1652  */
    {
        order_by_append_relattr(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num].order_by, (yyvsp[-4].string), (yyvsp[-2].string), 0);
    }
#line 2506 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 111:
#line 820 "yacc_sql.y" /* yacc.c:1652  */
    {
        order_by_append_relattr(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num].order_by, NULL, (yyvsp[-2].string), 0);
    }
#line 2514 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 113:
#line 826 "yacc_sql.y" /* yacc.c:1652  */
    {
        order_by_append_relattr(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num].order_by, (yyvsp[-4].string), (yyvsp[-2].string), 1);
    }
#line 2522 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 114:
#line 829 "yacc_sql.y" /* yacc.c:1652  */
    {
        order_by_append_relattr(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num].order_by, NULL, (yyvsp[-2].string), 1);
    }
#line 2530 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 115:
#line 832 "yacc_sql.y" /* yacc.c:1652  */
    {
        order_by_append_relattr(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num].order_by, (yyvsp[-4].string), (yyvsp[-2].string), 0);
    }
#line 2538 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 116:
#line 835 "yacc_sql.y" /* yacc.c:1652  */
    {
        order_by_append_relattr(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num].order_by, NULL, (yyvsp[-2].string), 0);
    }
#line 2546 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 117:
#line 838 "yacc_sql.y" /* yacc.c:1652  */
    {
        order_by_append_relattr(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num].order_by, (yyvsp[-3].string), (yyvsp[-1].string), 1);
    }
#line 2554 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 118:
#line 841 "yacc_sql.y" /* yacc.c:1652  */
    {
        order_by_append_relattr(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num].order_by, NULL, (yyvsp[-1].string), 1);
    }
#line 2562 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 120:
#line 847 "yacc_sql.y" /* yacc.c:1652  */
    {
        select_join_num_change(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num],1);
    }
#line 2570 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 122:
#line 853 "yacc_sql.y" /* yacc.c:1652  */
    {
        select_join_append_relation(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num], (yyvsp[-3].string));
        select_join_num_change(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num],0);
    }
#line 2579 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 124:
#line 858 "yacc_sql.y" /* yacc.c:1652  */
    {	
        selects_append_relation(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num], (yyvsp[-1].string));
    }
#line 2587 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 125:
#line 863 "yacc_sql.y" /* yacc.c:1652  */
    {
        selects_append_relation(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num], (yyvsp[-1].string));
    }
#line 2595 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 126:
#line 866 "yacc_sql.y" /* yacc.c:1652  */
    {
        selects_append_relation(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num], (yyvsp[-6].string));
        select_join_append_relation(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num], (yyvsp[-3].string));
    }
#line 2604 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 128:
#line 874 "yacc_sql.y" /* yacc.c:1652  */
    {
        select_join_append_condition(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num], (yyvsp[-1].Condition_Composite1));
    }
#line 2612 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 129:
#line 881 "yacc_sql.y" /* yacc.c:1652  */
    {
        select_join_append_condition(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num], (yyvsp[-1].Condition_Composite1));
    }
#line 2620 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 131:
#line 889 "yacc_sql.y" /* yacc.c:1652  */
    {	
        
    }
#line 2628 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 133:
#line 895 "yacc_sql.y" /* yacc.c:1652  */
    {
        select_append_condition(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num], (yyvsp[-1].Condition_Composite1));
        //show_condition(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num]);
    }
#line 2637 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 134:
#line 903 "yacc_sql.y" /* yacc.c:1652  */
    {
        show_select_num(CONTEXT->select_num);
        select_append_condition(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num], (yyvsp[-1].Condition_Composite1));
        //show_condition(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num]);
    }
#line 2647 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 135:
#line 911 "yacc_sql.y" /* yacc.c:1652  */
    {
        //show_select_num(CONTEXT->select_num);
        CONTEXT->select_stack[CONTEXT->select_stack_index++] = CONTEXT->select_num;
        CONTEXT->select_max++;
        CONTEXT->select_num = CONTEXT->select_max;
    }
#line 2658 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 136:
#line 920 "yacc_sql.y" /* yacc.c:1652  */
    {
        Condition_Composite condition_composite;
        condition_exp_exp_init(&condition_composite, (yyvsp[-2].expression1), (yyvsp[0].expression1), (yyvsp[-1].comOp));
        CONTEXT->condition_composites[CONTEXT->condition_total_num++] = condition_composite;
        
        //CONTEXT->condition_composite_num[CONTEXT->select_num]++;
        
        (yyval.Condition_Composite1) = &CONTEXT->condition_composites[CONTEXT->condition_total_num - 1];
    }
#line 2672 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 137:
#line 930 "yacc_sql.y" /* yacc.c:1652  */
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
#line 2690 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 138:
#line 944 "yacc_sql.y" /* yacc.c:1652  */
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
#line 2708 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 139:
#line 958 "yacc_sql.y" /* yacc.c:1652  */
    {
        CONTEXT->select_stack_index--;
        CONTEXT->select_num = CONTEXT->select_stack[CONTEXT->select_stack_index];
        show_select_num(CONTEXT->select_num);
        CONTEXT->select_stack_index--;
        CONTEXT->select_num = CONTEXT->select_stack[CONTEXT->select_stack_index];
        show_select_num(CONTEXT->select_num);
        
        Condition_Composite condition_composite;
        condition_select_select_init(&condition_composite, (yyvsp[-5].selects1), (yyvsp[-1].selects1), (yyvsp[-3].comOp));
        CONTEXT->condition_composites[CONTEXT->condition_total_num++] = condition_composite;
        
        //CONTEXT->condition_composite_num[CONTEXT->select_num]++;
        
        (yyval.Condition_Composite1) = &CONTEXT->condition_composites[CONTEXT->condition_total_num - 1];
    }
#line 2729 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 140:
#line 977 "yacc_sql.y" /* yacc.c:1652  */
    { (yyval.comOp) = EQUAL_TO; }
#line 2735 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 141:
#line 978 "yacc_sql.y" /* yacc.c:1652  */
    { (yyval.comOp) = LESS_THAN; }
#line 2741 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 142:
#line 979 "yacc_sql.y" /* yacc.c:1652  */
    { (yyval.comOp) = GREAT_THAN; }
#line 2747 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 143:
#line 980 "yacc_sql.y" /* yacc.c:1652  */
    { (yyval.comOp) = LESS_EQUAL; }
#line 2753 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 144:
#line 981 "yacc_sql.y" /* yacc.c:1652  */
    { (yyval.comOp) = GREAT_EQUAL; }
#line 2759 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 145:
#line 982 "yacc_sql.y" /* yacc.c:1652  */
    { (yyval.comOp) = NOT_EQUAL; }
#line 2765 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 146:
#line 983 "yacc_sql.y" /* yacc.c:1652  */
    {(yyval.comOp) = ATTR_IN;}
#line 2771 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 147:
#line 984 "yacc_sql.y" /* yacc.c:1652  */
    {(yyval.comOp) = ATTR_NOT_IN;}
#line 2777 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 148:
#line 985 "yacc_sql.y" /* yacc.c:1652  */
    {(yyval.comOp) = ATTR_IS;}
#line 2783 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 149:
#line 986 "yacc_sql.y" /* yacc.c:1652  */
    {(yyval.comOp) = ATTR_IS_NOT;}
#line 2789 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 150:
#line 991 "yacc_sql.y" /* yacc.c:1652  */
    {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2798 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;


#line 2802 "yacc_sql.tab.c" /* yacc.c:1652  */
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
#line 997 "yacc_sql.y" /* yacc.c:1918  */


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

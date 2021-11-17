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
    FROM = 299,
    WHERE = 300,
    AND = 301,
    SET = 302,
    ON = 303,
    LOAD = 304,
    DATA = 305,
    NULLABLE = 306,
    NULLL = 307,
    INNER = 308,
    JOIN = 309,
    GROUP = 310,
    ORDER = 311,
    BY = 312,
    MAX = 313,
    MIN = 314,
    AVG = 315,
    COUNT = 316,
    IN = 317,
    NOT = 318,
    INFILE = 319,
    NUMBER = 320,
    FLOAT = 321,
    ID = 322,
    PATH = 323,
    SSS = 324,
    STRING_V = 325
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 161 "yacc_sql.y" /* yacc.c:352  */

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

#line 277 "yacc_sql.tab.c" /* yacc.c:352  */
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
#define YYLAST   369

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  71
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  53
/* YYNRULES -- Number of rules.  */
#define YYNRULES  144
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  308

#define YYUNDEFTOK  2
#define YYMAXUTOK   325

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
      65,    66,    67,    68,    69,    70
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   195,   195,   197,   201,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   221,   226,   231,   237,   243,   249,   255,   261,   267,
     273,   277,   283,   288,   296,   303,   312,   314,   318,   329,
     342,   345,   346,   347,   348,   351,   360,   376,   377,   381,
     387,   389,   394,   397,   400,   403,   406,   410,   416,   426,
     435,   437,   441,   443,   448,   469,   489,   509,   531,   552,
     573,   593,   594,   600,   606,   614,   622,   630,   638,   646,
     654,   662,   670,   679,   686,   694,   701,   708,   715,   722,
     729,   736,   743,   753,   763,   768,   769,   772,   775,   776,
     779,   783,   784,   787,   790,   793,   796,   799,   804,   805,
     808,   811,   814,   817,   820,   824,   825,   830,   831,   836,
     837,   842,   845,   851,   852,   859,   865,   867,   872,   873,
     881,   889,   898,   908,   922,   936,   956,   957,   958,   959,
     960,   961,   962,   963,   967
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
  "FLOAT_T", "DATE", "HELP", "EXIT", "DOT", "INTO", "VALUES", "FROM",
  "WHERE", "AND", "SET", "ON", "LOAD", "DATA", "NULLABLE", "NULLL",
  "INNER", "JOIN", "GROUP", "ORDER", "BY", "MAX", "MIN", "AVG", "COUNT",
  "IN", "NOT", "INFILE", "NUMBER", "FLOAT", "ID", "PATH", "SSS",
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
     325
};
# endif

#define YYPACT_NINF -255

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-255)))

#define YYTABLE_NINF -116

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -255,   177,  -255,   164,    69,   101,   -59,    18,    -1,     3,
       9,     2,    76,    83,    94,   111,   112,    70,  -255,  -255,
    -255,  -255,  -255,  -255,  -255,  -255,  -255,  -255,  -255,  -255,
    -255,  -255,  -255,  -255,  -255,  -255,    26,    71,   135,    96,
      97,   -14,  -255,   101,   140,   147,   166,   167,  -255,  -255,
     156,  -255,   174,   203,   186,   205,   209,  -255,   157,   158,
     180,  -255,  -255,  -255,  -255,  -255,   189,   201,   183,   175,
     227,   243,   101,  -255,  -255,   178,   101,   101,   101,   101,
      -2,   187,   101,   101,   101,   101,   101,  -255,  -255,  -255,
    -255,   212,   218,   197,   196,   200,   202,   220,  -255,  -255,
     226,  -255,   236,   240,   250,   262,  -255,  -255,   -19,   230,
      46,   104,   273,  -255,   203,   257,    -6,   274,   284,   247,
    -255,   259,   241,   264,   224,  -255,  -255,  -255,  -255,  -255,
     228,   242,  -255,   113,   239,  -255,    84,   266,    86,  -255,
    -255,  -255,    13,  -255,    36,   252,  -255,    84,   282,   200,
     270,  -255,  -255,  -255,  -255,   275,   234,   276,   271,   244,
      74,    20,  -255,   101,   260,   246,   251,   277,   257,   295,
    -255,  -255,  -255,  -255,  -255,  -255,  -255,  -255,   245,  -255,
     248,    40,    52,    -6,  -255,   218,   249,   259,   299,   253,
     283,   285,   234,  -255,   269,  -255,   113,   289,   113,  -255,
     254,   263,  -255,    84,   292,   266,  -255,    36,  -255,  -255,
    -255,   286,  -255,   252,   309,   310,  -255,  -255,  -255,   296,
     234,   311,   298,   113,   272,   101,    36,   260,     6,   265,
     277,  -255,  -255,    79,   267,  -255,  -255,  -255,  -255,  -255,
    -255,   315,    43,   287,   300,   113,  -255,   268,   278,  -255,
     106,  -255,   290,  -255,  -255,  -255,   288,   279,  -255,   113,
    -255,  -255,   272,   101,    60,   305,   306,   306,   280,   281,
    -255,   291,  -255,   293,   287,   308,   294,  -255,  -255,  -255,
    -255,   134,    91,  -255,   113,  -255,  -255,   305,   306,   306,
     297,  -255,   306,   306,  -255,    43,  -255,  -255,  -255,   163,
    -255,  -255,  -255,   306,   306,  -255,  -255,  -255
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
       0,     0,    75,     0,     0,     0,     0,     0,    78,    79,
      76,    82,     0,    71,     0,     0,     0,    23,     0,     0,
       0,    24,    25,    26,    22,    21,     0,     0,     0,     0,
       0,     0,     0,    80,    81,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    73,    93,    29,
      28,     0,    60,     0,     0,     0,     0,     0,    27,    34,
       0,    83,     0,     0,     0,     0,    74,    77,   119,   126,
      85,    86,    87,    88,    71,     0,     0,     0,     0,     0,
      45,    36,     0,     0,     0,    84,    90,    91,    92,    89,
       0,     0,   121,     0,    98,    72,     0,    47,     0,    57,
      52,    53,     0,    56,     0,    62,    58,     0,     0,     0,
       0,    41,    42,    43,    44,    39,     0,     0,   119,     0,
       0,     0,   127,     0,   128,     0,   108,    50,     0,     0,
      54,    55,   136,   141,   137,   138,   140,   139,     0,   142,
       0,     0,     0,     0,    61,    60,     0,    36,     0,     0,
      30,     0,     0,   120,     0,   131,     0,     0,     0,   130,
       0,     0,    94,     0,     0,    47,    46,     0,   143,    66,
      64,    67,    65,    62,     0,     0,    37,    35,    40,     0,
       0,     0,     0,     0,   132,     0,     0,   128,    95,     0,
      50,    49,    48,     0,     0,    63,    59,   144,    38,    31,
      32,     0,   117,   123,     0,     0,   129,     0,     0,    99,
     101,    51,     0,    68,    69,    33,     0,     0,   122,     0,
     125,   133,   134,     0,    95,    95,   101,   101,     0,     0,
     114,     0,   116,     0,   123,     0,     0,    97,   100,   112,
     110,   101,   101,    70,     0,   124,   135,    95,   101,   101,
       0,   105,   101,   101,   113,   117,    96,   107,   103,   101,
     111,   109,   118,   101,   101,   104,   106,   102
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -255,  -255,  -255,  -255,  -255,  -255,  -255,  -255,  -255,  -255,
    -255,  -255,  -185,  -255,  -255,  -255,   152,   191,  -255,  -255,
    -255,  -255,   138,   176,   119,  -133,  -255,  -255,   165,   139,
     168,   255,  -255,    -5,  -255,  -161,  -254,  -255,   -60,  -255,
    -255,    58,   198,  -255,    80,    73,  -255,   128,  -255,  -190,
    -132,  -139,  -255
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,   191,    28,    29,    30,   150,   121,   219,   155,
     122,    31,   169,   137,   204,   144,    32,    33,   117,   184,
     145,    87,    52,   161,    34,    54,   249,   166,   270,   202,
     257,   258,   132,   109,   260,   242,   134,   199,   162,   163,
     243,   181,    35
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      53,   164,   197,   167,   138,   182,   225,   222,    55,   106,
     277,   278,   130,    57,   185,    72,   172,   173,   174,   175,
     176,   177,   196,   172,   173,   174,   175,   176,   177,    82,
      83,    84,    85,   296,   131,   239,    56,   247,    75,   172,
     173,   174,   175,   176,   177,    58,   139,   248,   210,   212,
     138,    73,    74,    59,   178,   263,    83,    84,    85,   140,
     141,   142,   138,   143,   244,   107,   227,   100,   233,    60,
     230,   102,   103,   104,   105,   179,   180,   110,   111,   112,
     113,   114,   179,   180,    41,    42,    39,   245,    40,   138,
      61,   247,   139,    67,   138,   195,   256,    62,   179,   180,
     253,   276,   275,    43,   139,   140,   141,   209,    63,   143,
    -115,    41,    42,   292,   293,    84,    85,   140,   141,   211,
      66,   143,   268,    41,    42,    64,    65,   274,   266,   267,
      43,   139,    44,    45,    46,    47,   139,   268,    68,    48,
      49,    50,   160,    51,   140,   141,   252,   269,   143,   140,
     141,   170,   171,   143,    69,    75,   288,   289,    53,    44,
      45,    46,    47,    70,    71,   268,    48,    49,    50,    76,
      51,    44,    45,    46,    47,   290,    77,     2,    48,    49,
      50,    36,    51,    37,    38,   303,   304,    82,    83,    84,
      85,   224,     3,     4,   268,    78,    79,    80,     5,     6,
      88,     7,     8,     9,    10,    11,   279,   280,   101,    12,
      13,    14,    82,    83,    84,    85,    15,    16,    81,    89,
      53,   291,   294,    90,    91,    92,    17,    93,   297,   298,
      95,    96,   300,   301,    86,    82,    83,    84,    85,   305,
     262,    98,    97,   306,   307,    82,    83,    84,    85,    82,
      83,    84,    85,    94,   108,   115,   125,    99,    53,    82,
      83,    84,    85,   116,   118,   119,   126,   120,   124,   123,
     127,    82,    83,    84,    85,   133,   151,   152,   153,   154,
     128,    82,    83,    84,    85,    85,   136,   147,   146,   148,
     149,   157,   129,   156,   165,   158,   159,   168,   183,   186,
     188,   190,   130,   200,   189,   192,   198,   201,   203,   206,
     208,   194,   207,   217,   220,   221,   215,   223,   218,   226,
     229,   228,   231,   236,   237,   240,   238,   234,   241,   255,
     261,   271,   250,   259,   254,   264,   247,   268,   286,   216,
     187,   284,   272,   232,   205,   265,   273,   281,   282,   251,
     214,   213,   235,   302,   285,   246,   193,   295,   283,     0,
       0,   287,     0,     0,   299,     0,     0,     0,     0,   135
};

static const yytype_int16 yycheck[] =
{
       5,   133,   163,   136,    10,   144,   196,   192,    67,    11,
     264,   265,    31,    14,   147,    29,     3,     4,     5,     6,
       7,     8,   161,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,   287,    53,   220,    18,    31,    43,     3,
       4,     5,     6,     7,     8,    42,    52,    41,   181,   182,
      10,    65,    66,    44,    41,   245,    10,    11,    12,    65,
      66,    67,    10,    69,   225,    67,   198,    72,   207,    67,
     203,    76,    77,    78,    79,    62,    63,    82,    83,    84,
      85,    86,    62,    63,    10,    11,    17,   226,    19,    10,
      14,    31,    52,    67,    10,    21,    53,    14,    62,    63,
     233,    41,   263,    29,    52,    65,    66,    67,    14,    69,
      67,    10,    11,    22,    23,    11,    12,    65,    66,    67,
      50,    69,    31,    10,    11,    14,    14,   259,    22,    23,
      29,    52,    58,    59,    60,    61,    52,    31,    67,    65,
      66,    67,    29,    69,    65,    66,    67,    41,    69,    65,
      66,    65,    66,    69,    19,   160,    22,    23,   163,    58,
      59,    60,    61,    67,    67,    31,    65,    66,    67,    29,
      69,    58,    59,    60,    61,    41,    29,     0,    65,    66,
      67,    17,    69,    19,    20,    22,    23,     9,    10,    11,
      12,   196,    15,    16,    31,    29,    29,    41,    21,    22,
      14,    24,    25,    26,    27,    28,   266,   267,    30,    32,
      33,    34,     9,    10,    11,    12,    39,    40,    44,    14,
     225,   281,   282,    14,    67,    67,    49,    47,   288,   289,
      29,    48,   292,   293,    31,     9,    10,    11,    12,   299,
     245,    14,    67,   303,   304,     9,    10,    11,    12,     9,
      10,    11,    12,    64,    67,    43,    30,    14,   263,     9,
      10,    11,    12,    45,    67,    69,    30,    67,    48,    67,
      30,     9,    10,    11,    12,    45,    35,    36,    37,    38,
      30,     9,    10,    11,    12,    12,    29,     3,    14,    42,
      31,    67,    30,    29,    55,    67,    54,    31,    46,    17,
      30,    67,    31,    57,    29,    29,    46,    56,    31,    14,
      62,    67,    67,    14,    31,    30,    67,    48,    65,    30,
      57,    67,    30,    14,    14,    14,    30,    41,    30,    14,
      30,    41,    67,    46,    67,    67,    31,    31,    30,   187,
     149,    48,    54,   205,   168,    67,    67,    67,    67,   230,
     185,   183,   213,   295,   274,   227,   158,   284,    67,    -1,
      -1,    67,    -1,    -1,    67,    -1,    -1,    -1,    -1,   114
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    72,     0,    15,    16,    21,    22,    24,    25,    26,
      27,    28,    32,    33,    34,    39,    40,    49,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    84,    85,
      86,    92,    97,    98,   105,   123,    17,    19,    20,    17,
      19,    10,    11,    29,    58,    59,    60,    61,    65,    66,
      67,    69,   103,   104,   106,    67,    18,    14,    42,    44,
      67,    14,    14,    14,    14,    14,    50,    67,    67,    19,
      67,    67,    29,    65,    66,   104,    29,    29,    29,    29,
      41,    44,     9,    10,    11,    12,    31,   102,    14,    14,
      14,    67,    67,    47,    64,    29,    48,    67,    14,    14,
     104,    30,   104,   104,   104,   104,    11,    67,    67,   114,
     104,   104,   104,   104,   104,    43,    45,    99,    67,    69,
      67,    88,    91,    67,    48,    30,    30,    30,    30,    30,
      31,    53,   113,    45,   117,   102,    29,    94,    10,    52,
      65,    66,    67,    69,    96,   101,    14,     3,    42,    31,
      87,    35,    36,    37,    38,    90,    29,    67,    67,    54,
      29,   104,   119,   120,   121,    55,   108,    96,    31,    93,
      65,    66,     3,     4,     5,     6,     7,     8,    41,    62,
      63,   122,   122,    46,   100,    96,    17,    88,    30,    29,
      67,    83,    29,   113,    67,    21,   122,   106,    46,   118,
      57,    56,   110,    31,    95,    94,    14,    67,    62,    67,
      96,    67,    96,   101,    99,    67,    87,    14,    65,    89,
      31,    30,    83,    48,   104,   120,    30,   121,    67,    57,
      96,    30,    93,   122,    41,   100,    14,    14,    30,    83,
      14,    30,   116,   121,   106,   122,   118,    31,    41,   107,
      67,    95,    67,    96,    67,    14,    53,   111,   112,    46,
     115,    30,   104,   120,    67,    67,    22,    23,    31,    41,
     109,    41,    54,    67,   121,   106,    41,   107,   107,   109,
     109,    67,    67,    67,    48,   115,    30,    67,    22,    23,
      41,   109,    22,    23,   109,   116,   107,   109,   109,    67,
     109,   109,   112,    22,    23,   109,   109,   109
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    71,    72,    72,    73,    73,    73,    73,    73,    73,
      73,    73,    73,    73,    73,    73,    73,    73,    73,    73,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    83,    84,    84,    85,    86,    87,    87,    88,    88,
      89,    90,    90,    90,    90,    91,    92,    93,    93,    94,
      95,    95,    96,    96,    96,    96,    96,    96,    97,    98,
      99,    99,   100,   100,   101,   101,   101,   101,   101,   101,
     101,   102,   102,   103,   104,   104,   104,   104,   104,   104,
     104,   104,   104,   104,   104,   104,   104,   104,   104,   104,
     104,   104,   104,   105,   106,   107,   107,   107,   108,   108,
     108,   109,   109,   109,   109,   109,   109,   109,   110,   110,
     110,   110,   110,   110,   110,   111,   111,   112,   112,   113,
     113,   114,   114,   115,   115,   116,   117,   117,   118,   118,
     119,   120,   121,   121,   121,   121,   122,   122,   122,   122,
     122,   122,   122,   122,   123
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     2,     2,     2,     4,     3,     3,
       1,     3,     9,    10,     4,     8,     0,     3,     5,     2,
       1,     1,     1,     1,     1,     1,     7,     0,     3,     4,
       0,     3,     1,     1,     2,     2,     1,     1,     5,     8,
       0,     3,     0,     3,     3,     3,     3,     3,     5,     5,
       7,     0,     3,     2,     3,     1,     1,     3,     1,     1,
       2,     2,     1,     3,     4,     3,     3,     3,     3,     4,
       4,     4,     4,     3,     6,     0,     5,     3,     0,     4,
       6,     0,     6,     4,     5,     3,     6,     4,     0,     7,
       5,     7,     5,     6,     4,     0,     2,     0,     5,     0,
       3,     2,     7,     0,     3,     2,     0,     2,     0,     3,
       2,     2,     3,     5,     5,     7,     1,     1,     1,     1,
       1,     1,     1,     2,     8
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
#line 221 "yacc_sql.y" /* yacc.c:1652  */
    {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1611 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 22:
#line 226 "yacc_sql.y" /* yacc.c:1652  */
    {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1619 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 23:
#line 231 "yacc_sql.y" /* yacc.c:1652  */
    {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1627 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 24:
#line 237 "yacc_sql.y" /* yacc.c:1652  */
    {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1635 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 25:
#line 243 "yacc_sql.y" /* yacc.c:1652  */
    {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1643 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 26:
#line 249 "yacc_sql.y" /* yacc.c:1652  */
    {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1651 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 27:
#line 255 "yacc_sql.y" /* yacc.c:1652  */
    {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1660 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 28:
#line 261 "yacc_sql.y" /* yacc.c:1652  */
    {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1668 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 29:
#line 267 "yacc_sql.y" /* yacc.c:1652  */
    {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1677 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 30:
#line 274 "yacc_sql.y" /* yacc.c:1652  */
    {
        create_index_append_attr(&CONTEXT->ssql->sstr.create_index, (yyvsp[0].string));
    }
#line 1685 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 31:
#line 278 "yacc_sql.y" /* yacc.c:1652  */
    {
        create_index_append_attr(&CONTEXT->ssql->sstr.create_index, (yyvsp[-2].string));
    }
#line 1693 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 32:
#line 284 "yacc_sql.y" /* yacc.c:1652  */
    {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-6].string), (yyvsp[-4].string), 0);
		}
#line 1702 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 33:
#line 289 "yacc_sql.y" /* yacc.c:1652  */
    {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-6].string), (yyvsp[-4].string), 1);
		}
#line 1711 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 34:
#line 297 "yacc_sql.y" /* yacc.c:1652  */
    {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1720 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 35:
#line 304 "yacc_sql.y" /* yacc.c:1652  */
    {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1732 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 37:
#line 314 "yacc_sql.y" /* yacc.c:1652  */
    {    }
#line 1738 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 38:
#line 319 "yacc_sql.y" /* yacc.c:1652  */
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
#line 1753 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 39:
#line 330 "yacc_sql.y" /* yacc.c:1652  */
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
#line 1768 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 40:
#line 342 "yacc_sql.y" /* yacc.c:1652  */
    {(yyval.number) = (yyvsp[0].number);}
#line 1774 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 41:
#line 345 "yacc_sql.y" /* yacc.c:1652  */
    { (yyval.number)=INTS; }
#line 1780 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 42:
#line 346 "yacc_sql.y" /* yacc.c:1652  */
    { (yyval.number)=CHARS; }
#line 1786 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 43:
#line 347 "yacc_sql.y" /* yacc.c:1652  */
    { (yyval.number)=FLOATS; }
#line 1792 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 44:
#line 348 "yacc_sql.y" /* yacc.c:1652  */
    {(yyval.number)=DATES;}
#line 1798 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 45:
#line 352 "yacc_sql.y" /* yacc.c:1652  */
    {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1807 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 46:
#line 361 "yacc_sql.y" /* yacc.c:1652  */
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
#line 1826 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 48:
#line 377 "yacc_sql.y" /* yacc.c:1652  */
    {
    }
#line 1833 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 49:
#line 381 "yacc_sql.y" /* yacc.c:1652  */
    {
        CONTEXT->value_lengths[CONTEXT->record_length] = CONTEXT->value_length;
        record_init_from_values(&CONTEXT->record_values[CONTEXT->record_length++], CONTEXT->values, CONTEXT->value_length);
        CONTEXT->value_length = 0;
      }
#line 1843 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 51:
#line 389 "yacc_sql.y" /* yacc.c:1652  */
    { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1851 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 52:
#line 394 "yacc_sql.y" /* yacc.c:1652  */
    {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 1859 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 53:
#line 397 "yacc_sql.y" /* yacc.c:1652  */
    {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 1867 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 54:
#line 400 "yacc_sql.y" /* yacc.c:1652  */
    {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], -(yyvsp[0].number));
		}
#line 1875 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 55:
#line 403 "yacc_sql.y" /* yacc.c:1652  */
    {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], -(yyvsp[0].floats));
		}
#line 1883 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 56:
#line 406 "yacc_sql.y" /* yacc.c:1652  */
    {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		}
#line 1892 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 57:
#line 410 "yacc_sql.y" /* yacc.c:1652  */
    {
        value_init_NULL(&CONTEXT->values[CONTEXT->value_length++], "GAY");
    }
#line 1900 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 58:
#line 417 "yacc_sql.y" /* yacc.c:1652  */
    {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 1912 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 59:
#line 427 "yacc_sql.y" /* yacc.c:1652  */
    {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
#line 1924 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 61:
#line 437 "yacc_sql.y" /* yacc.c:1652  */
    {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 1932 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 63:
#line 443 "yacc_sql.y" /* yacc.c:1652  */
    {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 1940 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 64:
#line 449 "yacc_sql.y" /* yacc.c:1652  */
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
#line 1965 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 65:
#line 470 "yacc_sql.y" /* yacc.c:1652  */
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
#line 1989 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 66:
#line 490 "yacc_sql.y" /* yacc.c:1652  */
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
#line 2013 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 67:
#line 510 "yacc_sql.y" /* yacc.c:1652  */
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
#line 2039 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 68:
#line 532 "yacc_sql.y" /* yacc.c:1652  */
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
#line 2064 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 69:
#line 553 "yacc_sql.y" /* yacc.c:1652  */
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
#line 2089 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 70:
#line 574 "yacc_sql.y" /* yacc.c:1652  */
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
#line 2112 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 72:
#line 595 "yacc_sql.y" /* yacc.c:1652  */
    {
        selects_append_attribute(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num], (yyvsp[-1].expression1));
    }
#line 2120 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 73:
#line 601 "yacc_sql.y" /* yacc.c:1652  */
    {
        selects_append_attribute(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num], (yyvsp[-1].expression1));
    }
#line 2128 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 74:
#line 606 "yacc_sql.y" /* yacc.c:1652  */
    {
        RelAttr attr;
        relation_attr_init(&attr, (yyvsp[-2].string), "*");
        Expression exp_leaf;
        expression_init_leaf_attr(&exp_leaf, &attr);
        CONTEXT->exp_array[CONTEXT->exp_num++] = exp_leaf;
        (yyval.expression1) = &CONTEXT->exp_array[CONTEXT->exp_num - 1];
    }
#line 2141 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 75:
#line 614 "yacc_sql.y" /* yacc.c:1652  */
    {
        RelAttr attr;
        relation_attr_init(&attr, NULL, "*");
        Expression exp_leaf;
        expression_init_leaf_attr(&exp_leaf, &attr);
        CONTEXT->exp_array[CONTEXT->exp_num++] = exp_leaf;
        (yyval.expression1) = &CONTEXT->exp_array[CONTEXT->exp_num - 1];
    }
#line 2154 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 76:
#line 622 "yacc_sql.y" /* yacc.c:1652  */
    {
        RelAttr attr;
        relation_attr_init(&attr, NULL, (yyvsp[0].string));
        Expression exp_leaf;
        expression_init_leaf_attr(&exp_leaf, &attr);
        CONTEXT->exp_array[CONTEXT->exp_num++] = exp_leaf;
        (yyval.expression1) = &CONTEXT->exp_array[CONTEXT->exp_num - 1];
    }
#line 2167 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 77:
#line 630 "yacc_sql.y" /* yacc.c:1652  */
    {
        RelAttr attr;
        relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
        Expression exp_leaf;
        expression_init_leaf_attr(&exp_leaf, &attr);
        CONTEXT->exp_array[CONTEXT->exp_num++] = exp_leaf;
        (yyval.expression1) = &CONTEXT->exp_array[CONTEXT->exp_num - 1];
    }
#line 2180 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 78:
#line 638 "yacc_sql.y" /* yacc.c:1652  */
    {
        value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
        Value *value = &CONTEXT->values[CONTEXT->value_length - 1];
        Expression exp_leaf;
        expression_init_leaf(&exp_leaf, value);
        CONTEXT->exp_array[CONTEXT->exp_num++] = exp_leaf;
        (yyval.expression1) = &CONTEXT->exp_array[CONTEXT->exp_num - 1];
    }
#line 2193 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 79:
#line 646 "yacc_sql.y" /* yacc.c:1652  */
    {
        value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
        Value *value = &CONTEXT->values[CONTEXT->value_length - 1];
        Expression exp_leaf;
        expression_init_leaf(&exp_leaf, value);
        CONTEXT->exp_array[CONTEXT->exp_num++] = exp_leaf;
        (yyval.expression1) = &CONTEXT->exp_array[CONTEXT->exp_num - 1];
    }
#line 2206 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 80:
#line 654 "yacc_sql.y" /* yacc.c:1652  */
    {
        value_init_integer(&CONTEXT->values[CONTEXT->value_length++], -(yyvsp[0].number));
        Value *value = &CONTEXT->values[CONTEXT->value_length - 1];
        Expression exp_leaf;
        expression_init_leaf(&exp_leaf, value);
        CONTEXT->exp_array[CONTEXT->exp_num++] = exp_leaf;
        (yyval.expression1) = &CONTEXT->exp_array[CONTEXT->exp_num - 1];
    }
#line 2219 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 81:
#line 662 "yacc_sql.y" /* yacc.c:1652  */
    {
        value_init_float(&CONTEXT->values[CONTEXT->value_length++], -(yyvsp[0].floats));
        Value *value = &CONTEXT->values[CONTEXT->value_length - 1];
        Expression exp_leaf;
        expression_init_leaf(&exp_leaf, value);
        CONTEXT->exp_array[CONTEXT->exp_num++] = exp_leaf;
        (yyval.expression1) = &CONTEXT->exp_array[CONTEXT->exp_num - 1];
    }
#line 2232 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 82:
#line 670 "yacc_sql.y" /* yacc.c:1652  */
    {
        (yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
        value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
        Value *value = &CONTEXT->values[CONTEXT->value_length - 1];
        Expression exp_leaf;
        expression_init_leaf(&exp_leaf, value);
        CONTEXT->exp_array[CONTEXT->exp_num++] = exp_leaf;
        (yyval.expression1) = &CONTEXT->exp_array[CONTEXT->exp_num - 1];
    }
#line 2246 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 83:
#line 679 "yacc_sql.y" /* yacc.c:1652  */
    {
        Expression exp_node;
        expression_init_node(&exp_node, (yyvsp[-1].expression1),NULL,CAL_SELF);
        CONTEXT->exp_array[CONTEXT->exp_num++] = exp_node;
        (yyval.expression1) = &CONTEXT->exp_array[CONTEXT->exp_num - 1];
        //show_expression(&CONTEXT->exp_array[(CONTEXT->exp_num) - 1]);
    }
#line 2258 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 84:
#line 686 "yacc_sql.y" /* yacc.c:1652  */
    {
    
        Expression exp_node;
        expression_init_node(&exp_node, (yyvsp[-1].expression1),NULL,CAL_MINUS);
        CONTEXT->exp_array[CONTEXT->exp_num++] = exp_node;
        (yyval.expression1) = &CONTEXT->exp_array[CONTEXT->exp_num - 1];
        //show_expression(&CONTEXT->exp_array[(CONTEXT->exp_num) - 1]);
    }
#line 2271 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 85:
#line 694 "yacc_sql.y" /* yacc.c:1652  */
    {
        Expression exp_node;
        expression_init_node(&exp_node, (yyvsp[-2].expression1), (yyvsp[0].expression1), CAL_ADD);
        CONTEXT->exp_array[CONTEXT->exp_num++] = exp_node;
        (yyval.expression1) = &CONTEXT->exp_array[CONTEXT->exp_num - 1];
        
    }
#line 2283 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 86:
#line 701 "yacc_sql.y" /* yacc.c:1652  */
    {
        Expression exp_node;
        expression_init_node(&exp_node, (yyvsp[-2].expression1), (yyvsp[0].expression1), CAL_SUB);
        CONTEXT->exp_array[CONTEXT->exp_num++] = exp_node;
        (yyval.expression1) = &CONTEXT->exp_array[CONTEXT->exp_num - 1];
        //show_expression(&CONTEXT->exp_array[(CONTEXT->exp_num) - 1]);
    }
#line 2295 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 87:
#line 708 "yacc_sql.y" /* yacc.c:1652  */
    {
        Expression exp_node;
        expression_init_node(&exp_node, (yyvsp[-2].expression1), (yyvsp[0].expression1), CAL_MUL);
        CONTEXT->exp_array[CONTEXT->exp_num++] = exp_node;
        (yyval.expression1) = &CONTEXT->exp_array[CONTEXT->exp_num - 1];
        //show_expression(&CONTEXT->exp_array[(CONTEXT->exp_num) - 1]);
    }
#line 2307 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 88:
#line 715 "yacc_sql.y" /* yacc.c:1652  */
    {
        Expression exp_node;
        expression_init_node(&exp_node, (yyvsp[-2].expression1), (yyvsp[0].expression1), CAL_DIV);
        CONTEXT->exp_array[CONTEXT->exp_num++] = exp_node;
        (yyval.expression1) = &CONTEXT->exp_array[CONTEXT->exp_num - 1];
        //show_expression(&CONTEXT->exp_array[(CONTEXT->exp_num) - 1]);
    }
#line 2319 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 89:
#line 722 "yacc_sql.y" /* yacc.c:1652  */
    {
        Expression exp_node;
        expression_init_node(&exp_node, (yyvsp[-1].expression1), NULL, CAL_COUNT);
        CONTEXT->exp_array[CONTEXT->exp_num++] = exp_node;
        (yyval.expression1) = &CONTEXT->exp_array[CONTEXT->exp_num - 1];
        //show_expression(&CONTEXT->exp_array[(CONTEXT->exp_num) - 1]);
    }
#line 2331 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 90:
#line 729 "yacc_sql.y" /* yacc.c:1652  */
    {
        Expression exp_node;
        expression_init_node(&exp_node, (yyvsp[-1].expression1), NULL, CAL_MAX);
        CONTEXT->exp_array[CONTEXT->exp_num++] = exp_node;
        (yyval.expression1) = &CONTEXT->exp_array[CONTEXT->exp_num - 1];
        //show_expression(&CONTEXT->exp_array[(CONTEXT->exp_num) - 1]);
    }
#line 2343 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 91:
#line 736 "yacc_sql.y" /* yacc.c:1652  */
    {
        Expression exp_node;
        expression_init_node(&exp_node, (yyvsp[-1].expression1), NULL, CAL_MIN);
        CONTEXT->exp_array[CONTEXT->exp_num++] = exp_node;
        (yyval.expression1) = &CONTEXT->exp_array[CONTEXT->exp_num - 1];
        //show_expression(&CONTEXT->exp_array[(CONTEXT->exp_num) - 1]);
    }
#line 2355 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 92:
#line 743 "yacc_sql.y" /* yacc.c:1652  */
    {
        Expression exp_node;
        expression_init_node(&exp_node, (yyvsp[-1].expression1), NULL, CAL_AVG);
        CONTEXT->exp_array[CONTEXT->exp_num++] = exp_node;
        (yyval.expression1) = &CONTEXT->exp_array[CONTEXT->exp_num - 1];
        //show_expression(&CONTEXT->exp_array[(CONTEXT->exp_num) - 1]);
    }
#line 2367 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 93:
#line 753 "yacc_sql.y" /* yacc.c:1652  */
    {
        CONTEXT->ssql->flag=SCF_SELECT;
        
        //CONTEXT->condition_length=0;
        //CONTEXT->from_length=0;
        //CONTEXT->select_length=0;
        //CONTEXT->value_length = 0;
    }
#line 2380 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 94:
#line 764 "yacc_sql.y" /* yacc.c:1652  */
    {
        (yyval.selects1) = &CONTEXT->ssql->sstr.selection[CONTEXT->select_num];
    }
#line 2388 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 96:
#line 769 "yacc_sql.y" /* yacc.c:1652  */
    {
        group_by_append_relattr(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num].group_by, (yyvsp[-3].string), (yyvsp[-1].string));
    }
#line 2396 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 97:
#line 772 "yacc_sql.y" /* yacc.c:1652  */
    {
        group_by_append_relattr(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num].group_by, NULL, (yyvsp[-1].string));
    }
#line 2404 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 99:
#line 776 "yacc_sql.y" /* yacc.c:1652  */
    {
        group_by_append_relattr(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num].group_by, NULL, (yyvsp[-1].string));
    }
#line 2412 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 100:
#line 779 "yacc_sql.y" /* yacc.c:1652  */
    {
        group_by_append_relattr(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num].group_by, (yyvsp[-3].string), (yyvsp[-1].string));
    }
#line 2420 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 102:
#line 784 "yacc_sql.y" /* yacc.c:1652  */
    {
        order_by_append_relattr(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num].order_by, (yyvsp[-4].string), (yyvsp[-2].string), 1);
    }
#line 2428 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 103:
#line 787 "yacc_sql.y" /* yacc.c:1652  */
    {
        order_by_append_relattr(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num].order_by, NULL, (yyvsp[-2].string), 1);
    }
#line 2436 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 104:
#line 790 "yacc_sql.y" /* yacc.c:1652  */
    {
        order_by_append_relattr(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num].order_by, (yyvsp[-3].string), (yyvsp[-1].string), 1);
    }
#line 2444 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 105:
#line 793 "yacc_sql.y" /* yacc.c:1652  */
    {
        order_by_append_relattr(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num].order_by, NULL, (yyvsp[-1].string), 1);
    }
#line 2452 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 106:
#line 796 "yacc_sql.y" /* yacc.c:1652  */
    {
        order_by_append_relattr(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num].order_by, (yyvsp[-4].string), (yyvsp[-2].string), 0);
    }
#line 2460 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 107:
#line 799 "yacc_sql.y" /* yacc.c:1652  */
    {
        order_by_append_relattr(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num].order_by, NULL, (yyvsp[-2].string), 0);
    }
#line 2468 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 109:
#line 805 "yacc_sql.y" /* yacc.c:1652  */
    {
        order_by_append_relattr(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num].order_by, (yyvsp[-4].string), (yyvsp[-2].string), 1);
    }
#line 2476 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 110:
#line 808 "yacc_sql.y" /* yacc.c:1652  */
    {
        order_by_append_relattr(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num].order_by, NULL, (yyvsp[-2].string), 1);
    }
#line 2484 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 111:
#line 811 "yacc_sql.y" /* yacc.c:1652  */
    {
        order_by_append_relattr(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num].order_by, (yyvsp[-4].string), (yyvsp[-2].string), 0);
    }
#line 2492 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 112:
#line 814 "yacc_sql.y" /* yacc.c:1652  */
    {
        order_by_append_relattr(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num].order_by, NULL, (yyvsp[-2].string), 0);
    }
#line 2500 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 113:
#line 817 "yacc_sql.y" /* yacc.c:1652  */
    {
        order_by_append_relattr(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num].order_by, (yyvsp[-3].string), (yyvsp[-1].string), 1);
    }
#line 2508 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 114:
#line 820 "yacc_sql.y" /* yacc.c:1652  */
    {
        order_by_append_relattr(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num].order_by, NULL, (yyvsp[-1].string), 1);
    }
#line 2516 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 116:
#line 826 "yacc_sql.y" /* yacc.c:1652  */
    {
        select_join_num_change(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num],1);
    }
#line 2524 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 118:
#line 832 "yacc_sql.y" /* yacc.c:1652  */
    {
        select_join_append_relation(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num], (yyvsp[-3].string));
        select_join_num_change(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num],0);
    }
#line 2533 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 120:
#line 837 "yacc_sql.y" /* yacc.c:1652  */
    {	
        selects_append_relation(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num], (yyvsp[-1].string));
    }
#line 2541 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 121:
#line 842 "yacc_sql.y" /* yacc.c:1652  */
    {
        selects_append_relation(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num], (yyvsp[-1].string));
    }
#line 2549 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 122:
#line 845 "yacc_sql.y" /* yacc.c:1652  */
    {
        selects_append_relation(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num], (yyvsp[-6].string));
        select_join_append_relation(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num], (yyvsp[-3].string));
    }
#line 2558 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 124:
#line 853 "yacc_sql.y" /* yacc.c:1652  */
    {
        select_join_append_condition(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num], (yyvsp[-1].Condition_Composite1));
    }
#line 2566 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 125:
#line 860 "yacc_sql.y" /* yacc.c:1652  */
    {
        select_join_append_condition(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num], (yyvsp[-1].Condition_Composite1));
    }
#line 2574 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 127:
#line 868 "yacc_sql.y" /* yacc.c:1652  */
    {	
        
    }
#line 2582 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 129:
#line 874 "yacc_sql.y" /* yacc.c:1652  */
    {
        select_append_condition(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num], (yyvsp[-1].Condition_Composite1));
        //show_condition(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num]);
    }
#line 2591 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 130:
#line 882 "yacc_sql.y" /* yacc.c:1652  */
    {
        show_select_num(CONTEXT->select_num);
        select_append_condition(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num], (yyvsp[-1].Condition_Composite1));
        //show_condition(&CONTEXT->ssql->sstr.selection[CONTEXT->select_num]);
    }
#line 2601 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 131:
#line 890 "yacc_sql.y" /* yacc.c:1652  */
    {
        //show_select_num(CONTEXT->select_num);
        CONTEXT->select_stack[CONTEXT->select_stack_index++] = CONTEXT->select_num;
        CONTEXT->select_max++;
        CONTEXT->select_num = CONTEXT->select_max;
    }
#line 2612 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 132:
#line 899 "yacc_sql.y" /* yacc.c:1652  */
    {
        Condition_Composite condition_composite;
        condition_exp_exp_init(&condition_composite, (yyvsp[-2].expression1), (yyvsp[0].expression1), (yyvsp[-1].comOp));
        CONTEXT->condition_composites[CONTEXT->condition_total_num++] = condition_composite;
        
        //CONTEXT->condition_composite_num[CONTEXT->select_num]++;
        
        (yyval.Condition_Composite1) = &CONTEXT->condition_composites[CONTEXT->condition_total_num - 1];
    }
#line 2626 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 133:
#line 909 "yacc_sql.y" /* yacc.c:1652  */
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
#line 2644 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 134:
#line 923 "yacc_sql.y" /* yacc.c:1652  */
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
#line 2662 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 135:
#line 937 "yacc_sql.y" /* yacc.c:1652  */
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
#line 2683 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 136:
#line 956 "yacc_sql.y" /* yacc.c:1652  */
    { (yyval.comOp) = EQUAL_TO; }
#line 2689 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 137:
#line 957 "yacc_sql.y" /* yacc.c:1652  */
    { (yyval.comOp) = LESS_THAN; }
#line 2695 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 138:
#line 958 "yacc_sql.y" /* yacc.c:1652  */
    { (yyval.comOp) = GREAT_THAN; }
#line 2701 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 139:
#line 959 "yacc_sql.y" /* yacc.c:1652  */
    { (yyval.comOp) = LESS_EQUAL; }
#line 2707 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 140:
#line 960 "yacc_sql.y" /* yacc.c:1652  */
    { (yyval.comOp) = GREAT_EQUAL; }
#line 2713 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 141:
#line 961 "yacc_sql.y" /* yacc.c:1652  */
    { (yyval.comOp) = NOT_EQUAL; }
#line 2719 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 142:
#line 962 "yacc_sql.y" /* yacc.c:1652  */
    {(yyval.comOp) = ATTR_IN;}
#line 2725 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 143:
#line 963 "yacc_sql.y" /* yacc.c:1652  */
    {(yyval.comOp) = ATTR_NOT_IN;}
#line 2731 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;

  case 144:
#line 968 "yacc_sql.y" /* yacc.c:1652  */
    {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2740 "yacc_sql.tab.c" /* yacc.c:1652  */
    break;


#line 2744 "yacc_sql.tab.c" /* yacc.c:1652  */
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
#line 974 "yacc_sql.y" /* yacc.c:1918  */


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

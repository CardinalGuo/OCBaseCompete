/* A Bison parser, made by GNU Bison 3.3.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

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
#line 163 "yacc_sql.y" /* yacc.c:1921  */

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

#line 145 "yacc_sql.tab.h" /* yacc.c:1921  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (void *scanner);

#endif /* !YY_YY_YACC_SQL_TAB_H_INCLUDED  */

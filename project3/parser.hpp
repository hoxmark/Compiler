/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
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
    T_PRINT = 258,
    T_RETURN = 259,
    T_IF = 260,
    T_ELSE = 261,
    T_WHILE = 262,
    T_NEW = 263,
    T_INTEGER = 264,
    T_BOOLEAN = 265,
    T_NONE = 266,
    T_EQUALS = 267,
    T_AND = 268,
    T_OR = 269,
    T_NOT = 270,
    T_TRUE = 271,
    T_FALSE = 272,
    T_EXTENDS = 273,
    T_REPEAT = 274,
    T_UNTIL = 275,
    T_EOF = 276,
    T_NEWLN = 277,
    T_LC = 278,
    T_RC = 279,
    T_LP = 280,
    T_RP = 281,
    T_PLUS = 282,
    T_MINUS = 283,
    T_DIVIDE = 284,
    T_MULTIPLY = 285,
    T_LESS = 286,
    T_LESSOREQUAL = 287,
    T_COMMA = 288,
    T_LITERAL = 289,
    T_DOT = 290,
    T_SEMICOL = 291,
    T_FUNC = 292,
    T_COLON = 293,
    T_ID = 294,
    T_ASSIGN = 295,
    T_UNARYMINUS = 296
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 61 "parser.y" /* yacc.c:1909  */

	int ival;
	char *sval;

#line 101 "parser.hpp" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_HPP_INCLUDED  */

/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     T_PRINT = 258,
     T_RETURN = 259,
     T_IF = 260,
     T_UNARYMINUS = 261,
     T_ELSE = 262,
     T_WHILE = 263,
     T_NEW = 264,
     T_INTEGER = 265,
     T_BOOLEAN = 266,
     T_NONE = 267,
     T_EQUALS = 268,
     T_AND = 269,
     T_OR = 270,
     T_NOT = 271,
     T_TRUE = 272,
     T_FALSE = 273,
     T_EXTENDS = 274,
     T_REPEAT = 275,
     T_UNTIL = 276,
     T_EOF = 277,
     T_NEWLN = 278,
     T_LC = 279,
     T_RC = 280,
     T_LP = 281,
     T_RP = 282,
     T_PLUS = 283,
     T_MINUS = 284,
     T_DIVIDE = 285,
     T_MULTIPLY = 286,
     T_LESS = 287,
     T_LESSOREQUAL = 288,
     T_COMMA = 289,
     T_LITERAL = 290,
     T_DOT = 291,
     T_SEMICOL = 292,
     T_FUNC = 293,
     T_COLON = 294,
     T_ID = 295,
     T_ASSIGN = 296
   };
#endif
/* Tokens.  */
#define T_PRINT 258
#define T_RETURN 259
#define T_IF 260
#define T_UNARYMINUS 261
#define T_ELSE 262
#define T_WHILE 263
#define T_NEW 264
#define T_INTEGER 265
#define T_BOOLEAN 266
#define T_NONE 267
#define T_EQUALS 268
#define T_AND 269
#define T_OR 270
#define T_NOT 271
#define T_TRUE 272
#define T_FALSE 273
#define T_EXTENDS 274
#define T_REPEAT 275
#define T_UNTIL 276
#define T_EOF 277
#define T_NEWLN 278
#define T_LC 279
#define T_RC 280
#define T_LP 281
#define T_RP 282
#define T_PLUS 283
#define T_MINUS 284
#define T_DIVIDE 285
#define T_MULTIPLY 286
#define T_LESS 287
#define T_LESSOREQUAL 288
#define T_COMMA 289
#define T_LITERAL 290
#define T_DOT 291
#define T_SEMICOL 292
#define T_FUNC 293
#define T_COLON 294
#define T_ID 295
#define T_ASSIGN 296




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;


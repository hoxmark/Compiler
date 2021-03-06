%option yylineno
%pointer

%{
    #include <stdlib.h>
    #include <errno.h>
    #include <limits.h>
    #include "ast.hpp"
    #include "parser.hpp"

    #include <cstdlib>
    #include <cerrno>
    #include <climits>
    #include <cstdio>
    #include <iostream>
    using namespace std;
    
	  void yyerror(const char *);
	  void printOut(const char *);
    int numLine = 0;
    int numChar = 0; 
%}

/* WRITEME: Copy any definitions and start conditions from Project 3 here */
%x COMMENT

%%

  /* WRITEME: Copy your Flex rules from Project 3 here */

"/*"         BEGIN(COMMENT);


<COMMENT>[^*\n]*        /* Taken from the given flex documentation. 
                          eat anything that's not a '*' */
<COMMENT>"*"+[^*/\n]*   /* eat up '*'s not followed by '/'s */
<COMMENT>\n             
<COMMENT>"*"+"/"        BEGIN(INITIAL);
<COMMENT><<EOF>>       {yyerror("EOF in Comment");}

[ \t\n]+                /* eat up whitespace */
"print"                {printOut("print");return T_PRINT;}
"return"               {printOut("return"); return T_RETURN;}
"if"                   {printOut("if"); return T_IF;}
"else"                 {printOut("else"); return T_ELSE;}
"while"                {printOut("while"); return T_WHILE;}
"new"                  {printOut("new"); return T_NEW;}
"integer"              {printOut("integer"); return T_INTEGER;}
"boolean"              {printOut("boolean"); return T_BOOLEAN;}
"none"                 {printOut("none"); return T_NONE;}
"equals"               {printOut("equals"); return T_EQUALS;}
"and"                  {printOut("and"); return T_AND;}
"or"                   {printOut("or"); return T_OR;}
"not"                  {printOut("not"); return T_NOT;}
"true"                 {printOut("true"); yylval.base_int = 1; return T_TRUE;}
"false"                {printOut("false"); yylval.base_int = 0; return T_FALSE;}
"extends"              {printOut("extends"); return T_EXTENDS;}
"repeat"               {printOut("repeat"); return T_REPEAT;}
"until"                {printOut("until"); return T_UNTIL;}

"{"                    {printOut("{"); return T_LC;}
"}"                    {printOut("}"); return T_RC;}
"("                    {printOut("("); return T_LP;}
")"                    {printOut(")"); return T_RP;}
"+"                    {printOut("+"); return T_PLUS;}
"/"                    {printOut("/"); return T_DIVIDE;}
"-"                    {printOut("-"); return T_MINUS;}
"*"                    {printOut("*"); return T_MULTIPLY;}
"."                    {printOut("."); return T_DOT;}
";"                    {printOut(";"); return T_SEMICOL;}
"->"                   {printOut("->" ); return T_FUNC;}
":"                    {printOut(":" ); return T_COLON;}
","                    {printOut("," ); return T_COMMA;}
"="                    {printOut("=" ); return T_ASSIGN;}
"<"                    {printOut("<" ); return T_LESS;}
"<="                   {printOut("<=" ); return T_LESSOREQUAL;}

                      
[1-9][0-9]*|0         {printOut("ITERAL:"); yylval.base_int  = atoi(yytext); return T_LITERAL;}

[a-zA-Z][a-zA-Z0-9]*  {printOut("ID:" ); yylval.base_char_ptr = yytext; char *key = (char*)malloc(yyleng * sizeof(char)); strcpy(key, yytext); yylval.base_char_ptr = key; return T_ID;}                     


.                   {yyerror("invalid character"); } 

%%

int yywrap(void) {
  return 1;
}

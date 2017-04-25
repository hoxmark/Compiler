%option yylineno
%pointer

%{
    #include <cstdlib>
    #include <cerrno>
    #include <climits>
    #include <limits>
    #include "parser.hpp"
    #include <cstdio>
    #include <iostream>
    using namespace std;
    
	void yyerror(const char *);
	void printOut(const char *);
  int numLine = 0;
  int numChar = 0; 
  
%}


/* WRITEME: Write any definitions here. You can find information on
            definitions here:
            ftp://ftp.gnu.org/old-gnu/Manuals/flex-2.5.4/html_mono/flex.html#SEC10 */

DIGIT    [0-9]


/* WRITEME: If you are going to use start conditions, write them here.
            You can find more information on start conditions here:
            ftp://ftp.gnu.org/old-gnu/Manuals/flex-2.5.4/html_mono/flex.html#SEC11
            You will probably want to use exclusive conditions rather
            than inclusive conditions (use the %x instead of the %s). */



%x COMMENT
%%

"/*"         BEGIN(COMMENT);


<COMMENT>[^*\n]*        /* Taken from the given documentation. eat anything that's not a '*' */
<COMMENT>"*"+[^*/\n]*   /* eat up '*'s not followed by '/'s */
<COMMENT>\n             ++numLine;
<COMMENT>"*"+"/"        BEGIN(INITIAL);
  /* WRITEME: Write your Flex token rules here */


[ \t\n]+                /* eat up whitespace */
"print"                {return T_PRINT;}
"return"               {return T_RETURN;}
"if"                   {return T_IF;}
"else"                 {return T_ELSE;}
"while"                {return T_WHILE;}
"new"                  {return T_NEW;}
"integer"              {return T_INTEGER;}
"boolean"              {return T_BOOLEAN;}
"none"                 {return T_NONE;}
"equals"               {return T_EQUALS;}
"and"                  {return T_AND;}
"or"                   {return T_OR;}
"not"                  {return T_NOT;}
"true"                 {return T_TRUE;}
"false"                {return T_FALSE;}
"extends"              {return T_EXTENDS;}
"repeat"               {return T_REPEAT;}
"until"                {return T_UNTIL;}

"{"                    {return T_LC;}
"}"                    {return T_RC;}
"("                    {return T_LP;}
")"                    {return T_RP;}

"+"                    {return T_PLUS;}
"/"                    {return T_DIVIDE;}
"-"                    {return T_MINUS;}
"*"                    {return T_MULTIPLY;}
"."                    {return T_DOT;}
"!"                    {return T_NOT;}
";"                    {return T_SEMICOL;}
"->"                   { return T_FUNC;}
":"                    { return T_COLON;}
","                    { return T_COMMA;}
"="                    { return T_EQUALS;}
"<"                    { return T_LESS;}
"<="                   { return T_LESSOREQUAL;}


[a-zA-Z][a-zA-Z0-9]*  { yylval.sval = strdup(yytext); return T_ID; } 

[1-9][0-9]*|0         { yylval.ival = atoi(yytext); return T_LITERAL;}

                    



.                   {yyerror("invalid character"); } 

%%

int yywrap(void) {
  
  return 1;
}


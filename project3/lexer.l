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
"true"                 {printOut("true"); return T_TRUE;}
"false"                {printOut("false"); return T_FALSE;}
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
"!"                    {printOut("!"); return T_NOT;}
";"                    {printOut(";"); return T_SEMICOL;}
"->"                   {printOut("->" ); return T_FUNC;}
":"                    {printOut(":" ); return T_COLON;}
","                    {printOut("," ); return T_COMMA;}
"="                    {printOut("=" ); return T_EQUALS;}

"<"                    {printOut("<" ); return T_LESS;}
"<="                   {printOut("<=" ); return T_LESSOREQUAL;}


[a-zA-Z][a-zA-Z0-9]*  {printOut("ID:" ); yylval.sval = strdup(yytext); return T_ID; } 

[1-9][0-9]*|0         {printOut("ITERAL:"); yylval.ival = atoi(yytext); return T_LITERAL;}

                    



.                   {yyerror("invalid character"); } 

%%

int yywrap(void) {
  
  return 1;
}

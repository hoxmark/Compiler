%{
    #include <cstdlib>
    #include <cstdio>
    #include <iostream>
    #include <cstdio>


    #define YYDEBUG 1

    using namespace std;
    int yylex(void);
    void yyerror(const char *);
%}

%error-verbose


/* List all your tokens here */
%token T_PRINT T_RETURN
%token T_IF
%token T_ELSE
%token T_WHILE
%token T_NEW
%token T_INTEGER
%token T_BOOLEAN
%token T_NONE
%token T_EQUALS
%token T_AND
%token T_OR
%token T_NOT
%token T_TRUE
%token T_FALSE
%token T_EXTENDS
%token T_REPEAT
%token T_UNTIL
%token <sval> T_ID
%token T_EOF
%token T_NEWLN
%token T_LC
%token T_RC
%token T_LP
%token T_RP
%token T_PLUS T_MINUS  
%token T_DIVIDE T_MULTIPLY
%token T_LESS
%token T_LESSOREQUAL
%token T_COMMA
%token <ival> T_LITERAL
%token T_DOT
%token T_SEMICOL
%token T_FUNC
%token T_COLON

%union {
	int ival;
	char *sval;
}


%left T_PLUS T_MINUS
%right T_NOT U_MINUS

%%


Expression: Expression T_PLUS Expression    {printf("+");}
        |Expression T_MULTIPLY Expression
        |Expression T_MULTIPLY Expression
        |Expression T_DIVIDE Expression
        |Expression T_LESS Expression
        |Expression T_LESSOREQUAL Expression
        |Expression T_EQUALS Expression
        |Expression T_AND Expression
        |Expression T_OR Expression
        |T_NOT Expression
        |T_MINUS Expression %prec U_MINUS
        |T_ID
        |T_ID T_DOT T_ID
        |MethodCall
        |T_LP Expression T_RP
        |T_INTEGER T_LITERAL {cout<<"he";}
        |T_TRUE
        |T_FALSE
        |T_NEW T_ID
        |T_NEW T_ID T_LP Arguments T_RP

MethodCall: T_ID T_LP Arguments T_RP
        | T_ID T_DOT T_ID T_LP Arguments T_RP

Arguments: ArgumentsP
        |
        ;

ArgumentsP: Arguments T_COMMA Expression
        | Expression

/* WRITME: Write your Bison grammar specification here */


%%

extern int yylineno;

void yyerror(const char *s) {
  fprintf(stderr, "%s at line %d\n", s, yylineno);
  exit(1);
}



%{
    #include <cstdlib>
    #include <cstdio>
    #include <iostream>
    #include <cstdio>
    #include <vector>
    #include <string>
    #include <map>


    #define YYDEBUG 1

    using namespace std;
    int yylex(void);
    void yyerror(const char *);
    void printOut(const char *);
    
    vector<string> a;
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
%token T_EOF
%token T_NEWLN
%token T_LC
%token T_RC
%token T_LP
%token T_RP
%token T_PLUS T_MINUS  
%token T_UNARYMINUS  
%token T_DIVIDE T_MULTIPLY
%token T_LESS
%token T_LESSOREQUAL
%token T_COMMA
%token <ival> T_LITERAL
%token T_DOT
%token T_SEMICOL
%token T_FUNC
%token T_COLON
%token <sval> T_ID

%union {
	int ival;
	char *sval;
}

%left T_PLUS T_MINUS
%left T_DIVIDE T_MULTIPLY
%right T_NOT T_UNARYMINUS


%%

Start: Classes                       
    ;

Classes: Classes Class                
        | Class                       
        ;

Class:  ClassId T_LC MethodsAndMembers T_RC 
        | ClassId T_EXTENDS T_ID T_LC MethodsAndMembers T_RC 
        ;

MethodsAndMembers: MethodsAndMembers Member  
        | MethodsAndMembers Method
        | Zero_Or_More_Members Zero_Or_More_Methods
        | %empty
        ; 

ClassId: T_ID    
        ;

Zero_Or_More_Members: Zero_Or_More_Members Member
        | %empty
        ;

Member: Type T_ID T_SEMICOL
        ;

Type: T_INTEGER                 {printOut("Type Inte");}
        | T_BOOLEAN             {printOut("Type bool");}
        | T_NONE                {printOut("Type None");}
        | T_ID                  {printOut("Type T_ID");}
        ;

Zero_Or_More_Methods: Zero_Or_More_Methods Method
        |%empty
        ;

Method: T_ID T_LP Zero_Or_More_Parameters T_RP T_FUNC Type T_LC Body T_RC  {printOut("METHOD \n");}
        ; 
 

Zero_Or_More_Parameters: Zero_Or_More_Parameters Parameter  {printOut("Zero or More Para \n");}
        |%empty
        ;

Parameter: T_ID T_COLON Type                        {printOut("Parameter1 \n");}
        | T_ID T_COLON Type T_COMMA Parameter       {printOut("Parameter2 \n");}
        ; 
  
Body: BodyDecStat ReturnStatement {printOut("BODY \n");}
        | %empty
        ; 

BodyDecStat:BodyDecStat Declaration 
        |BodyDecStat Statement
        | %empty
        ;

Declaration: Type IDS T_SEMICOL  {printOut("DEC 1\n");}
        ;

IDS:  T_ID
        | IDS T_COMMA T_ID
        ;


ReturnStatement: T_RETURN Expression T_SEMICOL
        |%empty
        ; 

One_Or_More_Statements: One_Or_More_Statements Statement 
        | Statement
        ;

Statement: Assignment
        |MethodCalling
        |Expression
        |IfElse
        |WhileLoop
        |RepeatUntil
        |Print
        ;

Assignment: T_ID T_EQUALS Expression T_SEMICOL {printOut("ASSIGNMENT OK  1");}
        | T_ID T_DOT T_ID T_EQUALS Expression T_SEMICOL
        ;

MethodCalling: MethodCall T_SEMICOL
        ;

IfElse: T_IF Expression T_LC Block T_RC
        | T_IF Expression T_LC Block T_RC T_ELSE T_LC Block T_RC
        ;

WhileLoop: T_WHILE Expression T_LC Block T_RC
        ;

RepeatUntil: T_REPEAT T_LC Block T_RC T_UNTIL T_LP Expression T_RP T_SEMICOL
        ;

Block: One_Or_More_Statements
        ;
Print: T_PRINT Expression T_SEMICOL
        ;

Expression: Expression T_PLUS Expression   
        |Expression T_MINUS Expression  
        |Expression T_MULTIPLY Expression 
        |Expression T_DIVIDE Expression 
        |Expression T_LESS Expression 
        |Expression T_LESSOREQUAL Expression 
        |Expression T_EQUALS Expression 
        |Expression T_AND Expression 
        |Expression T_OR Expression 
        |T_NOT Expression 
        |T_UNARYMINUS Expression %prec T_UNARYMINUS
        |T_ID 
        |T_ID T_DOT T_ID 
        |MethodCall 
        |T_LP Expression T_RP 
        |T_LITERAL  
        |T_TRUE 
        |T_FALSE 
        |T_NEW T_ID 
        |T_NEW T_ID T_LP Arguments T_RP 
        ;

MethodCall: T_ID T_LP Arguments T_RP
        | T_ID T_DOT T_ID T_LP Arguments T_RP
        ;
Arguments: ArgumentsP
        |%empty
        ;

ArgumentsP: Arguments T_COMMA Expression
        | Expression
        ;


%%

extern int yylineno;

void yyerror(const char *s) {
  fprintf(stderr, "%s at line %d\n", s, yylineno);
  exit(1);
}

void printOut(const char *s) {
//   fprintf(stderr, "printOut: %s at line %d\n", s, yylineno);  
}



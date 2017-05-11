%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <iostream>

    #include "ast.hpp"
    
    using namespace std;
    #define YYDEBUG 1
    int yylex(void);
    void yyerror(const char *);
    void printOut(const char *);
    
    extern ASTNode* astRoot; 

    
%}


%error-verbose


/* List all your tokens here */ 
%token T_PRINT T_RETURN
%token T_IF
%token T_UNARYMINUS
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
%token T_DIVIDE T_MULTIPLY
%token T_LESS
%token T_LESSOREQUAL
%token T_COMMA
%token T_LITERAL
%token T_DOT
%token T_SEMICOL
%token T_FUNC
%token T_COLON
%token T_ID
%token T_ASSIGN


%type <expression_ptr> Expression
%type <methodcall_ptr> MethodCall

%type <base_int> T_LITERAL 
%type <base_int> T_TRUE 
%type <base_int> T_FALSE 
%type <base_char_ptr> T_ID



%left T_OR 
%left T_AND
%left T_LESS T_LESSOREQUAL T_EQUALS
%left T_PLUS T_MINUS
%left T_DIVIDE T_MULTIPLY
%right T_NOT T_UNARYMINUS

%%

Start: Classes                       
    ;

Classes: Classes Class                
        | Class                       
        ;

Class:  T_ID T_LC MethodsAndMembers T_RC 
        | T_ID T_EXTENDS T_ID T_LC MethodsAndMembers T_RC 
        ;

MethodsAndMembers: One_Or_More_Members
        | One_Or_More_Methods
        | One_Or_More_Members One_Or_More_Methods
        | 
        ; 

One_Or_More_Members: One_Or_More_Members Member 
        | Member
        ;

One_Or_More_Methods: One_Or_More_Methods Method 
        | Method
        ;

Member: Type T_ID T_SEMICOL
        ;

Type: T_INTEGER                 {printOut("Type Inte");}
        | T_BOOLEAN             {printOut("Type bool");}
        | T_NONE                {printOut("Type None");}
        | T_ID                  {printOut("Type T_ID");}
        ;

Method: T_ID T_LP Zero_Or_More_Parameters T_RP T_FUNC Type T_LC BodyDecStat ReturnStatement T_RC  {printOut("METHOD \n");}
        ; 
 

Zero_Or_More_Parameters: Zero_Or_More_Parameters Parameter  {printOut("Zero or More Para \n");}
        | 
        ;

Parameter: T_ID T_COLON Type                        {printOut("Parameter1 \n");}
        | T_ID T_COLON Type T_COMMA Parameter       {printOut("Parameter2 \n");}
        ; 
  
BodyDecStat: One_Or_More_Declarations 
        | One_Or_More_Statements
        | One_Or_More_Declarations One_Or_More_Statements
        | 
        ;

 One_Or_More_Declarations: One_Or_More_Declarations Declaration 
        | Declaration
        ;

Declaration: Type IDS T_SEMICOL  
        ;

IDS:  T_ID
        | IDS T_COMMA T_ID
        ;

ReturnStatement: T_RETURN Expression T_SEMICOL
        |
        ; 

One_Or_More_Statements: One_Or_More_Statements Statement 
        | Statement
        ;

Statement:Assignment
        |MethodCalling
        |IfElse
        |WhileLoop
        |RepeatUntil
        |Print
        ;

Assignment: T_ID T_ASSIGN Expression T_SEMICOL 
        | T_ID T_DOT T_ID T_ASSIGN Expression T_SEMICOL
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

Expression: Expression T_PLUS Expression         {$$ = new PlusNode($1, $3); }   
        |Expression T_MINUS Expression           {$$ = new MinusNode($1, $3); }   
        |Expression T_MULTIPLY Expression       {$$ = new TimesNode($1, $3); } 
        |Expression T_DIVIDE Expression         {$$ = new DivideNode($1, $3); }      
        |Expression T_LESS Expression           {$$ = new LessNode($1, $3); }     
        |Expression T_LESSOREQUAL Expression    {$$ = new LessEqualNode($1, $3); } 
        |Expression T_EQUALS Expression         {$$ = new EqualNode($1, $3); }  
        |Expression T_AND Expression            {$$ = new AndNode($1, $3); }           
        |Expression T_OR Expression             {$$ = new OrNode($1, $3); }      
        |T_NOT Expression                       {$$ = new NotNode($2); }
        |T_MINUS Expression %prec T_UNARYMINUS  {$$ = new NegationNode($2); }  
        |MethodCall                             {$$ = $1;}   
        |T_ID                                   {$$ = new VariableNode(new IdentifierNode($1)); }
        |T_ID T_DOT T_ID                        {$$ = new MemberAccessNode(new IdentifierNode($1), new IdentifierNode($3));}
        |T_LP Expression T_RP                   {/*$$ = new ExpressionNode($2); */} 
        |T_LITERAL                              {$$ = new IntegerLiteralNode(new IntegerNode($1)); }  
        |T_TRUE                                 {$$ = new BooleanLiteralNode(new IntegerNode($1)); }                   
        |T_FALSE                                {$$ = new BooleanLiteralNode(new IntegerNode($1));  } 
        |T_NEW T_ID                             {$$ = new NewNode(new IdentifierNode($2), NULL); /* eller? new std::list<ExpressionNode*>());*/ }                           
        |T_NEW T_ID T_LP Arguments T_RP         {$$ = new NewNode(new IdentifierNode($2), NULL); /* eller? new std::list<ExpressionNode*>());*/ }  
        ;

MethodCall: T_ID T_LP Arguments T_RP            
        | T_ID T_DOT T_ID T_LP Arguments T_RP  
        ;

Arguments: ArgumentsP
        | 
        ;

ArgumentsP: Arguments T_COMMA Expression        
        | Expression                            
        ;

%%

extern int yylineno;

void yyerror(const char *s) {
  fprintf(stderr, "%s at line %d\n", s, yylineno);
  exit(0);
}

void printOut(const char *s) {
  // fprintf(stderr, "printOut: %s at line %d\n", s, yylineno);  
}


/*
 {$$ = MethodCallNode(new IdentifierNode($1), new IdentifierNode($3), $5)}

{$$ = new BooleanTypeNode(TypeNode(true)); astRoot = $$; }     


              
                           

      
*/


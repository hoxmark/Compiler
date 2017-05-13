%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <iostream>
    #include <list>
    #include "ast.hpp"
    
//     using namespace std;
    #define YYDEBUG 1
    #define YYINITDEPTH 10000
    int yylex(void);
    void yyerror(const char *);
    void printOut(const char *);
    void printOut2(const char *);
    
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



%type <program_ptr> Start
%type <class_list_ptr> Classes
%type <class_ptr> MethodsAndMembers Class
%type <method_list_ptr> One_Or_More_Methods
%type <method_ptr> Method
%type <methodbody_ptr> BodyDecStat
%type <parameter_list_ptr> Zero_Or_More_Parameters
%type <parameter_ptr> Parameter 
%type <type_ptr> Type
%type <declaration_list_ptr> One_Or_More_Declarations
%type <declaration_ptr> Declaration
%type <while_ptr> WhileLoop
%type <returnstatement_ptr> ReturnStatement
%type <statement_list_ptr> Block One_Or_More_Statements
%type <statement_ptr> Statement
%type <methodcall_ptr> MethodCall
%type <call_ptr> MethodCalling 

%type <assignment_ptr> Assignment
%type <ifelse_ptr> IfElse
%type <print_ptr> Print
%type <repeat_ptr> RepeatUntil
%type <expression_ptr> Expression
%type <identifier_list_ptr> IDS
%type <expression_list_ptr> Arguments ArgumentsP

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

Start: Classes          { $$ = new ProgramNode($1);   astRoot = $$;}                    
    ;

Classes: Classes Class  { $$=$1; $$->push_back($2); }
        | Class         { $$ = new std::list<ClassNode*>(); $$->push_back($1); }                   
        ;

Class:  T_ID T_LC MethodsAndMembers T_RC                        { $$ = new ClassNode(new IdentifierNode($1), NULL, $3->declaration_list, $3->method_list);}
        | T_ID T_EXTENDS T_ID T_LC MethodsAndMembers T_RC       { $$ = new ClassNode(new IdentifierNode($1), new IdentifierNode($3), $5->declaration_list, $5->method_list);}
        ;

MethodsAndMembers: One_Or_More_Declarations            {$$ = new ClassNode(NULL, NULL, $1,  NULL );}
        | One_Or_More_Methods                          {$$ = new ClassNode(NULL, NULL, NULL, $1);}
        | One_Or_More_Declarations One_Or_More_Methods {$$ = new ClassNode(NULL, NULL, $1, $2);}
        | 
        ; 

One_Or_More_Methods: One_Or_More_Methods Method { $$=$1;  $$->push_back($2);}
        | Method                                { $$ = new std::list<MethodNode*>(); $$->push_back($1);}
        ;

Type: T_INTEGER                 {$$ = new IntegerTypeNode();}
        | T_BOOLEAN             {$$ = new BooleanTypeNode();}
        | T_NONE                {$$ = new NoneNode();}
        | T_ID                  {$$ = new ObjectTypeNode(new IdentifierNode($1));}
        ;

Method: T_ID T_LP Zero_Or_More_Parameters T_RP T_FUNC Type T_LC BodyDecStat  T_RC  {$$ = new MethodNode(new IdentifierNode($1), $3, $6, $8);  }
        ; 
 

Zero_Or_More_Parameters: Zero_Or_More_Parameters Parameter      { $$ = $1; $$->push_back($2);}
        |                                                       { $$ = new std::list<ParameterNode*>();} 
        ;

Parameter: T_ID T_COLON Type                    { $$ = new ParameterNode($3, new IdentifierNode($1)); }      
        | T_ID T_COLON Type T_COMMA Parameter   { $$ = new ParameterNode($3, new IdentifierNode($1)); }    
        ; 
  
BodyDecStat: One_Or_More_Declarations ReturnStatement                           {$$ = new MethodBodyNode($1, NULL, $2); }
        | One_Or_More_Statements ReturnStatement                                {$$ = new MethodBodyNode(NULL, $1, $2); }
        | One_Or_More_Declarations One_Or_More_Statements ReturnStatement       {$$ = new MethodBodyNode($1, $2, $3); }
        | 
        ;

One_Or_More_Declarations: One_Or_More_Declarations Declaration  {$$=$1;  $$->push_back($2); }
        | Declaration                                           { $$ = new std::list<DeclarationNode*>(); $$->push_back($1);}
        ;

Declaration: Type IDS T_SEMICOL         { $$ = new DeclarationNode($1, $2);}
        ;

IDS:  T_ID                              { $$ = new std::list<IdentifierNode*>(); $$->push_back(new IdentifierNode($1));}
        | IDS T_COMMA T_ID              { $$->push_back(new IdentifierNode($3)); } 
        ;

ReturnStatement: T_RETURN Expression T_SEMICOL { $$ = new ReturnStatementNode($2); }
        | {$$ = NULL;}
        ; 

One_Or_More_Statements: One_Or_More_Statements Statement {$$=$1; $$->push_back($2); }
        | Statement      { $$ = new std::list<StatementNode*>(); $$->push_back($1); }
        ;

Statement:Assignment    {$$ = $1; }  
        |MethodCalling  {$$ = $1; }
        |IfElse         {$$ = $1; }
        |WhileLoop      {$$ =  $1; }
        |RepeatUntil    {$$ = $1; }
        |Print          {$$ = $1; }
        ;

Assignment: T_ID T_ASSIGN Expression T_SEMICOL          {$$ = new  AssignmentNode(new IdentifierNode($1), NULL, $3);}
        | T_ID T_DOT T_ID T_ASSIGN Expression T_SEMICOL {$$ = new  AssignmentNode(new IdentifierNode($1), new IdentifierNode($3), $5);}
        
        ;

MethodCalling: MethodCall T_SEMICOL     { $$ = new CallNode($1);}
        ;

IfElse:   T_IF Expression T_LC Block T_RC         {$$ = new IfElseNode($2, $4, NULL);}
        | T_IF Expression T_LC Block T_RC T_ELSE T_LC Block T_RC {$$ = new IfElseNode($2, $4, $8);}                           
        ;

WhileLoop: T_WHILE Expression T_LC Block T_RC  {$$ = new WhileNode($2, $4);}
        ;

RepeatUntil: T_REPEAT T_LC Block T_RC T_UNTIL T_LP Expression T_RP T_SEMICOL {  $$ = new RepeatNode($3, $7);}
        ;

Block: One_Or_More_Statements                   {$$ = $1;}        
        ;       
Print: T_PRINT Expression T_SEMICOL             {$$ = new PrintNode($2);}          
        ;

Expression: Expression T_PLUS Expression        {$$ = new PlusNode($1, $3); }   
        |Expression T_MINUS Expression          {$$ = new MinusNode($1, $3); }   
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
        |T_LP Expression T_RP                   {$$ =  $2; } 
        |T_LITERAL                              {$$ = new IntegerLiteralNode(new IntegerNode($1)); }  
        |T_TRUE                                 {$$ = new BooleanLiteralNode(new IntegerNode($1)); }                   
        |T_FALSE                                {$$ = new BooleanLiteralNode(new IntegerNode($1));  } 
        |T_NEW T_ID                             {$$ = new NewNode(new IdentifierNode($2), new std::list<ExpressionNode*>());  }                           
        |T_NEW T_ID T_LP Arguments T_RP         {$$ = new NewNode(new IdentifierNode($2), $4);  }  
        ;

MethodCall: T_ID T_LP Arguments T_RP           {$$ = new MethodCallNode(new IdentifierNode($1), NULL, $3);}
        | T_ID T_DOT T_ID T_LP Arguments T_RP  {$$ = new MethodCallNode(new IdentifierNode($1), new IdentifierNode($3), $5);}
        ;

Arguments: ArgumentsP {$$ = $1;}
        |   {$$ = new  std::list<ExpressionNode*>();}                                 
        ;

ArgumentsP: Arguments T_COMMA Expression    {$$->push_back($3);}        
        | Expression       {$$ = new  std::list<ExpressionNode*>(); $$->push_back($1);}                   
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

void printOut2(const char *s) {
  fprintf(stderr, "printOut: %s at line %d\n", s, yylineno);  
}




/*
One_Or_More_Members: One_Or_More_Members Type T_ID T_SEMICOL {}
        | Type T_ID T_SEMICOL { $$ = new std::list<DeclarationNode*>(); $$->push_back(new DeclarationNode($1, new IdentifierNode($1)));TODO: Multiple IDS? }
        ;
*/
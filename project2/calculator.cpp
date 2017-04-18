
#include "calculator.hpp"
#include <string>
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;



// Scanner implementation
// ifstream myfile; 
// string myfile; 
bool eatenClean = true; 
char oldChar; 

// You may have to modify this constructor, although it might not be neccessary.
Scanner::Scanner() : line(1), 
                     value(0) {
    // WRITEME
    
    // if (myfile.is_open()){
    //     // cout << "succefully opened file\n"; 
        
    // }else {
    //     cout << "Unable to open file"; 
    //     //TODO -> Throw error
    // }
}

Token Scanner::checkDoubleStar(){
    char first; 
    char sec; 

    cin.get(first);
    sec = cin.peek();
    if (sec == '*'){
        cin.putback(first);
        return T_EXP;
    } else {
        cin.putback(first);
        return T_MULTIPLY;      
    }
}

Token Scanner::checkDoubleStarAfterEaten(char first){
    char sec; 

    sec = cin.peek();
    if (sec == '*'){
        cin.get(sec);
        return T_EXP;
    } else {
        //cin.putback(first);
        return T_MULTIPLY;      
    }
}
// You need to fill this method with the appropriate code for it to work as described in the project description.
Token Scanner::nextToken() {
    // I am a placeholder. Change me into something that can actually decypher the next token without consuming it.
    // WRITEM
    char c; 
    // std::cin >> std::ws;
    c = cin.peek(); 
    
    
    int num = 0; 
    if ( c == EOF ) return T_EOF;
     cout<< "nextToken char:"<<c<<"\n";
    if ( isdigit(c)){
        cin >> num; 
        cin.putback(c);        
    } 
  
    switch(c) {
        case '+' : return T_PLUS;
        case '-' : return T_MINUS;
        case '*' : return checkDoubleStar();
        case '/' : return T_DIVIDE;
        case '%' : return T_MODULO;
        //case '**': return T_EXP; //TODO this will never happend? 
        case '(' : return T_OPENPAREN;
        case ')' : return T_CLOSEPAREN;
        case ';' : return T_SEMICOLON;
        case '0' : this->value = num;return T_NUMBER;
        case '1' : this->value = num;return T_NUMBER;
        case '2' : this->value = num;return T_NUMBER;
        case '3' : this->value = num;return T_NUMBER;
        case '4' : this->value = num;return T_NUMBER;
        case '5' : this->value = num;return T_NUMBER;
        case '6' : this->value = num;return T_NUMBER;
        case '7' : this->value = num;return T_NUMBER;
        case '8' : this->value = num;return T_NUMBER;
        case '9' : this->value = num;return T_NUMBER;        
        case '\n': this->line++; return T_NEWLN;  //TODO what baout new line? 
        default : scanError(this->line, c); //TODO, should i return line or line +1? 
    }
}



Token Scanner::findTokenFromChar(char c){
    switch(c) {
        case '+' : return T_PLUS;
        case '-' : return T_MINUS;
        case '*' : return checkDoubleStarAfterEaten(c);
        case '/' : return T_DIVIDE;
        case '%' : return T_MODULO;
        // case '**': return T_EXP; //TODO this will never happend? 
        case '(' : return T_OPENPAREN;
        case ')' : return T_CLOSEPAREN;
        case ';' : return T_SEMICOLON;
        case '0' : return T_NUMBER;
        case '1' : return T_NUMBER;
        case '2' : return T_NUMBER;
        case '3' : return T_NUMBER;
        case '4' : return T_NUMBER;
        case '5' : return T_NUMBER;
        case '6' : return T_NUMBER;
        case '7' : return T_NUMBER;
        case '8' : return T_NUMBER;
        case '9' : return T_NUMBER;        
        case '\n': return T_NEWLN; 
        default : cout << "ERROR in find token form char()"; //TODO, should i return line or line +1? 
    }
}

// You need to fill this method with the appropriate code for it to work as described in the project description.
void Scanner::eatToken(Token toConsume) {
    // I am a placeholder. I'm not even fun. Change me into something that can actually consume tokens!
    // WRITEME

    //The eatToken function takes in a 
    //token that the parser expects, 
    //and verifies that it is the same as the 
    //next token available before consuming it and 
    //removing it from the input stream.
    //Skal denne eates eller ikke

    char c; 
    cin.get(c); 
    cout << "eaten: " << c <<"\n" ;   

    Token found = findTokenFromChar(c);
    if (toConsume != found){
        mismatchError(this->line, toConsume, found);
    }
}

int Scanner::lineNumber() {
    return this->line;
}

int Scanner::getNumberValue() {
    return this->value;
}

// Parser implementation

// You may need to modify this constructor and make it do stuff, although it might not be neccessary.
Parser::Parser(bool eval) : evaluate(eval) {
    // WRITEME

}

// void S() {
//   switch(scanner.nextToken) {
//     case IF: {
//         match(IF); 
//         E(); 
//         match(THEN); 
//         S();
//         match(ELSE); 
//         S(); 
//         break;
//     }

//     case BEGIN: match(BEGIN); S(); L(); break;
//     case PRINT: match(PRINT); E(); break;
//     default: error();
//   }
// }


void Parser::parse() {
    cout<< "Parser Start"<<"\n";
    start();
    
    // Token nextToken = scanner.nextToken();
    // scanner.eatToken(nextToken);
    // Token thisToken = nextToken;
    // start(thisToken);

}

// void times

// void L() {
//   switch(lookahead) {
//     case END: match(END); break;
//     case SEMI: match(SEMI); S();
//                L(); break;
//     default: error();
// } }

// void S() {
//   switch(lookahead) {
//     case IF: match(IF); E(); match(THEN); S();
//              match(ELSE); S(); break;
//     case BEGIN: match(BEGIN); S(); L(); break;
//     case PRINT: match(PRINT); E(); break;
//     default: error();
//   }
// }
// void E() { match(NUM); match(EQ); match(NUM); }


//GRAMMER
// Start -> ExprList

// ExprList -> Expr ExprList’
// ExprList’ -> ; Expr ExprList’
// 	| ε 

// Expr -> term Expr’
// Expr’ -> 	+ term Expr’
// 	| 	- term Expr
// 	| 	epsilon 

// term -> factor term’
// term -> 	* factor term’
// 	| 	/ factor term’ 
// 	| 	epsilon 

// factor -> num


void Parser::start() {
    exprList(); //TODO MAKE THIS EcprList
    // I am a placeholder. Implement a recursive descent parser starting from me. Add other methods for different recursive steps.
    // Depending on how you designed your grammar, how many levels of operator precedence you need, etc., you might end up with more
    // or less steps in the process.
    //
    // WRITEME
}

void Parser::exprList(){
    expr();
    exprListP();
}

void Parser::exprListP(){
    switch(scanner.nextToken()){
        case T_SEMICOLON:{
          scanner.eatToken(T_SEMICOLON);           
          expr();
          exprListP();  
        } 
        // case epsilon: //TODO?
        default: cout<<"default in exprListP"<<"\n";
    }
}

void Parser::expr(){
    term();
    exprP();
}

void Parser::exprP(){
    cout <<"exprP"<<"\n";
   switch (scanner.nextToken()){
    //    case T_OPENPAREN: scanner.eatToken(); exprP(); break; 
       case T_PLUS: cout<<"+"<<"\n"; scanner.eatToken(T_PLUS); term(); exprP(); break; 
       case T_MINUS: scanner.eatToken(T_MINUS); term (); exprP(); break; 
       default:  cout<< "DEFAULT exprP"<<"\n";
   }
}

void Parser::term(){
    factor();
    termP();
}

void Parser::termP(){
    cout<< "termP: "<<scanner.nextToken()<< "\n";
    switch(scanner.nextToken()){
        case T_MULTIPLY: scanner.eatToken(T_MULTIPLY); factor(); termP(); break;
        case T_DIVIDE: scanner.eatToken(T_DIVIDE); factor(); termP(); break;
        default: cout << "termP default"<<"\n";
    }
}

void Parser::factor(){
    cout<< "facotr: " <<scanner.nextToken()<<"\n";
    switch(scanner.nextToken()){        
        case T_NUMBER:{
            cout<< "her:" << scanner.nextToken() << "\n"; 
            scanner.eatToken(T_NUMBER);
            break;
        }    
        default: cout<<"FACTOR default? "<<"\n";
    }
}



// You will need to add more methods for this to work. Don't forget to also define them in calculator.hpp!
// WRITEME


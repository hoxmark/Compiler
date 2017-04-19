
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
string file; 

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
    //  cout<< "nextToken char:"<<c<<"\n";
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
        case ' ' : char x; cin.get(x); return nextToken();
        case '\n': this->line++; eatToken(T_NEWLN); return nextToken() ;  
        default : scanError(this->line, c); 
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
        default : return T_EOF; //TODO OK? 
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
    // cout << "eaten: " << c <<"\n" ;   
// 
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

void Parser::parse() {
    start();
}

void Parser::start() {    
    // scanner.eatToken(T_EOF);
    // I am a placeholder. Implement a recursive descent parser starting from me. Add other methods for different recursive steps.
    // Depending on how you designed your grammar, how many levels of operator precedence you need, etc., you might end up with more
    // or less steps in the process.
    //
    // WRITEME
    exprList(); 
}

void Parser::exprList(){
    expr();
    exprListP();
}

void Parser::exprListP(){
    switch(scanner.nextToken()){
        case T_SEMICOLON:{
          scanner.eatToken(T_SEMICOLON);     
          exprList();      
        //   expr();
        //   exprListP();  
        } 
        default: return; 
    }
}

void Parser::expr(){
    term();
    exprP();
}

void Parser::exprP(){
   switch (scanner.nextToken()){
        case T_OPENPAREN: scanner.eatToken(T_OPENPAREN); term(); scanner.eatToken(T_CLOSEPAREN); break; 
        case T_PLUS:  scanner.eatToken(T_PLUS); term(); exprP(); break; 
        case T_MINUS: scanner.eatToken(T_MINUS); term (); exprP(); break; 
        default: return; 
   }
}

void Parser::term(){
    expp();
    termP();
}

void Parser::termP(){
    // cout<< "termP: "<< "\n";
    switch(scanner.nextToken()){
        case T_MULTIPLY: scanner.eatToken(T_MULTIPLY); expp(); termP(); break;
        case T_DIVIDE: scanner.eatToken(T_DIVIDE); expp(); termP(); break;
        case T_MODULO: scanner.eatToken(T_MODULO); expp(); termP(); break;
        default:return; 
    }
}


void Parser::expp(){
    factor();
    exppP();
}

void Parser::exppP(){
    switch(scanner.nextToken()){
        case T_EXP: scanner.eatToken(T_EXP); factor(); exppP(); break;
        default: return; 
    }
}

void Parser::factor(){
    // cout<< "factor: " <<tokenToString(scanner.nextToken())<<"\n";
    switch(scanner.nextToken()){        
        case T_NUMBER: scanner.eatToken(T_NUMBER); break; 
        case T_OPENPAREN: scanner.eatToken(T_OPENPAREN); expr(); scanner.eatToken(T_CLOSEPAREN); break;
        case T_EOF: return; 
        default: parseError(scanner.lineNumber(), scanner.nextToken());       
    }
}

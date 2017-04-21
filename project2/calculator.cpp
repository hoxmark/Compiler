
#include "calculator.hpp"
#include <string>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>
#include <limits>

using namespace std;



// Scanner implementation
// You may have to modify this constructor, although it might not be neccessary.
Scanner::Scanner() : line(1), 
                     value(0) {
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
        return T_MULTIPLY;      
    }
}
// You need to fill this method with the appropriate code for it to work as described in the project description.
Token Scanner::nextToken() {
    // I am a placeholder. Change me into something that can actually decypher the next token without consuming it.
    // WRITEM
    char c; 
    c = cin.peek(); 
    
    
    int num = 0; 
    if ( c == EOF ) return T_EOF;
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
    //The eatToken function takes in a token that the parser expects, and verifies that it is the same as the next token available before consuming it and removing it from the input stream.

    char c; 
    cin.get(c); 

    Token found = findTokenFromChar(c);

    if (toConsume != found){
        mismatchError(this->line, toConsume, found);
    } else {
       
        if (isdigit(c)){
            result.push_back(to_string(this->value));
        } else {
            result.push_back(tokenToString(found));
        }
}   }

int Scanner::lineNumber() {
    return this->line;
}

int Scanner::getNumberValue() {
    return this->value;
}

// Parser implementation
// You may need to modify this constructor and make it do stuff, although it might not be neccessary.
Parser::Parser(bool eval) : evaluate(eval) {
    this->lineNumber = 1;
}


Token Parser::findTokenFromString(string s){
    char c = s[0];
    switch(c) {
        case '+' : return T_PLUS;
        case '-' : return T_MINUS;
        case '*' : {
            if (s[1] == '*'){
                return T_EXP;
            } else {
                return T_MULTIPLY;
            }

        } 
        case '/' : return T_DIVIDE;
        case '%' : return T_MODULO;
        case '(' : return T_OPENPAREN;
        case ')' : return T_CLOSEPAREN;
        case 'S' : return T_SEMICOLON;
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
        case 'N' : return T_NEWLN;      
          
    }
}

void Parser::parse() {
    start();
    
    if (this->evaluate){        
       for(vector<string>::const_iterator i = scanner.result.begin(); i != scanner.result.end(); ++i) {
            string currentString = *i;            
            Token tok = findTokenFromString(currentString);        
            switch (tok){
                case T_NUMBER: {
                        int thisInt = stoi(currentString);
                        val.push(thisInt);
                        break;
                    }
                case T_PLUS : {
                    if (!op.empty()){
                        while (!op.empty() && isPrecidence(tok, op.top())){                            
                            addTwoOperands();                        
                        }                         
                    }                                        
                    op.push(T_PLUS); 
                    
                    break;
                }
                case T_MINUS : {
                    if (!op.empty()){ 
                        while (!op.empty() && isPrecidence(tok, op.top())){                            
                            addTwoOperands();                        
                        }                         
                    }                                     
                    op.push(T_MINUS); 
                    break;
                }
                case T_MULTIPLY: {
                    if (!op.empty()){
                        while (!op.empty() && isPrecidence(tok, op.top())){                            
                            addTwoOperands();                        
                        }                         
                    }                     
                    op.push(T_MULTIPLY); 
                    break;
                } 
                case T_DIVIDE : {
                    if (!op.empty()){
                        while (!op.empty() && isPrecidence(tok, op.top())){                            
                            addTwoOperands();                        
                        }                         
                    }                     
                    op.push(T_DIVIDE); 
                    break;
                }
                case T_MODULO : {
                    if (!op.empty()){
                        while (!op.empty() && isPrecidence(tok, op.top())){                            
                            addTwoOperands();                        
                        }                         
                    }                     
                    op.push(T_MODULO); 
                    break;
                }
                case T_EXP : {
                    if (!op.empty()){
                        while (!op.empty() && isPrecidence(tok, op.top())){                            
                            addTwoOperands();                        
                        }                         
                    }                     
                    op.push(T_EXP); 
                    break;
                }
                case T_OPENPAREN : op.push(T_OPENPAREN); break;
                case T_CLOSEPAREN : {
                    while (op.top()!=T_OPENPAREN){addTwoOperands(); }
                    op.pop();                                        
                    break;
                } 
                case T_SEMICOLON: {                             
                    while (!op.empty()&&(val.size()>1)){addTwoOperands(); }
                    if (!val.empty()) {
                        checkForErrors(val.top());
                        this->printOut += to_string(val.top());
                        this->printOut += "\n"; 
                        val.pop();
                    } 
                     
                    while (!op.empty()) op.pop();                                                   
                    break; 
                }
                case T_NEWLN: this->lineNumber = this->lineNumber+ 1; break;
                default: {
                   return;                                   
                }
            }        
       }        
         
        while (!op.empty()&&(val.size()>1)){addTwoOperands(); }
        if (!val.empty()) {
            checkForErrors(val.top());
            this->printOut += to_string(val.top());   
        }     
    }
    cout << printOut;
}


void Parser::checkForErrors(long in){
    if (in <= -(std::numeric_limits<int>::max())  || in >= (std::numeric_limits<int>::max())){ 
        outOfBoundsError((this->lineNumber), in);
    }
}

bool Parser::isPrecidence(Token first, Token sec){
    if (sec == T_CLOSEPAREN || sec == T_OPENPAREN)
            return false;
    switch(first){
        case T_PLUS : {         
            if (sec == T_MULTIPLY || 
                sec == T_DIVIDE || 
                sec == T_EXP || 
                sec == T_MODULO ){
                    return true; 
            }  
            break; 
        }
        case T_MINUS: {            
            if (sec == T_MULTIPLY || 
                sec == T_DIVIDE || 
                sec == T_EXP || 
                sec == T_MODULO){
                    return true; 
            }break; 
        }
        case T_MULTIPLY: {
            if (sec == T_PLUS || 
                sec == T_MINUS){
                 return false; 
            }break; 
        }
        case T_DIVIDE: {
            if (sec == T_PLUS || 
                sec == T_MINUS){
                return false; 
            }break;
        } 
        case T_MODULO: {
            if (sec == T_PLUS || 
                sec == T_MINUS){
                    return false; 
            }break;
        } 
        case T_EXP: {
            if (sec == T_PLUS || 
                sec == T_MINUS ||
                sec == T_MULTIPLY ||
                sec == T_DIVIDE || 
                sec == T_EXP || 
                sec == T_MODULO){
                return false; 
            }break;
        } 
        default: return true ;
    }
}

void Parser::addTwoOperands(){
    Token tok = op.top();
        op.pop();
        int val1 = val.top();val.pop();
        int val2 = val.top();val.pop();
        long currenValue = 0;            
        switch (tok){
            case T_PLUS: currenValue = val2 + val1; break; 
            case T_MINUS: currenValue = val2 - val1; break; 
            case T_MULTIPLY: currenValue = val2 * val1; break; 
            case T_DIVIDE: {
                    if (val1==0){divideByZeroError(this->lineNumber ,val2);
                } else {
                    currenValue = val2 / val1; break;
                }                 
                
            }               
            case T_MODULO: currenValue = val2 % val1; break;                 
            case T_EXP: currenValue = pow(val2,val1); break;                 
        }
        checkForErrors(currenValue);
        val.push(currenValue);
}

void Parser::start() {    
    // I am a placeholder. Implement a recursive descent parser starting from me. Add other methods for different recursive steps.
    // Depending on how you designed your grammar, how many levels of operator precedence you need, etc., you might end up with more
    // or less steps in the process.
    //
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
    switch(scanner.nextToken()){        
        case T_NUMBER: scanner.eatToken(T_NUMBER); break; 
        case T_OPENPAREN: scanner.eatToken(T_OPENPAREN); expr(); scanner.eatToken(T_CLOSEPAREN); break;
        case T_EOF: return; 
        default: parseError(scanner.lineNumber(), scanner.nextToken());       
    }
}
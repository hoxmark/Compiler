
#include "calculator.hpp"
#include <string>
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;



// Scanner implementation
ifstream myfile ("file.txt");

// You may have to modify this constructor, although it might not be neccessary.
Scanner::Scanner() : line(0), 
                     value(0) {
    // WRITEME
    
    if (myfile.is_open()){
        // cout << "succefully opened file\n"; 
        
        
    }else {
        cout << "Unable to open file"; 
        //TODO -> Throw error
    }
}

// You need to fill this method with the appropriate code for it to work as described in the project description.
Token Scanner::nextToken() {
    // I am a placeholder. Change me into something that can actually decypher the next token without consuming it.
    // WRITEME

    char c;
    while (myfile.get(c)){        
        // this->value = c;       
        // cout << "Value: " << this->value << "new char: "<<c << "\n";
        // cout << c;
        switch(c) {
            case '+' : return T_PLUS;
            case '-' : return T_MINUS;
            case '*' : return T_MULTIPLY;
            case '/' : return T_DIVIDE;
            case '%' : return T_MODULO;
            case '**': return T_EXP; //TODO this will never happend? 
            case '(' : return T_OPENPAREN;
            case ')' : return T_CLOSEPAREN;
            case ';' : return T_SEMICOLON;
            case '0' : this->value = createValue(0);return T_NUMBER;
            case '1' : this->value = createValue(1);return T_NUMBER;
            case '2' : this->value = createValue(2);return T_NUMBER;
            case '3' : this->value = createValue(3);return T_NUMBER;
            case '4' : this->value = createValue(4);return T_NUMBER;
            case '5' : this->value = createValue(5);return T_NUMBER;
            case '6' : this->value = createValue(6);return T_NUMBER;
            case '7' : this->value = createValue(7);return T_NUMBER;
            case '8' : this->value = createValue(8);return T_NUMBER;
            case '9' : this->value = createValue(9);return T_NUMBER;        
            case '\n': this->line++; return T_NEWLN; 
            case '\t': break;
            case ' ': break;            
            default : scanError(this->line, c); //TODO, should i return line or line +1? 
        }
    }     
    return T_EOF;   
}

int Scanner::createValue(int inVal){
    return inVal
    // int number = 0;
    // if (this->value == 0) {
    //     return inVal;    
    // } else {
    //     number = log(this->value)+1;
    //     return ((number*10)*inVal)+this->value;
    
    // }
}

// You need to fill this method with the appropriate code for it to work as described in the project description.
void Scanner::eatToken(Token toConsume) {
    // I am a placeholder. I'm not even fun. Change me into something that can actually consume tokens!
    // WRITEME
    switch(toConsume){
        case T_PLUS: {
            
            break; 
        }
        case T_MINUS: {

            break; 
        }
        case T_MULTIPLY: {

            break; 
        }
        case T_DIVIDE: {

            break; 
        }
        case T_MODULO: {

            break; 
        }
        case T_EXP: {

            break; 
        }
        case T_OPENPAREN: {

            break; 
        }
        case T_CLOSEPAREN: {

            break; 
        }
        case T_NUMBER: {

            break; 
        }
        case T_SEMICOLON: {

            break; 
        }
        case T_NEWLN: {

            break; 
        }
        case T_EOF: {

            break; 
        }    }

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
    cout<<"PARSER";
    // I am a placeholder. Implement a recursive descent parser starting from me. Add other methods for different recursive steps.
    // Depending on how you designed your grammar, how many levels of operator precedence you need, etc., you might end up with more
    // or less steps in the process.
    //
    // WRITEME

   
}

// You will need to add more methods for this to work. Don't forget to also define them in calculator.hpp!
// WRITEME


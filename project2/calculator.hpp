#pragma once

#include "helpers.hpp"
#include <string>
#include <climits>
#include <stack>
#include <vector>



// SCANNER DEFINITION

// You can freely add member fields and functions to this class.
class Scanner {
    int line;
    int value;
     
public:
    std::vector<std::string> result; 

    // You really need to implement these four methods for the scanner to work.
    Token nextToken();
    void eatToken(Token);
    int lineNumber();
    int getNumberValue();
    int createValue(int);
    Token checkDoubleStar();
    Token checkDoubleStarAfterEaten(char);
    Token findTokenFromChar(char);
    Scanner();
};



// PARSER DEFINITION

// You can freely add member fields and functions to this class.
class Parser {
    Scanner scanner;
    std::stack<Token> op; 
    std::stack<int> val;
    bool evaluate;
    void start();
    void exprList();
    void exprListP();
    void expr();
    void exprP();
    void term();
    void termP();
    void expp();
    void exppP();
    void paren();
    void parenP();
    void factor();
    void addTwoOperands();
    Token findTokenFromChar(char c);
    Token findTokenFromString(std::string s);
    bool isPrecidence(Token, Token);
    void checkForErrors(int);
    // You will need to define the recursive descent functions you're going to use here.
    // WRITEME
public:
    void parse();
    
    Parser(bool);
};

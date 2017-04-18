#pragma once

#include "helpers.hpp"

#include <climits>

// SCANNER DEFINITION

// You can freely add member fields and functions to this class.
class Scanner {
    int line;
    int value;
    bool lastWasAStar;//TODO 

public:
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
    
    bool evaluate;
    void start();
    void exprList();
    void exprListP();
    void expr();
    void exprP();
    void term();
    void termP();
    void factor();
    // You will need to define the recursive descent functions you're going to use here.
    // WRITEME
public:
    void parse();
    
    Parser(bool);
};

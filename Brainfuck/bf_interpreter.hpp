//
//  bf_interpreter.hpp
//  Brainfuck
//
//  Created by Filip Peterek on 13.08.16.
//  Copyright © 2016 Filip Peterek. All rights reserved.
//

#ifndef bf_interpreter_hpp
#define bf_interpreter_hpp

#include <stdio.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#define ARRAY_SIZE 30000


/* An exception, which is thrown, whenever the interpreter finds an opening bracket '[' without a matching closing bracket ']' */

class MissingBracketException : std::exception {
    
    unsigned long long _unclosedBracketPosition;
    
public:
    
    MissingBracketException(unsigned long long);
    std::string Message();
    
};


enum Status {
    
    Exit,
    Continue
    
};


class Brainfuck {
    
    unsigned char _array[ARRAY_SIZE];
    unsigned char * _ptr;
    long long _iter;
    std::string _input;
    
    long long FindLoopEnd(std::string str);
    void InterpretLoop();
    void Interpret();
    void InterpretToken(const char token);
    void Reset();
    
    void IncrementPtr();
    void DecrementPtr();
    void IncrementByte();
    void DecrementByte();
    void OutputByte();
    void AcceptByte();
    
public:
    
    Brainfuck();
    
    Status LiveInterpreter();
    void InterpretFromFile(std::string & filename);
    
};

#endif /* bf_interpreter_hpp */

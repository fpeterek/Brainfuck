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


/* An exception, which is thrown, when the interpreter finds an opening bracket '[' without a matching closing bracket ']' */

typedef std::exception MissingBracketException;


class Brainfuck {
    
    unsigned char _array[30000];
    unsigned char * _ptr;
    long long _iter;
    std::string _input;
    
    long long FindLoopEnd(std::string str);
    void InterpretLoop();
    void Interpret();
    void InterpretToken(const char token);
    
    void IncrementPtr();
    void DecrementPtr();
    void IncrementByte();
    void DecrementByte();
    void OutputByte();
    void AcceptByte();
    
public:
    
    Brainfuck();
    
    void LiveInterpreter();
    void InterpretFromFile(std::string & filename);
    
};

#endif /* bf_interpreter_hpp */

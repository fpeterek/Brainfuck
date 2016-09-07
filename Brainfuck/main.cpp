//
//  main.cpp
//  Brainfuck
//
//  Created by Filip Peterek on 13.08.16.
//  Copyright © 2016 Filip Peterek. All rights reserved.
//

#include <iostream>

#include "bf_interpreter.hpp"


int main(int argc, const char * argv[]) {
    
    Brainfuck bf;
    
    /* If the program receives a filename as a parameter, interpret the file, then open a live interpreter */
    
    if (argc > 1) {
    
        try {
            
            std::string file = argv[1];
            bf.InterpretFromFile(file);
            
        } catch (MissingBracketException e) {
            
            std::cout << e.what() << std::endl;
            
        }
        
    }
    
    Status status = Status::Continue;
    
    /* 
        Exit the interpreter if the user types in "exit"
     
        If an exception is thrown, the interpreter is reset (this is done before the exception is thrown) and it keeps on looping
     */
    
    while (status == Status::Continue) {
    
        try {
            
            status = bf.LiveInterpreter();
            
        } catch (MissingBracketException e) {
            
            std::cout << e.what() << std::endl;
            
        }
            
    }
     
    return 0;
    
}

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
    
    /* If the program receives a filename as a parameter, interpret the file, otherwise open a live interpreter. */
    
    if (argc > 1) {
    
        std::string file = argv[1];
        bf.InterpretFromFile(file);
        
    }
    
    else {
        
        bf.LiveInterpreter();
        
    }
     
    return 0;
    
}

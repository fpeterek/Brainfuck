//
//  bf_interpreter.cpp
//  Brainfuck
//
//  Created by Filip Peterek on 13.08.16.
//  Copyright © 2016 Filip Peterek. All rights reserved.
//

#include "bf_interpreter.hpp"


/************************************************************************************************************************************/
/*                                                                                                                                  */
/*                                                         ---------------                                                          */
/*                                                         -- Exception --                                                          */
/*                                                         ---------------                                                          */
/*                                                                                                                                  */
/************************************************************************************************************************************/

MissingBracketException::MissingBracketException(unsigned long long bracketPos) {
    
    _unclosedBracketPosition = bracketPos;
    
}

std::string MissingBracketException::Message() {
    
    /* Use stringstream to create an error message from a string literal and an unsigned long long */
    
    std::stringstream s;
    
    s << "Unclosed bracked at index ";
    s << _unclosedBracketPosition;
    
    return s.str();
    
}


/************************************************************************************************************************************/
/*                                                                                                                                  */
/*                                                   ---------------------------                                                    */
/*                                                   -- Brainfuck Interpreter --                                                    */
/*                                                   ---------------------------                                                    */
/*                                                                                                                                  */
/************************************************************************************************************************************/


Brainfuck::Brainfuck() {
    
    _ptr = _array;
    _input = "";
    
}

/* Self explanatory */

void Brainfuck::IncrementPtr() {
    
    if (_ptr == _array + 29999) {
        
        return;
        
    }
    
    ++_ptr;
    
}

void Brainfuck::DecrementPtr() {
    
    if (_ptr == _array) {
        
        return;
        
    }
    
    --_ptr;
    
}

void Brainfuck::IncrementByte() {
    
    ++(*_ptr);
    
}

void Brainfuck::DecrementByte() {
    
    --(*_ptr);
    
}

void Brainfuck::OutputByte() {
    
    std::cout << *_ptr;
    
}

void Brainfuck::AcceptByte() {
    
    *_ptr = getchar();
    
}

void Brainfuck::InterpretFromFile(std::string & file) {
    
    /* Laugh at php peasants */
    
    if (file.rfind(".php") == file.length() - 4) {
        
        std::cout << "Nice meme! " << std::endl;
        return;
        
    }
    
    /* Check if file is a Brainfuck file (extension .bf or .b) */
    
    if ( ( file.rfind(".bf") != file.length() - 3 ) and ( file.rfind(".b") != file.length() - 2 ) ) {
        
        std::cout << "File is not a Brainfuck file. " << std::endl;
        return;
        
    }
    
    std::fstream filestream;
    filestream.open(file);
    
    if (filestream.is_open()) {
        
        std::string line;
        
        while (not filestream.eof()) {
            
            std::getline(filestream, line);
            
            _input.append(line);
            
        }
        
    }
    else {
        
        std::cout << "File could not be opened. " << std::endl;
        
    }
    
    Interpret();
    
}

/* Searches _input to find where a certain loop ends */

long long Brainfuck::FindLoopEnd(std::string str) {
    
    long long loopEnd = -1;
    long long bracketCounter = 0;
    
    for (int i = 0; i < str.length(); ++i) {
        
        if (str[i] == '[') {
            
            ++bracketCounter;
            
        }
        
        else if (str[i] == ']' and bracketCounter == 1) {
            
            loopEnd = i;
            break;
            
        }
        else if (str[i] == ']') {
            
            --bracketCounter;
            
        }
        
    }
    
    if (loopEnd == -1) {
    
        /* Save iterator position before resetting the interpreter */
        
        unsigned long long iterPos = _iter;
        Reset();
        throw MissingBracketException(iterPos);
    
    }
    
    return loopEnd;
    
}

/* Calls corresponding method for each Brainfuck operator, ignores every other character */

void Brainfuck::InterpretToken(const char token) {
    
    switch (_input[_iter]) {
            
        case '>':
            IncrementPtr();
            break;
            
        case '<':
            DecrementPtr();
            break;
            
        case '+':
            IncrementByte();
            break;
            
        case '-':
            DecrementByte();
            break;
            
        case '.':
            OutputByte();
            break;
            
        case ',':
            AcceptByte();
            break;
            
        case '[':
            InterpretLoop();
            break;
            
        default:
            break;
    }

    
}

/* Resets the interpreter to it's initial state */

void Brainfuck::Reset() {
    
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        
        _array[i] = 0;
        
    }
    
    _ptr = _array;
    _iter = 0;
    
}

/* Whenever InterpretToken() finds a loop, this method executes it and then sets the iterator at the end of the loop so the code 
    can continue normally */

void Brainfuck::InterpretLoop() {
    
    const long long loopEnd = FindLoopEnd(_input.substr(_iter)) + _iter;
    const long long loopStart = _iter; /* The beggining of the loop (the first bracket '[') */
    
    while (*_ptr) {
        
        for (_iter = loopStart + 1; _iter < loopEnd; ++_iter) {
            
            InterpretToken(_input[_iter]);
            
        }
        
    }
    
    _iter = loopEnd;

}

/* Iterates through _input and passes each character to InterpretToken() */

void Brainfuck::Interpret() {
    
    for (_iter = 0; _iter < _input.length(); ++_iter) {
        
        InterpretToken(_input[_iter]);
        
    }
    
    
}

/* Reads line from stdin and passes it to the interpreter unless the input is equal to 'exit', in which case the programs quits */

Status Brainfuck::LiveInterpreter() {
    
    while (true) {
        
        std::cout << "$ ";
        std::getline(std::cin, _input);
        
        if (_input == "exit")   return Status::Exit;
        if (_input == "reset")  Reset();
        
        Interpret();
        
    }
    
}

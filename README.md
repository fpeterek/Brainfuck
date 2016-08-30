# Brainfuck
Brainfuck interpreter written in C++


Probably the worst Brainfuck interpreter you'll ever see. 


For whatever reason Xcode pushes the entire project to git, so just ignore the .xcodeproj file. 
The source code can be found in Brainfuck/


# Usage

To interpret a file, pass the file name to the interpreter as a parameter.

After the file is interpreted or if no/invalid parameter has been passed to the interpreter, a live interpreter is started.

The live interpreter is similar to eg. Python, Lua or Lisp live interpreters. Type in the code you want interpreted and press enter. To exit the live interpreter, type in "exit" (no whitespaces or other characters, otherwise it will be ignored). To reset the live interpret to it's initial value, type in "reset" (again, no other characters are allowed).

The interpreter is not reset after interpreting a file. If you want the interpreter to reset, you will have to do so manually.

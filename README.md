# CS_280_FALL_Parser

# Puropse of the project:
The main purpose of this project is to build the Parser for the simple language in C++. The follow up projects for this project for the Lexical Analyzer and will be building interpreter as a continuation for the project.

# About the Project:

In this programming assignment, you will be building a parser for a simple programming language. A preliminary grammar rules of the language and its tokens were given in Programming Assignment 1. However, the following specification is an update to the previously introduced grammar rules of the language and its tokens. Your implementation of a parser to the language is based on the following grammar rules specified in EBNF notations.


Prog ::= PROGRAM IDENT StmtList END PROGRAM

DeclStmt ::= (INT | FLOAT) IdentList

IdentList ::= IDENT, {, IDENT}

StmtList ::= Stmt; {Stmt;}

Stmt ::= DeclStmt | ControlStmt

ControlStmt ::= AssigStmt | IfStmt | WriteStmt

WriteStmt ::= WRITE ExprList

IfStmt ::= IF (LogicExpr) ControlStmt

AssignStmt ::= Var = Expr

ExprList ::= Expr {, Expr}

Expr ::= Term {(+|-) Term}

Term ::= SFactor {( *| / | % ) SFactor}

SFactor ::= (+ | -) Factor | Factor

LogicExpr ::= Expr (== | >) Expr

Var ::= IDENT

Factor = IDENT | ICONST | RCONST | SCONST | (Expr)

 

# Parser Requirements:

1) Implement a recursive-descent parser for the given simple programming language.

 The parser provide the following:

a) The results of an unsuccessful parsing are a set of error messages printed by the parser functions, as well as the error messages that might be detected by the lexical analyzer.
b) If the parser fails, the program  stop after the parser function returns.
c) Print the error message in the format of the messages  line number, followed by a colon and a space, followed by some descriptive text such as  “No statements in program”, “Invalid statement”, “Missing Right Parentheis”, “Undefined Variable”, “Missing END”, etc.

 

# Provided Files

1) The header file for the parser, “parse.h” 
2) “lex.h”, “lex.cpp” - from the lexical analyzer project
3) test cases

# Main files:
Prog2.cpp : It is the driver code that calls the recursive fuctions for token to determine IDENT | ICONST | RCONST | SCONST | (Expr)
parse.cpp: It is the cpp file that contains list of all functions that are called recursively to parse the word based on the grammer.

# concepts that are used in this project:
Recursion
Map
Vector
Inbuilt C++ function that are imported from algorithm library
Input and Output stream
Sstream
strings
Operator overloading
File operations : Importing, extrating,reading file content.
Contributing
Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are greatly appreciated. If you have a suggestion that would make this better, please fork the repo and creat

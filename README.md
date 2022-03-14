# CS_280_FALL_Parser

# Puropse of the project:
The main purpose of this project is to build the Parser for the simple language in C++. The follow up projects for this project for the Lexical Analyzer and will be building interpreter as a continuation for the project.

# About the Project:

In this project,  we build parser for a simple programming language. A preliminary grammar rules of the language and its tokens were given as:


Based on the language definitions, the lexical rules of the language and the assigned tokens to terminals are as follows:
The language has identifiers, referred to by ident terminal, which are defined to be a letter followed by zero or more letters or digit. It is defined as: ident := Letter {(Letter|Digit|_)}

Letter := [a-z A-Z]

Digit := [0-9]

The token for an identifier is IDENT.

Integer constants, referred to by iconst terminal, are defined as one or more digits. It is defined as: iconst := [0-9]+

The token for an integer constant is ICONST.

Real constants, referred to by rconst terminal, are defined as zero or more digits followed by a decimal point (dot) and one or more digits. It is defined as: Rconst := ([0-9]*).([0-9]+)

The token for a real constant is RCONST. For example, real number constants such as 12.0 and .2 are accepted, but 2. is not.

String literals, referred to by sconst terminal, are defined as a sequence of characters delimited by double quotes, that should all appear on the same line. The assigned token for a string constant is SCONST. For example, “Hello to CS 280.” is a string literal.

The reserved words of the language are: program, end, begin, write, if, int, float, string, repeat. These reserved words have the following tokens, respectively: PROGRAM, END, BEGIN, WRITE, IF, INT, FLOAT, STRING and REPEAT.

The operators of the language are: +, -, *, /, %, =, (, ), ==, >. These operators are for plus, subtract, multiply, divide, remainder, assignment, left parenthesis, right parenthesis, equality, and greater than operations. They have the following tokens, respectively: PLUS, MINUS, MULT, DIV, REM, ASSOP, LPAREN, RPAREN, EQUAL, GTHAN.

The semicolon and comma characters are terminals with the following tokens: SEMICOL, COMMA.

A comment is defined by all the characters following the exclamation mark “#” to the end of the line. A comment does not overlap one line. A recognized comment is ignored and does not have a token.

White spaces are skipped. However, white spaces between tokens are used to improve readability and can be used as a one way to delimit tokens.

An error will be denoted by the ERR token.

End of file will be denoted by the DONE token.

# The implementation of a parser to the language is based on the following grammar rules specified in EBNF notations.


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
1) Recursion
2)Map
3) Vector, Inbuilt C++ function that are imported from algorithm library
5) Input and Output stream
6) Sstream
7) strings
8) Operator overloading
9) File operations : Importing, extrating,reading file content.

# Contributing
Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are greatly appreciated. If you have a suggestion that would make this better, please fork the repo and creat

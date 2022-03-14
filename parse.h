//
// Created by samikshya poudel on 11/10/21.
//

#ifndef CS_280_FALL_PARSER_PARSE_H
#define CS_280_FALL_PARSER_PARSE_H



#include <iostream>

using namespace std;

#include "lex.h"


extern bool Prog(istream& in, int& line);
extern bool StmtList(istream& in, int& line);
extern bool Stmt(istream& in, int& line);
extern bool ControlStmt(istream& in, int& line);
extern bool DeclStmt(istream& in, int& line);
extern bool WriteStmt(istream& in, int& line);
extern bool IfStmt(istream& in, int& line);
extern bool IdentList(istream& in, int& line, LexItem tok);
extern bool Var(istream& in, int& line);
extern bool AssignStmt(istream& in, int& line);
extern bool ExprList(istream& in, int& line);
extern bool LogicExpr(istream& in, int& line);
extern bool Expr(istream& in, int& line);
extern bool Term(istream& in, int& line);
extern bool SFactor(istream& in, int& line);
extern bool Factor(istream& in, int& line, int sign);
extern int ErrCount();






#endif //CS_280_FALL_PARSER_PARSE_H

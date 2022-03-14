/* Incomplete Implementation of Recursive-Descent Parser
 * parse.cpp
 * Programming Assignment 2
 * Fall 2021
*/

#include "parse.h"

map<string, bool> defVar;
map<string, Token> SymTable;

namespace Parser {
    bool pushed_back = false;
    LexItem	pushed_token;

    static LexItem GetNextToken(istream& in, int& line) {
        if( pushed_back ) {
            pushed_back = false;
            return pushed_token;
        }
        return getNextToken(in, line);
    }

    static void PushBackToken(LexItem & t) {
        if( pushed_back ) {
            abort();
        }
        pushed_back = true;
        pushed_token = t;
    }

}

static int error_count = 0;

int ErrCount()
{
    return error_count;
}

void ParseError(int line, string msg)
{
    ++error_count;
    cout << line << ": " << msg << endl;
}


///Functions for the parser


// Prog ::= PROGRAM IDENT StmtList END PROGRAM
//PROGRAM circle
bool Prog(istream& in, int& line){
    bool status = false;
    LexItem tok = Parser::GetNextToken(in, line);


    if (tok.GetToken() == PROGRAM) {
        tok = Parser::GetNextToken(in, line); // circle


// ask kazi about it
        if (tok.GetToken() == IDENT) {

            status = StmtList(in, line);
            if (!status) {
                ParseError(line, "Incorrect Syntax in program");
                return false;
            }



            tok = Parser::GetNextToken(in, line);

//END PROGRAM


            if (tok.GetToken() == END) {
                tok = Parser::GetNextToken(in, line);

                if (tok.GetToken() == PROGRAM) {
                    tok = Parser::GetNextToken(in, line);

                    if (tok.GetToken() == DONE) {
                        return true;
                    }
                    else
                    {
                        ParseError(line, " Wrong file");
                        return false;
                    }
                }
                else
                {
                    ParseError(line, "Missing PROGRAM at the End");
                    return false;
                }
            }
            else
            {
                ParseError(line, "Missing END of Program");
                return false;
            }
        }

        else if(tok.GetToken() == ERR){
            ParseError(line, "Unrecognized pattern");
            cout << "(" << tok.GetLexeme() << ")" << endl;
            return false;
        }
        else{
            ParseError(line, "Missing Program Name");
            return  false;

        }


    }
    return status;
}

//DeclStmt ::= (INT | FLOAT) IdentList


//Type = INTEGER | FLOAT
bool DeclStmt(istream& in, int& line) {
    bool status = false;
    LexItem t = Parser::GetNextToken(in, line);

    if(t.GetToken() == INT || t.GetToken() == FLOAT ) {
        status = IdentList(in, line, t);
        //cout<< "returning from IdentList" << " " << (status? 1: 0) << endl;
        if (!status)
        {
            ParseError(line, "Incorrect variable in Declaration Statement.");
            return status;
        }
    }
    else{
        Parser::PushBackToken(t);
        ParseError(line, "Incorrect Type.");
        return false;
    }
    return status;

}

//IdentList ::= IDENT, {, IDENT} gotta work on it


//IdentList ::= IDENT, {, IDENT}
bool IdentList(istream& in, int& line, LexItem type){ // tok = INT/ FlOAT
    bool status = false;
    string ident;

    LexItem t = Parser::GetNextToken(in, line);
    if(t == IDENT)
    {
        //set IDENT lexeme to the type tok value
        ident = t.GetLexeme();
        if (defVar.find(ident) == defVar.end())
        {
            defVar[ident] = true;
            SymTable[ident] = type.GetToken();
        }
        else
        {
            ParseError(line, "Variable Redefinition");
            return false;
        }

    }
    else
    {
        ParseError(line, "Missing Variable");
        return false;
    }

    t = Parser::GetNextToken(in, line);

    if (t == COMMA) {
        status = IdentList(in, line, t);
    }
    else if(t.GetToken() == ERR){
        ParseError(line, "Unrecognized Input Pattern");
        cout << "(" << t.GetLexeme() << ")" << endl;
        return false;
    }
    else{
        Parser::PushBackToken(t);
        return true;
    }
    return status;
}
// ASK KAZI ABOUT IT
//StmtList ::= Stmt; {Stmt;}
//StmtList ::= Stmt; {Stmt;}
bool StmtList(istream& in, int& line){
    bool status;
    LexItem t;
    status = Stmt(in,line);


//    if(! status ){
//        ParseError(line, "Error");
//        return false;
//    }
    t = Parser::GetNextToken(in, line);

    if(t.GetToken() != SEMICOL){

        ParseError(line, "Missing semicolon");
        return false;
    }
    while((t = Parser::GetNextToken(in, line)) != END){

        Parser::PushBackToken(t);

        status = Stmt(in,line);


//        if(! status ){
//            ParseError(line, "Error");
//            return false;
//        }
        t = Parser::GetNextToken(in, line);

        if(t.GetToken() != SEMICOL){

            ParseError(line, "Missing semicolon");
            return false;
        }

    }

    Parser::PushBackToken(t);

    return status;


}

//Stmt ::= DeclStmt | ControlStmt

bool Stmt(istream& in, int& line){
    bool status=true;

    LexItem t = Parser::GetNextToken(in, line);

    switch( t.GetToken() ) {
        case INT: case FLOAT:
            Parser::PushBackToken(t);
            status = DeclStmt(in, line);
            if(!status)
            {
                ParseError(line, "Incorrect Declaration Statement.");
                return status;
            }
            break;
        case IF: case WRITE: case IDENT:
            Parser::PushBackToken(t);
            status = ControlStmt(in, line);
            if(!status)
            {
                ParseError(line, "Incorrect control Statement.");
                return status;
            }
            break;

        default:
            Parser::PushBackToken(t);
    }
    return status;
}


//ControlStmt ::= AssigStmt | IfStmt | WriteStmt

bool ControlStmt(istream& in, int& line){
    //cout<<"lets see"<<endl;
    bool status;
    LexItem t = Parser::GetNextToken(in, line);
    if( t == IF){
        status = IfStmt(in, line);


    }
    else if (t == WRITE){
        status = WriteStmt(in, line);


    }
    else if (t == IDENT){
        Parser::PushBackToken(t);
        status = AssignStmt(in, line);


    }
    else {
        Parser::PushBackToken(t);
        return true;
    }
    return status;
}


//WriteStmt ::= WRITE ExprList


bool WriteStmt(istream& in, int& line) {

    bool status = ExprList(in, line);

    if( !status ) {
        ParseError(line, "Missing expression after WRITE");
        return false;
    }

    return status;
}



//IfStmt ::= IF (LogicExpr) ControlStmt


bool IfStmt(istream& in, int& line){
    bool status = false;
    LexItem t = Parser::GetNextToken(in, line);
    if(t != LPAREN ){
        ParseError(line, "Missing Left Parenthesis");
        return false;

    }
    status = LogicExpr(in, line);
    if( !status ) {
        ParseError(line, "Missing Logic Expression");
        return false;
    }

    t=Parser::GetNextToken(in, line);

    if(t != RPAREN ) {

        ParseError(line, "Missing Right Parenthesis");
        return false;
    }
    status = ControlStmt(in, line);
    if(!status){
        ParseError(line, "Missing Statement for IF");
        return false;
    }

    return status;

}

//AssignStmt ::= Var = Expr
//AssignStmt ::= Var = Expr
bool AssignStmt(istream& in, int& line) {

    bool varstatus = false, status = false;
    LexItem t;

    varstatus = Var( in, line);


    if (varstatus){
        t = Parser::GetNextToken(in, line);

        if (t == ASSOP){ // r = 8;
            status = Expr(in, line);
            if(!status) {
                ParseError(line, "Missing Expression in Assignment Statment");
                return status;
            }

        }
        else if(t.GetToken() == ERR){
            ParseError(line, "Unrecognized Input Pattern");
            cout << "(" << t.GetLexeme() << ")" << endl;
            return false;
        }
        else {
            ParseError(line, "Missing Assignment Operator =");
            return false;
        }
    }
    else {
        ParseError(line, "Missing Left-Hand Side Variable in Assignment statement");
        return false;
    }
    return status;
}



//ExprList:= Expr {,Expr}
bool ExprList(istream& in, int& line) {
    bool status;

    status = Expr(in, line);
    if(!status){
        ParseError(line, "Missing Expression");
        return false;
    }

    LexItem t = Parser::GetNextToken(in, line);

    if (t.GetToken() == COMMA) {
        status = ExprList(in, line);
    }

    else if(t.GetToken() == ERR){
        ParseError(line, "Unrecognized Input Pattern");
        cout << "(" << t.GetLexeme() << ")" << endl;
        return false;
    }
    else{
        Parser::PushBackToken(t);
        return true;
    }
    return status;
}
//Expr ::= Term {(+|-) Term}
bool Expr(istream& in, int& line){

   LexItem t ;//= Parser::GetNextToken(in, line);
//    if (t.GetToken()== SCONST){
//        Parser::PushBackToken(t);
//    }

    bool status = Term(in, line);


    if( !status ) {
        return false;
    }

    t = Parser::GetNextToken(in, line);
    if(t.GetToken() == ERR){
        ParseError(line, "Unrecognized Input Pattern");
        cout << "(" << t.GetLexeme() << ")" << endl;
        return false;
    }
    while ( t.GetToken()== PLUS || t.GetToken() == MINUS )
    {
        status = Term(in, line);
        if( !status )
        {
            ParseError(line, "Missing operand after operator");
            return false;
        }

        t = Parser::GetNextToken(in, line);
        if(t.GetToken() == ERR){
            ParseError(line, "Unrecognized Input Pattern");
            cout << "(" << t.GetLexeme() << ")" << endl;
            return false;
        }


    }
    Parser::PushBackToken(t);
    return true;


}



//Term ::= SFactor {( *| / | % ) SFactor}
bool Term(istream& in, int& line) {

    bool status = SFactor(in, line);

    if( !status ) {
        return false;
    }

    LexItem t	= Parser::GetNextToken(in, line);
    if(t.GetToken() == ERR){
        ParseError(line, "Unrecognized Input Pattern");
        cout << "(" << t.GetLexeme() << ")" << endl;
        return false;
    }
    while ( t.GetToken() == MULT || t.GetToken() == DIV || t.GetToken() == REM  )
    {
        status = SFactor(in, line);

        if( !status ) {
            ParseError(line, "Missing operand after operator");
            return false;
        }

        t	= Parser::GetNextToken(in, line);
        if(t.GetToken() == ERR){
            ParseError(line, "Unrecognized Input Pattern");
            cout << "(" << t.GetLexeme() << ")" << endl;
            return false;
        }

    }
    Parser::PushBackToken(t);
    return true;
}



//SFactor ::= (+ | -) Factor | Factor

bool SFactor(istream& in, int& line) {
    LexItem t = Parser::GetNextToken(in, line);
    bool status;
    int sign = 0;
    if(t.GetToken() == MINUS )
    {
        sign = -1;
    }
    else if(t.GetToken() == PLUS)
    {
        sign = 1;
    }
    else
        Parser::PushBackToken(t);

    status = Factor(in, line, sign);
    return status;

}

//LogicExpr ::= Expr (== | >) Expr

bool LogicExpr(istream& in, int& line){

    bool status = Expr(in, line);
    LexItem t;

    if( !status ) {
        return false;
    }

    t = Parser::GetNextToken(in, line);
    if(t.GetToken() == ERR){
        ParseError(line, "Unrecognized Input Pattern");
        cout << "(" << t.GetLexeme() << ")" << endl;
        return false;
    }
    if ( t.GetToken() == GTHAN  || t.GetToken() == EQUAL)
    {
        status = Expr(in, line);
        if( !status )
        {
            ParseError(line, "Missing expression after relational operator");
            return false;
        }
        return true;
    }
    Parser::PushBackToken(t);
    return true;


}

//Var ::= IDENT

bool Var(istream& in, int& line)
{
    string ident;

    LexItem t = Parser::GetNextToken(in, line);

    if (t.GetToken() == IDENT){
        ident = t.GetLexeme();
        if (!(defVar.find(ident)->second))
        {
            ParseError(line, "Undeclared Variable");
            return false;

        }
        return true;
    }
    else if(t.GetToken() == ERR){
        ParseError(line, "Unrecognized Input Pattern");
        cout << "(" << t.GetLexeme() << ")" << endl;
        return false;
    }
    return false;
}


//Factor = IDENT | ICONST | RCONST | SCONST | (Expr)

bool Factor(istream& in, int& line, int sign){
    LexItem t = Parser::GetNextToken(in, line);


    if( t.GetToken() == IDENT ) {
        //check if the var is defined
        string lexeme = t.GetLexeme();
        if (!(defVar.find(lexeme)->second))
        {
            ParseError(line, "Undefined Variable");
            return false;
        }
        return true;
    }
    else if( t.GetToken() == ICONST ) {

        return true;
    }
    else if( t.GetToken() == SCONST ) {

        return true;
    }
    else if( t.GetToken() == RCONST ) {

        return true;
    }
    else if( t.GetToken() == LPAREN ) {
        bool status = Expr(in, line);
        if( !status ) {
            ParseError(line, "Missing expression after (");
            return false;
        }
        if( Parser::GetNextToken(in, line) == RPAREN )
            return status;

        ParseError(line, "Missing ) after expression");
        return false;
    }
    else if(t.GetToken() == ERR){
        ParseError(line, "Unrecognized Input Pattern");
        cout << "(" << t.GetLexeme() << ")" << endl;
        return false;
    }

    ParseError(line, "Unrecognized input");
    return 0;

}








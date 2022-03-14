//
// Created by samikshya poudel on 11/10/21.
//

#ifndef CS_280_FALL_PARSER_LEX_H
#define CS_280_FALL_PARSER_LEX_H



#include <string>
#include <iostream>
#include <map>
using namespace std;


//Definition of all the possible token types
enum Token {
    // keywords
    PROGRAM, WRITE, INT, END, IF, FLOAT, STRING,

    // an identifier
    REPEAT, BEGIN, IDENT,

    // an integer, real, and string constant
    ICONST, RCONST, SCONST,

    // the operators, parens, semicolon
    PLUS, MINUS, MULT, DIV, REM, ASSOP, LPAREN, RPAREN, COMMA,
    EQUAL, GTHAN, SEMICOL,
    // any error returns this token
    ERR,

    // when completed (EOF), return this token
    DONE
};


//Class definition of LexItem
class LexItem {
    Token	token;
    string	lexeme;
    int	lnum;

public:
    LexItem() {
        token = ERR;
        lnum = -1;
    }
    LexItem(Token token, string lexeme, int line) {
        this->token = token;
        this->lexeme = lexeme;
        this->lnum = line;
    }

    bool operator==(const Token token) const { return this->token == token; }
    bool operator!=(const Token token) const { return this->token != token; }

    Token	GetToken() const { return token; }
    string	GetLexeme() const { return lexeme; }
    int	GetLinenum() const { return lnum; }
};



extern ostream& operator<<(ostream& out, const LexItem& tok);
extern LexItem id_or_kw(const string& lexeme, int linenum);
extern LexItem getNextToken(istream& in, int& linenum);









#endif //CS_280_FALL_PARSER_LEX_H

#pragma once
#include <string>

enum class TokenType {
    id,
    INT,
    FLOAT,
    sum, res, mul, div,
    assing,
    Lparen, Rparen,
    semiColon,
    End_of_line,
    unknown
};

struct Token {
    
    TokenType type;
    std::string lexeme;
    int line;
    int col;
};

class lexer
{
private:
    std::string input;
    size_t pos;
    int line;
    int col;

    char peek() const;
    char get() const;
    void skipWhiteSpace();
    Token identifier();
    Token number();    
    
public:
     explicit lexer(const std::string& input);
     Token genNextToken();
};




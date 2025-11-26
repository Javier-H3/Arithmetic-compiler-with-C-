#include "lexer.h"
#include <cctype>

lexer::lexer(const std::string& input):input(input), pos(0), line(1), col(1) {}

char lexer::peek() const {
    if (pos >= input.size()) return '\0';
    return input[pos];
}

char lexer::get() {
    if (pos >= input.size()) return '\0';
    char c = input[pos++];
    if (c == '\n') {
        line++;
        col = 1;
    } else {
        col++;
    }
    return c;
}

void lexer::skipWhiteSpace() {
    while (std::isspace(static_cast<unsigned char>(peek()))) {
        get();
    }
}

Token lexer::identifier() {
    int startCol = col;
    std::string lex;
    char c = peek();

    while (std::isalpha(static_cast<unsigned char>(c)) ||
           std::isdigit(static_cast<unsigned char>(c)) ||
           c == '_') {
        lex.push_back(get());
        c = peek();
    }

    Token tok;
    tok.type = TokenType::id;
    tok.lexeme = lex;
    tok.line = line;
    tok.col = startCol;
    return tok;
}

Token lexer::number() {
    int startCol = col;
    std::string lex;
    bool isFloat = false;

    char c = peek();
    while (std::isdigit(static_cast<unsigned char>(c))) {
        lex.push_back(get());
        c = peek();
    }

    if (c == '.') {
        isFloat = true;
        lex.push_back(get());
        c = peek();
        while (std::isdigit(static_cast<unsigned char>(c))) {
            lex.push_back(get());
            c = peek();
        }
    }

    Token tok;
    tok.lexeme = lex;
    tok.line = line;
    tok.col = startCol;
    tok.type = isFloat ? TokenType::FLOAT : TokenType::INT;
    return tok;
}

Token lexer::getNextToken() {
    skipWhiteSpace();

    int startCol = col;
    char c = peek();

    if (c == '\0') {
        return Token{TokenType::End_of_line, "", line, startCol};
    }

    if (std::isalpha(static_cast<unsigned char>(c)) || c == '_') {
        return identifier();
    }

    if (std::isdigit(static_cast<unsigned char>(c))) {
        return number();
    }

    get();

    Token tok;
    tok.lexeme = std::string(1, c);
    tok.line = line;
    tok.col = startCol;

    switch (c) {
        case '+':
            tok.type = TokenType::sum;
            break;
        case '-':
            tok.type = TokenType::res;
            break;
        case '*':
            tok.type = TokenType::mul;
            break;
        case '/':
            tok.type = TokenType::div;
            break;
        case '=':
            tok.type = TokenType::assing;
            break;
        case '(':
            tok.type = TokenType::Lparen;
            break;
        case ')':
            tok.type = TokenType::Rparen;
            break;
        case ';':
            tok.type = TokenType::semiColon;
            break;
        default:
            tok.type = TokenType::unknown;
            break;
    }
    return tok;
}
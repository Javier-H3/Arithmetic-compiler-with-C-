#pragma once

#include <memory>
#include <string>
#include "lexer.h"   
#include "ast.h"

class parser {
public:
    explicit parser(lexer& lexer);

    std::unique_ptr<Program> parseProgram();

private:
    lexer& _lexer;
    Token currentToken;

    void advance();  
    bool match(TokenType expected); 
    void expect(TokenType expected, const std::string& message);

    std::unique_ptr<ASTnode> parseStatement();
    std::unique_ptr<AssignmentStmt> parseAssignment();

    std::unique_ptr<Expr> parseExpr();   
    std::unique_ptr<Expr> parseTerm();   
    std::unique_ptr<Expr> parseFactor();
};

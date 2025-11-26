#pragma once

#include <memory>
#include <string>
#include "lexer.h"   
#include "ast.h"

class parser {
public:
    explicit parser(lexer& lexer);

    // Punto de entrada: parsea todo el programa
    std::unique_ptr<Program> parseProgram();

private:
    lexer& _lexer;
    Token currentToken;

    // Funciones auxiliares
    void advance();  // lee siguiente token
    bool match(TokenType expected);  // si coincide, consume
    void expect(TokenType expected, const std::string& message);

    // Reglas de la gramática
    std::unique_ptr<ASTnode> parseStatement();
    std::unique_ptr<AssignmentStmt> parseAssignment();

    std::unique_ptr<Expr> parseExpr();   
    std::unique_ptr<Expr> parseTerm();   
    std::unique_ptr<Expr> parseFactor();
};

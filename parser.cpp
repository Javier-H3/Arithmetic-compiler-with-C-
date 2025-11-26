#include "parser.h"
#include <stdexcept>
#include <iostream>

parser::parser(lexer& lexer) : _lexer(lexer) {
    currentToken = this->_lexer.getNextToken();
}

void parser::advance() {
    currentToken = _lexer.getNextToken();
}

bool parser::match(TokenType expected) {
    if (currentToken.type == expected) {
        advance();
        return true;
    }
    return false;
}

void parser::expect(TokenType expected, const std::string& message) {
    if (!match(expected)) {
        throw std::runtime_error(
            message + " (línea " + std::to_string(currentToken.line) +
            ", col " + std::to_string(currentToken.col) + ")"
        );
    }
}

std::unique_ptr<Program> parser::parseProgram() {
    auto program = std::make_unique<Program>();

    while (currentToken.type != TokenType::End_of_line &&
           currentToken.type != TokenType::unknown) {
        program->statements.push_back(parseStatement());
    }

    if (currentToken.type != TokenType::End_of_line) {
        throw std::runtime_error("Se esperaba fin de entrada");
    }

    return program;
}

std::unique_ptr<ASTnode> parser::parseStatement() {
    if (currentToken.type == TokenType::id) {
        return parseAssignment();
    }

    throw std::runtime_error(
        "Se esperaba un identificador al inicio de la sentencia (línea " +
        std::to_string(currentToken.line) + ")"
    );
}

std::unique_ptr<AssignmentStmt> parser::parseAssignment() {
    std::string varName = currentToken.lexeme;

    expect(TokenType::id, "Se esperaba un identificador en la asignación");
    expect(TokenType::assing, "Se esperaba '=' en la asignación");

    auto expr = parseExpr();

    expect(TokenType::semiColon, "Se esperaba ';' al final de la asignación");

    auto node = std::make_unique<AssignmentStmt>();
    node->variableName = varName;
    node->expr = std::move(expr);
    return node;
}

std::unique_ptr<Expr> parser::parseExpr() {
    auto left = parseTerm();

    while (currentToken.type == TokenType::sum ||
           currentToken.type == TokenType::res) {

        std::string op;
        if (currentToken.type == TokenType::sum) op = "+";
        else op = "-";

        advance();

        auto right = parseTerm();

        auto bin = std::make_unique<BinaryExpr>();
        bin->Operator = op;
        bin->left = std::move(left);
        bin->right = std::move(right);

        left = std::move(bin);
    }

    return left;
}

std::unique_ptr<Expr> parser::parseTerm() {
    auto left = parseFactor();

    while (currentToken.type == TokenType::mul ||
           currentToken.type == TokenType::div) {

        std::string op;
        if (currentToken.type == TokenType::mul) op = "*";
        else op = "/";

        advance();

        auto right = parseFactor();

        auto bin = std::make_unique<BinaryExpr>();
        bin->Operator = op;
        bin->left = std::move(left);
        bin->right = std::move(right);

        left = std::move(bin);
    }

    return left;
}

std::unique_ptr<Expr> parser::parseFactor() {
    // Número entero
    if (currentToken.type == TokenType::INT) {
        auto num = std::make_unique<NumberExpr>();
        num->value = currentToken.lexeme;
        num->literalType = ValueType::type_int;
        advance();
        return num;
    }

    // float numbers
    if (currentToken.type == TokenType::FLOAT) {
        auto num = std::make_unique<NumberExpr>();
        num->value = currentToken.lexeme;
        num->literalType = ValueType::type_float;
        advance();
        return num;
    }

    // vars
    if (currentToken.type == TokenType::id) {
        auto var = std::make_unique<VariableExpr>();
        var->name = currentToken.lexeme;
        advance();
        return var;
    }

    // parens
    if (currentToken.type == TokenType::Lparen) {
        advance();
        auto expr = parseExpr();
        expect(TokenType::Rparen, "Se esperaba ')' para cerrar la expresión");
        return expr;
    }

    throw std::runtime_error(
        "Token inesperado en factor: '" + currentToken.lexeme +
        "' (línea " + std::to_string(currentToken.line) + ")"
    );
}

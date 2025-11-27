#include "lexer.h"
#include <string>
#include <vector>
#include <iostream>

std::string tokenCategory(TokenType t) {
    switch (t) {
        case TokenType::id:    return "id";
        case TokenType::INT:   return "int";
        case TokenType::FLOAT: return "float";

        case TokenType::sum:
        case TokenType::res:
        case TokenType::mul:
        case TokenType::div:
            return "operator";

        case TokenType::assing:
            return "assignment";

        case TokenType::Lparen:
        case TokenType::Rparen:
            return "parentesis";

        case TokenType::semiColon:
            return "separator";

        case TokenType::End_of_line:
            return "EOF";

        default:
            return "unknown";
    }
}

void printTokenTable(const std::vector<Token>& tokens) {
    std::cout << "===== TABLA DE TOKENS =====\n";
    std::cout << "Token\tTipo\n";
    std::cout << "---------------------------\n";
    for (const auto& t : tokens) {
        if (t.type == TokenType::End_of_line) break;
        std::cout << t.lexeme << "\t" << tokenCategory(t.type) << "\n";
    }
    std::cout << "===========================\n";
}

#include <iostream>
#include <string>
#include "lexer.h"
#include "parser.h"
#include "symbol_table.h"
#include "type_table.h"
#include "semantic.h"
#include "tokens_table.h"

int main() {
    
    std::cout <<"User, enter your code, end your code with the word {END}."<<"\n";
    
    //For now, this is the only way to input strings into the compiler.
    std::string source;
    std::string line;

    while (true) {
        std::getline(std::cin, line);
        if (!std::cin) break;
        if (line == "END") break;
        source += line + "\n";      
    }
    

    // 1. Lexer
    lexer lexTokens(source);
    std::vector<Token> tokens;

    while (true) {
        Token t = lexTokens.getNextToken();
        tokens.push_back(t);
        if (t.type == TokenType::End_of_line)
            break;
    }

    printTokenTable(tokens);

    // 2. Parser

    lexer lex(source);
    parser p(lex);

    std::unique_ptr<Program> prog;

    try {
        prog = p.parseProgram();
        std::cout << "Parseo correcto.\n";
    } catch (const std::exception& e) {
        std::cerr << "Error de parseo: " << e.what() << '\n';
        return 1;
    }

    // 3. Tables
    SymbolTable symTable;
    TypeTable typeTable;
    SemanticAnalyzer sem(symTable, typeTable);

    sem.analyze(prog.get());

    // 4. Print tables 
    std::cout << "\n"<<"\n";
    symTable.print();
    std::cout << "\n"<<"\n";
    typeTable.print();

    system("pause"); //Add this pause because it closes as soon as it compiles.
    return 0;
}


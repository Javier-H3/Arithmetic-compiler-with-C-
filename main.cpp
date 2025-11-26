#include <iostream>
#include <string>
#include "lexer.h"
#include "parser.h"
#include "symbol_table.h"
#include "type_table.h"
#include "semantic.h"

int main() {
    //For now, this is the only way to input strings into the compiler.
    std::string source =
        "a = 5 + 3 * 2;\n"
        "b = a / 2.0;\n";

    // 1. Lexer
    lexer lex(source);

    // 2. Parser
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
    std::cout << "\n";
    symTable.print();
    std::cout << "\n";
    typeTable.print();

    system("pause"); //Add this pause because it closes as soon as it compiles.
    return 0;
}


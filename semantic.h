#pragma once
#include "ast.h"
#include "symbol_table.h"
#include "type_table.h"

class SemanticAnalyzer {

    private:
    
        SymbolTable& symTable;
        TypeTable& typeTable;

        ValueType analyzeExpr(Expr* expr){
           if (auto* num = dynamic_cast<NumberExpr*>(expr)) {
                expr->inferredType = num->literalType;
                return expr->inferredType;
           }

          if (auto* var = dynamic_cast<VariableExpr*>(expr)) {
            auto* info = symTable.lookup(var->name);
            expr->inferredType = info ? info->type : ValueType::type_error;
            return expr->inferredType;
        }
        if (auto* bin = dynamic_cast<BinaryExpr*>(expr)) {
            ValueType leftT = analyzeExpr(bin->left.get());
            ValueType rightT = analyzeExpr(bin->right.get());
            ValueType res = typeTable.resultTypeFor(bin->Operator, leftT, rightT);
            expr->inferredType = res;
            return res;
        }
        return ValueType::type_error;          
     }
    public:

    SemanticAnalyzer(SymbolTable& sym, TypeTable& tt)
        : symTable(sym), typeTable(tt) {}

    void analyze(Program* program) {
        for (auto& stmt : program->statements) {
            if (auto* asg = dynamic_cast<AssignmentStmt*>(stmt.get())) {
                ValueType t = analyzeExpr(asg->expr.get());
                symTable.insert(asg->variableName, t);
            }
        }
    }
    
};
#pragma once
#include <string>
#include <memory>
#include <vector>

enum class ValueType {
    type_int,
    type_float,
    type_error
};

struct ASTnode {
    virtual ~ASTnode() = default;
};

struct Expr: public ASTnode {
    ValueType inferredType = ValueType::type_error;
};

struct NumberExpr : public Expr {
    std::string value;
    ValueType literalType;
};

struct VariableExpr : public Expr {
    std::string name;
};

struct BinaryExpr : public Expr {
    std::string Operator;
    std::unique_ptr<Expr> left;
    std::unique_ptr<Expr> right;
};


struct AssignmentStmt : public ASTnode {
    std::string variableName;
    std::unique_ptr<Expr> expr;
};

struct Program : public ASTnode {
    std::vector<std::unique_ptr<ASTnode>> statements;
};


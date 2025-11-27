#pragma once
#include "ast.h"
#include <array>
#include <iostream>

class TypeTable
{
private:
    std::array<std::array<ValueType, 3>, 3> addTable;
    std::array<std::array<ValueType, 3>, 3> mulTable;

    void printTable(const std::array<std::array<ValueType,3>,3>& table) const {
        std::string names[3] = {"int", "float", "error"};
        std::cout<<"\t";

        for(int j = 0; j < 3; j++) std::cout<<names[j]<<"\t";
        
        std::cout<<"\n";

        for (int i = 0; i < 3; i++) {
            std::cout<<names[i]<<"\t";
            for (int j = 0; j < 3; j++) {
                std::cout<<names[(int)table[i][j]]<<"\t";
            }
            std::cout<<"\n";
        }       
    }

public:
    TypeTable () {
        for (auto &row : addTable) row.fill(ValueType::type_error);
        for (auto &row : mulTable) row.fill(ValueType::type_error);

        addTable[(int)ValueType::type_int]  [(int)ValueType::type_int]   = ValueType::type_int;
        addTable[(int)ValueType::type_int]  [(int)ValueType::type_float] = ValueType::type_float;
        addTable[(int)ValueType::type_float][(int)ValueType::type_int]   = ValueType::type_float;
        addTable[(int)ValueType::type_float][(int)ValueType::type_float] = ValueType::type_float;
        
        mulTable = addTable;
    }

    ValueType resultTypeFor(const std::string& op, ValueType left, ValueType right) {
        if (op == "+" || op == "-")
          return addTable[(int)left][(int)right];
        if (op == "*" || op == "/")
            return mulTable[(int)left][(int)right];
          return ValueType::type_error; 
    }

    void print() const {
        std::cout << "===== TABLA DE TIPOS (Suma/Resta) =====\n";
        printTable(addTable);
        std::cout << "===== TABLA DE TIPOS (Mult/Div) =====\n";
        printTable(mulTable);
    }
};

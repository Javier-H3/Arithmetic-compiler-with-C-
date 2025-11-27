//symbol_table.h
#pragma once
#include <string>
#include <unordered_map>
#include <iostream>
#include "ast.h"

struct SymbolInfo {
    std::string name;
    ValueType type;
};

class SymbolTable {

    private:
        std::unordered_map<std::string, SymbolInfo> table;

        std::string valueTypeToString(ValueType t) const {
            switch (t) {
            case ValueType::type_int: return "int";
            case ValueType::type_float: return "float";
            default: return "error";
            }
        }

    public:
        bool insert(const std::string& name, ValueType type){
            if (table.find(name) != table.end()) return false;
            table[name] = SymbolInfo{name, type};
            return true;
        }

        SymbolInfo* lookup(const std::string& name) {
            auto it = table.find(name);
            if (it == table.end()) return nullptr;
            return &it->second;
        }

        void print() const {
            std::cout << "===== TABLA DE SIMBOLOS =====\n";
            std::cout << "Nombre\tTipo\n";
            std::cout << "-----------------------------\n";
                for (const auto& [k, sym] : table) {
                    std::cout << sym.name << "\t" << valueTypeToString(sym.type) << "\n";
                }
            std::cout << "=============================\n";
    }
};

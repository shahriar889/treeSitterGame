#pragma once

#include <cpp-tree-sitter.h>
#include <filesystem>
#include <string_view>
#include <fstream>
#include <rule.h>

extern "C" {
    TSLanguage* tree_sitter_socialgaming();
}

class Parser {
    public:
        Parser(const std::string_view&);
        Rule createRuleAbstraction();

    private:
        std::string getSourceCode(const std::string_view&);
        ts::Tree syntaxTree;
};
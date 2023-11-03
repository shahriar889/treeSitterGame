#pragma once

#include <cpp-tree-sitter.h>
#include <filesystem>
#include <string_view>
#include <fstream>
#include <string>
#include <iostream>
#include <memory>
#include "rule.h"

extern "C" {
    TSLanguage* tree_sitter_socialgaming();
}

class Parser {
    public:
        explicit Parser(const std::string_view&);
        void createRuleAbstraction();

    private:
        std::unique_ptr<ts::Tree> syntaxTree;
        std::string sourceCode;

        //Helpers
        void dfs(ts::Node);
        std::string getSourceCode(const std::string_view&);
};
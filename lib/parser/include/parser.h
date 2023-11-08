#pragma once

#include <cpp-tree-sitter.h>
#include <filesystem>
#include <string_view>
#include <fstream>
#include <string>
#include <iostream>
#include <memory>
#include <typeinfo>
#include "rules.h"
#include "ruleManager.h"
#include "ruleTranslator.h"

extern "C"
{
    TSLanguage *tree_sitter_socialgaming();
}

class Parser
{
public:
    explicit Parser(const std::string_view &);
    RuleManager createRuleManager();

private:
    std::unique_ptr<ts::Tree> syntaxTree;
    std::string sourceCode;

    // Helpers
    void dfs(ts::Node, std::vector<Translator::RulePointer> &);
    std::string getSourceCode(const std::string_view &);
};
#pragma once

#include "rules.h"
#include "ruleTranslator.h"
#include "treeManager.h"

// Receives a vector of rules from Parser, and iterates over them to construct a game's rules
class RuleManager {
public:
    using RulePointer = std::unique_ptr<Rule>;
    RuleManager() = default;
    RuleManager(std::shared_ptr<StateManager>);
    void configure(TM::TreeManager& tm);
    void start();

protected:
    std::shared_ptr<StateManager> globalState;

private:
    void dfs(ts::Node node, std::vector<Translator::RulePointer>&);
    std::vector<Expression> getExpressions(ts::Node);
    std::vector<RulePointer> rules;
};


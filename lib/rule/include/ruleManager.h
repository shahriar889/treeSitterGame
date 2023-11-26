#pragma once

#include "rules.h"

// Receives a vector of rules from Parser, and iterates over them to construct a game's rules
class RuleManager {
public:
    using RulePointer = std::unique_ptr<Rule>;
    RuleManager() = default;
    RuleManager(std::vector<RulePointer>);
    void start();
    void setGlobalState(std::shared_ptr<StateManager>);

protected:
    std::shared_ptr<StateManager> globalState;

private:
    std::vector<RulePointer> rules;
};


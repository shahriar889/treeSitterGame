#pragma once

#include "rules.h"

// Receives a vector of rules from Parser, and iterates over them to construct a game's rules
class RuleManager {
public:
    using RulePointer = std::unique_ptr<Rule>;
    RuleManager(std::vector<RulePointer>);
    void start();
private:
    std::vector<RulePointer> rules;
};
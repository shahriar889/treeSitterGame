#pragma once

#include "rule.h"

class RuleManager {
public:
    using RulePointer = std::unique_ptr<Rule>;
    RuleManager(std::vector<RulePointer>);
    void start();
private:
    std::vector<RulePointer> rules;
};
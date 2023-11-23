#include "ruleManager.h"

RuleManager::RuleManager(std::vector<RulePointer> rp, std::shared_ptr<StateManager> states) :
    rules{std::move(rp)}, globalState{states} {};

RuleManager::RuleManager(std::vector<RulePointer> rp) :
    rules{std::move(rp)} {};

void RuleManager::start() {
    std::for_each(rules.begin(), rules.end(), [](const RulePointer& rp) {
        rp->execute();
    });
}
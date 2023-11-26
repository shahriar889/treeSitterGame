#include "ruleManager.h"

RuleManager::RuleManager(std::vector<RulePointer> r) :
    rules{std::move(r)} {};

void RuleManager::start() {
    std::for_each(rules.begin(), rules.end(), [this](const RulePointer& rp) {
        rp->execute(this->globalState);
    });
}

void RuleManager::setGlobalState(std::shared_ptr<StateManager> states) {
    globalState = states;
}

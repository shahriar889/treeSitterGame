#include "ruleManager.h"

RuleManager::RuleManager(std::shared_ptr<StateManager> states) :
    globalState{states} {};

void RuleManager::start() {
    std::for_each(rules.begin(), rules.end(), [](const RulePointer& rp) {
        rp->execute();
    });
}

void RuleManager::configure(TM::TreeManager& tm) {
    ts::Node root = tm.getRoot();
    ts::Node rulesNode = root.getChildByFieldName("rules");
    std::vector<Translator::RulePointer> rules;
    dfs(rulesNode, rules);

    this->rules = std::move(rules);
}

void RuleManager::dfs(ts::Node node, std::vector<Translator::RulePointer>& rules) {
    Translator translator = buildTreeSitterTranslator();
    auto numChildren = node.getNumNamedChildren();

    auto rule = translator.createOperation(std::string{node.getType()});

    std::vector<Translator::RulePointer> nestedRules;
    if (rule && rule->isNested()) {
        for (int i = 0; i < numChildren; i++) {
             dfs(node.getNamedChild(i), nestedRules);
        }
    }
    else {
        for (int i = 0; i < numChildren; i++) {
            dfs(node.getNamedChild(i), rules);
        }
    }

    if (rule) {
        if (rule->isNested()) {
            dynamic_cast<NestedRule*>(rule.get())->setRules(std::move(nestedRules));
        }
        rules.emplace_back(std::move(rule));
    }
}

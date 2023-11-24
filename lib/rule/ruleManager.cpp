#include "ruleManager.h"

RuleManager::RuleManager(std::shared_ptr<StateManager> states) :
    globalState{states} {};

void RuleManager::start() {
    std::for_each(rules.begin(), rules.end(), [this](const RulePointer& rp) {
        rp->execute(this->globalState);
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
    std::vector<Expression> expressions;
    auto rule = translator.createOperation(std::string{node.getType()}, expressions);

    std::vector<Translator::RulePointer> nestedRules;
    if (rule && rule->isNested()) {
        for (int i = 0; i < node.getNumNamedChildren(); i++) {
             dfs(node.getNamedChild(i), nestedRules);
        }
    }
    else {
        for (int i = 0; i < node.getNumNamedChildren(); i++) {
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

std::vector<Expression> RuleManager::getExpressions(ts::Node node) {
    std::vector<Expression> expressions;
    for (int i = 0; i < node.getNumChildren(); i++) {
        ts::Node child = node.getNamedChild(i);
        if (child.getType() == "expression") {
            //expressions.emplace_back();
        }
    }

    return expressions;
}

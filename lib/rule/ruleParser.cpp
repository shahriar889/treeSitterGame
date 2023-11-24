#include "ruleParser.h"

RuleManager RuleParser::createRuleManager(TM::TreeManager& tm) {
    ts::Node root = tm.getRoot();
    ts::Node rulesNode = root.getChildByFieldName("rules");
    std::vector<Translator::RulePointer> rules;
    
    dfs(rulesNode, rules);
    RuleManager ruleManager = RuleManager(std::move(rules));

    return std::move(ruleManager);
}

void RuleParser::dfs(ts::Node node, std::vector<Translator::RulePointer>& rules) {
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

std::vector<Expression> RuleParser::getExpressions(ts::Node node, TM::TreeManager& tm) {
    std::vector<Expression> expressions;
    for (int i = 0; i < node.getNumChildren(); i++) {
        ts::Node child = node.getNamedChild(i);
        if (child.getType() == "expression") {
            //expressions.emplace_back();
        }
    }

    return expressions;
}

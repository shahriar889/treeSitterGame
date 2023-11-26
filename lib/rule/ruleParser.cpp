#include "ruleParser.h"

RuleManager RuleParser::createRuleManager(TM::TreeManager& tm) {
    ts::Node root = tm.getRoot();
    ts::Node rulesNode = root.getChildByFieldName("rules");
    std::vector<Translator::RulePointer> rules;
    
    dfs(tm, rulesNode, rules);
    RuleManager ruleManager = RuleManager(std::move(rules));

    return std::move(ruleManager);
}

void RuleParser::dfs(TM::TreeManager& tm, ts::Node node, std::vector<Translator::RulePointer>& rules) {
    Translator translator = buildTreeSitterTranslator();
    std::vector<Expression> expressions = getExpressions(tm, node);
    auto rule = translator.createOperation(std::string{node.getType()}, expressions);

    std::vector<Translator::RulePointer> nestedRules;
    if (rule && rule->isNested()) {
        for (int i = 0; i < node.getNumNamedChildren(); i++) {
             dfs(tm, node.getNamedChild(i), nestedRules);
        }
    }
    else {
        for (int i = 0; i < node.getNumNamedChildren(); i++) {
            dfs(tm, node.getNamedChild(i), rules);
        }
    }

    if (rule) {
        if (rule->isNested()) {
            dynamic_cast<NestedRule*>(rule.get())->setRules(std::move(nestedRules));
        }
        rules.emplace_back(std::move(rule));
    }
}

std::vector<Expression> RuleParser::getExpressions(TM::TreeManager& tm, ts::Node node) {
    std::vector<Expression> expressions;
    for (int i = 0; i < node.getNumNamedChildren(); i++) {
        ts::Node child = node.getNamedChild(i);
        if (child.getType() != "body") {
            auto e = Expression{tm.getSourceRange(child)};
            expressions.push_back(e);
        }
    }
    return expressions;
}
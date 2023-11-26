#include "rules.h"
#include "treeManager.h"
#include "ruleManager.h"
#include "ruleTranslator.h"

// Receives a vector of rules from Parser, and iterates over them to construct a game's rules
class RuleParser {
public:
    using RulePointer = std::unique_ptr<Rule>;
    static RuleManager createRuleManager(TM::TreeManager& tm);

private:
    static void dfs(TM::TreeManager&, ts::Node, std::vector<Translator::RulePointer>&);
    static std::vector<Expression> getExpressions(TM::TreeManager&, ts::Node);
};

#include "rules.h"
#include "treeManager.h"
#include "ruleManager.h"
#include "ruleTranslator.h"

class RuleParser {
public:
    using RulePointer = std::unique_ptr<Rule>;
    static RuleManager createRuleManager(TM::TreeManager&, const Translator&);

private:
    static void dfs(TM::TreeManager&, ts::Node, std::vector<Translator::RulePointer>&, const Translator&);
    static std::vector<Expression> getExpressions(TM::TreeManager&, ts::Node);
};

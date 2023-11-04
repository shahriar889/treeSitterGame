#include "rules.h"

class RuleFactory {
public:
    std::unique_ptr<Rule> create() {
        return createImpl();
    };
private:
    virtual std::unique_ptr<Rule> createImpl() = 0;
};

class ForEachLoopFactory final : public RuleFactory {
private:
    std::unique_ptr<Rule> createImpl() override;
};

class WhileLoopFactory final : public RuleFactory {
private:
    std::unique_ptr<Rule> createImpl() override;
};

class ParallelForLoopFactory final : public RuleFactory {
private:
    std::unique_ptr<Rule> createImpl() override;
};

class MatchLoopFactory final : public RuleFactory {
private:
    std::unique_ptr<Rule> createImpl() override;
};

class ExtendListFactory final : public RuleFactory {
private:
    std::unique_ptr<Rule> createImpl() override;
};

class DiscardListFactory final : public RuleFactory {
private:
    std::unique_ptr<Rule> createImpl() override;
};

class MessageOutputRuleFactory final : public RuleFactory {
private:
    std::unique_ptr<Rule> createImpl() override;
};
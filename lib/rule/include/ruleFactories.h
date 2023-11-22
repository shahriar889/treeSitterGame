#include "rules.h"

class RuleFactory {
public:
    std::unique_ptr<Rule> create() {
        return createImpl();
    };

    virtual ~RuleFactory() = default;
private:
    virtual std::unique_ptr<Rule> createImpl() = 0;
};

class NestedRuleFactory : public RuleFactory {
    public:
        std::unique_ptr<Rule> create() {
            return createImpl();
        }
        private:
        virtual std::unique_ptr<Rule> createImpl() = 0;
};

class PrimitiveRuleFactory : public RuleFactory{
    public:
        std::unique_ptr<Rule> create() {
            return createImpl();
        }
        private:
        virtual std::unique_ptr<Rule> createImpl() = 0;
};

class ForEachLoopFactory final : public NestedRuleFactory {
private:
    std::unique_ptr<Rule> createImpl() override;
};

class WhileLoopFactory final : public NestedRuleFactory {
private:
    std::unique_ptr<Rule> createImpl() override;
};

class ParallelForLoopFactory final : public NestedRuleFactory {
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

class AssignmentRuleFactory final : public RuleFactory {
private:
    std::unique_ptr<Rule> createImpl() override;
};
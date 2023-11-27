#include "rules.h"

class RuleFactory {
public:
    virtual ~RuleFactory() = default;
    std::unique_ptr<Rule> create(std::vector<Expression> expressions) {
        return createImpl(expressions);
    };
private:
    virtual std::unique_ptr<Rule> createImpl(std::vector<Expression>) = 0;
};

class NestedRuleFactory : public RuleFactory {
public:
    std::unique_ptr<Rule> create(std::vector<Expression> expressions) {
        return createImpl(expressions);
    }
private:
    virtual std::unique_ptr<Rule> createImpl(std::vector<Expression>) = 0;
};

class PrimitiveRuleFactory : public RuleFactory{
public:
    std::unique_ptr<Rule> create(std::vector<Expression> expressions) {
        return createImpl(expressions);
    }
private:
    virtual std::unique_ptr<Rule> createImpl(std::vector<Expression>) = 0;
};

class ForEachLoopFactory final : public NestedRuleFactory {
private:
    std::unique_ptr<Rule> createImpl(std::vector<Expression>) override;
};

class WhileLoopFactory final : public NestedRuleFactory {
private:
    std::unique_ptr<Rule> createImpl(std::vector<Expression>) override;
};

class ParallelForLoopFactory final : public NestedRuleFactory {
private:
    std::unique_ptr<Rule> createImpl(std::vector<Expression>) override;
};

class MatchLoopFactory final : public RuleFactory {
private:
    std::unique_ptr<Rule> createImpl(std::vector<Expression>) override;
};

class ExtendListFactory final : public RuleFactory {
private:
    std::unique_ptr<Rule> createImpl(std::vector<Expression>) override;
};

class DiscardListFactory final : public RuleFactory {
private:
    std::unique_ptr<Rule> createImpl(std::vector<Expression>) override;
};

class MessageOutputRuleFactory final : public RuleFactory {
private:
    std::unique_ptr<Rule> createImpl(std::vector<Expression>) override;
};

class AssignmentRuleFactory final : public RuleFactory {
private:
    std::unique_ptr<Rule> createImpl(std::vector<Expression>) override;
};

class InputChoiceRuleFactory final : public RuleFactory {
private:
    std::unique_ptr<Rule> createImpl(std::vector<Expression>) override;
};
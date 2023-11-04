#include "ruleFactories.h"

class ForEachLoopFactory final : public RuleFactory {
private:
    std::unique_ptr<Rule> createImpl() override {
    return std::make_unique<ForEachLoopRule>();
  }
};

class WhileLoopFactory final : public RuleFactory {
private:
    std::unique_ptr<Rule> createImpl() override {
    return std::make_unique<WhileLoopRule>();
  }
};

class ParallelForLoopFactory final : public RuleFactory {
private:
    std::unique_ptr<Rule> createImpl() override {
    return std::make_unique<ParallelForLoopRule>();
  }
};

class MatchLoopFactory final : public RuleFactory {
private:
    std::unique_ptr<Rule> createImpl() override {
    return std::make_unique<MatchLoopRule>();
  }
};

class ExtendListFactory final : public RuleFactory {
private:
    std::unique_ptr<Rule> createImpl() override {
    return std::make_unique<ExtendListRule>();
  }
};

class DiscardListFactory final : public RuleFactory {
private:
    std::unique_ptr<Rule> createImpl() override {
    return std::make_unique<DiscardListRule>();
  }
};

class MessageOutputRuleFactory final : public RuleFactory {
private:
    std::unique_ptr<Rule> createImpl() override {
    return std::make_unique<MessageOutputRule>();
  }
};

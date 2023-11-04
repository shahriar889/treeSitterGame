#include "rule.h"

class ForEachLoopRule : public Rule {
private:
    void executeImpl() override {
        std::cout << "Executing For-Each loop...\n";
    }
};

class ForEachLoopFactory final : public RuleFactory {
private:
    std::unique_ptr<Rule> createImpl() override {
    return std::make_unique<ForEachLoopRule>();
  }
};

class WhileLoopRule : public Rule {
private:
    void executeImpl() override {
        std::cout << "Executing While loop...\n";
    }
};

class WhileLoopFactory final : public RuleFactory {
private:
    std::unique_ptr<Rule> createImpl() override {
    return std::make_unique<WhileLoopRule>();
  }
};

class ParallelForLoopRule : public Rule {
private:
    void executeImpl() override {
        std::cout << "Executing Parallel-For loop...\n";
    }
};

class ParallelForLoopFactory final : public RuleFactory {
private:
    std::unique_ptr<Rule> createImpl() override {
    return std::make_unique<ParallelForLoopRule>();
  }
};

class MatchLoopRule : public Rule {
private:
    void executeImpl() override {
        std::cout << "Executing Match loop...\n";
    }
};

class MatchLoopFactory final : public RuleFactory {
private:
    std::unique_ptr<Rule> createImpl() override {
    return std::make_unique<MatchLoopRule>();
  }
};

class ExtendListRule : public Rule {
private:
    void executeImpl() override {
        std::cout << "Executing Extend list...\n";
    }
};

class ExtendListFactory final : public RuleFactory {
private:
    std::unique_ptr<Rule> createImpl() override {
    return std::make_unique<ExtendListRule>();
  }
};

class DiscardListRule : public Rule {
private:
    void executeImpl() override {
        std::cout << "Executing Discard list...\n";
    }
};

class DiscardListFactory final : public RuleFactory {
private:
    std::unique_ptr<Rule> createImpl() override {
    return std::make_unique<DiscardListRule>();
  }
};


class MessageOutputRule : public Rule {
private:
    void executeImpl() override {
        std::cout << "Executing Message output...\n";
    }
};

class MessageOutputRuleFactory final : public RuleFactory {
private:
    std::unique_ptr<Rule> createImpl() override {
    return std::make_unique<MessageOutputRule>();
  }
};

class AssignmentRule : public Rule {
private:
    void executeImpl() override {
        std::cout << "Executing Assignment...\n";
    }
};

class AssignmentRuleFactory final : public RuleFactory {
private:
    std::unique_ptr<Rule> createImpl() override {
    return std::make_unique<AssignmentRule>();
  }
};
void Translator::registerFactory(std::string spelling, FactoryPointer factory) noexcept {
  canonicalizeSpelling(spelling);
  factories[spelling] = std::move(factory);
}

Translator buildTreeSitterTranslator() noexcept {
    Translator translator = Translator{};

    //Control Structures
    translator.registerFactory("for", std::make_unique<ForEachLoopFactory>());
    translator.registerFactory("loop", std::make_unique<WhileLoopFactory>());
    translator.registerFactory("parallel_for", std::make_unique<ParallelForLoopFactory>());
    translator.registerFactory("match", std::make_unique<MatchLoopFactory>());

    //List Operations
    translator.registerFactory("extend", std::make_unique<ExtendListFactory>());
    translator.registerFactory("discard", std::make_unique<DiscardListFactory>());

    //Output Operations
    translator.registerFactory("message", std::make_unique<MessageOutputRuleFactory>());

    //Assignment Operations
    translator.registerFactory("assignment", std::make_unique<AssignmentRuleFactory>());

    return translator;
}

Translator::RulePointer
Translator::createOperation(std::string spelling) const noexcept {
  auto factory = factories.find(spelling);
  if (factory == factories.end()) {
    return {};
  }

  return factory->second->create();
}

static void canonicalizeSpelling(std:: string& spelling) {
  std::transform(spelling.begin(), spelling.end(), spelling.begin(), tolower);
}
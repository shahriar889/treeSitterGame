#include "rules.h"

class ForEachLoopRule : public Rule {
private:
    void executeImpl() override {
        std::cout << "Executing For-Each loop...\n";
    }
};

class WhileLoopRule : public Rule {
private:
    void executeImpl() override {
        std::cout << "Executing While loop...\n";
    }
};

class ParallelForLoopRule : public Rule {
private:
    void executeImpl() override {
        std::cout << "Executing Parallel-For loop...\n";
    }
};


class MatchLoopRule : public Rule {
private:
    void executeImpl() override {
        std::cout << "Executing Match loop...\n";
    }
};

class ExtendListRule : public Rule {
private:
    void executeImpl() override {
        std::cout << "Executing Extend list...\n";
    }
};

class DiscardListRule : public Rule {
private:
    void executeImpl() override {
        std::cout << "Executing Discard list...\n";
    }
};


class MessageOutputRule : public Rule {
private:
    void executeImpl() override {
        std::cout << "Executing Message output...\n";
    }
};


class AssignmentRule : public Rule {
private:
    void executeImpl() override {
        std::cout << "Executing Assignment...\n";
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
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

void Translator::registerFactory(std::string spelling, FactoryPointer factory) noexcept {
  canonicalizeSpelling(spelling);
  factories[spelling] = std::move(factory);
}

Translator buildTreeSitterTranslator() noexcept {
    Translator translator = Translator{};

    //Control Structures
    translator.registerFactory("for", std::make_unique<ForEachLoopFactory>());
    translator.registerFactory("loop", std::make_unique<WhileLoopFactory>());
    //List Operations
    translator.registerFactory("extend", std::make_unique<ExtendListFactory>());

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
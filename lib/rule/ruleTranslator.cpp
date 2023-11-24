#include "ruleTranslator.h"

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
Translator::createOperation(std::string spelling, std::vector<Expression> expressions) const noexcept {
  auto factory = factories.find(spelling);
  if (factory == factories.end()) {
    return {};
  }

  return factory->second->create(expressions);
}

static void canonicalizeSpelling(std:: string& spelling) {
  std::transform(spelling.begin(), spelling.end(), spelling.begin(), tolower);
}
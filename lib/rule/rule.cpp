#include "rule.h"

class ForEachRule : public Rule {
private:
    void executeImpl() override {

    }
};

class ForEachFactory final : public RuleFactory {
private:
    std::unique_ptr<Rule> createImpl() override {
    return std::make_unique<ForEachRule>();
  }
};

void Translator::registerFactory(std::string spelling, FactoryPointer factory) noexcept {
  canonicalizeSpelling(spelling);
  factories[spelling] = std::move(factory);
}

static void canonicalizeSpelling(std::string& spelling) {
  std::transform(spelling.begin(), spelling.end(), spelling.begin(), tolower);
}
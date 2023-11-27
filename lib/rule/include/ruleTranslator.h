#include "ruleFactories.h"

class Translator {
public:
    using FactoryPointer = std::unique_ptr<RuleFactory>;
    using RulePointer = std::unique_ptr<Rule>;

    void registerFactory(std::string spelling, FactoryPointer factory) noexcept;
    RulePointer createOperation(std::string, std::vector<Expression>) const noexcept;

private:
    std::unordered_map<std::string, FactoryPointer> factories;
};

//HELPER FUNCTIONS
Translator buildTreeSitterTranslator() noexcept;
static void canonicalizeSpelling(std::string& spelling);
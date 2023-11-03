#pragma once

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <algorithm>

class Rule {
public:
    void execute() {
        executeImpl();
    }
private:
    virtual void executeImpl() = 0;
};

class RuleFactory {
public:
    std::unique_ptr<Rule> create() {
        return createImpl();
    };
private:
    virtual std::unique_ptr<Rule> createImpl() = 0;
};

class Translator {
public:
  using FactoryPointer = std::unique_ptr<RuleFactory>;
  using OperationPointer = std::unique_ptr<Rule>;

  void registerFactory(std::string spelling, FactoryPointer factory) noexcept;

private:
  OperationPointer createOperation(const std::string& spelling) const noexcept;

  std::unordered_map<std::string, FactoryPointer> factories;
};

//HELPER FUNCTIONS
static void canonicalizeSpelling(std::string& spelling);

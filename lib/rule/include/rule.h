#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <unordered_map>
#include <algorithm>
#include <iostream>

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
    using RulePointer = std::unique_ptr<Rule>;

    void registerFactory(std::string spelling, FactoryPointer factory) noexcept;
    RulePointer createOperation(std::string spelling) const noexcept;

private:
    std::unordered_map<std::string, FactoryPointer> factories;
};

//HELPER FUNCTIONS
Translator buildTreeSitterTranslator() noexcept;
static void canonicalizeSpelling(std::string& spelling);

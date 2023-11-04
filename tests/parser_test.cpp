#include <gtest/gtest.h>
#include "parser.h"

const std::string RULE_MANAGER_TEST_GAME = "games/rule-manager-test.game";

// Demonstrate some basic assertions.
TEST(ParserTest, createRules)
{
    Parser parser{RULE_MANAGER_TEST_GAME};
    auto ruleManager = parser.createRuleManager();

    ruleManager.start();
}
#include <gtest/gtest.h>
#include <filesystem>
#include "treeManager.h"
#include "ruleManager.h"

const std::string RULE_MANAGER_TEST_GAME = "games/rule-manager-test.game";
const std::string NESTING_TEST_GAME = "games/nesting-test.game";

std::string getAbsolutePath(const std::string_view& path) {
    std::filesystem::path projectDirectory = std::filesystem::current_path();
    std::filesystem::path absolutePath = projectDirectory / path;

    return absolutePath.string();
}

// Demonstrate some basic assertions.
TEST(ParserTest, createRules)
{
    TM::TreeManager parser{getAbsolutePath(RULE_MANAGER_TEST_GAME)};
    auto ruleManager = RuleManager{};
    ruleManager.configure(parser);
    ruleManager.start();
    EXPECT_EQ(1, 1);
}

TEST(ParserTest, createNestingRules)
{
    TM::TreeManager parser{getAbsolutePath(NESTING_TEST_GAME)};
    auto ruleManager = RuleManager{};
    ruleManager.configure(parser);

    ruleManager.start();
    EXPECT_EQ(1, 1);
}
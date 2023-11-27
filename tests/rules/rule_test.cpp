#include <gtest/gtest.h>
#include <filesystem>
#include <memory>
#include "treeManager.h"
#include "ruleManager.h"
#include "ruleParser.h"

const std::string RULE_MANAGER_TEST_GAME = "games/rule-manager-test.game";
const std::string NESTING_TEST_GAME = "games/nesting-test.game";
const std::string PARALLEL_FOR_RPS_GAME = "games/parallel-for-rps.game";

std::string getAbsolutePath(const std::string_view& path) {
    std::filesystem::path projectDirectory = std::filesystem::current_path();
    std::filesystem::path absolutePath = projectDirectory / path;

    return absolutePath.string();
}

std::shared_ptr<StateManager> getStates(TM::TreeManager& tm) {
    ConfigurationState conf;
    conf.configure(tm);
    ConstantState constantState = ConstantState();
    constantState.configure(tm);
    VariableState variableState = VariableState();
    variableState.configure(tm);

    return std::make_shared<StateManager>(variableState, constantState, conf);
}

TEST(RuleTest, createRules)
{
    TM::TreeManager tree{getAbsolutePath(RULE_MANAGER_TEST_GAME)};
    auto ruleManager = RuleParser::createRuleManager(tree);
    ruleManager.setGlobalState(getStates(tree));
    ruleManager.start();
    EXPECT_EQ(1, 1);
}

TEST(RuleTest, createNestingRules)
{
    TM::TreeManager tree{getAbsolutePath(NESTING_TEST_GAME)};
    RuleParser parser = RuleParser{};
    auto ruleManager = parser.createRuleManager(tree);
    ruleManager.setGlobalState(getStates(tree));
    ruleManager.start();
    EXPECT_EQ(1, 1);
}

TEST(RuleTest, createParallelRule)
{
    TM::TreeManager tree{getAbsolutePath(PARALLEL_FOR_RPS_GAME)};
    RuleParser parser = RuleParser{};
    auto ruleManager = parser.createRuleManager(tree);
    ruleManager.setGlobalState(getStates(tree));
    ruleManager.start();
    EXPECT_EQ(1, 1);
}
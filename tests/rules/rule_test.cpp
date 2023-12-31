#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <filesystem>
#include <memory>
#include "treeManager.h"
#include "ruleManager.h"
#include "ruleParser.h"
using namespace testing;

const std::string RULE_MANAGER_TEST_GAME = "games/rule-manager-test.game";
const std::string NESTING_TEST_GAME = "games/nesting-test.game";
const std::string PARALLEL_FOR_RPS_GAME = "games/parallel-for-rps.game";
const std::string FOR_EACH_RPS_GAME = "games/for-each-rps.game";

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

class MockRule : public Rule {
public:
    MOCK_METHOD(void, executeImpl, (std::shared_ptr<StateManager>), (override));
    MOCK_METHOD(bool, isNestedImpl, (), (override));
};

class MockRuleFactory : public RuleFactory {
public:
    MOCK_METHOD(std::unique_ptr<Rule>, createImpl, (std::vector<Expression>), (override));
};


TEST(RuleTest, MockFactoryTest)
{
    auto factory = std::make_unique<MockRuleFactory>();

    EXPECT_CALL(*factory, createImpl(_))
        .Times(3);

    std::vector<Expression> expressions;
    std::unique_ptr<Rule> rule1 = factory->createImpl(expressions);
    std::unique_ptr<Rule> rule2 = factory->createImpl(expressions);
    std::unique_ptr<Rule> rule3 = factory->createImpl(expressions);
}

TEST(RuleTest, MockRuleTest)
{
    auto rule = std::make_unique<MockRule>();

    EXPECT_CALL(*rule, executeImpl(_))
        .Times(3);

    std::shared_ptr<StateManager> states;
    rule->executeImpl(states);
    rule->executeImpl(states);
    rule->executeImpl(states);
}

TEST(RuleTest, createRules)
{
    TM::TreeManager tree{getAbsolutePath(RULE_MANAGER_TEST_GAME)};
    auto ruleManager = RuleParser::createRuleManager(tree, buildTreeSitterTranslator());
    ruleManager.setGlobalState(getStates(tree));
    ruleManager.start();
    EXPECT_EQ(1, 1);
}

TEST(RuleTest, createNestingRules)
{
    TM::TreeManager tree{getAbsolutePath(NESTING_TEST_GAME)};
    RuleParser parser = RuleParser{};
    auto ruleManager = parser.createRuleManager(tree, buildTreeSitterTranslator());
    ruleManager.setGlobalState(getStates(tree));
    ruleManager.start();
    EXPECT_EQ(1, 1);
}

TEST(RuleTest, createParallelRule)
{
    TM::TreeManager tree{getAbsolutePath(PARALLEL_FOR_RPS_GAME)};
    RuleParser parser = RuleParser{};
    auto ruleManager = parser.createRuleManager(tree, buildTreeSitterTranslator());
    ruleManager.setGlobalState(getStates(tree));
    ruleManager.start();
    EXPECT_EQ(1, 1);
}
#include <gtest/gtest.h>
#include <filesystem>
#include "Game.h"

const std::string RULE_MANAGER_TEST_GAME = "games/rule-manager-test.game";
const std::string NESTING_TEST_GAME = "games/nesting-test.game";
const std::string ROCK_PAPER_SCISSORS_GAME = "games/rock-paper-scissors.game";
const std::string FOR_EACH_RPS_GAME = "games/for-each-rps.game";

std::string getAbsolutePath(const std::string_view& path) {
    std::filesystem::path projectDirectory = std::filesystem::current_path();
    std::filesystem::path absolutePath = projectDirectory / path;

    return absolutePath.string();
}

TEST(GameTest, createGame)
{
    Game game{getAbsolutePath(FOR_EACH_RPS_GAME)};
    game.start();

    //Should not execute rules another time
    game.start();
    
    EXPECT_EQ(1, 1);
}

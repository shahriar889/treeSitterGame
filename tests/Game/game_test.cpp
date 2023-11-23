#include <gtest/gtest.h>
#include <filesystem>
#include "Game.h"

const std::string RULE_MANAGER_TEST_GAME = "games/rule-manager-test.game";
const std::string NESTING_TEST_GAME = "games/nesting-test.game";
const std::string ROCK_PAPER_SCISSORS_GAME = "games/rock-paper-scissors.game";

std::string getAbsolutePath(const std::string_view& path) {
    std::filesystem::path projectDirectory = std::filesystem::current_path();
    std::filesystem::path absolutePath = projectDirectory / path;

    return absolutePath.string();
}

// Demonstrate some basic assertions.
TEST(GameTest, createGame)
{

    Game game{getAbsolutePath(ROCK_PAPER_SCISSORS_GAME)};
    EXPECT_EQ(1, 1);
    
}

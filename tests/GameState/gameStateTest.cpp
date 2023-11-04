#include "configurationState.h"
#include "gtest/gtest.h"
#include <map>
#include <string>
#include <filesystem>

TEST(ConfigurationStateTest, testWithRockPaperScissors){
    // Get the project directory path
    std::filesystem::path projectDirectory = std::filesystem::current_path();

    // Define the relative path to your file
    std::string relativePath = "games/rock-paper-scissors.game";

    // Construct the absolute path by concatenating the project directory and the relative path
    std::filesystem::path absolutePath = projectDirectory / relativePath;
    TM::TreeManager treeManager(absolutePath);
    ConfigurationState conf;
    conf.configure(treeManager);
    EXPECT_EQ(conf.getValue("name").getStringValue(), "Rock, Paper, Scissors");
    EXPECT_EQ(conf.getValue("playerRangeMin").getIntValue(), 2);
    EXPECT_EQ(conf.getValue("playerRangeMax").getIntValue(), 4);
    EXPECT_EQ(conf.getValue("hasAudience").getBoolValue(), false);
    std::map<std::string, GS::DataValuePtr> mapValue = conf.getValue("rounds").getMapValue();
    EXPECT_EQ(mapValue["prompt"]->getStringValue(), "The number of rounds to play");
    EXPECT_EQ(mapValue["rangeMin"]->getIntValue(), 1);
    EXPECT_EQ(mapValue["rangeMax"]->getIntValue(), 20);
}
    
#include "configurationState.h"
#include "ConstantState.h"
#include "variableState.h"
#include "perPlayerState.h"
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
    std::string gameName = std::get<std::string>(conf.getValue("name").getValueVariant());

    EXPECT_EQ(gameName, "Rock, Paper, Scissors");
    int pLRangeMin = std::get<int>(conf.getValue("playerRangeMin").getValueVariant());
    EXPECT_EQ(pLRangeMin, 2);
    int pLRangeMax = std::get<int>(conf.getValue("playerRangeMax").getValueVariant());
    EXPECT_EQ(pLRangeMax, 4);
    int pLRangeCur = std::get<int>(conf.getValue("playerRangeCur").getValueVariant());
    EXPECT_EQ(pLRangeCur, 2);
    bool hasAudience = std::get<bool>(conf.getValue("hasAudience").getValueVariant());
    EXPECT_EQ(hasAudience, false);
    GS::DataValue data = conf.getValue("rounds");
    std::map<std::string, GS::DataValue> mapValue = std::get<std::map<std::string, GS::DataValue>>(data.getValueVariant());
    std::string prompt = std::get<std::string>(mapValue["prompt"].getValueVariant());
    EXPECT_EQ(prompt, "The number of rounds to play");
    int rangeMin = std::get<int>(mapValue["rangeMin"].getValueVariant());
    EXPECT_EQ(rangeMin, 1);
    int rangeCur = std::get<int>(mapValue["rangeCur"].getValueVariant());
    EXPECT_EQ(rangeCur, 1);
    int rangeMax = std::get<int>(mapValue["rangeMax"].getValueVariant());
    EXPECT_EQ(rangeMax, 20);
}

TEST(ConstantStateTest, testWithRockPaperScissors){
    // Get the project directory path
    std::filesystem::path projectDirectory = std::filesystem::current_path();

    // Define the relative path to your file
    std::string relativePath = "games/rock-paper-scissors.game";

    // Construct the absolute path by concatenating the project directory and the relative path
    std::filesystem::path absolutePath = projectDirectory / relativePath;
    TM::TreeManager treeManager(absolutePath);
    ConstantState constantState = ConstantState();
    constantState.configure(treeManager);
    GS::DataValue data = constantState.getValue("constant1");
    std::map<std::string, GS::DataValue> mapValue = std::get<std::map<std::string, GS::DataValue>>(data.getValueVariant());
    GS::DataValue data2 = mapValue["weapons"];
    std::vector<GS::DataValue> listValue = std::get<std::vector<GS::DataValue>>(data2.getValueVariant());
    std::map<std::string, GS::DataValue> mapValue2 = std::get<std::map<std::string, GS::DataValue>>(listValue[0].getValueVariant());
    std::string hitter; std::string victim;
    hitter = std::get<std::string>(mapValue2["name"].getValueVariant());
    victim = std::get<std::string>(mapValue2["beats"].getValueVariant());

    EXPECT_EQ(hitter, "Rock");
    EXPECT_EQ(victim, "Scissors");
    mapValue2 = std::get<std::map<std::string, GS::DataValue>>(listValue[1].getValueVariant());
    hitter = std::get<std::string>(mapValue2["name"].getValueVariant());
    victim = std::get<std::string>(mapValue2["beats"].getValueVariant());
    EXPECT_EQ(hitter, "Paper");
    EXPECT_EQ(victim, "Rock");
    mapValue2 = std::get<std::map<std::string, GS::DataValue>>(listValue[2].getValueVariant());
    hitter = std::get<std::string>(mapValue2["name"].getValueVariant());
    victim = std::get<std::string>(mapValue2["beats"].getValueVariant());
    EXPECT_EQ(hitter, "Scissors");
    EXPECT_EQ(victim, "Paper");
    

}

TEST(VariableStateTest, testWithRockPaperScissors){
    // Get the project directory path
    std::filesystem::path projectDirectory = std::filesystem::current_path();

    // Define the relative path to your file
    std::string relativePath = "games/rock-paper-scissors.game";

    // Construct the absolute path by concatenating the project directory and the relative path
    std::filesystem::path absolutePath = projectDirectory / relativePath;
    TM::TreeManager treeManager(absolutePath);
    VariableState variableState = VariableState();
    variableState.configure(treeManager);
    GS::DataValue data = variableState.getValue("variable1");
    std::map<std::string, GS::DataValue> mapValue = std::get<std::map<std::string, GS::DataValue>>(data.getValueVariant());
    GS::DataValue data2 = mapValue["winners"];
    std::vector<GS::DataValue> listValue = std::get<std::vector<GS::DataValue>>(data2.getValueVariant());
    EXPECT_EQ(listValue.size(), 0);
    std::string pl = "Player1";
    DataValue data3; data3.setValue(pl);
    listValue.push_back(data3);
    EXPECT_EQ(listValue.size(), 1);
    DataValue data4 = listValue[0];
    std::string value = std::get<std::string>(data4.getValueVariant());
    EXPECT_EQ(value,"Player1");


}

TEST(PerPlayerStateTest, testWithRockPaperScissors){
    // Get the project directory path
    std::filesystem::path projectDirectory = std::filesystem::current_path();

    // Define the relative path to your file
    std::string relativePath = "games/rock-paper-scissors.game";

    // Construct the absolute path by concatenating the project directory and the relative path
    std::filesystem::path absolutePath = projectDirectory / relativePath;
    TM::TreeManager treeManager(absolutePath);
    PerPlayerState perPlayerState = PerPlayerState(1);
    perPlayerState.configure(treeManager);
    GS::DataValue data = perPlayerState.getValue("perPlayer1");
    EXPECT_EQ(perPlayerState.getPlayerID(), 1);
    std::map<std::string, GS::DataValue> mapValue = std::get<std::map<std::string, GS::DataValue>>(data.getValueVariant());
    int wins = std::get<int>(mapValue["wins"].getValueVariant());
    EXPECT_EQ(wins, 0);
    mapValue["wins"].setValue(1);
    wins = std::get<int>(mapValue["wins"].getValueVariant());
    EXPECT_EQ(wins, 1);
}
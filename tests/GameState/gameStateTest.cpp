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
    EXPECT_EQ(conf.getValue("name").getStringValue(), "Rock, Paper, Scissors");
    EXPECT_EQ(conf.getValue("playerRangeMin").getIntValue(), 2);
    EXPECT_EQ(conf.getValue("playerRangeMax").getIntValue(), 4);
    EXPECT_EQ(conf.getValue("playerRangeCur").getIntValue(), 2);
    EXPECT_EQ(conf.getValue("hasAudience").getBoolValue(), false);
    std::map<std::string, GS::DataValuePtr> mapValue = conf.getValue("rounds").getMapValue();
    EXPECT_EQ(mapValue["prompt"]->getStringValue(), "The number of rounds to play");
    EXPECT_EQ(mapValue["rangeMin"]->getIntValue(), 1);
    EXPECT_EQ(mapValue["rangeCur"]->getIntValue(), 1);
    EXPECT_EQ(mapValue["rangeMax"]->getIntValue(), 20);
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
    std::map<std::string, GS::DataValuePtr> mapValue = data.getMapValue();
    GS::DataValuePtr data2 = mapValue["weapons"];
    std::vector<GS::DataValue> listValue = data2->getListValue();
    std::map<std::string, GS::DataValuePtr> mapValue2 = listValue[0].getMapValue();
    EXPECT_EQ(mapValue2["name"]->getStringValue(), "Rock");
    EXPECT_EQ(mapValue2["beats"]->getStringValue(), "Scissors");
    mapValue2 = listValue[1].getMapValue();
    EXPECT_EQ(mapValue2["name"]->getStringValue(), "Paper");
    EXPECT_EQ(mapValue2["beats"]->getStringValue(), "Rock");
    mapValue2 = listValue[2].getMapValue();
    EXPECT_EQ(mapValue2["name"]->getStringValue(), "Scissors");
    EXPECT_EQ(mapValue2["beats"]->getStringValue(), "Paper");
    

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
    std::map<std::string, GS::DataValuePtr> mapValue = data.getMapValue();
    GS::DataValuePtr data2 = mapValue["winners"];
    std::vector<GS::DataValue> listValue = data2->getListValue();
    EXPECT_EQ(listValue.size(), 0);
    DataValue data3; data3.setStringValue("Player1");
    listValue.push_back(data3);
    EXPECT_EQ(listValue.size(), 1);
    EXPECT_EQ(listValue[0].getStringValue(),"Player1");


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
    std::map<std::string, GS::DataValuePtr> mapValue = data.getMapValue();
    EXPECT_EQ(mapValue["wins"]->getIntValue(), 0);
    mapValue["wins"]->setIntValue(1);
    EXPECT_EQ(mapValue["wins"]->getIntValue(), 1);



}
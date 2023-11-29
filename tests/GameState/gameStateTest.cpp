#include "configurationState.h"
#include "constantState.h"
#include "variableState.h"
#include "perPlayerState.h"
#include "gtest/gtest.h"
#include <map>
#include <string>
#include <filesystem>

using namespace DV;
using namespace GS;

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
    DataValue RHS;
    DataValue LHS;

    bool check;

    LHS = conf.getValue("name");
    check = LHS.getType() == DataType::STRING;
    EXPECT_EQ(check, true);
    RHS.setValue("Rock, Paper, Scissors");
    EXPECT_EQ(LHS, RHS);
    

    LHS  = conf.getValue("playerRangeMin");
    check = LHS.getType() == DataType::INT;
    EXPECT_EQ(check, true);
    RHS.setValue(2);
    EXPECT_EQ(LHS, RHS);

    LHS  = conf.getValue("playerRangeMax");
    check = LHS.getType() == DataType::INT;
    EXPECT_EQ(check, true);
    RHS.setValue(4);
    EXPECT_EQ(LHS, RHS);

    LHS  = conf.getValue("playerRangeCur");
    check = LHS.getType() == DataType::INT;
    EXPECT_EQ(check, true);
    RHS.setValue(2);
    EXPECT_EQ(LHS, RHS);

    LHS  = conf.getValue("hasAudience");
    check = LHS.getType() == DataType::BOOL;
    EXPECT_EQ(check, true);
    RHS.setValue(false);
    EXPECT_EQ(LHS, RHS);

    LHS  = conf.getValue("rounds");
    check = LHS.getType() == DataType::MAP;
    EXPECT_EQ(check, true);
    std::map<std::string, DataValue> map;
    map["prompt"] = DataValue{"The number of rounds to play"};
    map["rangeMin"] = DataValue{1};
    map["rangeCur"] = DataValue{1};
    map["rangeMax"] = DataValue{20};
    RHS.setValue(map);
    EXPECT_EQ(LHS, RHS);
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

    DataValue LHS;
    DataValue RHS;
    bool check;

    LHS = constantState.getValue("constant1");
    check = LHS.getType() == DataType::MAP;
    EXPECT_EQ(check, true);
    std::vector<DataValue> list;
    std::map<std::string, DataValue> map1;
    std::map<std::string, DataValue> map2;
    std::map<std::string, DataValue> map3;
    map1["name"] = DataValue{"Rock"};
    map1["beats"] = DataValue{"Scissors"};
    map2["name"] = DataValue{"Paper"};
    map2["beats"] = DataValue{"Rock"};
    map3["name"] = DataValue{"Scissors"};
    map3["beats"] = DataValue{"Paper"};
    list.push_back(DataValue{map1});
    list.push_back(DataValue{map2});
    list.push_back(DataValue{map3});
    std::map<std::string, DataValue> map;
    map["weapons"] = DataValue{list};
    RHS.setValue(map);
    EXPECT_EQ(LHS, RHS);
    

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

    DataValue LHS;
    DataValue RHS;
    bool check;

    LHS = variableState.getValue("variable1");
    check = LHS.getType() == DataType::MAP;
    EXPECT_EQ(check, true);
    auto winners = LHS.get_map_item("winners");
    check = winners.getType() == DataType::LIST;
    EXPECT_EQ(check, true);
    size_t size = winners.size();
    EXPECT_EQ(size, 0);
    std::string pl = "Player1";
    DataValue data3; data3.setValue(pl);
    winners.push_back_list(data3);
    size = winners.size();
    EXPECT_EQ(size, 1);
    DataValue data4 = winners.get_list(0);
    check = data4.getType() == DataType::STRING;
    EXPECT_EQ(check, true);
    EXPECT_EQ(data4, data3);
    std::optional<DataValue> data5 = winners.remove_from_list(0);
    check = data5.has_value();
    EXPECT_EQ(check, true);
    size = data5.value().size();
    EXPECT_EQ(size, 0);

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

    DataValue LHS;
    DataValue RHS;
    bool check;

    LHS = perPlayerState.getValue("perPlayer1");
    check = LHS.getType() == DataType::MAP;
    EXPECT_EQ(check, true);
    auto wins = LHS.get_map_item("wins");
    check = wins.getType() == DataType::INT;
    EXPECT_EQ(check, true);
    DataValue data1; data1.setValue(0);
    EXPECT_EQ(wins, data1);
    wins.setValue(1);
    data1.setValue(1);
    EXPECT_EQ(wins, data1);
}

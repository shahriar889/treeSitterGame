#include "configurationState.h"
#include "constantState.h"
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

TEST(DataValueTest, IntValueTest) {
    GS::DataValue dataValue;

    // Positive int value
    dataValue.setValue(420);
    EXPECT_EQ(std::get<int>(dataValue.getValueVariant()), 420);

    // Zero int value
    dataValue.setValue(0);
    EXPECT_EQ(std::get<int>(dataValue.getValueVariant()), 0);

    // Negative int value
    dataValue.setValue(-420);
    EXPECT_EQ(std::get<int>(dataValue.getValueVariant()), -420);

    //Max and min Interger value
    dataValue.setValue(std::numeric_limits<int>::max());
    EXPECT_EQ(std::get<int>(dataValue.getValueVariant()), std::numeric_limits<int>::max());

    dataValue.setValue(std::numeric_limits<int>::min());
    EXPECT_EQ(std::get<int>(dataValue.getValueVariant()), std::numeric_limits<int>::min());
}

TEST(DataValueTest, BooleanValueTest) {
    GS::DataValue dataValue;

    dataValue.setValue(true);
    EXPECT_EQ(std::get<bool>(dataValue.getValueVariant()), true);

    dataValue.setValue(false);
    EXPECT_EQ(std::get<bool>(dataValue.getValueVariant()), false);
}

TEST(DataValueTest, StringValueTest) {
    GS::DataValue dataValue;

    // Normal string
    dataValue.setValue(std::string("Hello, World!"));
    EXPECT_EQ(std::get<std::string>(dataValue.getValueVariant()), "Hello, World!");

    // Empty string
    dataValue.setValue(std::string(""));
    EXPECT_EQ(std::get<std::string>(dataValue.getValueVariant()), "");

    // Test string with special characters
    std::string specialCharsString = "!@#$%^&*()_+{}[]|;:,.<>?";
    dataValue.setValue(specialCharsString);
    EXPECT_EQ(std::get<std::string>(dataValue.getValueVariant()), specialCharsString);

    // Test string with numbers
    std::string numericString = "12345";
    dataValue.setValue(numericString);
    EXPECT_EQ(std::get<std::string>(dataValue.getValueVariant()), numericString);

    // Test string with spaces
    std::string stringWithSpaces = "   This is a test   ";
    dataValue.setValue(stringWithSpaces);
    EXPECT_EQ(std::get<std::string>(dataValue.getValueVariant()), stringWithSpaces);

    // Test long string
    std::string longString(100000, 'a');
    dataValue.setValue(longString);
    EXPECT_EQ(std::get<std::string>(dataValue.getValueVariant()), longString);

    // Test string with newline characters
    std::string stringWithNewlines = "Line 1\nLine 2\nLine 3";
    dataValue.setValue(stringWithNewlines);
    EXPECT_EQ(std::get<std::string>(dataValue.getValueVariant()), stringWithNewlines);
}

TEST(DataValueTest, MapValueTest) {
    GS::DataValue dataValue;

    // Test an empty map
    dataValue.setValue(std::map<std::string, GS::DataValue>{});
    auto emptyMap = std::get<std::map<std::string, GS::DataValue>>(dataValue.getValueVariant());
    EXPECT_TRUE(emptyMap.empty());

    //Test map with one entry
    GS::DataValue intValue;
    intValue.setValue(1);
    std::map<std::string, GS::DataValue> sampleMap = {{"Hello World!", intValue}};
    dataValue.setValue(sampleMap);
    auto retrievedMap = std::get<std::map<std::string, GS::DataValue>>(dataValue.getValueVariant());

    EXPECT_EQ(retrievedMap.size(), 1);

    //Test map with two entries
    GS::DataValue firstValue;
    firstValue.setValue(1);

    GS::DataValue secondValue;
    secondValue.setValue(2);

    sampleMap = {{"Hello World!", firstValue},
                {"This is a test", secondValue}};
    dataValue.setValue(sampleMap);
    retrievedMap = std::get<std::map<std::string, GS::DataValue>>(dataValue.getValueVariant());

    EXPECT_EQ(retrievedMap.size(), 2);

    //Check if key existed in retrieved map
    EXPECT_TRUE(retrievedMap.find("Hello World!") != retrievedMap.end());
    EXPECT_TRUE(retrievedMap.find("This is a test") != retrievedMap.end());

    // Check if a key not in the map is not in the map
    EXPECT_TRUE(retrievedMap.find("NotInMap") == retrievedMap.end());
}

TEST(DataValueTest, VectorValueTest){
    GS::DataValue dataValue;

    //Test an empty vector
    std::vector<DataValue> valueVector = {};
    dataValue.setValue(valueVector);
    auto retrievedVector = std::get<std::vector<DataValue>>(dataValue.getValueVariant());
    EXPECT_EQ(retrievedVector.size(), 0);

    //Adding one int entry to vector
    GS::DataValue intValue;
    intValue.setValue(1);
    valueVector.emplace_back(intValue);
    dataValue.setValue(valueVector);
    retrievedVector = std::get<std::vector<DataValue>>(dataValue.getValueVariant());

    EXPECT_EQ(retrievedVector.size(), 1);
    EXPECT_EQ(std::get<int>(retrievedVector.at(0).getValueVariant()), std::get<int>(valueVector.at(0).getValueVariant()));

    //Adding one boolean entry to vector
    GS::DataValue boolValue;
    boolValue.setValue(true);
    valueVector.emplace_back(boolValue);
    dataValue.setValue(valueVector);
    retrievedVector = std::get<std::vector<DataValue>>(dataValue.getValueVariant());

    EXPECT_EQ(retrievedVector.size(), 2);
    EXPECT_EQ(std::get<bool>(retrievedVector.at(1).getValueVariant()), std::get<bool>(valueVector.at(1).getValueVariant()));

     //Adding one string entry to vector
    GS::DataValue stringValue;
    std::string newString = "Hello World!";
    stringValue.setValue(newString);
    valueVector.emplace_back(stringValue);
    dataValue.setValue(valueVector);
    retrievedVector = std::get<std::vector<DataValue>>(dataValue.getValueVariant());

    EXPECT_EQ(retrievedVector.size(), 3);
    EXPECT_EQ(std::get<std::string>(retrievedVector.at(2).getValueVariant()), std::get<std::string>(valueVector.at(2).getValueVariant()));

    //Stress testing ability to hold large number of value in DataValue vector

    // //The vector already have 3 values in it
    int startingEntry = 3;
    for (int i = 0; i < 10000; i++) {
        GS::DataValue currentIntValue;
        currentIntValue.setValue(i);
        valueVector.emplace_back(currentIntValue);
        dataValue.setValue(valueVector);
        retrievedVector = std::get<std::vector<DataValue>>(dataValue.getValueVariant());

        EXPECT_EQ(std::get<int>(retrievedVector.at(startingEntry + i).getValueVariant()), std::get<int>(valueVector.at(startingEntry + i).getValueVariant()));
    }
    EXPECT_EQ(retrievedVector.size(), 10003);
}

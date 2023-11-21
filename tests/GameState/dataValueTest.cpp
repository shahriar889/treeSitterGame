#include "configurationState.h"
#include "constantState.h"
#include "variableState.h"
#include "perPlayerState.h"
#include "gtest/gtest.h"
#include <map>
#include <string>

using GS::DataValue;
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
}

//Test for Parameterized Constructor
TEST(DataValueTest, ConstructorTest){

    //Test constructor with passed in int value
    DataValue intValue { 420 };
    EXPECT_EQ(std::get<int>(intValue.getValueVariant()), 420);

    //Test constructor with passed in String value
    DataValue stringValue { std::string{"Hello World!"} };
    EXPECT_EQ(std::get<std::string>(stringValue.getValueVariant()), "Hello World!");

    //Test constructor with passed in boolean value
    DataValue boolValue { true };
    EXPECT_EQ(std::get<bool>(boolValue.getValueVariant()), true);

    //Test constructor with passed in vector 
    std::vector<DataValue> sampleVector = { };
    DataValue vectorValue { sampleVector };
    auto retrievedVector = std::get<std::vector<DataValue>>(vectorValue.getValueVariant());
    EXPECT_EQ(retrievedVector.size(), 0);

    //Test constructor with passed in map 
    std::map<std::string, GS::DataValue> sampleMap = { };
    DataValue mapValue { sampleMap };
    auto emptyMap = std::get<std::map<std::string, GS::DataValue>>(mapValue.getValueVariant());
    EXPECT_TRUE(emptyMap.empty());
}
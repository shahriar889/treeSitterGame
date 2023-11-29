#include "configurationState.h"
#include "constantState.h"
#include "variableState.h"
#include "perPlayerState.h"
#include "gtest/gtest.h"
#include <map>
#include <string>
#include <vector>

using DV::DataValue;

TEST(DataValueTest, Equality_with_int){
    DataValue dataValue1 { 420 };
    DataValue dataValue2 { 420 };
    bool check = dataValue1 == dataValue2;
    EXPECT_EQ(check, true);

    DataValue dataValue3 { 69 };
    check = dataValue1 == dataValue3;
    EXPECT_EQ(check, false);

    DataValue dataValue4 { "Hello World!" };
    check = dataValue1 == dataValue4;
    EXPECT_EQ(check, false);
}

TEST(DataValueTest, Equality_with_string){
    DataValue dataValue1 { std::string{"Hello World!"} };
    DataValue dataValue2 { std::string{"Hello World!"} };
    bool check = dataValue1 == dataValue2;
    EXPECT_EQ(check, true);

    DataValue dataValue3 { std::string{"Hello World"} };
    check = dataValue1 == dataValue3;
    EXPECT_EQ(check, false);

    DataValue dataValue4 { 420 };
    check = dataValue1 == dataValue4;
    EXPECT_EQ(check, false);
}

TEST(DataValueTest, Equality_with_bool){
    DataValue dataValue1 { true };
    DataValue dataValue2 { true };
    bool check = dataValue1 == dataValue2;
    EXPECT_EQ(check, true);

    DataValue dataValue3 { false };
    check = dataValue1 == dataValue3;
    EXPECT_EQ(check, false);

    DataValue dataValue4 { 420 };
    check = dataValue1 == dataValue4;
    EXPECT_EQ(check, false);
}

TEST(DataValueTest, Equality_with_different_types){
    DataValue dataValue1 { true };
    DataValue dataValue2 { 1 };
    bool check = dataValue1 == dataValue2;
    EXPECT_EQ(check, false);

    DataValue dataValue3 { std::string{"Hello World!"} };
    check = dataValue1 == dataValue3;
    EXPECT_EQ(check, false);

    DataValue dataValue4 { std::string{"Hello World!"} };
    check = dataValue3 == dataValue4;
    EXPECT_EQ(check, true);

    std::vector<DataValue> vec1;
    DataValue temp{1};
    vec1.push_back(temp);
    DataValue dataValue5 { vec1 };
    check = dataValue1 == dataValue5;
    EXPECT_EQ(check, false);

    std::map<std::string, DataValue> map1;
    map1["key"] = temp;
    DataValue dataValue6 { map1 };
    check = dataValue5 == dataValue6;
    EXPECT_EQ(check, false);
}

TEST(DataValueTest, Equality_with_vector){
    std::vector<DataValue> vec1;
    DataValue temp{1};
    vec1.push_back(temp);
    DataValue dataValue1 { vec1 };
    DataValue dataValue2 { vec1 };
    bool check = dataValue1 == dataValue2;
    EXPECT_EQ(check, true);

    vec1.push_back(DataValue{2});
    dataValue1.setValue(vec1);
    check = dataValue1 == dataValue2;
    EXPECT_EQ(check, false);

    std::vector<DataValue> vec2;
    vec2.push_back(DataValue{2});
    vec2.push_back(DataValue{1});
    DataValue dataValue3 { vec2 };
    check = dataValue1 == dataValue3;
    EXPECT_EQ(check, false);

    std::vector<DataValue> vec3;
    vec3.push_back(DataValue{"Hello World!"});
    DataValue dataValue4 { vec3 };
    std::vector<DataValue> vec4;
    vec4.push_back(DataValue{1});
    DataValue dataValue5 { vec4 };
    check = dataValue4 == dataValue5;
    EXPECT_EQ(check, false);

}

TEST(DataValueTest, Equality_with_map){
    std::map<std::string, DataValue> map1;
    DataValue temp{1};
    map1["key"] = temp;
    DataValue dataValue1 { map1 };
    DataValue dataValue2 { map1 };
    bool check = dataValue1 == dataValue2;
    EXPECT_EQ(check, true);

    map1["key2"] = DataValue{2};
    dataValue1.setValue(map1);
    check = dataValue1 == dataValue2;
    EXPECT_EQ(check, false);

    std::map<std::string, DataValue> map2;
    map2["key2"] = DataValue{2};
    map2["key"] = DataValue{1};
    DataValue dataValue3 { map2 };
    check = dataValue1 == dataValue3;
    EXPECT_EQ(check, true);

    std::map<std::string, DataValue> map3;
    map3["key"] = DataValue{"Hello World!"};
    DataValue dataValue4 { map3 };
    std::map<std::string, DataValue> map4;
    map4["key"] = DataValue{1};
    DataValue dataValue5 { map4 };
    check = dataValue4 == dataValue5;
    EXPECT_EQ(check, false);
}
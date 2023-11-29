#include "configurationState.h"
#include "constantState.h"
#include "variableState.h"
#include "perPlayerState.h"
#include "gtest/gtest.h"
#include <map>
#include <string>
#include <vector>

using DV::DataValue;
using DV::DataType;

TEST(DataValueTest, Push_Back_List_And_Get_List_Methods){
    std::vector<DataValue> vec;
    DataValue dataValue {vec};
    DataValue dataValue1 { 420 };
    DataValue dataValue2 { 69 };
    DataValue dataValue3 { "Hello World!" };
    dataValue.push_back_list(dataValue1);
    dataValue.push_back_list(dataValue2);
    dataValue.push_back_list(dataValue3);
    DataValue dataValue4 = dataValue.get_list(0);
    DataValue dataValue5 = dataValue.get_list(1);
    DataValue dataValue6 = dataValue.get_list(2);

    EXPECT_EQ(dataValue4, dataValue1);
    EXPECT_EQ(dataValue5, dataValue2);
    EXPECT_EQ(dataValue6, dataValue3);

}

TEST(DataValueTest, Insert_Map_And_Get_Map_Item_Methods){
    std::map<std::string, DataValue> map;
    DataValue dataValue {map};
    DataValue dataValue1 { 420 };
    DataValue dataValue2 { 69 };
    DataValue dataValue3 { "Hello World!" };
    dataValue.insert_map("key1", dataValue1);
    dataValue.insert_map("key2", dataValue2);
    dataValue.insert_map("key3", dataValue3);
    DataValue dataValue4 = dataValue.get_map_item("key1");
    DataValue dataValue5 = dataValue.get_map_item("key2");
    DataValue dataValue6 = dataValue.get_map_item("key3");

    EXPECT_EQ(dataValue4, dataValue1);
    EXPECT_EQ(dataValue5, dataValue2);
    EXPECT_EQ(dataValue6, dataValue3);

}

TEST(DataValueTest, Empty){
    DataValue dataValue;
    bool check = dataValue.isEmpty();
    EXPECT_EQ(check, true);
    dataValue.setValue(420);
    check = dataValue.isEmpty();
    EXPECT_EQ(check, false);
    dataValue.setValue("Hello World!");
    check = dataValue.isEmpty();
    EXPECT_EQ(check, false);
    dataValue.setValue(true);
    check = dataValue.isEmpty();
    EXPECT_EQ(check, false);
    std::vector<DataValue> vec;
    dataValue.setValue(vec);
    check = dataValue.isEmpty();
    EXPECT_EQ(check, false);
    std::map<std::string, DataValue> map;
    dataValue.setValue(map);
    check = dataValue.isEmpty();
    EXPECT_EQ(check, false);
}

TEST(DataValueTest, Size){
    DataValue dataValue;
    size_t size = dataValue.size();
    EXPECT_EQ(size, 0);
    dataValue.setValue(420);
    size = dataValue.size();
    EXPECT_EQ(size, 1);
    dataValue.setValue("Hello World!");
    size = dataValue.size();
    EXPECT_EQ(size, 1);
    dataValue.setValue(true);
    size = dataValue.size();
    EXPECT_EQ(size, 1);
    std::vector<DataValue> vec;
    dataValue.setValue(vec);
    size = dataValue.size();
    EXPECT_EQ(size, 0);
    vec.push_back(DataValue{1});
    dataValue.setValue(vec);
    size = dataValue.size();
    EXPECT_EQ(size, 1);
    std::map<std::string, DataValue> map;
    dataValue.setValue(map);
    size = dataValue.size();
    EXPECT_EQ(size, 0);
    map["key"] = DataValue{1};
    dataValue.setValue(map);
    size = dataValue.size();
    EXPECT_EQ(size, 1);
}

TEST(DataValueTest, Print){
    DataValue dataValue;
    dataValue.print();
    dataValue.setValue(420);
    dataValue.print();
    dataValue.setValue("Hello World!");
    dataValue.print();
    dataValue.setValue(true);
    dataValue.print();
    std::vector<DataValue> vec;
    dataValue.setValue(vec);
    dataValue.print();
    vec.push_back(DataValue{1});
    dataValue.setValue(vec);
    dataValue.print();
    std::map<std::string, DataValue> map;
    dataValue.setValue(map);
    dataValue.print();
    map["key"] = DataValue{1};
    dataValue.setValue(map);
    dataValue.print();
    EXPECT_EQ(1,1);
}

TEST(DataValueTest, TypeTest){
    DataValue dataValue;
    bool check;
    check = (DataType::EMPTY == dataValue.getType());
    EXPECT_EQ(check, true);
    dataValue.setValue(420);
    check = (DataType::INT == dataValue.getType());
    EXPECT_EQ(check, true);
    dataValue.setValue("Hello World!");
    check = (DataType::STRING == dataValue.getType());
    EXPECT_EQ(check, true);
    dataValue.setValue(true);
    check = (DataType::BOOL == dataValue.getType());
    EXPECT_EQ(check, true);
    std::vector<DataValue> vec;
    dataValue.setValue(vec);
    check = (DataType::LIST == dataValue.getType());
    EXPECT_EQ(check, true);
    std::map<std::string, DataValue> map;
    dataValue.setValue(map);
    check = (DataType::MAP == dataValue.getType());
    EXPECT_EQ(check, true);
}

TEST(DataValueTest, Remove_From_List){
    DataValue dataValue;
    std::vector<DataValue> vec;
    DataValue dataValue1 { 420 };
    DataValue dataValue2 { 69 };
    DataValue dataValue3 { "Hello World!" };
    vec.push_back(dataValue1);
    vec.push_back(dataValue2);
    vec.push_back(dataValue3);
    dataValue.setValue(vec);
    std::optional<DataValue> dataValue4 = dataValue.remove_from_list(0);
    bool check = dataValue4.has_value();
    EXPECT_EQ(check, true);
    DataValue dataValue5 = dataValue4.value();
    std::vector<DataValue> vec2;
    vec2.push_back(dataValue2);
    vec2.push_back(dataValue3);
    DataValue dataValue6 { vec2 };
    check = (dataValue5 == dataValue6);
    EXPECT_EQ(check, true);
    EXPECT_EQ(dataValue5.size(), 2);

    std::vector<DataValue> vec3;
    DataValue dataValue7 { vec3 };
    dataValue4 = dataValue7.remove_from_list(0);
    check = dataValue4.has_value();
    EXPECT_EQ(check, false);
}

TEST(DataValueTest, Remove_From_Map){
    DataValue dataValue;
    std::map<std::string, DataValue> map;
    DataValue dataValue1 { 420 };
    DataValue dataValue2 { 69 };
    DataValue dataValue3 { "Hello World!" };
    map["key1"] = dataValue1;
    map["key2"] = dataValue2;
    map["key3"] = dataValue3;
    dataValue.setValue(map);
    std::optional<DataValue> dataValue4 = dataValue.remove_from_map("key1");
    bool check = dataValue4.has_value();
    EXPECT_EQ(check, true);
    DataValue dataValue5 = dataValue4.value();
    std::map<std::string, DataValue> map2;
    map2["key2"] = dataValue2;
    map2["key3"] = dataValue3;
    DataValue dataValue6 { map2 };
    check = (dataValue5 == dataValue6);
    EXPECT_EQ(check, true);
    EXPECT_EQ(dataValue5.size(), 2);

    std::map<std::string, DataValue> map3;
    DataValue dataValue7 { map3 };
    dataValue4 = dataValue7.remove_from_map("key1");
    check = dataValue4.has_value();
    EXPECT_EQ(check, false);
}
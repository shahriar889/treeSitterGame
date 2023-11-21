#include "configurationState.h"
#include "constantState.h"
#include "variableState.h"
#include "perPlayerState.h"
#include "gtest/gtest.h"
#include <map>
#include <string>

using GS::DataValue;

//Stress testing ability to hold large number of value in DataValue vector   
TEST(DataValueStressTest, VectorValueStressTest){
    GS::DataValue dataValue;
    std::vector<DataValue> retrievedVector;
    std::vector<DataValue> valueVector = { };
    
     for (int i = 0; i < 10000; i++) {
        GS::DataValue currentIntValue;
        currentIntValue.setValue(i);
        valueVector.emplace_back(currentIntValue);
        dataValue.setValue(valueVector);
        retrievedVector = std::get<std::vector<DataValue>>(dataValue.getValueVariant());
        EXPECT_EQ(std::get<int>(retrievedVector.at(i).getValueVariant()), std::get<int>(valueVector.at(i).getValueVariant()));
    }

    EXPECT_EQ(retrievedVector.size(), 10000);
}
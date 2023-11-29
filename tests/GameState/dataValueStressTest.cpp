#include "configurationState.h"
#include "constantState.h"
#include "variableState.h"
#include "perPlayerState.h"
#include "gtest/gtest.h"
#include <map>
#include <string>

// Helper function to create a placeholder string
std::string getPlaceholder(int index) {
    return "This is entry number" + std::to_string(index);
}

// Helper function to create a map for stress testing
std::map<std::string, DV::DataValue> createMapForStressTest(int numEntries) {
    std::map<std::string, DV::DataValue> valueMap;

    for (int i = 0; i < numEntries; i++) {
        valueMap.insert(std::make_pair(getPlaceholder(i),
                                        DV::DataValue{ i + 1 }));
    }

    return valueMap;
}


// Helper function to create a vector for stress testing
std::vector<DV::DataValue> createVectorForStressTest(int numEntries){
    std::vector<DV::DataValue> valueVector;

    for (int i = 0; i < numEntries; i++){
        valueVector.emplace_back(DV::DataValue{ i });
    }

    return valueVector;
}

// Stress testing ability to hold a large number of values in a vector of DataValue
TEST(DataValueStressTest, VectorValueStressTest) {
    DV::DataValue dataValue;
    std::vector<DV::DataValue> valueVector = createVectorForStressTest(10000);
    std::vector<DV::DataValue> retrievedVector;

    dataValue.setValue(valueVector);
    retrievedVector = std::get<std::vector<DV::DataValue>>(dataValue.getValueVariant());

    for (int i = 0; i < 10000; i++) {
        EXPECT_EQ(std::get<int>(retrievedVector.at(i).getValueVariant()), std::get<int>(valueVector.at(i).getValueVariant()));
    }
    
    EXPECT_EQ(retrievedVector.size(), 10000);
}

// Stress testing ability to hold a large number of values in a map of DataValue
TEST(DataValueStressTest, MapValueStressTest) {
    DV::DataValue dataValue;
    std::map<std::string, DV::DataValue> valueMap = createMapForStressTest(10000);
    std::map<std::string, DV::DataValue> retrievedMap;

    dataValue.setValue(valueMap);
    retrievedMap = std::get<std::map<std::string, DV::DataValue>>(dataValue.getValueVariant());

    EXPECT_EQ(retrievedMap.size(), 10000);
}

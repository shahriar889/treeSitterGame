#include <string> 
#include <map>
#include "treeManager.h"
#include <iostream>      

namespace GS{


    class DataValue;

    using DataValuePtr = std::shared_ptr<DataValue>;

    class DataValue {
    private:
        int intValue;
        bool boolValue;
        std::string stringValue;
        std::map<std::string, DataValuePtr> mapValue;

    public:
        DataValue()
            : intValue(0), boolValue(false), stringValue(""), mapValue() {
        }

        // Getter methods for different types
        int getIntValue() const {
            return intValue;
        }

        bool getBoolValue() const {
            return boolValue;
        }

        std::string getStringValue() const {
            return stringValue;
        }

        std::map<std::string, DataValuePtr> getMapValue() const {
            return mapValue;
        }

        // Setter methods for different types
        void setIntValue(int newValue) {
            intValue = newValue;
        }

        void setBoolValue(bool newValue) {
            boolValue = newValue;
        }

        void setStringValue(const std::string& newValue) {
            stringValue = newValue;
        }

        void setMapValue(const std::map<std::string, DataValuePtr>& newValue) {
            mapValue = newValue;
        }
    };


    class GameState{
        public:
            GameState() = default;
            virtual ~GameState() = default;

            void setValue(const std::string& name,const GS::DataValue& value);

            GS::DataValue getValue(const std::string& name) const;
            virtual void configure(TM::TreeManager& treeManager) = 0;
    
        private:
            std::map<std::string, GS::DataValue> values;
    };
}
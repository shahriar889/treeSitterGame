#pragma once
#include <string> 
#include <map>
#include <vector>
#include "treeManager.h"
#include <iostream>
#include <functional>      

namespace GS{


    class DataValue;

    using DataValuePtr = std::shared_ptr<DataValue>;

    class DataValue {
    private:
        int intValue;
        bool boolValue;
        std::string stringValue;
        std::map<std::string, DataValuePtr> mapValue;
        std::vector<DataValue> listValue;

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

        std::vector<DataValue> getListValue() const {
            return listValue;
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
        void setListValue(const DataValue& newValue) {
            listValue.push_back(newValue);
        }
    };


    class GameState{
        public:
            using FuncType = std::function<GS::DataValue(const ts::Node&,const ts::Symbol&, TM::TreeManager&)>;
            GameState();
            virtual ~GameState() = default;

            void setValue(const std::string& name,const GS::DataValue& value);

            GS::DataValue getValue(const std::string& name) const;
            virtual void configure(TM::TreeManager& treeManager) = 0;
        protected:    
            GS::DataValue getQuotedString(const ts::Node& root,const ts::Symbol& symb, TM::TreeManager& treeManager)noexcept;
            GS::DataValue getNumber(const ts::Node& root,const ts::Symbol& symb, TM::TreeManager& treeManager) noexcept;
            GS::DataValue getBoolean(const ts::Node& root,const ts::Symbol& symb, TM::TreeManager& treeManager) noexcept;
            GS::DataValue getExpression(const ts::Node& root,const ts::Symbol& symb, TM::TreeManager& treeManager) noexcept;
            GS::DataValue getMapValue(const ts::Node& root,const ts::Symbol& symb, TM::TreeManager& treeManager) noexcept;
            GS::DataValue getListValue(const ts::Node& root,const ts::Symbol& symb, TM::TreeManager& treeManager) noexcept;
            std::map<ts::Symbol, FuncType> functionMap;

        private:
            std::map<std::string, GS::DataValue> values;


    };
}
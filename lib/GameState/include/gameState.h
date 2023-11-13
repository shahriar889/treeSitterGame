#pragma once
#include <string>
#include <map>
#include <vector>
#include "treeManager.h"
#include <iostream>
#include <functional>
#include <variant>

namespace GS {

    class DataValue;

    using DataValueVariant = std::variant<int, bool, std::string, std::map<std::string, DataValue>, std::vector<DataValue>>;

    class DataValue {
    private:
        DataValueVariant data;

    public:
        DataValue() = default;

        // Setter method for the value, map, or list
        void setValue(const int& newValue) {
            data = newValue;
        }

        void setValue(const bool& newValue) {
            data = newValue;
        }
        void setValue(const std::string& newValue) {
            data = newValue;
        }
        void setValue(const std::map<std::string, DataValue>& newValue) {
            data = newValue;
        }
        void setValue(const std::vector<DataValue>& newValue) {
            data = newValue;
        }

        // Getter method for the value, map, or list
        auto getValueVariant() const {
            return data;
        }
    };

    class GameState {
    public:
        using FuncType = std::function<DataValue(const ts::Node&, const ts::Symbol&, TM::TreeManager&)>;

        GameState();
        virtual ~GameState() = default;

        void setValue(const std::string& name, const DataValue& value);

        DataValue getValue(const std::string& name) const;
        virtual void configure(TM::TreeManager& treeManager) = 0;

    protected:
        GS::DataValue getQuotedString(const ts::Node& root, const ts::Symbol& symb, TM::TreeManager& treeManager) noexcept;
        GS::DataValue getNumber(const ts::Node& root, const ts::Symbol& symb, TM::TreeManager& treeManager) noexcept;
        GS::DataValue getBoolean(const ts::Node& root, const ts::Symbol& symb, TM::TreeManager& treeManager) noexcept;
        GS::DataValue getExpression(const ts::Node& root, const ts::Symbol& symb, TM::TreeManager& treeManager) noexcept;
        GS::DataValue getMapValue(const ts::Node& root, const ts::Symbol& symb, TM::TreeManager& treeManager) noexcept;
        GS::DataValue getListValue(const ts::Node& root, const ts::Symbol& symb, TM::TreeManager& treeManager) noexcept;

        std::map<ts::Symbol, FuncType> functionMap;

    private:
        std::map<std::string, GS::DataValue> values;
    };

}
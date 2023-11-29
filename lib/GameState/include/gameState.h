#pragma once
#include <string>
#include "treeManager.h"
#include <iostream>
#include <functional>
#include "dataValue.h"

namespace GS {

    class GameState {
    public:
        using FuncType = std::function<DV::DataValue(const ts::Node&, const ts::Symbol&, TM::TreeManager&)>;

        GameState();
        virtual ~GameState() = default;

        void setValue(const std::string& name, const DV::DataValue& value);

        DV::DataValue getValue(const std::string& name) const;
        virtual void configure(TM::TreeManager& treeManager) = 0;

    protected:
        DV::DataValue getQuotedString(const ts::Node& root, const ts::Symbol& symb, TM::TreeManager& treeManager) noexcept;
        DV::DataValue getNumber(const ts::Node& root, const ts::Symbol& symb, TM::TreeManager& treeManager) noexcept;
        DV::DataValue getBoolean(const ts::Node& root, const ts::Symbol& symb, TM::TreeManager& treeManager) noexcept;
        DV::DataValue getExpression(const ts::Node& root, const ts::Symbol& symb, TM::TreeManager& treeManager) noexcept;
        DV::DataValue getMapValue(const ts::Node& root, const ts::Symbol& symb, TM::TreeManager& treeManager) noexcept;
        DV::DataValue getListValue(const ts::Node& root, const ts::Symbol& symb, TM::TreeManager& treeManager) noexcept;

        std::map<ts::Symbol, FuncType> functionMap;

    private:
        std::map<std::string, DV::DataValue> values;
    };

}
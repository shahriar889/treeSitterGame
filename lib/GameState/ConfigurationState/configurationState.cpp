#include "configurationState.h"

using namespace GS;
using FunctionType = std::function<void(const ts::Symbol&, TM::TreeManager&, ConfigurationState&)>;

// Helper function to set a string value
void setDataValueString(ConfigurationState& conf, const std::string& name, const std::string& value) {
    DataValue data;
    data.setStringValue(value);
    conf.setValue(name, data);
}

// Helper function to set an integer value
void setDataValueInt(ConfigurationState& conf, const std::string& name, int value) {
    DataValue data;
    data.setIntValue(value);
    conf.setValue(name, data);
}

void name(const ts::Symbol& symb, TM::TreeManager& treeManager, ConfigurationState& conf) {
    ts::Node root = treeManager.getRoot();
    ts::Node nameNode = std::get<1>(treeManager.findNodeBySymbol(root, symb));
    ts::Node valueNode = nameNode.getNextSibling();
    std::string name = treeManager.getSourceRange(valueNode);
    setDataValueString(conf, "name", name);
}

void playerRange(const ts::Symbol& symb, TM::TreeManager& treeManager, ConfigurationState& conf) {
    ts::Node root = treeManager.getRoot();
    ts::Node playerRangeNode = std::get<1>(treeManager.findNodeBySymbol(root, symb));
    ts::Node valueNode = playerRangeNode.getNextSibling();
    std::tuple<int, int> playerRange = treeManager.getNumberRange(valueNode);
    setDataValueInt(conf, "playerRangeMin", std::get<0>(playerRange));
    setDataValueInt(conf, "playerRangeCur", std::get<0>(playerRange));
    setDataValueInt(conf, "playerRangeMax", std::get<1>(playerRange));
}


// Helper function to set a boolean value
void setDataValueBool(ConfigurationState& conf, const std::string& name, bool value) {
    DataValue data;
    data.setBoolValue(value);
    conf.setValue(name, data);
}

void hasAudience(const ts::Symbol& symb, TM::TreeManager& treeManager, ConfigurationState& conf) {
    ts::Node root = treeManager.getRoot();
    ts::Node hasAudienceNode = std::get<1>(treeManager.findNodeBySymbol(root, symb));
    ts::Node valueNode = hasAudienceNode.getNextSibling();
    std::string hasAudience = treeManager.getSourceRange(valueNode);

    // Check if the value is "true" and set the boolean accordingly
    setDataValueBool(conf, "hasAudience", (hasAudience == "true"));
}

std::map<std::string, GS::DataValuePtr> parseIntegerKind(TM::TreeManager& treeManager, const ts::Symbol& symb) {
    ts::Node root = treeManager.getRoot();
    ts::Node promptNode = std::get<1>(treeManager.findNodeBySymbol(root, symb));
    ts::Node temp = promptNode.getNextSibling();
    std::string prompt = treeManager.getSourceRange(temp);

    DataValue dataString;
    dataString.setStringValue(prompt);

    std::map<std::string, GS::DataValuePtr> tempMap;
    tempMap["prompt"] = std::make_shared<DataValue>(dataString);

    ts::Node rangeNode = temp.getNextSibling();
    std::tuple<int, int> range = treeManager.getNumberRange(rangeNode.getNextSibling());

    DataValue dataMin;
    dataMin.setIntValue(std::get<0>(range));

    GS::DataValuePtr tempPtr1 = std::make_shared<DataValue>(dataMin);
    tempMap["rangeMin"] = tempPtr1;

    DataValue dataMax;
    dataMax.setIntValue(std::get<1>(range));
    DataValue dataCur;
    dataCur.setIntValue(std::get<0>(range));
    GS::DataValuePtr tempPtr3 = std::make_shared<DataValue>(dataCur);
    tempMap["rangeCur"] = tempPtr3;

    GS::DataValuePtr tempPtr2 = std::make_shared<DataValue>(dataMax);
    tempMap["rangeMax"] = tempPtr2;

    return tempMap;
}

void setUpRule(const ts::Symbol& symb, TM::TreeManager& treeManager, ConfigurationState& conf) {
    ts::Node root = treeManager.getRoot();
    ts::Node setUpRuleNode = std::get<1>(treeManager.findNodeBySymbol(root, symb));
    std::vector<ts::Node> iden;
    std::vector<ts::Node> kind;
    for (int i = 0; i < setUpRuleNode.getNumChildren(); i++) {
        if (setUpRuleNode.getChild(i).getSymbol() == ts::Symbol(85)) {
            iden.push_back(setUpRuleNode.getChild(i));
        }
        else if (setUpRuleNode.getChild(i).getSymbol() == ts::Symbol(8)) {
            kind.push_back(setUpRuleNode.getChild(i + 1));
        }
    }

    for (int i = 0; i < kind.size(); i++) {
        std::string idenName = treeManager.getSourceRange(iden[i]);
        std::string kindName = treeManager.getSourceRange(kind[i]);

        if (kindName == "integer") {
            std::map<std::string, GS::DataValuePtr> tempMap = parseIntegerKind(treeManager, kind[i].getNextSibling().getSymbol());
            DataValue data;
            data.setMapValue(tempMap);
            conf.setValue(idenName, data);
        }
    }
}

void ConfigurationState::configure(TM::TreeManager& treeManager) {
    ts::Node root = treeManager.getRoot();
    ts::Node configurationNode = std::get<1>(treeManager.findNodeBySymbol(root, ts::Symbol(91)));
    std::map<ts::Symbol, FunctionType> functionMap;
    functionMap[ts::Symbol(3)] = name;
    functionMap[ts::Symbol(4)] = playerRange;
    functionMap[ts::Symbol(5)] = hasAudience;
    functionMap[ts::Symbol(92)] = setUpRule;
    for (int i = 0; i < configurationNode.getNumChildren(); i++) {
        ts::Node temp = configurationNode.getChild(i);
        if (functionMap.find(temp.getSymbol()) != functionMap.end()) {
            functionMap[temp.getSymbol()](temp.getSymbol(), treeManager, *this);
        }
    }
}

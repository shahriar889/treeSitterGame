#include "gameState.h"
using namespace GS;

DataValue GameState::getValue(const std::string& name) const {
    auto it = values.find(name);
    if (it != values.end()) {
        printf("found value\n");
        return it->second; 
    }
    return DataValue(); // Default-constructed std::variant, which is empty. 
}

void GameState::setValue(const std::string& name, const DataValue& value) {
    values[name] = value;
}

GameState::GameState() {
    values = std::map<std::string, DataValue>();
    this->functionMap[ts::Symbol(84)] = [this](const ts::Node& root,const ts::Symbol& symb, TM::TreeManager& treeManager) -> DataValue { return this->getQuotedString(root,symb,treeManager); };
    this->functionMap[ts::Symbol(81)] = [this](const ts::Node& root,const ts::Symbol& symb, TM::TreeManager& treeManager) -> DataValue { return this->getNumber(root,symb,treeManager); };
    this->functionMap[ts::Symbol(123)] = [this](const ts::Node& root,const ts::Symbol& symb, TM::TreeManager& treeManager) -> DataValue { return this->getBoolean(root,symb,treeManager); };
    this->functionMap[ts::Symbol(128)] = [this](const ts::Node& root,const ts::Symbol& symb, TM::TreeManager& treeManager) -> DataValue { return this->getMapValue(root,symb,treeManager); };
    this->functionMap[ts::Symbol(126)] = [this](const ts::Node& root,const ts::Symbol& symb, TM::TreeManager& treeManager) -> DataValue { return this->getListValue(root,symb,treeManager); };
}
DataValue GameState::getQuotedString(const ts::Node& root,const ts::Symbol& symb, TM::TreeManager& treeManager) noexcept{
    printf("getQuotedString\n");
    DataValue data;
    data.setStringValue(treeManager.getSourceRange(root));
    return data;
}

DataValue GameState::getNumber(const ts::Node& root,const ts::Symbol& symb, TM::TreeManager& treeManager) noexcept{
    printf("getNumber\n");
    DataValue data;
    std::string number = treeManager.getSourceRange(root);
    data.setIntValue(std::stoi(number));
    return data;
}

DataValue GameState::getBoolean(const ts::Node& root,const ts::Symbol& symb, TM::TreeManager& treeManager) noexcept{
    printf("getBoolean\n");
    DataValue data;
    std::string boolean = treeManager.getSourceRange(root);
    data.setBoolValue(boolean == "true");
    return data;
}

DataValue GameState::getExpression(const ts::Node& root,const ts::Symbol& symb, TM::TreeManager& treeManager) noexcept{
    printf("getExpression\n");
    ts::Node temp = root.getChild(0);
    DataValue data;
    if (functionMap.find(temp.getSymbol()) != functionMap.end()) {
            data = functionMap[temp.getSymbol()](temp,temp.getSymbol(), treeManager);
            return data;
        }
    return data;
}

DataValue GameState::getListValue(const ts::Node& root,const ts::Symbol& symb, TM::TreeManager& treeManager) noexcept{
    printf("getListValue\n");
    std::tuple<int, ts::Node> listTuple = treeManager.findNodeBySymbol(root, ts::Symbol(125));
    ts::Node expressionListNode = std::get<1>(listTuple);
    DataValue data;
    for(uint32_t i = 0; i < expressionListNode.getNumChildren();i++){
        ts::Node expressionNode = expressionListNode.getChild(i);
        if(expressionNode.getSymbol() == ts::Symbol(120)){
            DataValue value = getExpression(expressionNode,expressionNode.getSymbol(), treeManager);
            data.setListValue(value);
        }
    }
    return data;
}

DataValue GameState::getMapValue(const ts::Node& root,const ts::Symbol& symb, TM::TreeManager& treeManager)noexcept{
    printf("getMapValue\n");
    DataValue data;
    std::map<std::string, DataValuePtr> map;
    for(u_int32_t i = 0; i < root.getNumChildren();i++){
        ts::Node mapEntryNode = root.getChild(i);
        if(mapEntryNode.getSymbol() == ts::Symbol(127)){
            ts::Node keyNode = mapEntryNode.getChild(0);
            std::string key = treeManager.getSourceRange(keyNode);
            ts::Node expressionNode = mapEntryNode.getChild(2);
            DataValue value = getExpression(expressionNode,expressionNode.getSymbol(), treeManager);
            DataValuePtr valuePtr = std::make_shared<DataValue>(value);
            map[key] = valuePtr;
        }
    }
    data.setMapValue(map);
    return data;
}



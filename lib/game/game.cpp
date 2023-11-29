#include "Game.h"

Game::Game(std::string path) {
    TM::TreeManager treeManager(path);
    
    ConfigurationState conf;
    conf.configure(treeManager);
    ConstantState constantState = ConstantState();
    constantState.configure(treeManager);
    VariableState variableState = VariableState();
    variableState.configure(treeManager);

    std::string gameName = std::get<std::string>(conf.getValue("name").getValueVariant());
    int pLRangeMin = std::get<int>(conf.getValue("playerRangeMin").getValueVariant());
    int pLRangeMax = std::get<int>(conf.getValue("playerRangeMax").getValueVariant());
    int pLRangeCur = std::get<int>(conf.getValue("playerRangeCur").getValueVariant());
    bool hasAudience = std::get<bool>(conf.getValue("hasAudience").getValueVariant());
    DV::DataValue data = conf.getValue("rounds");

    std::map<std::string, DV::DataValue> mapValue = std::get<std::map<std::string, DV::DataValue>>(data.getValueVariant());
    std::string prompt = std::get<std::string>(mapValue["prompt"].getValueVariant());
    int rangeMin = std::get<int>(mapValue["rangeMin"].getValueVariant());
    int rangeCur = std::get<int>(mapValue["rangeCur"].getValueVariant());
    int rangeMax = std::get<int>(mapValue["rangeMax"].getValueVariant());

    DV::DataValue data2 = constantState.getValue("constant1");
    std::map<std::string, DV::DataValue> mapValue2 = std::get<std::map<std::string, DV::DataValue>>(data2.getValueVariant());
    DV::DataValue data3 = mapValue2["weapons"];
    std::vector<DV::DataValue> listValue = std::get<std::vector<DV::DataValue>>(data3.getValueVariant());
    DV::DataValue data4 = variableState.getValue("variable1");
    std::map<std::string, DV::DataValue> mapValue3 = std::get<std::map<std::string, DV::DataValue>>(data4.getValueVariant());
    DV::DataValue data5 = mapValue3["weapons"];

    auto stateManager = std::make_shared<StateManager>(variableState, constantState, conf);
    ruleManager = RuleParser::createRuleManager(treeManager, buildTreeSitterTranslator());
    ruleManager.setGlobalState(stateManager);
}

void Game::start() {
    ruleManager.start();
}
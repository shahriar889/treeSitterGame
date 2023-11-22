#include "Game.h"



Game::Game(std::string path){
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
    GS::DataValue data = conf.getValue("rounds");

    std::map<std::string, GS::DataValue> mapValue = std::get<std::map<std::string, GS::DataValue>>(data.getValueVariant());
    std::string prompt = std::get<std::string>(mapValue["prompt"].getValueVariant());
    int rangeMin = std::get<int>(mapValue["rangeMin"].getValueVariant());
    int rangeCur = std::get<int>(mapValue["rangeCur"].getValueVariant());
    int rangeMax = std::get<int>(mapValue["rangeMax"].getValueVariant());


    GS::DataValue data2 = constantState.getValue("constant1");
    std::map<std::string, GS::DataValue> mapValue2 = std::get<std::map<std::string, GS::DataValue>>(data2.getValueVariant());
    GS::DataValue data3 = mapValue2["weapons"];
    std::vector<GS::DataValue> listValue = std::get<std::vector<GS::DataValue>>(data3.getValueVariant());
    GS::DataValue data4 = variableState.getValue("variable1");
    std::map<std::string, GS::DataValue> mapValue3 = std::get<std::map<std::string, GS::DataValue>>(data4.getValueVariant());
    GS::DataValue data5 = mapValue3["weapons"];

    RuleManager ruleManager = treeManager.createRuleManager();

    //based on number of player created create player states reuquire user input
    //PerPlayerState perPlayerState = PerPlayerState();
    //perPlayerState.configure(treeManager);

}
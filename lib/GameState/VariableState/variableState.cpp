#include "variableState.h"

using namespace GS;
using namespace DV;


void VariableState::configure(TM::TreeManager& treeManager) {
    ts::Node root = treeManager.getRoot();
    ts::Node varibleNode = std::get<1>(treeManager.findNodeBySymbol(root, ts::Symbol(95)));
    for(uint32_t i = 0; i < varibleNode.getNumChildren(); i++){
        ts::Node varibleEntryNode = varibleNode.getChild(i);
        ts::Symbol symb = varibleEntryNode.getSymbol();
            if (functionMap.find(symb) != functionMap.end()) {
                DataValue data = functionMap[symb](varibleEntryNode,symb, treeManager);
                std::string counter = std::to_string(i);
                std::string_view counterView(counter);
                std::string name = "variable" + std::string(counterView);
                setValue(name, data);
            }
    }
}


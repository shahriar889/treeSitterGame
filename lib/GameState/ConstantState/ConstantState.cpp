#include "ConstantState.h"

using namespace GS;


void ConstantState::configure(TM::TreeManager& treeManager) {
    printf("ConstantState::configure\n");
    ts::Node root = treeManager.getRoot();
    ts::Node constantNode = std::get<1>(treeManager.findNodeBySymbol(root, ts::Symbol(94)));
    for(uint32_t i = 0; i < constantNode.getNumChildren(); i++){
        ts::Node constantEntryNode = constantNode.getChild(i);
        ts::Symbol symb = constantEntryNode.getSymbol();
            if (functionMap.find(symb) != functionMap.end()) {
                DataValue data = functionMap[symb](constantEntryNode,symb, treeManager);
                std::string counter = std::to_string(i);
                std::string_view counterView(counter);
                std::string name = "constant" + std::string(counterView);
                setValue(name, data);
            }
    }
}


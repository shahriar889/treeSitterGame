#include "perPlayerState.h"

using namespace GS;


void PerPlayerState::configure(TM::TreeManager& treeManager) {
    ts::Node root = treeManager.getRoot();
    ts::Node perPlayerNode = std::get<1>(treeManager.findNodeBySymbol(root, ts::Symbol(96)));
    for(uint32_t i = 0; i < perPlayerNode.getNumChildren(); i++){
        ts::Node perPlayerEntryNode = perPlayerNode.getChild(i);
        ts::Symbol symb = perPlayerEntryNode.getSymbol();
            if (functionMap.find(symb) != functionMap.end()) {
                DataValue data = functionMap[symb](perPlayerEntryNode,symb, treeManager);
                std::string counter = std::to_string(i);
                std::string_view counterView(counter);
                std::string name = "perPlayer" + std::string(counterView);
                setValue(name, data);
            }
    }
}


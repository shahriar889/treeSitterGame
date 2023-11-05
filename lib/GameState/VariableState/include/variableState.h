#pragma once
#include "gameState.h"
#include <vector>
#include <functional>
using namespace GS;

class VariableState : public GS::GameState {
    public:
        VariableState() = default;
        ~VariableState() = default;
        void configure(TM::TreeManager& treeManager) override;
};
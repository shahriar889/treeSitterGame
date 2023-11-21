#pragma once
#include "gameState.h"
#include <vector>
#include <functional>
using namespace GS;

class ConstantState : public GS::GameState {
    public:
        ConstantState() = default;
        ~ConstantState() = default;
        void configure(TM::TreeManager& treeManager) override;
};
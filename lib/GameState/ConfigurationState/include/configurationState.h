#pragma once
#include "gameState.h"
#include <vector>
#include <functional>

class ConfigurationState : public GS::GameState {
    public:
        ConfigurationState() = default;
        ~ConfigurationState() = default;
        void configure(TM::TreeManager& treeManager) override;
};
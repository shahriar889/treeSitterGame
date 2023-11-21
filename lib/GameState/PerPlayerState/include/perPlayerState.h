#pragma once
#include "gameState.h"
#include <vector>
#include <functional>
using namespace GS;

class PerPlayerState : public GS::GameState {
    public:
        PerPlayerState(const int& playerID) : GameState(), playerID(playerID) {}
        ~PerPlayerState() = default;
        int getPlayerID() const {return playerID;}
        void configure(TM::TreeManager& treeManager) override;
    private:
        int playerID;
};
#pragma once

#include "GameInterface.h"

class FakeGame : public GameInterface {
public:
    // constructor
    FakeGame();

    // destructor
    virtual ~FakeGame();

    // implement GameInterface methods
    virtual void start() override;
    virtual void pause() override;
    virtual void resume() override;
    virtual void stop() override;
};

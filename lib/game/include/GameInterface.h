

class GameInterface {
public:
    virtual void incrementRound() = 0;
    virtual void incrementScore() = 0;
    virtual void start() =0 ;
    virtual void pause() =0;
    virtual void resume() =0;
    virtual void stop() =0;
};

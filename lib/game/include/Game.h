#include "treeManager.h"
#include "configurationState.h"
#include "constantState.h"
#include "variableState.h"
#include "perPlayerState.h"
#include "ruleManager.h"
#include "ruleParser.h"

class Game{
    public:
        Game(std::string path);
        void start();
        
    private:
        RuleManager ruleManager;
};


#include "rules.h"

void ForEachLoopRule::executeImpl(std::shared_ptr<StateManager> states)
{
    std::cout << "Executing For-Each loop...\n";
    for (int i = 0; i < expressions.size(); i++) {
        std::cout << expressions[i].value << "\n";
    }
    std::for_each(rules.begin(), rules.end(), [&states](std::unique_ptr<Rule> &rule){ rule.get()->execute(states); });
    this->setDone();

}

void WhileLoopRule::executeImpl(std::shared_ptr<StateManager>)
{
    std::cout << "Executing While loop...\n";
}

void ParallelForLoopRule::executeImpl(std::shared_ptr<StateManager>)
{
    std::cout << "Executing Parallel-For loop...\n";
};

void MatchLoopRule::executeImpl(std::shared_ptr<StateManager>)
{
    std::cout << "Executing Match loop...\n";
};
void ExtendListRule::executeImpl(std::shared_ptr<StateManager>)
{
    std::cout << "Executing Extend list...\n";
};

void DiscardListRule::executeImpl(std::shared_ptr<StateManager>)
{
    std::cout << "Executing Discard list...\n";
}

void MessageOutputRule::executeImpl(std::shared_ptr<StateManager>)
{
    std::cout << "Executing Message output...\n";
}

void AssignmentRule::executeImpl(std::shared_ptr<StateManager>)
{
    std::cout << "Executing Assignment...\n";
}
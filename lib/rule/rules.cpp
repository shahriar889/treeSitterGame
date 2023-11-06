#include "rules.h"

void ForEachLoopRule::executeImpl()
{
    std::cout << "Executing For-Each loop...\n";
}

void WhileLoopRule::executeImpl()
{
    std::cout << "Executing While loop...\n";
}

void ParallelForLoopRule::executeImpl()
{
    std::cout << "Executing Parallel-For loop...\n";
};

void MatchLoopRule::executeImpl()
{
    std::cout << "Executing Match loop...\n";
};
void ExtendListRule::executeImpl()
{
    std::cout << "Executing Extend list...\n";
};

void DiscardListRule::executeImpl()
{
    std::cout << "Executing Discard list...\n";
}

void MessageOutputRule::executeImpl()
{
    std::cout << "Executing Message output...\n";
}

void AssignmentRule::executeImpl()
{
    std::cout << "Executing Assignment...\n";
}
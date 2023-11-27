#include "rules.h"

//HELPERS
std::vector<std::string> tokenizeExpression(Expression input) {
    std::istringstream iss(input.value);
    std::string token;
    std::vector<std::string> tokens;

    while (std::getline(iss, token, '.')) {
        tokens.emplace_back(token);
    }

    return tokens;
}

void ForEachLoopRule::executeImpl(std::shared_ptr<StateManager> states)
{
    std::cout << "Executing For-Each loop...\n";

    std::for_each(expressions.begin(), expressions.end(), [](Expression e) {
        std::cout << "For-each Expression: " << e.value << "\n";
    });

    auto tokens = tokenizeExpression(expressions[1].value);
    //auto val = states->configuration.getValue(tokens[1]);
    
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

void InputChoiceRule::executeImpl(std::shared_ptr<StateManager>)
{
    std::cout << "Executing Input Choice...\n";
}
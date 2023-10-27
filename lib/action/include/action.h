#pragma once

#include <string>
#include <vector>

class Action {
    public:
        Action(std::string, std::vector<Action>);
    private:
        std::string type;
        std::vector<Action> body;
};
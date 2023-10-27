#include "action.h"

Action::Action(std::string type, std::vector<Action> body) 
    : type(type), body(body) {};
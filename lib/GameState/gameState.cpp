#include "gameState.h"

GS::DataValue GS::GameState::getValue(const std::string& name) const {
    auto it = values.find(name);
    if (it != values.end()) {
        return it->second; 
    }
    return GS::DataValue(); // Default-constructed std::variant, which is empty. 
}

void GS::GameState::setValue(const std::string& name, const GS::DataValue& value) {
    values[name] = value;
}

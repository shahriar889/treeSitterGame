#include "configurationState.h"
#include "constantState.h"
#include "variableState.h"

struct StateManager {
    StateManager() = default;
    StateManager(VariableState vs, ConstantState cs, ConfigurationState cf) :
        variables{vs}, constants(cs), configuration(cf) {};

    VariableState variables;
    ConstantState constants;
    ConfigurationState configuration;
};
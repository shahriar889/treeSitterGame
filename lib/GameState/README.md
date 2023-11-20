gameState.h includes a DataValue class which is variant that can hold string, int, double, bool, list of DataValue and map of string to DataValue.

GameState is an abstarct class that different states can inherit. It implements different fucntions for getting quoted string node, number node, bool node, value_map, expression_lists and expression. These functions are put in a map corresponding to their symbols called FuncType.

All States must implement configure method to set their value by using the treeManager Library.

ConfigurationState implements its own functions to get accurate value since its structure is different than other states. Then assigns these functions to Functype and uses it set its data.

ConstantState, VariableState and PerPlayerState has the same structure so it uses the FuncType defined by GameState class and uses it set its data starting from its root.
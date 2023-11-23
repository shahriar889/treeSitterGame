add_library(StateManager stateManager.cpp)

target_link_libraries(StateManager
    ConfigurationState ConstantState PerPlayerState VariableState
)

target_include_directories(StateManager PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

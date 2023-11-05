add_library(GameState gameState.cpp)

target_include_directories(GameState PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
target_link_libraries(GameState PUBLIC
    TreeManager
)
add_subdirectory(ConfigurationState)
add_subdirectory(ConstantState)
add_subdirectory(VariableState)
add_subdirectory(PerPlayerState)
add_library(VariableState variableState.cpp)

target_link_libraries(VariableState
GameState
)

target_include_directories(VariableState PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
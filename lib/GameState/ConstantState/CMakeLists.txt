add_library(ConstantState constantState.cpp)

target_link_libraries(ConstantState
GameState
)

target_include_directories(ConstantState PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
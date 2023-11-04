add_library(ConfigurationState configurationState.cpp)

target_link_libraries(ConfigurationState
TreeManager
GameState
)

target_include_directories(ConfigurationState PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
add_library(PerPlayerState perPlayerState.cpp)

target_link_libraries(PerPlayerState
GameState
)

target_include_directories(PerPlayerState PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

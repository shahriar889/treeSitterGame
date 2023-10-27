add_library(rules rules.cpp)

target_link_libraries(rules 
    action
)

target_include_directories(rules PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

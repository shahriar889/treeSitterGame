add_library(rule rule.cpp)

target_link_libraries(rule 
    node
)

target_include_directories(rule PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

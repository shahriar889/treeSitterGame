add_library(node node.cpp)

target_link_libraries(node 

)

target_include_directories(node PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

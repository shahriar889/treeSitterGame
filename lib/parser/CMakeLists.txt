add_library(parser parser.cpp)

target_link_libraries(parser 
    cpp-tree-sitter
    tree-sitter-socialgaming
    rule
)

target_include_directories(parser PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

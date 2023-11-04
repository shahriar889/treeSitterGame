add_library(TreeManager treeManager.cpp)

target_link_libraries(TreeManager
cpp-tree-sitter
tree-sitter-socialgaming
)

target_include_directories(TreeManager PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
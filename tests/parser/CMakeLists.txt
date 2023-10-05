add_executable(testparser)
target_sources(testparser
  PRIVATE
    testparser.cpp
)

target_link_libraries(testparser
  tree-sitter-socialgaming
  cpp-tree-sitter
)

set_target_properties(testparser 
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

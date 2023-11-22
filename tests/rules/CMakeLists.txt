add_executable(rule_test)

target_sources(rule_test
  PRIVATE
  rule_test.cpp
)

target_link_libraries(rule_test
   gtest gmock gtest_main TreeManager ruleManager ruleTranslator
)

set_target_properties(rule_test 
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

gtest_discover_tests(rule_test WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
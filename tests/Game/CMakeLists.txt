add_executable(game_test)

target_sources(game_test
  PRIVATE
  game_test.cpp
)

target_link_libraries(game_test
   gtest gmock gtest_main TreeManager StateManager ruleManager ruleTranslator GameState Game
)

set_target_properties(game_test 
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

gtest_discover_tests(game_test WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
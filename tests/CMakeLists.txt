cmake_minimum_required(VERSION 3.14)
project(socialgaming-tests)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

# Define test targets below, and link them against the google test library
add_executable(hello_world hello_world.cpp)
add_executable(parser_test parser_test.cpp)
add_subdirectory(parser)
# TODO add test

set(TEST_TARGETS hello_world parser_test)

foreach(TEST_TARGET IN LISTS TEST_TARGETS)
  target_link_libraries(${TEST_TARGET} PRIVATE GTest::gtest_main)
  add_test(NAME ${TEST_TARGET} COMMAND ${TEST_TARGET})
endforeach(TEST_TARGET IN LISTS TEST_TARGETS)


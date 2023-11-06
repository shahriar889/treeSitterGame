cmake_minimum_required(VERSION 3.14)
project(socialgaming-tests)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add test library directories
add_subdirectory(lib)

# Add test subdirectories
add_subdirectory(parser)
add_subdirectory(server-v1)

### DEFAULT TEST DEFINITION FORMAT

# Define test targets below, and link them against the google test library
add_executable(hello_world)
target_sources(hello_world PRIVATE hello_world.cpp)
# Remove g_test_main if writing your own main function in your test source file. Add more libraries as necessary
target_link_libraries(hello_world gtest gmock gtest_main)
# gtest_discover_tests replaces gtest_add_tests,
# see https://cmake.org/cmake/help/v3.10/module/GoogleTest.html for more options to pass to it
set_target_properties(hello_world PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
gtest_discover_tests(hello_world WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

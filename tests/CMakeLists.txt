cmake_minimum_required(VERSION 3.14)
project(socialgaming-tests)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add test subdirectories
add_subdirectory(parser)

# Macro for adding tests linked to googletest
# Use as such: package_add_test(test1 test1.cpp)
macro(package_add_test TESTNAME TESTFILE)
    add_executable(${TESTNAME} ${TESTFILE})
    # Remove g_test_main if writing your own main function.
    target_link_libraries(${TESTNAME} gtest gmock gtest_main)
    # gtest_discover_tests replaces gtest_add_tests,
    # see https://cmake.org/cmake/help/v3.10/module/GoogleTest.html for more options to pass to it
    set_target_properties(${TESTNAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    gtest_discover_tests(${TESTNAME})
    # set_target_properties(${TESTNAME} PROPERTIES FOLDER tests)
endmacro()

# Macro for adding tests linked to googletest with libraries
# Use as such: package_add_test(test1 test1.cpp lib1 lib2)
macro(package_add_test_libraries TESTNAME TESTFILE LIBRARIES)
    add_executable(${TESTNAME} ${TESTFILE})
    # Remove g_test_main if writing your own main function.
    target_link_libraries(${TESTNAME} gtest gmock gtest_main ${LIBRARIES})
    # gtest_discover_tests replaces gtest_add_tests,
    # see https://cmake.org/cmake/help/v3.10/module/GoogleTest.html for more options to pass to it
    set_target_properties(${TESTNAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    gtest_discover_tests(${TESTNAME})
    # set_target_properties(${TESTNAME} PROPERTIES FOLDER tests)
endmacro()

# Define test targets below, and link them against the google test library
package_add_test(hello_world hello_world.cpp)
package_add_test(parser_test parser_test.cpp)
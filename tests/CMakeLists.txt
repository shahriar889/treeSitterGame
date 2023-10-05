cmake_minimum_required(VERSION 3.14)
project(socialgaming-tests)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Install the google test dependency
CPMAddPackage(
  NAME googletest 
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz
  URL_HASH SHA256=8ad598c73ad796e0d8280b082cebd82a630d73e73cd3c70057938a6501bba5d7
  VERSION 1.14.0
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Define test targets below, and link them against the google test library
add_executable(hello_world hello_world.cpp)
add_executable(parser_test parser_test.cpp)

set(TEST_TARGETS hello_world parser_test)

foreach(TEST_TARGET IN LISTS TEST_TARGETS)
  target_link_libraries(${TEST_TARGET} PRIVATE GTest::gtest_main)
  add_test(NAME ${TEST_TARGET} COMMAND ${TEST_TARGET})
endforeach(TEST_TARGET IN LISTS TEST_TARGETS)


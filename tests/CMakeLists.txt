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

add_executable(
  parser_test
  parser_test.cpp
)
target_link_libraries(
  parser_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(parser_test)

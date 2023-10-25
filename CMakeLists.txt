cmake_minimum_required(VERSION 3.14)
include(cmake/CPM.cmake)

project(SocialGamingBrawndo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR/bin}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR/lib}")

# Build tests along with the project by default
# Build project with flag "-DPACKAGE_TESTS=OFF" to disable building test directory
option(PACKAGE_TESTS "Build the tests" OFF)
if(PACKAGE_TESTS)
    enable_testing()
    include(GoogleTest)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)
endif()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/extern) # All external libraries/deps to be built


# The executable code is here
add_subdirectory(apps)

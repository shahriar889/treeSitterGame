cmake_minimum_required(VERSION 3.14)
project(SocialGamingBrawndo)

include(cmake/CPM.cmake)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR/bin}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR/lib}")


add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests) 
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/extern) # All external libraries/deps to be built

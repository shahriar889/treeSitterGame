# Define the test sources for gameClass
set(TREE_MANAGER_TEST_SOURCES
    treeManagerTest.cpp
    # Add more test source files as needed
)

# Create the test executables for TreeManager
foreach(TEST_SOURCE ${TREE_MANAGER_TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
    add_executable(${TEST_NAME})
    target_sources(${TEST_NAME} PRIVATE ${TEST_SOURCE})
    target_link_libraries(${TEST_NAME} gtest gmock gtest_main TreeManager) # Link your gameClass library
    set_target_properties(${TEST_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    gtest_discover_tests(${TEST_NAME} WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
endforeach()

project(server-v1)
add_executable(${PROJECT_NAME} main.cpp)
# add_subdirectory(ServerManager)
# add_subdirectory(Room)
# add_subdirectory(User)
# add_subdirectory(StringHandling)

# target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} 
    PUBLIC
   ServerManager
)
set_target_properties(${PROJECT_NAME} 
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 17
                      PREFIX ""
)


set_target_properties(${PROJECT_NAME}
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

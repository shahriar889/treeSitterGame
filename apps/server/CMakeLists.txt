# Define the source files for your project



add_executable(server server.cpp Room.cpp)

target_include_directories(server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(server
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 17
                      PREFIX ""
)

find_package(Threads REQUIRED)

target_link_libraries(server
  networking
  ${CMAKE_THREAD_LIBS_INIT}
)

install(TARGETS server
  RUNTIME DESTINATION bin
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/webchat.html DESTINATION ${CMAKE_BINARY_DIR}/bin)
set_target_properties(server 
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

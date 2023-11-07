# Define the source files for your project



add_executable(server-san-prototype server.cpp Room.cpp)

target_include_directories(server-san-prototype PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(server-san-prototype
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 17
                      PREFIX ""
)

find_package(Threads REQUIRED)

target_link_libraries(server-san-prototype 
  networking
  ${CMAKE_THREAD_LIBS_INIT}
)

install(TARGETS server-san-prototype
  RUNTIME DESTINATION bin
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/webchat.html DESTINATION ${CMAKE_BINARY_DIR}/bin)
set_target_properties(server-san-prototype 
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(s1-server-model)
add_executable(server-jar-prototype
  chatserver.cpp
  serverdriver.cpp
)

set_target_properties(server-jar-prototype
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 17
                      PREFIX ""
)

find_package(Threads REQUIRED)

target_link_libraries(server-jar-prototype
  networking
  ${CMAKE_THREAD_LIBS_INIT}
)

target_link_libraries(server-jar-prototype
  server_model
)

install(TARGETS server-jar-prototype
  RUNTIME DESTINATION bin
)

set_target_properties(server-jar-prototype 
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


add_executable(serverdriver
  chatserver.cpp
  serverdriver.cpp
)

set_target_properties(serverdriver
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 17
                      PREFIX ""
)

find_package(Threads REQUIRED)

target_link_libraries(serverdriver
  networking
  ${CMAKE_THREAD_LIBS_INIT}
)

target_link_libraries(serverdriver
  server_model
)

install(TARGETS serverdriver
  RUNTIME DESTINATION bin
)



add_executable(s1-serverdriver
  chatserver.cpp
  serverdriver.cpp
)

set_target_properties(s1-serverdriver
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 17
                      PREFIX ""
)

find_package(Threads REQUIRED)

target_link_libraries(s1-serverdriver
  networking
  ${CMAKE_THREAD_LIBS_INIT}
)

target_link_libraries(s1-serverdriver
  server_model
)

install(TARGETS s1-serverdriver
  RUNTIME DESTINATION bin
)


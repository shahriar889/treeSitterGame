
add_executable(s1-client-ncurses
  chatclient.cpp
  ChatWindow.cpp
)

set_target_properties(s1-client-ncurses
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 17
                      PREFIX ""
)

find_package(Curses REQUIRED)
find_package(Threads REQUIRED)

target_link_libraries(s1-client-ncurses
  networking
  ${CURSES_LIBRARIES}
  ${CMAKE_THREAD_LIBS_INIT}
)

install(TARGETS s1-client-ncurses
  RUNTIME DESTINATION bin
)


add_library(server_model
  src/Room.cpp
  src/JoinCode.cpp
)

target_include_directories(server_model
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(server_model networking)

set_target_properties(server_model
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 17
)

install(TARGETS server_model
  ARCHIVE DESTINATION lib
)


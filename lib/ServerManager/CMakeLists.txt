# Define the library target
add_library(ServerManager ServerManager.cpp)

# Set the C++ standard and linker language for the target
set_target_properties(ServerManager PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 17
)

# Specify the include directories for the target
target_include_directories(ServerManager
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(ServerManager Room networking)
# Set the output directory for the library
set_target_properties(ServerManager PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/ServerManager"
)

# Install the target and its public headers
install(TARGETS ServerManager
    EXPORT ServerManagerTargets
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include
)

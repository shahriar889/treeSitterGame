# Define the library target
add_library(ServerManager serverManager.cpp)

# Set the C++ standard and linker language for the target
set_target_properties(ServerManager PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 17
)

# Specify the include directories for the target
target_include_directories(ServerManager
    PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)


# Set the output directory for the library
set_target_properties(ServerManager PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/server-v1"
)

# Install the target and its public headers
install(TARGETS ServerManager
    EXPORT ServerManagerTargets
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include
)

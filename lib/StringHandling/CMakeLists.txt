# Define the library target
add_library(StringHandling StringHandling.cpp)

# Set the C++ standard and linker language for the target
set_target_properties(StringHandling PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 17
)

# Specify the include directories for the target
target_include_directories(StringHandling
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# Set the output directory for the library
set_target_properties(StringHandling PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/StringHandling"
)

# Install the target and its public headers
install(TARGETS StringHandling
    EXPORT StringHandlingTargets
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include
)

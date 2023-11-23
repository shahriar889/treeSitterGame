# Define the library target
add_library(Game game.cpp)

# Set the C++ standard and linker language for the target
set_target_properties(Game PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 17
)

# Specify the include directories for the target
target_include_directories(Game
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(Game TreeManager ConfigurationState ConstantState PerPlayerState VariableState StateManager ruleManager)


# Install the target and its public headers
install(TARGETS Game
    EXPORT GameTargets
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include
)

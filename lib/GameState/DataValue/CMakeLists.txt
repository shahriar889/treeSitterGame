add_library(DataValue dataValue.cpp)

target_include_directories(DataValue PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
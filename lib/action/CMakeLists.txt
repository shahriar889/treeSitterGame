add_library(action action.cpp)

target_link_libraries(action 

)

target_include_directories(action PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

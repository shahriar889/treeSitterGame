add_library(rule rule.cpp)
target_link_libraries(rule 

)
target_include_directories(rule PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)


add_library(ruleManager ruleManager.cpp)
target_link_libraries(ruleManager
    rule
)
target_include_directories(ruleManager PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

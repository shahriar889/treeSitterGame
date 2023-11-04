add_library(rules rules.cpp)
target_link_libraries(rules

)
target_include_directories(rules PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

add_library(ruleFactories ruleFactories.cpp)
target_link_libraries(ruleFactories
    rules
)
target_include_directories(rules PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)


add_library(ruleManager ruleManager.cpp)
target_link_libraries(ruleManager
    rules
)
target_include_directories(ruleManager PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

add_library(ruleTranslator ruleTranslator.cpp)
target_link_libraries(ruleTranslator 
    ruleFactories
)
target_include_directories(ruleTranslator PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

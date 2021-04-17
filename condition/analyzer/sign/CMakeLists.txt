# for sign state
add_subdirectory(state)

add_library(ConditionSignAnalyzer SignAnalyzer.cpp SignStateMerger.cpp)

target_link_libraries(ConditionSignAnalyzer PUBLIC ConditionParser ConditionSignState ConditionCFG)

target_include_directories(ConditionSignAnalyzer PUBLIC "${PROJECT_SOURCE_DIR}/condition/front-end/parser" 
                                               "${PROJECT_SOURCE_DIR}/condition/analyzer/sign/state"
					       "${PROJECT_SOURCE_DIR}/condition/analyzer/cfg")

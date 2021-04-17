add_subdirectory(analyzer)
add_subdirectory(front-end)

add_executable(ConditionProgramAnalyzer main.cpp)

target_link_libraries(ConditionProgramAnalyzer PUBLIC ConditionParser 
						      ConditionSignAnalyzer 
						      ConditionCFG)

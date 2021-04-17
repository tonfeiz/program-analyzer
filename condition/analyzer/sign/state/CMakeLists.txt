add_library(ConditionSignState SignState.cpp SignStateMap.cpp)

target_include_directories(ConditionSignState PUBLIC "${PROJECT_SOURCE_DIR}/condition/analyzer/state"
					      	     "${PROJECT_SOURCE_DIR}/utils")

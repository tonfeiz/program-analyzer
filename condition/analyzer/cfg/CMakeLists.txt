add_library(ConditionCFG ControlFlowGraph.cpp ControlFlowNode.cpp)

target_include_directories(ConditionCFG PUBLIC "${PROJECT_SOURCE_DIR}/condition/front-end/parser"
					       "${PROJECT_SOURCE_DIR}/condition/analyzer/state")

					      


add_library(ConditionLexer Lexer.cpp)

target_link_libraries(ConditionLexer PUBLIC ConditionProgram)

target_include_directories(ConditionLexer PUBLIC "${PROJECT_SOURCE_DIR}/condition/front-end/program"
	     					 "${PROJECT_SOURCE_DIR}/utils"
)

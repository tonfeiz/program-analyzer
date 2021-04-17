add_library(ConditionParser Parser.cpp ExprASTUtils.cpp)

target_link_libraries(ConditionParser PUBLIC ConditionLexer)

target_include_directories(ConditionParser PUBLIC "${PROJECT_SOURCE_DIR}/condition/front-end/lexer"
				  	 "${PROJECT_SOURCE_DIR}/utils")

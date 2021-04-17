add_library(StraightParser Parser.cpp)

target_link_libraries(StraightParser PUBLIC StraightLexer)

target_include_directories(StraightParser PUBLIC "${PROJECT_SOURCE_DIR}/straight-line/front-end/lexer"
				  	 "${PROJECT_SOURCE_DIR}/utils")

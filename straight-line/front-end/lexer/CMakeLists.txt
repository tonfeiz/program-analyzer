add_library(StraightLexer Lexer.cpp)

target_link_libraries(StraightLexer PUBLIC StraightProgram)

target_include_directories(StraightLexer PUBLIC "${PROJECT_SOURCE_DIR}/straight-line/front-end/program")

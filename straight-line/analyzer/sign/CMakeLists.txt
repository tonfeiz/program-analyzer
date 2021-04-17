# for sign state
add_subdirectory(state)

add_library(StraightSignAnalyzer SignAnalyzer.cpp)

target_link_libraries(StraightSignAnalyzer PUBLIC StraightParser StraightSignState)

target_include_directories(StraightSignAnalyzer PUBLIC "${PROJECT_SOURCE_DIR}/straight-line/front-end/parser" 
                                               "${PROJECT_SOURCE_DIR}/straight-line/analyzer/sign/state")

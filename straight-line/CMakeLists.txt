add_subdirectory(analyzer)
add_subdirectory(front-end)

add_executable(StraightProgramAnalyzer main.cpp)

target_link_libraries(StraightProgramAnalyzer PUBLIC StraightParser StraightSignAnalyzer)

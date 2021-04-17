add_library(StraightSignState SignState.cpp SignStateMap.cpp)

target_include_directories(StraightSignState PUBLIC "${PROJECT_SOURCE_DIR}/straight-line/analyzer/state")

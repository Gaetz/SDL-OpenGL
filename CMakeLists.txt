cmake_minimum_required (VERSION 3.0.0)
 
project (Tetris)
set(EXECUTABLE_OUTPUT_PATH ./${CMAKE_BUILD_TYPE})
 
file(
    GLOB_RECURSE
    SOURCES
    src/*
) 
add_executable (${PROJECT_NAME} ${SOURCES})
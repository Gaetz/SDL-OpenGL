cmake_minimum_required(VERSION 3.1.0)
project(Tetris VERSION 0.1.0)

include(CTest)
enable_testing()

# Includes and libraries
set(SDL2_DIR ${CMAKE_SOURCE_DIR}/external/SDL2-2.0.10)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set(GLEW_DIR ${CMAKE_SOURCE_DIR}/external/glew-2.1.0)
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

set(GLM_DIR ${CMAKE_SOURCE_DIR}/external/glm-0.9.5)
include_directories(${GLM_DIR})

find_package(OpenGL)

# subdirectories
#include_directories(src src/engine src/game)
add_subdirectory( src/engine )
add_subdirectory( src/game )

# Executable and link
add_executable(Tetris src/main.cpp)
target_link_libraries(Tetris engine game ${SDL2_LIBRARIES} ${GLEW_LIBRARIES} ${OPENGL_gl_LIBRARY})


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
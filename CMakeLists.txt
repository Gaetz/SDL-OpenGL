cmake_minimum_required(VERSION 3.5.0)
set(CMAKE_CXX_STANDARD 17)
project(Tetris VERSION 0.1.0)
set(OpenGL_GL_PREFERENCE "GLVND")

include(CTest)
enable_testing()

# Includes and libraries
if (WIN32)
    set(SDL2_DIR ${CMAKE_SOURCE_DIR}/external/SDL2-2.0.30)
    set(GLEW_DIR ${CMAKE_SOURCE_DIR}/external/glew-2.2.0)
endif (WIN32)

find_package(OpenGL REQUIRED COMPONENTS OpenGL)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

find_package(OpenGL)

# subdirectories
add_subdirectory( src/engine )
add_subdirectory( src/game )

# Executable and link
if (NOT WIN32)
    string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
endif (NOT WIN32)
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} game engine ${SDL2_LIBRARIES} ${GLEW_LIBRARIES} OpenGL::GL)

# Copying assets to the build folder
add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_LIST_DIR}/assets
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
        COMMENT "---- Copy Assets"
)

# Copying dlls to the build folder
if (WIN32)
    add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${SDL2_DIR}/lib/x64/SDL2.dll
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
            COMMENT "---- Copy SDL2.dll")

    add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${GLEW_DIR}/bin/Release/x64/glew32.dll
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
            COMMENT "---- Copy glew32.dll")
endif (WIN32)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
file( GLOB engine_SOURCES *.cpp )
add_library( engine ${engine_SOURCES} )
target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

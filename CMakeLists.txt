cmake_minimum_required(VERSION 3.10)
project(crs)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

include_directories( ./src )

file(GLOB cpp_files src/*.cpp src/libs/*.cpp)
add_executable( crs ${cpp_files} )

cmake_minimum_required(VERSION 3.9)
project(crs)

set (CMAKE_CXX_STANDARD 17)

include_directories( ./src )

file(GLOB cpp_files src/*.cpp src/libs/*.cpp)
add_executable( crs ${cpp_files} )

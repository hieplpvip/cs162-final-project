cmake_minimum_required(VERSION 3.9)
project(tests)

set (CMAKE_CXX_STANDARD 17)

file(GLOB cpp_files *.cpp ../src/libs/*.cpp)
add_executable( run_tests ${cpp_files} )

cmake_minimum_required (VERSION 2.8.12)
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(CMAKE_C_COMPILER "clang-6.0")
set(CMAKE_CXX_COMPILER "clang++-6.0")

project (CUBE)

include_directories("${CMAKE_SOURCE_DIR}/external/termcolor/include")
include_directories("${CMAKE_SOURCE_DIR}")
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g -std=c++2a -fsanitize=address -fsanitize=undefined")

add_executable(cube src/cube.cpp)
add_executable(pll src/pll.cpp)
add_executable(every_colour_every_face src/every_colour_every_face.cpp)
add_executable(zygoloid src/zygoloid.cpp)
target_link_libraries(cube readline)
target_link_libraries(pll readline)

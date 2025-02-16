cmake_minimum_required(VERSION 3.30)

project(jello)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories("src")

add_executable(demo examples/demo.cpp)

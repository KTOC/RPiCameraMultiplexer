cmake_minimum_required(VERSION 3.8)
project(RPiCameraMultiplexer)

set(CMAKE_CXX_STANDARD 11)

include_directories("include/")

set(SOURCE_FILES main.cpp)
add_executable(RPiCameraMultiplexer ${SOURCE_FILES})
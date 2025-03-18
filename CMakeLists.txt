cmake_minimum_required(VERSION 3.15)
project(untitled)

set(CMAKE_CXX_STANDARD 17)

add_executable(rover src/main.cpp src/resource.cpp src/resource.hpp src/rover.cpp src/rover.hpp src/task.cpp src/task.hpp)

add_subdirectory(Google_tests)

cmake_minimum_required(VERSION 3.15)

project(01-hello-world CXX)

set(CMAKE_CXX_STANDARD 17)

option(BUILD_TEST "Build unit tests" ON)

add_subdirectory(bin)
add_subdirectory(lib)

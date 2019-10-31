cmake_minimum_required(VERSION 3.15.4)

project(gamedev CXX)

add_subdirectory(01-hello-world)
add_subdirectory(02-sdl)

include(CTest)
enable_testing()

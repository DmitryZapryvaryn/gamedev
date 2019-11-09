cmake_minimum_required(VERSION 3.15)

project(gamedev CXX)

add_subdirectory(01-hello-world)
add_subdirectory(02-sdl)
add_subdirectory(03-sdl-input)

include(CTest)
enable_testing()

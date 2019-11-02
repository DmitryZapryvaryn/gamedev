cmake_minimum_required(VERSION 3.15)

project(sdl-hello-world CXX)

find_path(SDL2_INCL_DIR NAMES SDL2 HINTS include)

if(EXISTS ${SDL2_INCL_DIR})
    message(FATAL_ERROR "SDL2 includes not found")
else()
    message(STATUS "SDL2 includes found ${SDL2_INCL_DIR}")
endif()

add_subdirectory(sdl-static)
add_subdirectory(sdl-shared)

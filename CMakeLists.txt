cmake_minimum_required(VERSION 3.15)

project(gamedev CXX)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Werror")
endif()

add_subdirectory(01-hello-world)

include(CTest)
enable_testing()
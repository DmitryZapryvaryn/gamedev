cmake_minimum_required(VERSION 3.15)

project(sdl-hello-world CXX)

# STATIC
find_library(LIB_SDL_STATIC libSDL2.a)

if(LIB_SDL_STATIC)
    message(STATUS "SDL2 static lib found ${LIB_SDL_STATIC}")
else()
    message(FATAL_ERROR "SDL2 static lib not found")
endif()

add_executable(sdl-main-static main.cpp)
target_compile_features(sdl-main-static PRIVATE cxx_std_17)
target_compile_options(sdl-main-static PRIVATE -static)

target_include_directories(sdl-main-static PRIVATE /usr/local/include/SDL2)

target_link_libraries(sdl-main-static PRIVATE
    ${LIB_SDL_STATIC}
    -Wl,--enable-new-dtags
    -ldl
    -lm
    -lrt
    -Wl,--no-undefined
    -pthread)

# SHARED
find_library(LIB_SDL_SHARED libSDL2.so)

if(LIB_SDL_SHARED)
    message(STATUS "SDL2 shared lib found ${LIB_SDL_SHARED}")
else()
    message(FATAL_ERROR "SDL2 shared lib not found")
endif()

add_executable(sdl-main-shared main.cpp)
target_compile_features(sdl-main-shared PRIVATE cxx_std_17)

target_include_directories(sdl-main-shared PRIVATE /usr/local/include/SDL2)

target_link_libraries(sdl-main-shared PRIVATE
    ${LIB_SDL_SHARED}
    -Wl,--enable-new-dtags
    -pthread
    -lSDL2)


if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

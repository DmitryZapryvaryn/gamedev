project(sdl-static CXX)

add_executable(sdl-main-static src/main.cpp)
target_compile_features(sdl-main-static PRIVATE cxx_std_17)
if(NOT MSVC)
    target_compile_options(sdl-main-static PRIVATE -static)
endif()

if(MSVC)

    find_package(SDL2 REQUIRED)

    #target_include_directories(sdl-main-static PRIVATE ${SDL2_INCLUDE_DIRS})
    target_link_libraries(sdl-main-static PRIVATE SDL2::SDL2-static SDL2::SDL2main)

else()
    find_library(LIB_SDL_STATIC
                NAMES libSDL2.a)

    if(LIB_SDL_STATIC)
        message(STATUS "SDL2 static lib found ${LIB_SDL_STATIC}")
    else()
        message(FATAL_ERROR "SDL2 static lib not found")
    endif()

    target_include_directories(sdl-main-static PUBLIC ${SDL2_INCL_DIR}/SDL2)

    target_link_libraries(sdl-main-static PRIVATE
        ${LIB_SDL_STATIC}
        -Wl,--enable-new-dtags
        -ldl
        -lm
        -lrt
        -Wl,--no-undefined
        -pthread
        -lSDL2)
endif()

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

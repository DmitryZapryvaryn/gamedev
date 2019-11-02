project(sdl-shared CXX)


add_executable(sdl-main-shared src/main.cpp)
target_compile_features(sdl-main-shared PRIVATE cxx_std_17)

if(MSVC)
    find_package(SDL2 REQUIRED)

    #target_include_directories(sdl-main-shared PRIVATE ${SDL2_INCLUDE_DIRS})
    target_link_libraries(sdl-main-shared PRIVATE SDL2::SDL2)

else()
    find_library(LIB_SDL_SHARED
                NAMES libSDL2.so)

    if(LIB_SDL_SHARED)
        message(STATUS "SDL2 shared lib found ${LIB_SDL_SHARED}")
    else()
        message(FATAL_ERROR "SDL2 shared lib not found")
    endif()

    target_include_directories(sdl-main-shared PUBLIC ${SDL2_INCL_DIR}/SDL2)

    target_link_libraries(sdl-main-shared PRIVATE
        ${LIB_SDL_SHARED}
        -Wl,--enable-new-dtags
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

project(sdl-shared CXX)


add_executable(sdl-main-shared src/main.cpp)
target_compile_features(sdl-main-shared PRIVATE cxx_std_17)

find_package(sdl2 REQUIRED)

if(sdl2_FOUND)
    message(STATUS "SDL2 package found")

    target_include_directories(sdl-main-shared PRIVATE ${SDL2_INCLUDE_DIRS})
    target_link_libraries(sdl-main-shared PRIVATE ${SDL2_LIBRARIES})

else()
    find_library(LIB_SDL_SHARED
                NAMES libSDL2.so SDL2.dll
                HINTS /usr/local/lib)

    if(LIB_SDL_SHARED)
        message(STATUS "SDL2 shared lib found ${LIB_SDL_SHARED}")
    else()
        message(FATAL_ERROR "SDL2 shared lib not found")
    endif()

    target_include_directories(sdl-main-shared PRIVATE /usr/local/include/SDL2)

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

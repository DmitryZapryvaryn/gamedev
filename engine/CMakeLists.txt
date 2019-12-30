cmake_minimum_required(VERSION 3.15)

project(game-engine CXX)


add_library(engine SHARED include/engine.hpp src/engine.cpp)
target_include_directories(engine
    PUBLIC ${PROJECT_SOURCE_DIR}/include)


find_package(SDL2 REQUIRED)
target_include_directories(engine PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(engine PRIVATE ${SDL2_LIBRARIES})
find_package(OpenGL REQUIRED)

if(UNIX)
    target_link_libraries(engine PRIVATE
        -lSDL2
        -lGL
        )
elseif(MSVC)
    target_link_libraries(engine PRIVATE
        SDL2::SDL2
        SDL2::SDL2main
        opengl32)
endif()

add_executable(sdl-main src/main.cpp)
target_compile_features(sdl-main PRIVATE cxx_std_17)
target_link_libraries(sdl-main PRIVATE engine)

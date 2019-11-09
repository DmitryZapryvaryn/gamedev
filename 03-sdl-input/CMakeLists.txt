project(sdl-input)


add_executable(sdl-input src/main.cpp)
target_compile_features(sdl-input PRIVATE cxx_std_17)


find_package(SDL2 REQUIRED)

target_link_libraries(sdl-input PUBLIC SDL2::SDL2 SDL2::SDL2main)

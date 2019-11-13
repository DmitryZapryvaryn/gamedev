project(sdl-input-simple CXX)


add_executable(sdl-input-simple src/main.cpp)
target_compile_features(sdl-input-simple PRIVATE cxx_std_17)


find_package(SDL2 REQUIRED)
target_link_libraries(sdl-input-simple PUBLIC SDL2::SDL2 SDL2::SDL2main)

project(sdl-input-engine)


add_library(engine SHARED include/engine.hpp src/engine.cpp)
target_include_directories(engine
    PUBLIC ${PROJECT_SOURCE_DIR}/include)


find_package(SDL2 REQUIRED)
target_link_libraries(engine PRIVATE SDL2::SDL2 SDL2::SDL2main)


add_executable(sdl-input-main src/main.cpp)
target_compile_features(sdl-input-main PRIVATE cxx_std_17)
target_link_libraries(sdl-input-main PRIVATE engine)

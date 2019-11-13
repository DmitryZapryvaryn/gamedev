project(basic-render CXX)

add_executable(image-unit-tests tests/image_tests.cpp include/image.hpp include/render_line.hpp)
target_compile_features(image-unit-tests PRIVATE cxx_std_17)

target_include_directories(image-unit-tests
    PUBLIC ${PROJECT_SOURCE_DIR}/include)

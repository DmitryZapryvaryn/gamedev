project(basic-render CXX)

add_executable(render-unit-tests
    tests/render_tests.cpp
    include/image.hpp
    include/render_line.hpp
    include/render_triangle.hpp)
target_compile_features(render-unit-tests PRIVATE cxx_std_17)

target_include_directories(render-unit-tests
    PUBLIC ${PROJECT_SOURCE_DIR}/include)

enable_testing()
add_test(render render-unit-tests)

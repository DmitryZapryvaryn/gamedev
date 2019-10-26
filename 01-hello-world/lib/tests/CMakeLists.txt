project(lib-tests)

enable_testing()
add_executable(unit-tests unit_tests.cpp)

target_link_libraries(unit-tests LINK_PUBLIC
    lib-shared
    Catch2::Test
)

add_test(test_lib unit-tests)
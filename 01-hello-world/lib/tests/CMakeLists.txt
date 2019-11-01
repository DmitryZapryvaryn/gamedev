project(lib-tests)

add_executable(unit-tests unit_tests.cpp)

add_dependencies(unit-tests 
    lib-shared
    Catch2::Test)

target_link_libraries(unit-tests LINK_PUBLIC
    lib-shared
    Catch2::Test
)

enable_testing()
add_test(test_lib unit-tests)
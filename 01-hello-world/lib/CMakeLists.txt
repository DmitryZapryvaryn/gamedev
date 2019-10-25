project(lib CXX)

add_library(${PROJECT_NAME}-static STATIC include/hello_lib.hpp src/hello_lib.cpp)
target_include_directories(${PROJECT_NAME}-static
    PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_library(${PROJECT_NAME}-shared SHARED include/hello_lib.hpp src/hello_lib.cpp)
target_include_directories(${PROJECT_NAME}-shared
    PUBLIC ${PROJECT_SOURCE_DIR}/include)

enable_testing()
add_subdirectory(tests)
project(catch2 CXX)

add_library(Catch2 INTERFACE)
add_library(Catch2::Test ALIAS Catch2)
target_include_directories(Catch2 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

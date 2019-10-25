project(bin CXX)

add_executable(${PROJECT_NAME}-static src/main.cpp)
target_link_libraries(${PROJECT_NAME}-static LINK_PUBLIC lib-static)

add_executable(${PROJECT_NAME}-shared src/main.cpp)
target_link_libraries(${PROJECT_NAME}-shared LINK_PUBLIC lib-shared)

install(TARGETS ${PROJECT_NAME}-static ${PROJECT_NAME}-shared
    LIBRARY DESTINATION ${PROJECT_BINARY_DIR}/lib
    ARCHIVE DESTINATION ${PROJECT_BINARY_DIR}/lib
    RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/bin)

enable_testing()
add_subdirectory(tests)
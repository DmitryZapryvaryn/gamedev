project(bin CXX)



add_executable(${PROJECT_NAME}-static src/main.cpp)
add_dependencies(${PROJECT_NAME}-static lib-static)
target_compile_features(${PROJECT_NAME}-static PRIVATE cxx_std_17)
target_link_libraries(${PROJECT_NAME}-static LINK_PUBLIC lib-static)

add_executable(${PROJECT_NAME}-shared src/main.cpp)
add_dependencies(${PROJECT_NAME}-shared lib-shared)
target_compile_features(${PROJECT_NAME}-shared PRIVATE cxx_std_17)
target_link_libraries(${PROJECT_NAME}-shared LINK_PUBLIC lib-shared)

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

install(TARGETS ${PROJECT_NAME}-static ${PROJECT_NAME}-shared
    LIBRARY DESTINATION ${PROJECT_BINARY_DIR}/lib
    ARCHIVE DESTINATION ${PROJECT_BINARY_DIR}/lib
    RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/bin)

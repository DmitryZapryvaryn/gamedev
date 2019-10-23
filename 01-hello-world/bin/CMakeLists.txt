project(bin CXX)

add_executable(${PROJECT_NAME}-static main.cpp)
target_link_libraries(${PROJECT_NAME}-static LINK_PUBLIC lib-static)
target_link_options(${PROJECT_NAME}-static PRIVATE -static)

add_executable(${PROJECT_NAME}-shared main.cpp)
target_link_libraries(${PROJECT_NAME}-shared LINK_PUBLIC lib-shared)

install(TARGETS ${PROJECT_NAME}-static ${PROJECT_NAME}-shared
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

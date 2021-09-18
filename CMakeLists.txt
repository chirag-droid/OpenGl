cmake_minimum_required(VERSION 3.21.2)
project(OpenGl)

add_subdirectory(vendor/glad)
add_subdirectory(vendor/glfw)

add_executable(main main.cpp)
target_link_libraries(main
    PUBLIC
    glad
    glfw

    PRIVATE
    ${CMAKE_DL_LIBS}
)
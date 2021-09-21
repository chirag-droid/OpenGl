cmake_minimum_required(VERSION 3.21.2)

# Show error if build_dir is not equal to build/
if(NOT ${CMAKE_BINARY_DIR} STREQUAL ${CMAKE_SOURCE_DIR}/build)
    message(FATAL_ERROR "Please set your build dir to build. cmake -B build/")
endif()

project(OpenGl)

# Add external dependencies
add_subdirectory(vendor/glad)
add_subdirectory(vendor/glfw)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

# Set Shader files and their paths
set(SHADERS_SOURCE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/res/shaders)
set(SHADERS_BUILD_PATH ${CMAKE_CURRENT_BINARY_DIR}/res/shaders)
set(SHADER_FILES basic.glsl)

# Set source files and header files
set(SOURCE_FILES
    src/main.cpp
    src/Shader.cpp
    src/VertexBuffer.cpp
    src/IndexBuffer.cpp
    src/VertexArray.cpp
    src/Shader.h
    src/VertexBuffer.h
    src/IndexBuffer.h
    src/VertexArray.h
    src/VertexBufferLayout.h
)

add_executable(main ${SOURCE_FILES})

# Set src/ directory as a include directory for main
target_include_directories(main
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Iterate over all the shader files
foreach(item IN LISTS SHADER_FILES)
    # Add command to build the shader files i.e.
    # to copy the shader file from source dir to build dir
    add_custom_command(
        OUTPUT ${SHADERS_BUILD_PATH}/${item}
        COMMAND ${CMAKE_COMMAND} -E copy
            ${SHADERS_SOURCE_PATH}/${item}
            ${SHADERS_BUILD_PATH}/${item}
        DEPENDS ${SHADERS_SOURCE_PATH}/${item}
        COMMENT "Copying ${SHADERS_SOURCE_PATH}/${item} to ${SHADERS_BUILD_PATH}/${item}"
    )

    # Add shader file as a dependency to main target
    target_sources(main
        PUBLIC ${SHADERS_BUILD_PATH}/${item}
    )
endforeach()

# Set glad and glfw libraries as depencies to main
target_link_libraries(main
    PUBLIC
    glad
    glfw

    PRIVATE
    ${CMAKE_DL_LIBS}
)
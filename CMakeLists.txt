cmake_minimum_required(VERSION 3.21.2)

# Show error if build_dir is not equal to build/
if(NOT ${CMAKE_BINARY_DIR} STREQUAL ${CMAKE_SOURCE_DIR}/build)
    message(FATAL_ERROR "Please set your build dir to build. cmake -B build/")
endif()

project(OpenGl)

# C++ standard 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add glad and glfw subdirectory
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glad)

# Set source files and header files
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS src/*.h src/*cpp)
add_executable(main ${SOURCE_FILES})
set_property(
    TARGET
        main
    PROPERTY
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
)

# Include src/ dir and vendor headers
target_include_directories(main
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Link libs from vendor subdirectory
target_link_libraries(main
    PUBLIC
        glfw
        glad
)

# Set resource shader and texture files
set(RES_FILES
    shaders/basic.glsl
)

# iterate over resource files
foreach(item IN LISTS RES_FILES)
    # copy from source resource file to build resource file
    configure_file(res/${item} res/${item} COPYONLY)
endforeach()

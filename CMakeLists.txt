# this is a minimal CMake file to compile simple
# projects that us GLFW and Glad to do graphics
# programming in C or C++.
cmake_minimum_required(VERSION 3.9)
project(gulag)

# generate config.h
configure_file(
    ${PROJECT_SOURCE_DIR}/cmake/config.h.in
    ${PROJECT_SOURCE_DIR}/src/config.h
)

# name of the generated executable
set(EXE_NAME gulag.out)

# find all c++ source files
FILE(GLOB SOURCE_FILES src/*.cpp)

# We just add the glad source file to the executable
# directly, because it is so simple (only one file).
add_executable(${EXE_NAME}
    ${SOURCE_FILES}
    vendor/glad/src/glad.c
    vendor/stb/stb_image.cpp
)

# compile glfw
add_subdirectory(vendor/glfw)

# these need to go after compilation of glfw
include_directories(vendor/glfw/include)
include_directories(vendor/glad/include)
include_directories(vendor/stb)

# link. we need to link with GL to retrieve the opengl
# function pointers, even though glew automates it for us.
target_link_libraries(${EXE_NAME} glfw)

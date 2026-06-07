cmake_minimum_required(VERSION 3.20)
project(graphics_sandbox)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

add_executable(graphics_sandbox src/Module2/main.cpp)

target_link_libraries(graphics_sandbox PRIVATE
    SDL3::SDL3
    OpenGL::GL
    GLEW::GLEW
)
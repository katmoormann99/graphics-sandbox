# graphics-sandbox

A sandbox for learning OpenGL, experimenting with rendering techniques, and building interactive 3D scenes.

## Downloaded Pieces

### SDL3

**SDL3** is a cross-platform library for creating windows, handling keyboard/mouse input, audio, controllers, and creating graphics contexts for OpenGL/Vulkan/Metal/etc. It officially supports Windows, macOS, Linux, iOS, and others.

### OpenGL

**OpenGL** is the graphics API we will use to talk to the GPU and render 2D/3D graphics. Khronos describes it as an API for high-performance graphics applications.</br></br>
*One thing I would like to mention - and this is why my next project will be developing in Vulkan and/or Metal because I would like to learn this process on a lower level. **macOS** supports OpenGL but Apple has deprecated it, and modern macOS generally caps OpenGL support around older versions.*

### GLEW

**GLEW** is an OpenGL extension loader. It helps expose OpenGL functions/extensions consistently across platforms.

## Installs

I am developing on my Mac for these initial set up processes:</br>
`brew install cmake sdl3 glew`

Verify your install:</br>
`brew list | grep -E "cmake|sdl3|glew`

Verify CMake: </br>
`cmake --version`

Verify SDL: </br>
`brew install pkgconf`</br>
`pkg-config --modversion sdl3`

## Setting up Scaffolding for my project

`mkdir src include shaders build`</br>
`touch src/main.cpp`</br>
`touch CMakeLists.txt`</br>

## OpenGL Pipeline Overview

1. **Vertex Specification**</b> This is where OpenGL receives the raw vertex data for an object. Vertex data usually includes positions, colors, normals, texture coordinates, and sometimes index data.</b>

2. **Vertex Shader**</b> The vertex shader runs once per every vertex. This is where transformations matter.

3. **Tessellation**</b>

4. **Geometry Shader**

5. **Vertex Post-Processing**

6. **Primitive Assembly**

7. **Rasterization**

8. **Fragment Shader**

9. **Per-Sample Operations**



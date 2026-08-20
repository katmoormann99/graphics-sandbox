# Fragment Shader Explanation

The fragment shader runs after the vertex shader.

While the vertex shader determines **where vertices are positioned** and calculates the lighting color, the fragment shader determines the **final color that gets written for each fragment**.

In this program, the fragment shader is very simple because the lighting calculation was already performed in the vertex shader.

The fragment shader receives the interpolated color and sends it directly to the framebuffer.

---

## GLSL Version

```glsl
#version 410 core
```

This tells OpenGL that the shader uses **GLSL version 4.10**.

`core` means that the shader uses the modern/core OpenGL feature set.

This matches the GLSL version used by the vertex shader.

---

# Input Color

```glsl
layout (location = 0) smooth in vec4 color;
```

This receives the color that was output by the vertex shader.

Recall that the vertex shader had:

```glsl
layout (location = 0) smooth out vec4 color;
```

The two shaders are connected through this variable.

The vertex shader uses:

```glsl
out vec4 color;
```

because it is **sending the color out**.

The fragment shader uses:

```glsl
in vec4 color;
```

because it is **receiving that color as input**.

The matching:

```glsl
layout (location = 0)
```

allows the output from the vertex shader to correspond to the input of the fragment shader.

---

## Why Is `smooth` Used?

The `smooth` keyword tells OpenGL to **interpolate** the color between vertices.

This is important because the vertex shader only runs once for each vertex, but the fragment shader runs for the fragments produced between those vertices.

For example, imagine a triangle whose vertices receive different brightness values from the lighting calculation:

```text
                 Vertex
                Bright
                  /\
                 /  \
                /    \
               /      \
              /        \
             /          \
            /            \
           /              \
        Dark ------------ Medium
       Vertex              Vertex
```

The vertex shader calculates a lighting color at each of the three vertices.

OpenGL then smoothly interpolates those colors across the triangle.

This means the fragment shader may receive a color somewhere between the colors calculated for the surrounding vertices.

Without this interpolation, the lighting would not transition smoothly across the surface.

This technique is commonly associated with **Gouraud shading**, because the lighting is calculated at the vertices and the resulting colors are interpolated across the surface.

---

# Fragment Shader Output

```glsl
layout (location = 0) out vec4 frag_color;
```

This declares the final color produced by the fragment shader.

The `out` keyword means that the fragment shader is outputting this value.

`frag_color` is a `vec4`, so it contains four components:

- Red
- Green
- Blue
- Alpha

The alpha component represents opacity.

The vertex shader sets the alpha value to `1.0`, so the resulting fragments are fully opaque.

---

## Why Is This Also `location = 0`?

```glsl
layout (location = 0) out vec4 frag_color;
```

Here, `location = 0` has a slightly different meaning than the input location.

It identifies which color output of the fragment shader this value is written to.

For this program, there is only one final color output, so it uses color output location 0.

---

# Main Fragment Shader Function

```glsl
void main()
{
    frag_color = color;
}
```

Every fragment runs through the fragment shader's `main()` function.

This shader only needs to perform one operation:

```glsl
frag_color = color;
```

It takes the interpolated `color` received from the vertex shader and assigns it directly to the fragment shader's output.

There is no additional lighting calculation here because the vertex shader already calculated the diffuse lighting.

---

# How the Vertex and Fragment Shaders Work Together

The vertex shader calculates a color using:

```glsl
color = vec4(material_color * max(dot(L, N), 0.0), 1.0);
```

That color depends on:

- The object's material color
- The surface normal
- The direction toward the light
- The angle between the normal and light direction

The vertex shader then outputs that color:

```glsl
layout (location = 0) smooth out vec4 color;
```

The fragment shader receives it:

```glsl
layout (location = 0) smooth in vec4 color;
```

OpenGL interpolates the colors between vertices before each fragment shader runs.

The process can be thought of as:

```text
              VERTEX SHADER
                    |
                    |
          Calculate dot(L, N)
                    |
                    v
          Calculate vertex color
                    |
                    v
             out vec4 color
                    |
                    |
                    v
          OpenGL Rasterization
                    |
          Colors are interpolated
          between the vertices
                    |
                    v
             in vec4 color
                    |
                    |
                    v
             FRAGMENT SHADER
                    |
                    v
          frag_color = color
                    |
                    v
             Final Pixel Color
```

---

# Why Doesn't the Fragment Shader Calculate Lighting?

In this program, the lighting calculations happen in the **vertex shader**.

For each vertex, the vertex shader calculates:

```glsl
dot(L, N)
```

to determine how directly the surface is facing the light.

It then uses that value to calculate the vertex's color.

The fragment shader therefore does not need to calculate the lighting again. It simply receives the interpolated result.

This makes the fragment shader extremely simple:

```glsl
frag_color = color;
```

Another approach would be to pass the normal and position to the fragment shader and perform the lighting calculation there.

That would calculate lighting for each fragment instead of each vertex and can produce more detailed lighting, but it would require a more complicated fragment shader.

---

# Complete Fragment Shader

```glsl
#version 410 core

// Receive the color calculated by the vertex shader.
// OpenGL smoothly interpolates this value between vertices.
layout (location = 0) smooth in vec4 color;

// The final color produced by this fragment shader.
layout (location = 0) out vec4 frag_color;

void main()
{
    // The vertex shader already calculated the lighting/color.
    // Simply use the interpolated color as this fragment's final color.
    frag_color = color;
}
```

---

# Summary

The fragment shader is simple because most of the work is being done by the vertex shader.

The overall process is:

```text
Vertex Shader
     |
     | Calculates lighting at each vertex
     v
Vertex Color
     |
     | Smooth interpolation
     v
Fragment Color
     |
     | Fragment Shader
     v
frag_color
     |
     v
Final image
```

The most important idea is that **`color` does not necessarily have exactly the same value for every fragment**.

The vertex shader calculates colors only at the vertices. OpenGL uses `smooth` interpolation to create intermediate colors for the fragments between those vertices.

The fragment shader then takes each interpolated color and outputs it using:

```glsl
frag_color = color;
```
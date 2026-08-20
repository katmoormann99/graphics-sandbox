# Vertex Shader Explanation

This vertex shader performs two main jobs:

1. It transforms each vertex so OpenGL knows where it should appear on the screen.
2. It calculates simple diffuse lighting based on the direction the surface is facing compared to the position of the light.

## GLSL Version

```glsl
#version 410 core
```

This tells OpenGL that the shader uses **GLSL version 4.10**.

`core` means that the shader uses the modern/core OpenGL feature set.

---

## Vertex Position

```glsl
layout (location = 0) in vec3 vtx_position;
```

Each vertex of an object has a position containing an **x, y, and z coordinate**.

The `in` keyword means that this value is being passed into the vertex shader.

`location = 0` tells OpenGL that the position data is stored in vertex attribute location 0.

The position is later transformed using matrices to determine where the vertex appears in the world and eventually on the screen.

---

## Vertex Normal

```glsl
layout (location = 1) in vec3 vtx_normal;
```

Each vertex also has a **normal**.

A normal is a vector that points outward from a surface and tells us which direction that surface is facing.

Normals are important for lighting because the amount of light hitting a surface depends on whether the surface is facing toward or away from the light.

`location = 1` tells OpenGL that the normal data is stored in vertex attribute location 1.

---

## Output Color

```glsl
layout (location = 0) smooth out vec4 color;
```

This is the color calculated by the vertex shader and passed to the fragment shader.

The `out` keyword means that this shader is outputting the value.

The `smooth` keyword tells OpenGL to interpolate the color between neighboring vertices. This prevents the color from suddenly changing when moving from one vertex to another.

A `vec4` is used because a color contains four components:

- Red
- Green
- Blue
- Alpha

---

# Uniform Variables

Uniforms are values supplied to the shader by the OpenGL program.

Unlike vertex attributes, uniforms remain the same for all vertices during a draw operation.

## Material Color

```glsl
uniform vec3 material_color;
```

This contains the base color of the object being drawn.

In `main.cpp`, different `ColorNode`s are used to give the floor, walls, ceiling, and box different colors.

The lighting calculation will make this material color brighter or darker depending on how directly the surface faces the light.

---

## PVM Matrix

```glsl
uniform mat4 pvm_matrix;
```

The PVM matrix combines three transformations:

**Projection × View × Model**

Each transformation has a different purpose:

- **Model** - Positions, rotates, and scales an object in the world.
- **View** - Positions the world relative to the camera.
- **Projection** - Applies perspective and prepares the vertex for display.

Together, these transformations convert the original vertex position into the clip coordinates OpenGL needs to draw it on the screen.

---

## Model Matrix

```glsl
uniform mat4 model_matrix;
```

The model matrix contains the transformations applied to an object, such as:

- Translation
- Rotation
- Scaling

The model matrix is used in the lighting calculation because the original vertex position is relative to its object.

We need to transform that position into **world coordinates** so that it can be compared with the light, which is also located in world coordinates.

---

## Normal Matrix

```glsl
uniform mat4 normal_matrix;
```

The normal matrix transforms the vertex normal into world coordinates.

Normals need their own transformation because they represent **directions**, not positions.

Using the normal matrix also makes sure that the normal remains perpendicular to its surface when transformations such as non-uniform scaling are applied.

The normal matrix is based on the inverse-transpose of the model transformation.

---

# Main Shader Function

```glsl
void main()
{
    ...
}
```

Every vertex runs through the `main()` function.

The shader calculates the lighting for that vertex and determines the vertex's final position.

---

## Light Position

```glsl
vec3 light_position = vec3(0.0, -100.0, 50.0f);
```

For this program, the light is placed at a fixed position in world coordinates:

- **x = 0**
- **y = -100**
- **z = 50**

The light is hard-coded because it does not move in this program.

Normally, a light position could also be supplied to the shader using a uniform.

---

## Calculate the Surface Normal

```glsl
vec3 N = normalize(vec3(normal_matrix * vec4(vtx_normal, 0.0)));
```

`N` represents the direction the surface is facing.

The original `vtx_normal` is transformed using the normal matrix so that it is in **world coordinates**.

The normal is converted from a `vec3` to a `vec4`:

```glsl
vec4(vtx_normal, 0.0)
```

The fourth value is `0.0` because a normal represents a **direction rather than a position**.

This is important because translations should not affect a direction. Moving an object somewhere else in the world does not automatically change which direction its surface faces.

Finally:

```glsl
normalize(...)
```

makes the vector have a length of 1. This is important for the lighting calculation.

---

## Calculate the Vertex's World Position

```glsl
vec4 v = model_matrix * vec4(vtx_position, 1.0);
```

The original vertex position is relative to the object itself.

The model matrix transforms that position into **world coordinates**.

Unlike the normal, the fourth value here is:

```glsl
1.0
```

This is because a vertex represents a **position**.

Translations should affect positions. If an object moves, all of its vertices need to move with it.

At this point:

- `v` = vertex position in world coordinates
- `N` = surface normal in world coordinates

---

## Calculate the Direction Toward the Light

```glsl
vec3 L = normalize(vec3(light_position - vec3(v)));
```

`L` represents the direction from the current vertex toward the light.

This is calculated using:

```text
light position - vertex position
```

Both values are in world coordinates, so they can be compared correctly.

The result is normalized because the lighting calculation only needs the **direction** toward the light.

---

# Diffuse Lighting

```glsl
color = vec4(material_color * max(dot(L, N), 0.0), 1.0);
```

This line calculates simple **diffuse lighting**.

The most important part is:

```glsl
dot(L, N)
```

The dot product compares:

- `L` - the direction toward the light
- `N` - the direction the surface is facing

If the surface faces toward the light, the dot product will be closer to `1`, making the surface brighter.

If the light hits the surface at an angle, the value becomes smaller and the surface becomes darker.

If the light is behind the surface, the dot product can become negative.

Because negative light does not make sense here, the shader uses:

```glsl
max(dot(L, N), 0.0)
```

This prevents the lighting value from going below zero.

That lighting amount is then multiplied by:

```glsl
material_color
```

This keeps the object's assigned color while changing its brightness based on the lighting.

Finally:

```glsl
1.0
```

is used as the alpha value, making the object fully opaque.

---

# Final Vertex Position

```glsl
gl_Position = pvm_matrix * vec4(vtx_position, 1.0);
```

Every vertex shader must eventually assign a value to `gl_Position`.

The original vertex position is transformed by the PVM matrix:

```text
Original Vertex
      |
      v
Model Transformation
      |
      v
World Coordinates
      |
      v
View Transformation
      |
      v
Camera Coordinates
      |
      v
Projection Transformation
      |
      v
Clip Coordinates
```

The resulting clip-coordinate position allows OpenGL to determine where the vertex will eventually appear on the screen.

---

# Overall Lighting Process

The main lighting process can be summarized as:

```text
Vertex Normal
     |
     | normal matrix
     v
World-Space Normal (N)
     |
     |
     +-------------------+
                         |
Vertex Position          |
     |                   |
     | model matrix      |
     v                   |
World Position           |
     |                   |
     | compare with      |
     | light position    |
     v                   |
Direction to Light (L)   |
     |                   |
     +-------------------+
              |
              v
          dot(L, N)
              |
              v
       Lighting Amount
              |
              v
     × Material Color
              |
              v
         Final Color
```

The shader therefore uses the **vertex position** to determine where the vertex is and the **vertex normal** to determine which direction its surface is facing.

Both are converted into the same world coordinate system so they can be used with the world-space light position.

---

# Complete Vertex Shader

```glsl
#version 410 core

layout (location = 0) in vec3 vtx_position;
layout (location = 1) in vec3 vtx_normal;

layout (location = 0) smooth out vec4 color;

uniform vec3 material_color;
uniform mat4 pvm_matrix;
uniform mat4 model_matrix;
uniform mat4 normal_matrix;

void main()
{
    // Fixed light position in world coordinates
    vec3 light_position = vec3(0.0, -100.0, 50.0f);

    // Transform and normalize the surface normal
    vec3 N = normalize(vec3(normal_matrix * vec4(vtx_normal, 0.0)));

    // Transform the vertex into world coordinates
    vec4 v = model_matrix * vec4(vtx_position, 1.0);

    // Find the direction from the vertex toward the light
    vec3 L = normalize(vec3(light_position - vec3(v)));

    // Calculate diffuse lighting and apply it to the material color
    color = vec4(material_color * max(dot(L, N), 0.0), 1.0);

    // Transform the vertex into clip coordinates for drawing
    gl_Position = pvm_matrix * vec4(vtx_position, 1.0);
}
```

## Summary

The vertex shader performs two major tasks:

**Positioning:** The vertex position is transformed using the PVM matrix so OpenGL knows where to draw it.

**Lighting:** The vertex position and normal are transformed into world coordinates. The shader compares the direction of the surface normal with the direction toward the light using a dot product. This determines how bright the material should appear.
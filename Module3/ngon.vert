#version 410 core

layout (location = 0) in vec2 vtx_position;

uniform mat4 ortho;

void main() 
{
    // IMPORTANT:
    // The reason position has to become a vec4 is becaused 3D graphics uses 4D homogeneous coordinates 
    // so that translation, rotation, scaling, and projection can be handled with 4x4 matrices
    // The fourth value (w) is what allows a 4x4 transformation matrix to perform translation
    // OpenGL eventually then calculates x_ndc = x/w, y_ndc = y/w, z_ndc = z/w 
    // The perspective divide is a built-in fixed step in the OpenGL graphics pipeline
    // We do not write the divide ourselves
    // After the perspective divide we have normalized device coordinates that are then passed into the viewport transform
    
    gl_Position = ortho * vec4(vtx_position, 0.0, 1.0);
}

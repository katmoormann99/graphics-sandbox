#version 410 core
layout (location = 0) in vec3 vtx_position;
layout (location = 1) in vec3 vtx_normal;

layout (location = 0) flat out vec4 color;

uniform mat4 normal_matrix;
uniform mat4 model_matrix;
uniform vec3 material_color;
uniform mat4 pvm_matrix;



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

    // Gouraud Shading - calculating the lighting at each vertex
    color = vec4(material_color * max(dot(L,N), 0.0), 1.0);

    // Transform the vertex into clip coordinates for drawing
    gl_Position = pvm_matrix * vec4(vtx_position, 1.0);
}
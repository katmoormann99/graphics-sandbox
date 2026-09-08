#version 410 core

layout (location = 0) smooth in vec4 color;
layout (location = 1) smooth in vec2 texcoord;

layout (location = 0) out vec4 frag_color;

uniform bool use_checkerboard;

void main()
{
    if (use_checkerboard){
        // Turn UV space 0..1 into an 8x8 grid
        vec2 grid = floor(texcoord * 8.0);

        // Alternate between even and odd squares 
        float checker = mod(grid.x + grid.y, 2.0); 

        vec3 checker_color; 

        if (checker < 0.5){
            checker_color = vec3(1.0, 1.0, 1.0);
        } else {
            checker_color = vec3(0.0, 0.0, 0.0);
        }

        // Multiply by the checker pattern
        frag_color = vec4(checker_color, 1.0);
    } else {
        frag_color = color;
    }

}
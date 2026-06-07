#include "Module2/line_node.hpp"

#include "scene/scene.hpp"

#include <SDL_opengl_glext.h>
#include <SDL_opengles2_gl2.h>

/**
 * Mental Model 
 *
 * Mouse Click 
 * ↓
 * vertex_list_ (CPU vector)
 * ↓
 * glBufferData()
 * ↓
 * VBO (GPU memory)
 * ↓
 * VAO tells OpenGL: "EAch vertex is an (x, y) pair"
 * ↓
 * Shader receives vertices 
 * ↓
 * glDrawArrays() draws the line
 */

namespace cg
{

    LineNode::LineNode(const Color4 &c){
        // Copy the color 
        color_ = c;

        /**
         * Create a Vertex Buffer Object (VBO)
         * Thinking of a VBO as a chunk of memory that lives on the GPU 
         * We will copy our vertex positions into this buffer so the GPU can access them when drawing 
         * 
         * vbo_ itself is NOT the buffer 
         * It is simply an integer ID that OpenGL uses to identify the buffer
         */
        glGenBuffers(1, &vbo_);

        /**
         * Create a Vertex Array Object (VAO)
         * The VAO stores information about how the vertex data is organized 
         */
        glGenVertexArrays(1, &vao_);
    };

    LineNode:~LineNode(){
        /**
         * Tell OpenGL to delete the GPU resources when this object is destroyed
         */
        glDeleteBuffers(1, &vbo_);
        glDeleteVertexArrays
    }

    void LineNode::add(float x, float y, int32_t position_loc){
        /**
         * Add a new point to our CPU-side list of vertices
         * 
         * vertex_list is a normal C++ vector that lives in RAM
         */
        vertex_list_.emplace_back(Point2(x, y));

        /**
         * Bind (activate) the VBO so future buffer commands affect it (upload data to the VBO)
         */
        glBindBuffer(GL_ARRAY_BUFFER, vbo_);

        /**
         * Copy all points from CPU memory into GPU memory 
         * 
         * vertex_list.size() * sizeof(Point2) = total number of bytes to copy
         * 
         * &vertex_list_[0] = address of the first point in the vector
         * 
         * GL_DYNAMIC_DRAW = tells OpenGL that this data will change often because 
         *      the user will continue to add points
         */
        glBufferData(GL_ARRAY_BUFFER, vertex_list.size() * sizeof(Point2), (GLvoid *)&vertex_list[0], GL_DYNAMIC_DRAW);

        /**
         * Bind (activate) the VAO
         */
        glBindVertexArray(vao_);

        /**
         * Associate the currently bound VBO with this VAO (tell the VAO which VBO to use)
         */
        glBindBuffer(GL_ARRAY_BUFFER, vbo_);

        /**
         * Enable the vertex attribute used by the shader 
         * position_loc is the shader's position input 
         * 
         * Example: 
         * layout(location = 0) in vec2 position
         * 
         * Then position_loc is 0
         */
        glEnableVertexAttribArray(position_loc);

        /**
         * Describe the layout of the vertex data 
         */
        glVertexAttribPointer(position_loc, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);
    }

    void LineNode::draw(SceneState &scene_state){
        /* Need at least TWO points to draw a line segment*/
        if (vertex_list_.size() > 1){
            /**
             * Send the line color to the shader 
             * 
             * scene_state.color_loc is the location of a uniform variable inside the shader 
             */
            glUniform4f(scene_state.color_loc, color_.r, color_.g, color_.b, color_.a);

            /**
             * Activate the VAO
             * 
             * Since the VAO remembers how our vertex data is organized, 
             * OpenGL now knows where to find the vertices
             */
            glBindVertexArray(vao_);

            // Draw the connected line segments 
            // static_cast<GLsizei>(vertex_list.size()) needed because std::size_t is usually an unsigned long on the Mac - but openGL wants an int
            glDrawArrays(GL_LINE_STRIP, 0, static_cast<GLsizei>(vertex_list.size()));

            // Unbind the VAO 
            glBindVertexArray(0);

            check_error("End of lines:");
        }
    }
} // namespace cg
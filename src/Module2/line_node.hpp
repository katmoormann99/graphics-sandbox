//============================================================================
//	Johns Hopkins University Engineering Programs for Professionals
//	605.667 Computer Graphics and 605.767 Applied Computer Graphics
//	Instructor:	Brian Russin
//
//	Author:  David W. Nesbitt
//	File:    line_node.hpp
//	Purpose: Simple geometry node that draws a connected line.
//
//============================================================================

#ifndef _MODULE2_LINE_NODE_HPP
#define _MODULE2_LINE_NODE_HPP

#include "scene/geometry_node.hpp"
#include "geometry/point2.hpp"
#include "scene/color4.hpp"
#include <vector>
#include <SDL_opengl.h>

namespace cg 
{
    class LineNode : public GeometryNode {
        public:
            LineNode(const Color4 &c);

            ~LineNode(); // Destructor to delete the VBO and VAO

            // position_loc is a shader vertex attribute
            void add(float x, float y, int32_t position_loc);

            void draw(SceneState &scene_state) override;

        protected:
            Color4 color_;
            GLuint vbo_; // ID number for a Vertex Buffer Object 
            GLuint vao_; // ID number for a Vertex Array Object
            std::vector<Point2> vertex_list_; // The actual points stored in C++ memory (CPU)

            // VBO is the chunk of GPU memory where we copy in the vertex_list: the actual points stored in C++ memory
            // VAO is the set of instructions that tell OpenGL how to interpret the data inside the VBO

    };
}

#endif
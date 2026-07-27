//============================================================================
//	Johns Hopkins University Engineering Programs for Professionals
//	605.667 Computer Graphics and 605.767 Applied Computer Graphics
//	Instructor:	Brian Russin
//
//	Author:	David W. Nesbitt
//	File:    unit_square_node.hpp
//	Purpose:	Simple geometry node that defines a unit square.
// 
//  Modified by Kat Moormann Monday July 27 2026
//
//============================================================================

#ifndef __MODULE4_UNIT_SQUARE_NODE_HPP__
#define __MODULE4_UNIT_SQUARE_NODE_HPP__

#include "scene/geometry_node.hpp"

namespace cg
{   
    // Unit square is a specialized kind of Geometry Node
    // Inheritance Hierarchy is: SceneNode <- GeometryNode <- UnitSquare
    // Therefore - unit square is the FINAL node that draws the geometry
    class UnitSquare : public GeometryNode
    {
        public: 
            /**
             * Constructor.
             *
             * Builds the vertex buffer for a unit square centered at the origin
             * in the xy-plane (z = 0). The square has width and height of 1,
             * so its corners span from -0.5 to +0.5 in both x and y.
             *
             * The vertices are stored in triangle-strip order rather than as
             * independent triangles. A triangle strip allows OpenGL to reuse
             * vertices so that a square can be rendered using only four vertices:
             *
             *      v0 ----- v2
             *      |      /
             *      |    /
             *      |  /
             *      v1 ----- v3
             *
             * Vertex order:
             *
             *      v0 = top-left
             *      v1 = bottom-left
             *      v2 = top-right
             *      v3 = bottom-right
             *
             * Notice the ordering alternates between the top and bottom rows.
             * This "zig-zag" ordering is required so GL_TRIANGLE_STRIP generates
             * the two triangles that form the square:
             *
             *      Triangle 1: v0, v1, v2
             *      Triangle 2: v1, v2, v3
             *
             * Since the square lies entirely in the xy-plane, every vertex shares
             * the same surface normal:
             *
             *      (0, 0, 1)
             *
             * which points in the positive z direction.
             */
            UnitSquare(int32_t position_loc, int32_t normal_loc);

            // Destructor
            ~UnitSquare();

            /**
             * Draw a unit square
             * Geometry nodes are leaf nodes in the scene graph. By the time execution reaches this node, 
             * all parent nodes (such as TransformNode and PresentationNode) have already applied their transformations,
             * materials, shaders, and other rendering state 
             * 
             * As a result, this function's only responsibility is to issue the OpenGL draw call for the square 
             * Unlike other scene graph nodes, GeometryNode does NOT traverse or draw child nodes because it represents 
             * the end of a rendering path 
             */
            void draw(SceneState &scene_state) override;

        protected: 
            GLuint vao_; // Vertex array object 
            GLuint vbo_; // Vertex buffer object
            GLsizei vertex_count_; // Number of vertices in the square
    };


};  // namespace cg

#endif

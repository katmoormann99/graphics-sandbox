//============================================================================
//	Johns Hopkins University Engineering Programs for Professionals
//	605.667 Computer Graphics and 605.767 Applied Computer Graphics
//	Instructor:	Brian Russin
//
//	Author:	 David W. Nesbitt
//	File:    scene_state.hpp
//	Purpose: Class used to propogate state during traversal of the scene graph.
//
//
//  Modified by Kat Moormann Friday May 01 2026
//============================================================================


#ifndef __SCENE_SCENE_STATE_HPP__
#define __SCENE_SCENE_STATE_HPP__

#include "scene/graphics.hpp"

#include <array>

namespace cg
{

/**
 * SceneState is like a shared backpack that gets passed around while drawing.
 *
 * When the program draws the scene graph, many different nodes need access to
 * the same OpenGL information, such as:
 *
 * - where vertex position data goes in the shader
 * - where color data goes in the shader
 * - what projection matrix is currently being used
 *
 * Instead of passing all those variables separately, they are grouped together
 * inside this one structure.
 */
struct SceneState
{
    // This stores the location of the "position" input in the shader.
    // A shader needs vertex positions so it knows where to draw each point.
    GLint position_loc;

    // This stores the location of the orthographic projection matrix in the shader.
    // Orthographic projection is often used for simple 2-D style drawing.
    GLint ortho_matrix_loc;

    // This stores the location of the color value in the shader.
    // The drawing code can use this to send a color to the GPU.
    GLint color_loc;

    // This stores the actual orthographic projection matrix.
    //
    // A matrix is a set of numbers used to transform coordinates.
    // Here, the matrix helps convert object coordinates into screen coordinates.
    //
    // There are 16 floats because this is a 4x4 matrix.
    std::array<float, 16> ortho;
};

} // namespace cg

#endif
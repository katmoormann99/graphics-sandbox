//============================================================================
//	Johns Hopkins University Engineering Programs for Professionals
//	605.667 Computer Graphics and 605.767 Applied Computer Graphics
//	Instructor:	Brian Russin
//
//	Original Author: David W. Nesbitt
//	Modified by Kat Moormann
//	File:    shader_node.hpp
//	Purpose: Scene graph shader node.
//
//  Modified by Kat Moormann Friday May 01 2026
//  
//  ShaderNode controls which GPU shader program is currently active
//  A shader is a small program that runs on the GPU and helps determine: 
//      - where vertices appear on screen
//      - how pixels are colored
//      - lighting calculations
//      - visual effects
// 
//  This node usually does NOT draw geometry itself 
//  Instead: 
//  1. It activates a shader program
//  2. It sends data to the shader 
//  3. It allows child nodes to draw
//============================================================================

#ifndef __SCENE_SHADER_NODE_HPP__
#define __SCENE_SHADER_NODE_HPP__

#include "scene/scene_node.hpp"

#include "shader_support/glsl_shader.hpp"
#include "shader_support/glsl_shader_program.hpp"

namespace cg
{

/**
 * Quick Summary:
 * Scene Node → organizes everything
 * Transform Node → where object is
 * Presentation Node → how object looks
 * Geometry Node → draws object 
 * CameraNode → how scene is viewed 
 * ShaderNode → how GPU processes the object
 */

class ShaderNode : public SceneNode 
{
    public: 
        ShaderNode();
        virtual ~ShaderNode();

        /**
         * Create a shader program using shader files
         * Then it compiles and links them into one shader program
         */
        bool create (
            const char *vertex_shader_filename,
            const char *fragment_shader_filename
        );

        bool create_from_source (
            const char *vertex_shader_filename,
            const char *fragment_shader_filename
        );
        /**
         * Pure virtual function
         * Derived shader classes MUST implment this
         * This is used to locate:
         *  - uniforms
         *  - attributes
         * 
         * Since this function = 0, 
         * ShaderNode is considered an abstract class 
         * This means: you cannot directly create a plain ShaderNode object
         * 
         * You must create a specialized shader class instead
         */
        virtual bool get_locations() = 0;

    protected: 

        /**
         * Stores the vertex shader object 
         * Vertex shaders process vertex positions 
         */
        GLSLVertexShader vertex_shader_;

        /**
         * Stores the fragment shader object
         * Fragment shaders determine pixel color
         */
        GLSLFragmentShader fragment_shader_;

        /**
         * Stores the final linked shader program
         * This combines both shaders into something OpenGL can use
         */
        GLSLShaderProgram shader_program_;
};
} // namespace cg

#endif
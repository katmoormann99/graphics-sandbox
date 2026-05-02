//============================================================================
//	Johns Hopkins University Engineering Programs for Professionals
//	605.667 Computer Graphics and 605.767 Applied Computer Graphics
//	Instructor:	Brian Russin
//
//	Author:  David W. Nesbitt
//	File:    glsl_shader.hpp
//	Purpose: Support for loadng a shader from a file and compiling it
//
//  Modified by Kat Moormann Friday May 01 2026
//============================================================================

#ifndef __SHADER_SUPPORT_GLSL_SHADER_HPP__
#define __SHADER_SUPPORT_GLSL_SHADER_HPP__

#include "filesystems/file_loader.hpp"
#include "scene/graphics.hpp"

namespace cg
{

/**
 * Base GLSL shader class
 * 
 * This class contains functionality shared by different shader types
 * It can: 
 * - load shader source code from a file
 * - compile shader source code 
 * - check whether compilation succeeded
 * - log compile errors
 */
class GLSLShader
{
    public:
        // Prevent creating a generic shader without specifying its source/name and type
        GLSLShader() = delete;
        GLSLShader(const std::string &shader_str, GLenum shader_type);

        // Create and compile a shader from source code text
        bool create_from_source(const char *source);

        // Load shader source code from a file, then create and compile the shader
        bool create(const char *filename);

        // Get the OpenGL shader handle
        GLuint get() const;

    protected:
        std::string shader_type_str;

        // OpenGL shader type: GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
        GLenum gl_shader_type;

        GLuint gl_shader_;

        // Check whether a shader compiled successfully
        bool check_compile_status(GLuint shader);

        // Read shader source code from a file into a FileContents object
        bool read_shader_source(const char *filename, FileContents &file_contents);

}

class GLSLVertexShader : public GLSLShader
{
    public:
        GLSLVertexShader();

}

class GLSLFragmentShader : public GLSLShader
{
    public:
        GLSLFragmentShader();

}
} // namespace cg
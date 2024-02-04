#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <iostream>
#include <string>
#include <fstream>

#include "maths.h"

// General purpose shader object. Compiles from file, generates
// compile/link-time error messages and hosts several utility 
// functions for easy management.
class Shader {
public:
    // State
    GLuint id;

    // Sets the current shader as active
    Shader& use();

    // Compiles the shader from given source code
    void compile(
            const GLchar* vertexSource,
            const GLchar* fragmentSource,
            const GLchar* geometrySource = nullptr
    );

    // Utility functions
    void setFloat(const GLchar* name, GLfloat value) const;

    void setInteger(const GLchar* name, GLint value) const;

    void setVector2f(const GLchar* name, GLfloat x, GLfloat y) const;

    void setVector2f(const GLchar* name, const Vector2& value) const;

    void setVector3f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z) const;

    void setVector3f(const GLchar* name, const Vector3& value) const;

    void setVector4f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w) const;

    void setVector4f(const GLchar* name, const Vector4& value) const;

    void setMatrix4(const GLchar* name, const Matrix4& matrix) const;

private:
    GLuint vs;
    GLuint fs;
    GLuint gs;

    void compileVertexShader(const GLchar* vertexSource);

    void compileFragmentShader(const GLchar* fragmentSource);

    bool compileGeometryShader(const GLchar* geometrySource);

    void createShaderProgram(bool geometryShaderExists);

    static void checkShaderErrors(GLuint shader, const std::string& shaderType);

    static void printShaderInfoLog(GLuint shaderIndex);

    static void printProgrammeInfoLog(GLuint programme);

    static const char* GLTypeToString(GLenum type);

    static void printAllParams(GLuint _id);

    static bool isValid(GLuint _id);
};

#endif

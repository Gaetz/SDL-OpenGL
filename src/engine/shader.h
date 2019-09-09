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
class Shader
{
public:
	// State
	GLuint id;

	// Constructor
	Shader() { }

	// Sets the current shader as active
	Shader& use();

	// Compiles the shader from given source code
	void compile(
		const GLchar *vertexSource,
		const GLchar *fragmentSource,
		const GLchar *geometrySource = nullptr
	);

	// Utility functions
	void setFloat(const GLchar *name, GLfloat value);
	void setInteger(const GLchar *name, GLint value);
	void setVector2f(const GLchar *name, GLfloat x, GLfloat y);
	void setVector2f(const GLchar *name, const Vector2 &value);
	void setVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z);
	void setVector3f(const GLchar *name, const Vector3 &value);
	void setVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
	void setVector4f(const GLchar *name, const Vector4 &value);
	void setMatrix4(const GLchar *name, const Matrix4 &matrix);

private:
	// Checks if compilation or linking failed and if so, print the error logs
	void checkCompileErrors(GLuint object, std::string type);

	GLuint vs;
    GLuint fs;
    GLuint gs;

    void compileVertexShader(const GLchar *vertexSource);
    void compileFragmentShader(const GLchar *fragmentSource);
    bool compileGeometryShader(const GLchar *geometrySource);
    void createShaderProgram(bool geometryShaderExists);

    void checkShaderErrors(GLuint shader, std::string shaderType);
    void printShaderInfoLog(GLuint shaderIndex);
    void printProgrammeInfoLog(GLuint programme);
    const char *GLTypeToString(GLenum type);
    void printAllParams(GLuint programme);
    bool isValid(GLuint programme);
};

#endif

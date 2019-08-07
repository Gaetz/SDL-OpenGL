#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

#include <iostream>
#include <string>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// General purpose shader object. Compiles from file, generates
// compile/link-time error messages and hosts several utility 
// functions for easy management.
class Shader
{
public:
	// State
	unsigned int id;

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
	void setVector2f(const GLchar *name, const glm::vec2 &value);
	void setVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z);
	void setVector3f(const GLchar *name, const glm::vec3 &value);
	void setVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
	void setVector4f(const GLchar *name, const glm::vec4 &value);
	void setMatrix4(const GLchar *name, const glm::mat4 &matrix);

private:
	// Checks if compilation or linking failed and if so, print the error logs
	void checkCompileErrors(GLuint object, std::string type);
};

#endif

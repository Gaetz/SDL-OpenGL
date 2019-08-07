#include "shader.h"

#ifdef __linux__
	#include <SDL2/SDL.h>
#elif _WIN32
	#include <SDL.h>
#endif

#include <sstream>
#include <string>

Shader &Shader::use()
{
	glUseProgram(id);
	return *this;
}

void Shader::compile(const GLchar* vertexSource, const GLchar* fragmentSource, const GLchar* geometrySource)
{
	GLuint sVertex, sFragment, gShader = 0;
	// Vertex Shader
	sVertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(sVertex, 1, &vertexSource, NULL);
	glCompileShader(sVertex);
	checkCompileErrors(sVertex, "VERTEX");
	// Fragment Shader
	sFragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(sFragment, 1, &fragmentSource, NULL);
	glCompileShader(sFragment);
	checkCompileErrors(sFragment, "FRAGMENT");
	// If geometry shader source code is given, also compile geometry shader
	if (geometrySource != nullptr)
	{
		gShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(gShader, 1, &geometrySource, NULL);
		glCompileShader(gShader);
		checkCompileErrors(gShader, "GEOMETRY");
	}
	// Shader Program
	id = glCreateProgram();
	glAttachShader(id, sVertex);
	glAttachShader(id, sFragment);
	if (geometrySource != nullptr)
		glAttachShader(id, gShader);
	glLinkProgram(id);
	checkCompileErrors(id, "PROGRAM");
	// Delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(sVertex);
	glDeleteShader(sFragment);
	if (geometrySource != nullptr)
		glDeleteShader(gShader);
}

void Shader::setFloat(const GLchar *name, GLfloat value)
{
	glUniform1f(glGetUniformLocation(id, name), value);
}
void Shader::setInteger(const GLchar *name, GLint value)
{
	glUniform1i(glGetUniformLocation(id, name), value);
}
void Shader::setVector2f(const GLchar *name, GLfloat x, GLfloat y)
{
	glUniform2f(glGetUniformLocation(id, name), x, y);
}
void Shader::setVector2f(const GLchar *name, const glm::vec2 &value)
{
	glUniform2f(glGetUniformLocation(id, name), value.x, value.y);
}
void Shader::setVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z)
{
	glUniform3f(glGetUniformLocation(id, name), x, y, z);
}
void Shader::setVector3f(const GLchar *name, const glm::vec3 &value)
{
	glUniform3f(glGetUniformLocation(id, name), value.x, value.y, value.z);
}
void Shader::setVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	glUniform4f(glGetUniformLocation(id, name), x, y, z, w);
}
void Shader::setVector4f(const GLchar *name, const glm::vec4 &value)
{
	glUniform4f(glGetUniformLocation(id, name), value.x, value.y, value.z, value.w);
}
void Shader::setMatrix4(const GLchar *name, const glm::mat4 &matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(id, name), 1, GL_FALSE, glm::value_ptr(matrix));
}


void Shader::checkCompileErrors(GLuint object, std::string type)
{
	GLint success;
	GLchar infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(object, 1024, NULL, infoLog);
			std::ostringstream shaderError;
			shaderError << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
				<< infoLog << "\n -- --------------------------------------------------- -- "
				<< std::endl;
			const std::string error = shaderError.str();
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, error.c_str());
		}
	}
	else
	{
		glGetProgramiv(object, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(object, 1024, NULL, infoLog);
			std::ostringstream shaderError;
			shaderError << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
				<< infoLog << "\n -- --------------------------------------------------- -- "
				<< std::endl;
			const std::string error = shaderError.str();
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, error.c_str());
		}
	}
}

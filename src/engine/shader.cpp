#include "shader.h"
#include "log.h"

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

void Shader::compile(const GLchar *vertexSource, const GLchar *fragmentSource, const GLchar *geometrySource)
{
    compileVertexShader(vertexSource);
    compileFragmentShader(fragmentSource);
    bool gsExists = compileGeometryShader(geometrySource);
    createShaderProgram(gsExists);
    printAllParams(id);
}

void Shader::compileVertexShader(const GLchar *vertex_source)
{
    vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_source, NULL);
    glCompileShader(vs);
    checkShaderErrors(vs, "vertex");
}

void Shader::compileFragmentShader(const GLchar *fragment_source)
{
    fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_source, NULL);
    glCompileShader(fs);
    checkShaderErrors(fs, "fragment");
}

bool Shader::compileGeometryShader(const GLchar *geometry_source)
{
    if (geometry_source == nullptr)
    {
        return false;
    }

    gs = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(gs, 1, &geometry_source, NULL);
    glCompileShader(gs);
    checkShaderErrors(gs, "geometry");

    return true;
}

void Shader::createShaderProgram(bool geometryShaderExists)
{
    // Create program
    id = glCreateProgram();
    glAttachShader(id, fs);
    glAttachShader(id, vs);
    if (geometryShaderExists)
    {
        glAttachShader(id, gs);
    }
    glLinkProgram(id);

    // Check for linking error
    int params = -1;
    glGetProgramiv(id, GL_LINK_STATUS, &params);
    if (params != GL_TRUE)
    {
        LOG(Error) << "Could not link shader programme GL index " << id;
        printProgrammeInfoLog(id);
    }
    if (!isValid(id))
    {
        LOG(Error) << "Could not validate shader" << id;
    }

    // Delete shaders for they are no longer used
    glDeleteShader(vs);
    glDeleteShader(fs);
    if (geometryShaderExists)
    {
        glDeleteShader(gs);
    }
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
void Shader::setVector2f(const GLchar *name, const Vector2 &value)
{
    glUniform2f(glGetUniformLocation(id, name), value.x, value.y);
}
void Shader::setVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z)
{
    glUniform3f(glGetUniformLocation(id, name), x, y, z);
}
void Shader::setVector3f(const GLchar *name, const Vector3 &value)
{
    glUniform3f(glGetUniformLocation(id, name), value.x, value.y, value.z);
}
void Shader::setVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    glUniform4f(glGetUniformLocation(id, name), x, y, z, w);
}
void Shader::setVector4f(const GLchar *name, const Vector4 &value)
{
    glUniform4f(glGetUniformLocation(id, name), value.x, value.y, value.z, value.w);
}
void Shader::setMatrix4(const GLchar *name, const Matrix4 &matrix)
{
    glUniformMatrix4fv(glGetUniformLocation(id, name), 1, GL_FALSE, matrix.getAsFloatPtr());
}

void Shader::printShaderInfoLog(GLuint shaderIndex)
{
    int max_length = 2048;
    int actual_length = 0;
    char log[2048];
    glGetShaderInfoLog(shaderIndex, max_length, &actual_length, log);
    LOG(Info) << "Shader info log for GL index" << shaderIndex;
    LOG(Info) << log;
}

void Shader::printProgrammeInfoLog(GLuint id)
{
    int max_length = 2048;
    int actual_length = 0;
    char log[2048];
    glGetProgramInfoLog(id, max_length, &actual_length, log);
    LOG(Info) << "program info log for GL index" << id;
    LOG(Info) << log;
}

void Shader::checkShaderErrors(GLuint shader, std::string shaderType)
{
    int params = -1;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &params);
    if (params != GL_TRUE)
    {
        LOG(Error) << "GL " << shaderType << " shader index " << shader << " did not compile.";
        printShaderInfoLog(shader);
    }
}

const char *Shader::GLTypeToString(GLenum type)
{
    switch (type)
    {
    case GL_BOOL:
        return "bool";
    case GL_INT:
        return "int";
    case GL_FLOAT:
        return "float";
    case GL_FLOAT_VEC2:
        return "vec2";
    case GL_FLOAT_VEC3:
        return "vec3";
    case GL_FLOAT_VEC4:
        return "vec4";
    case GL_FLOAT_MAT2:
        return "mat2";
    case GL_FLOAT_MAT3:
        return "mat3";
    case GL_FLOAT_MAT4:
        return "mat4";
    case GL_SAMPLER_2D:
        return "sampler2D";
    case GL_SAMPLER_3D:
        return "sampler3D";
    case GL_SAMPLER_CUBE:
        return "samplerCube";
    case GL_SAMPLER_2D_SHADOW:
        return "sampler2DShadow";
    default:
        break;
    }
    return "other";
}

void Shader::printAllParams(GLuint id)
{
    LOG(Info) << "-----------------------------";
    LOG(Info) << "Shader programme " << id << " info:";
    int params = -1;
    glGetProgramiv(id, GL_LINK_STATUS, &params);
    LOG(Info) << "GL_LINK_STATUS = " << params;

    glGetProgramiv(id, GL_ATTACHED_SHADERS, &params);
    LOG(Info) << "GL_ATTACHED_SHADERS = " << params;

    glGetProgramiv(id, GL_ACTIVE_ATTRIBUTES, &params);
    LOG(Info) << "GL_ACTIVE_ATTRIBUTES = " << params;
    for (GLuint i = 0; i < (GLuint)params; i++)
    {
        char name[64];
        int max_length = 64;
        int actual_length = 0;
        int size = 0;
        GLenum type;
        glGetActiveAttrib(id, i, max_length, &actual_length, &size, &type, name);
        if (size > 1)
        {
            for (int j = 0; j < size; j++)
            {
                char long_name[77];
#if __linux__
                sprintf(long_name, "%s[%i]", name, j);
#else
                sprintf_s(long_name, "%s[%i]", name, j);
#endif
                int location = glGetAttribLocation(id, long_name);
                LOG(Info) << "  " << i << ") type:" << GLTypeToString(type) << " name:" << long_name << " location:" << location;
            }
        }
        else
        {
            int location = glGetAttribLocation(id, name);
            LOG(Info) << "  " << i << ") type:" << GLTypeToString(type) << " name:" << name << " location:" << location;
        }
    }

    glGetProgramiv(id, GL_ACTIVE_UNIFORMS, &params);
    LOG(Info) << "GL_ACTIVE_UNIFORMS = " << params;
    for (GLuint i = 0; i < (GLuint)params; i++)
    {
        char name[64];
        int max_length = 64;
        int actual_length = 0;
        int size = 0;
        GLenum type;
        glGetActiveUniform(id, i, max_length, &actual_length, &size, &type, name);
        if (size > 1)
        {
            for (int j = 0; j < size; j++)
            {
                char long_name[77];
                sprintf(long_name, "%s[%i]", name, j);
                int location = glGetUniformLocation(id, long_name);
                LOG(Info) << "  " << i << ") type:" << GLTypeToString(type) << " name:" << long_name << " location:" << location;
            }
        }
        else
        {
            int location = glGetUniformLocation(id, name);
            LOG(Info) << "  " << i << ") type:" << GLTypeToString(type) << " name:" << name << " location:" << location;
        }
    }
    printProgrammeInfoLog(id);
}

bool Shader::isValid(GLuint id)
{
    glValidateProgram(id);
    int params = -1;
    glGetProgramiv(id, GL_VALIDATE_STATUS, &params);
    LOG(Info) << "program " << id << " GL_VALIDATE_STATUS = " << params;
    if (params != GL_TRUE)
    {
        printProgrammeInfoLog(id);
        return false;
    }
    return true;
}
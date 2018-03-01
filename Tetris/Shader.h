#ifndef DEF_SHADER
#define DEF_SHADER

#if defined(_WIN32) || defined(_WIN64)
#include <gl/glew.h>
#elif __APPLE__
#define GL3_PROTOTYPES 1
#include <OpenGL/gl3.h>
#else
#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>
#endif

#include <iostream>
#include <string>
#include <fstream>

class Shader
{
    public:

    Shader();
    Shader(Shader const &copyShader);
    Shader(std::string vertexSource, std::string fragmentSource);
    ~Shader();

    Shader& operator=(Shader const &shaderACopier);

    bool load();
    bool compileShader(GLuint &shader, GLenum type, std::string const &sourceFile);
    GLuint getProgramID() const;


    private:

    GLuint vertexID_;
    GLuint fragmentID_;
    GLuint programID_;

    std::string vertexSource_;
    std::string fragmentSource_;
};

#endif

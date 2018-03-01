#include "Shader.h"
#include <SDL.h>
#include <sstream>

Shader::Shader() : vertexID_(0), fragmentID_(0), programID_(0), vertexSource_(), fragmentSource_()
{
}

Shader::Shader(Shader const &copyShader)
{
    vertexSource_ = copyShader.vertexSource_;
    fragmentSource_ = copyShader.fragmentSource_;
    load();
}

Shader::Shader(std::string vertexSource, std::string fragmentSource):
	vertexID_(0), fragmentID_(0), programID_(0),
	vertexSource_(vertexSource), fragmentSource_(fragmentSource)
{
}

Shader::~Shader()
{
    glDeleteShader(vertexID_);
    glDeleteShader(fragmentID_);
    glDeleteProgram(programID_);
}

Shader& Shader::operator=(Shader const &shaderACopier)
{
    vertexSource_ = shaderACopier.vertexSource_;
    fragmentSource_ = shaderACopier.fragmentSource_;
    load();
    return *this;
}

bool Shader::load()
{
    // Destroy former shader
    if(glIsShader(vertexID_) == GL_TRUE)
        glDeleteShader(vertexID_);
    if(glIsShader(fragmentID_) == GL_TRUE)
        glDeleteShader(fragmentID_);
    if(glIsProgram(programID_) == GL_TRUE)
        glDeleteProgram(programID_);

    // Compile
    if(!compileShader(vertexID_, GL_VERTEX_SHADER, vertexSource_))
        return false;
    if(!compileShader(fragmentID_, GL_FRAGMENT_SHADER, fragmentSource_))
        return false;

    // Create program
    programID_ = glCreateProgram();

    // Attach shader
    glAttachShader(programID_, vertexID_);
    glAttachShader(programID_, fragmentID_);

    // Lock shader inputs
    glBindAttribLocation(programID_, 0, "in_Vertex");
    glBindAttribLocation(programID_, 1, "in_Color");
    glBindAttribLocation(programID_, 2, "in_TexCoord0");

    // Link program
    glLinkProgram(programID_);

    // Check link
    GLint erreurLink(0);
    glGetProgramiv(programID_, GL_LINK_STATUS, &erreurLink);
    if(erreurLink != GL_TRUE)
    {
        GLint tailleErreur(0);
        glGetProgramiv(programID_, GL_INFO_LOG_LENGTH, &tailleErreur);
        char *error = new char[tailleErreur + 1];
        glGetShaderInfoLog(programID_, tailleErreur, &tailleErreur, error);
        error[tailleErreur] = '\0';

		SDL_LogError(SDL_LOG_CATEGORY_RENDER, error);

        delete[] error;
        glDeleteProgram(programID_);

        return false;
    }
    else
        return true;
}

bool Shader::compileShader(GLuint &shader, GLenum type, std::string const &sourceFile)
{
	std::ostringstream ossError;

	// Create shader
    shader = glCreateShader(type);
    if(shader == 0)
    {
		ossError << "Erreur, shader type (" << type << ") doesn't exists.";
		const std::string error = ossError.str();
		SDL_LogError(SDL_LOG_CATEGORY_RENDER, error.c_str());
        return false;
    }

	// Open file
    std::ifstream file(sourceFile.c_str());
    if(!file)
    {
		ossError << "Shader file " << sourceFile << " cannot be found." << std::endl;
		const std::string error = ossError.str();
		SDL_LogError(SDL_LOG_CATEGORY_RENDER, error.c_str());

        glDeleteShader(shader);
        return false;
    }

    std::string line;
    std::string sourceCode;

    // Read
    while(getline(file, line))
        sourceCode += line + '\n';
    file.close();

	// Send to shader
    const GLchar* chaineCodeSource = sourceCode.c_str();
    glShaderSource(shader, 1, &chaineCodeSource, 0);

    // Compile shader
    glCompileShader(shader);

    // Error check
    GLint compilationError(0);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compilationError);
    if(compilationError != GL_TRUE)
    {
        GLint errorSize(0);
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &errorSize);
        char *error = new char[errorSize + 1];
        glGetShaderInfoLog(shader, errorSize, &errorSize, error);
        error[errorSize] = '\0';

		SDL_LogError(SDL_LOG_CATEGORY_RENDER, error);

        delete[] error;
        glDeleteShader(shader);

        return false;
    }
    else
        return true;
}

GLuint Shader::getProgramID() const
{
    return programID_;
}

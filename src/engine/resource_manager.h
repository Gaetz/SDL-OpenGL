#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>

#include <GL/glew.h>

#include "texture.h"
#include "shader.h"

// A static singleton ResourceManager class that hosts several
// functions to load Textures and Shaders. Each loaded texture
// and/or shader is also stored for future reference by string
// handles. All functions and resources are static and no 
// public constructor is defined.
class ResourceManager
{
public:
	// Resource storage
	static std::map<std::string, Shader> shaders;
	static std::map<std::string, Texture2D> textures;

	// Loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code. If gShaderFile is not nullptr, it also loads a geometry shader
	static Shader loadShader(const std::string& vShaderFile, const std::string& fShaderFile, const std::string& gShaderFile, const std::string& name);

	// Retrieves a stored sader
	static Shader getShader(const std::string& name);

	// Loads (and generates) a texture from file
	static Texture2D loadTexture(const std::string& file, const std::string& name);

	// Retrieves a stored texture
	static Texture2D getTexture(const std::string& name);

	// Properly de-allocates all loaded resources
	static void clear();

private:
	// Private constructor, that is we do not want any actual resource manager objects.
	// Its members and functions should be publicly available (static).
	ResourceManager() { }

	// Loads and generates a shader from file
	static Shader loadShaderFromFile(const std::string& vShaderFile, const std::string& fShaderFile, const std::string& gShaderFile = "");

	// Loads a single texture from file
	static Texture2D loadTextureFromFile(const std::string& file);
};

#endif
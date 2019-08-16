#include "resource_manager.h"

#include <iostream>
#include <sstream>
#include <fstream>

// Instantiate static variables
std::map<std::string, Texture2D> ResourceManager::textures;
std::map<std::string, Shader> ResourceManager::shaders;

Shader ResourceManager::loadShader(const std::string& vShaderFile, const std::string& fShaderFile, const std::string& gShaderFile, const std::string& name)
{
	shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
	return shaders[name];
}

Shader ResourceManager::getShader(const std::string& name)
{
	return shaders[name];
}

Texture2D ResourceManager::loadTexture(const std::string& file, const std::string& name)
{
	textures[name] = loadTextureFromFile(file.c_str());
	return textures[name];
}

Texture2D ResourceManager::getTexture(const std::string& name)
{
	return textures[name];
}

void ResourceManager::clear()
{
	// (Properly) delete all shaders	
	for (auto iter : shaders)
		glDeleteProgram(iter.second.id);
	// (Properly) delete all textures
	for (auto iter : textures)
		glDeleteTextures(1, &iter.second.id);
}

Shader ResourceManager::loadShaderFromFile(const std::string& vShaderFile, const std::string& fShaderFile, const std::string& gShaderFile)
{
	// 1. Retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;
	try
	{
		// Open files
		std::ifstream vertexShaderFile(vShaderFile);
		std::ifstream fragmentShaderFile(fShaderFile);
		std::stringstream vShaderStream, fShaderStream;
		// Read file's buffer contents into streams
		vShaderStream << vertexShaderFile.rdbuf();
		fShaderStream << fragmentShaderFile.rdbuf();
		// close file handlers
		vertexShaderFile.close();
		fragmentShaderFile.close();
		// Convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
		// If geometry shader path is present, also load a geometry shader
		if (gShaderFile != "")
		{
			std::ifstream geometryShaderFile(gShaderFile);
			std::stringstream gShaderStream;
			gShaderStream << geometryShaderFile.rdbuf();
			geometryShaderFile.close();
			geometryCode = gShaderStream.str();
		}
	}
	catch (std::exception e)
	{
		std::ostringstream loadError;
		std::string geomShaderFile = "";
		if (gShaderFile != "")
			geomShaderFile = gShaderFile;

		loadError << "ERROR::SHADER: Failed to read shader files " << vShaderFile << " " << fShaderFile << " " << geomShaderFile << "\n"
			<< "\n -- --------------------------------------------------- -- "
			<< std::endl;
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, loadError.str().c_str());
	}
	const GLchar *vShaderCode = vertexCode.c_str();
	const GLchar *fShaderCode = fragmentCode.c_str();
	const GLchar *gShaderCode = geometryCode.c_str();
	// 2. Now create shader object from source code
	Shader shader;
	shader.compile(vShaderCode, fShaderCode, gShaderFile != "" ? gShaderCode : "");
	return shader;
}

Texture2D ResourceManager::loadTextureFromFile(const std::string& file)
{
	// Create Texture object
	Texture2D texture;

	// Load image
	SDL_Surface* surface = SDL_LoadBMP(file.c_str());
	if (surface == nullptr) {
		std::ostringstream loadError;
		loadError << "ERROR::IMG: Unable to load image " << file << "\n"
			<< SDL_GetError() << "\n -- --------------------------------------------------- -- "
			<< std::endl;
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, loadError.str().c_str());
	}

	// Mode
	if (surface->format->BytesPerPixel == 4)
	{
		texture.internalFormat = GL_RGBA;
		texture.imageFormat = GL_RGBA;
	}
	else 
	{
		texture.internalFormat = GL_RGB;
		texture.imageFormat = GL_RGB;
	}

	// Now generate texture
	texture.generate(surface);
	// And finally free image data
	SDL_FreeSurface(surface);
	return texture;
}
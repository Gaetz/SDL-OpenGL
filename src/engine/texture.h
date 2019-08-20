#ifndef TEXTURE_H
#define TEXTURE_H

#ifdef __linux__
#include <SDL2/SDL.h>
#elif _WIN32
#include <SDL.h>
#endif

#include <GL/glew.h>
#include <memory>

// Used by SDL_Surface unique pointer
struct SdlSurfaceDestroyer
{
	void operator()(SDL_Surface *surface) const
	{
		SDL_FreeSurface(surface);
	}
};

// Texture2D is able to store and configure a texture in OpenGL.
// It also hosts utility functions for easy management.
class Texture2D
{
public:
	// Holds the id of the texture object, used for all texture operations to reference to this particlar texture
	GLuint id;

	// Texture image dimensions
	GLuint width, height; // Width and height of loaded image in pixels

	// Texture Format
	GLuint internalFormat; // Format of texture object
	GLuint imageFormat;	// Format of loaded image

	// Texture configuration
	GLuint wrapS;	 // Wrapping mode on S axis
	GLuint wrapT;	 // Wrapping mode on T axis
	GLuint filterMin; // Filtering mode if texture pixels < screen pixels
	GLuint filterMax; // Filtering mode if texture pixels > screen pixels

	// Constructor (sets default texture modes)
	Texture2D();

	// Generates texture from image data
	void generate(std::unique_ptr<SDL_Surface, SdlSurfaceDestroyer> &surface);

	// Binds the texture as the current active GL_TEXTURE_2D texture object
	void setActive() const;
};

#endif
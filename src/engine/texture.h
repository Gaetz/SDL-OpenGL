#ifndef TEXTURE_H
#define TEXTURE_H

#ifdef __linux__
#include <SDL2/SDL.h>
#elif _WIN32

#include <SDL.h>

#endif

#include <GL/glew.h>
#include <GL/gl.h>

#include <memory>

// Used by SDL_Surface unique pointer
struct SdlSurfaceDestroyer {
    void operator()(SDL_Surface* surface) const {
        SDL_FreeSurface(surface);
    }
};

// Texture2D is able to store and configure a texture in OpenGL.
// It also hosts utility functions for easy management.
class Texture2D {
public:
    // Holds the id of the texture object, used for all texture operations to reference to this specific texture
    GLuint id { 0 };

    // Hold loaded data
    unsigned char* image_data { nullptr };

    // Texture image dimensions
    // Width and height of loaded image in pixels
    int width { 0 };
    int height { 0 };

    int n { 0 };

    // Texture Format
    GLuint internalFormat { GL_RGB }; // Format of texture object
    GLuint imageFormat { GL_RGB };    // Format of loaded image

    // Texture configuration
    GLint wrapS { GL_REPEAT };     // Wrapping mode on S axis
    GLint wrapT { GL_REPEAT };     // Wrapping mode on T axis
    GLfloat filterMin { GL_LINEAR }; // Filtering mode if texture pixels < screen pixels
    GLfloat filterMax { GL_LINEAR }; // Filtering mode if texture pixels > screen pixels

    // Constructor (sets default texture modes)
    Texture2D();

    // Load texture file
    void load(const std::string& filename);

    // Generates texture from image data
    void generate() const;

    // Binds the texture as the current active GL_TEXTURE_2D texture object
    void setActive() const;
};

#endif
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "texture.h"
#include "log.h"

Texture2D::Texture2D()
	: width(0), height(0), internalFormat(GL_RGB), imageFormat(GL_RGB),
	  wrapS(GL_REPEAT), wrapT(GL_REPEAT),
	  filterMin(GL_LINEAR), filterMax(GL_LINEAR)
{
	glGenTextures(1, &id);
}

void Texture2D::load(const std::string& filename)
{
	image_data = stbi_load(filename.c_str(), &width, &height, &n, 4);
    if (!image_data)
    {
        LOG(Error) << "Could not load " << filename;
    }
    if ((width & (width - 1)) != 0 || (height & (height - 1)) != 0)
    {
        LOG(Warning) << "Texture " << filename << " is not power-of-2 dimensions";
    }

    // Flip image vertically
    int width_in_bytes = width * 4;
    unsigned char *top = NULL;
    unsigned char *bottom = NULL;
    unsigned char temp = 0;
    int half_height = height / 2;

    for (int row = 0; row < half_height; row++)
    {
        top = image_data + row * width_in_bytes;
        bottom = image_data + (height - row - 1) * width_in_bytes;
        for (int col = 0; col < width_in_bytes; col++)
        {
            temp = *top;
            *top = *bottom;
            *bottom = temp;
            top++;
            bottom++;
        }
    }
}

void Texture2D::generate()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA,
        width,
        height,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        image_data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT); // GL_CLAMP_TO_EDGE
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMin);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMax);
	glBindTexture(GL_TEXTURE_2D, 0);
	delete image_data;
}

void Texture2D::setActive() const
{
	glBindTexture(GL_TEXTURE_2D, id);
}

//void Texture2D::generate(std::unique_ptr<SDL_Surface, SdlSurfaceDestroyer> &surface)
/*void Texture2D::generate(SDL_Surface *surface)
{
	width = surface->w;
	height = surface->h;
	// Create Texture
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, imageFormat, GL_UNSIGNED_BYTE, surface->pixels);
	// Set Texture wrap and filter modes
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMin);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMax);
	// Unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);
}*/


/*
    Loading with SDL

	// Load image
	//auto surface = std::unique_ptr<SDL_Surface, SdlSurfaceDestroyer>(SDL_LoadBMP(file.c_str()));
	auto surface = SDL_LoadBMP(file.c_str());
	if (!surface) {
		std::ostringstream loadError;
		loadError << "ERROR::IMG: Unable to load image " << file << "\n"
			<< SDL_GetError() << "\n -- --------------------------------------------------- -- "
			<< std::endl;
		LOG(Error) << loadError.str();
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

	//SDL_FreeSurface(surface);

*/

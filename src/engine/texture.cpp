#include <iostream>

#include "texture.h"

Texture2D::Texture2D()
	: width(0), height(0), internalFormat(GL_RGB), imageFormat(GL_RGB),
	  wrapS(GL_REPEAT), wrapT(GL_REPEAT),
	  filterMin(GL_LINEAR), filterMax(GL_LINEAR)
{
	glGenTextures(1, &id);
}

void Texture2D::generate(std::unique_ptr<SDL_Surface, SdlSurfaceDestroyer> &surface)
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
}

void Texture2D::setActive() const
{
	glBindTexture(GL_TEXTURE_2D, id);
}
/*
 * =====================================================================================
 *
 *       Filename:  Texture.cpp
 *
 *    Description:
 *
 *        Created:  20/12/2014 01:15:43
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "gk/gl/Texture.hpp"
#include "gk/system/Exception.hpp"

namespace gk {

Texture::Texture(const std::string &filename) {
	loadFromFile(filename);
}

Texture::Texture(SDL_Surface *surface) {
	loadFromSurface(surface);
}

Texture::Texture(Texture &&texture) {
	m_filename = texture.m_filename;

	m_width = texture.m_width;
	m_height = texture.m_height;

	m_texture = texture.m_texture;
	texture.m_texture = 0;
}

Texture::~Texture() noexcept {
	glDeleteTextures(1, &m_texture);
}

void Texture::loadFromFile(const std::string &filename) {
	m_filename = filename;

	SDL_Surface *surface = IMG_Load(m_filename.c_str());
	if(!surface) {
		throw EXCEPTION("Failed to load texture:", filename);
	}

	loadFromSurface(surface);

	SDL_FreeSurface(surface);
}

void Texture::loadFromSurface(SDL_Surface *surface) {
	m_width = surface->w;
	m_height = surface->h;

	glGenTextures(1, &m_texture);

	bind(this);

	// GLenum format = (surface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
	// glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, surface->pixels);

	GLenum format;
	if (surface->format->BytesPerPixel == 4) {
		format = (surface->format->Rmask = 0x000000ff) ? GL_RGBA : GL_BGRA_EXT;
	} else {
		format = GL_RGB;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, surface->format->BytesPerPixel, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, surface->pixels);

	// FIXME: Move these lines to OpenMiner's TextureLoader
	glGenerateMipmap(GL_TEXTURE_2D);

	// FIXME: GL_NEAREST_MIPMAP_LINEAR causes blue shadows on trees, probably due to blending..
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 4);

	bind(nullptr);
}

void Texture::bind(const Texture *texture) {
	if(texture) {
		glBindTexture(GL_TEXTURE_2D, texture->m_texture);
	} else {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

} // namespace gk


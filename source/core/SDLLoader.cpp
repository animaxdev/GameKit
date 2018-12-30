/*
 * =====================================================================================
 *
 *       Filename:  SDLLoader.cpp
 *
 *    Description:
 *
 *        Created:  15/09/2014 00:07:14
 *
 *         Author:  Quentin Bazin, <gnidmoo@gmail.com>
 *
 * =====================================================================================
 */
#include "gk/system/Exception.hpp"
#include "gk/core/SDLHeaders.hpp"
#include "gk/core/SDLLoader.hpp"

namespace gk {

SDLLoader::~SDLLoader() {
	if(m_mixInitialized) Mix_CloseAudio();
	if(m_ttfInitialized) TTF_Quit();
	if(m_imgInitialized) IMG_Quit();
	if(m_sdlInitialized) SDL_Quit();
}

void SDLLoader::load() {
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		throw EXCEPTION("SDL init error:", SDL_GetError());
	} else {
		m_sdlInitialized = true;
	}

	int imgFlags = IMG_INIT_PNG;
	if((!IMG_Init(imgFlags)) & imgFlags) {
		throw EXCEPTION("SDL_image init error:", IMG_GetError());
	} else {
		m_imgInitialized = true;
	}

	if(TTF_Init() < 0) {
		throw EXCEPTION("SDL_ttf init error:", TTF_GetError());
	} else {
		m_ttfInitialized = true;
	}

	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) {
		throw EXCEPTION("SDL_mixer init error:", Mix_GetError());
	} else {
		m_mixInitialized = true;
	}

	Mix_AllocateChannels(32);

	Mix_VolumeMusic(MIX_MAX_VOLUME / 3);
	Mix_Volume(-1, MIX_MAX_VOLUME);
}

} // namespace gk


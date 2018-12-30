/*
 * =====================================================================================
 *
 *       Filename:  SoundEffect.cpp
 *
 *    Description:
 *
 *        Created:  15/09/2014 23:03:35
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "gk/audio/SoundEffect.hpp"
#include "gk/system/Exception.hpp"

namespace gk {

SoundEffect::SoundEffect(const std::string &filename) {
	load(filename);
}

void SoundEffect::load(const std::string &filename) {
	m_sfx.reset(Mix_LoadWAV(filename.c_str()));
	if(!m_sfx) {
		throw EXCEPTION("Unable to load sound effect:", filename, ":", Mix_GetError());
	}

	m_timer.start();
}

void SoundEffect::play(s8 channel) {
	Mix_PlayChannel(channel, m_sfx.get(), 0);
}

void SoundEffect::repeat(u16 delay, s8 channel) {
	if(m_timer.time() > delay) {
		play(channel);

		m_timer.reset();
		m_timer.start();
	}
}

} // namespace gk

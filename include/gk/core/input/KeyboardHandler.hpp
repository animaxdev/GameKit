/*
 * =====================================================================================
 *
 *  GameKit
 *  Copyright (C) 2018-2020 Unarelith, Quentin Bazin <openminer@unarelith.net>
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this library; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
 *
 * =====================================================================================
 */
#ifndef GK_KEYBOARDHANDLER_HPP_
#define GK_KEYBOARDHANDLER_HPP_

#include <map>
#include <string>

#include "gk/core/input/InputHandler.hpp"
#include "gk/core/SDLHeaders.hpp"

namespace gk {

class KeyboardHandler : public InputHandler {
	public:
		void loadKeysFromFile(const std::string &filename);

		bool isKeyPressed(GameKey key);

		SDL_Keycode getKeyCode(GameKey key) { return SDL_GetKeyFromScancode(m_keys[key]); }
		std::string getKeyName(GameKey key) { return SDL_GetKeyName(getKeyCode(key)); }
		void setKeycode(GameKey key, SDL_Keycode keycode) { m_keys[key] = SDL_GetScancodeFromKey(keycode); }

	protected:
		std::map<GameKey, SDL_Scancode> m_keys;
};

} // namespace gk

#endif // GK_KEYBOARDHANDLER_HPP_

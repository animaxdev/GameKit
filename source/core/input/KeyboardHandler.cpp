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
#include "gk/core/input/KeyboardHandler.hpp"
#include "gk/core/Debug.hpp"
#include "gk/core/IntTypes.hpp"
#include "gk/core/XMLFile.hpp"

namespace gk {

void KeyboardHandler::loadKeysFromFile(const std::string &filename) {
	XMLFile doc(filename);

	tinyxml2::XMLElement *keys = doc.FirstChildElement("keys").ToElement();
	if (keys) {
		GameKey key = 0;
		tinyxml2::XMLElement *keyElement = keys->FirstChildElement("key");
		while (keyElement) {
			m_keys[key] = SDL_GetScancodeFromName(keyElement->Attribute("key"));

			if(m_keys[key] == SDL_SCANCODE_UNKNOWN) {
				DEBUG("Key '", keyElement->Attribute("key"), "' not recognized");
			}

			InputHandler::addKey(key);

			++key;
			keyElement = keyElement->NextSiblingElement("key");
		}
	}
}

bool KeyboardHandler::isKeyPressed(GameKey key) {
	const u8 *keyboardState = SDL_GetKeyboardState(nullptr);
	SDL_Scancode keyScancode = m_keys[key];

	m_keysPressed[key] = keyboardState[keyScancode];

	return keyboardState[keyScancode];
}

} // namespace gk


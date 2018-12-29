/*
 * =====================================================================================
 *
 *       Filename:  InputHandler.hpp
 *
 *    Description:
 *
 *        Created:  17/01/2018 19:09:57
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_INPUTHANDLER_HPP_
#define GK_INPUTHANDLER_HPP_

#include <map>

#include "gk/core/IntTypes.hpp"

namespace gk {

using GameKey = u32;

class InputHandler {
	public:
		virtual ~InputHandler() = default;

		virtual bool isKeyPressed(GameKey key) { return m_keysPressed[key]; }
		virtual bool isKeyPressedOnce(GameKey key);
		virtual bool isKeyPressedWithDelay(GameKey key, u16 delay);

		const std::map<GameKey, bool> &keysPressed() const { return m_keysPressed; }

	protected:
		void addKey(GameKey key);

		std::map<GameKey, bool> m_keysPressed;
		std::map<GameKey, bool> m_keysPressedOnce;
		std::map<GameKey, u32> m_lastTimePressed;
};

} // namespace gk

#endif // GK_INPUTHANDLER_HPP_

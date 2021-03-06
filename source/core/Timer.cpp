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
#include "gk/core/Timer.hpp"
#include "gk/core/GameClock.hpp"

namespace gk {

Timer::Timer(bool useRealTime) {
	m_useRealTime = useRealTime;
	m_t = GameClock::getTicks(m_useRealTime);
}

void Timer::stop() {
	if(m_isStarted) {
		m_isStarted = false;
		m_tick = GameClock::getTicks(m_useRealTime) - m_t;
	}
}

void Timer::start() {
	if(!m_isStarted) {
		m_isStarted = true;
		m_t = GameClock::getTicks(m_useRealTime) - m_tick;
	}
}

void Timer::reset() {
	m_isStarted = false;
	m_t = GameClock::getTicks(m_useRealTime);
	m_tick = 0;
}

u32 Timer::time() const {
	if(m_isStarted) {
		return GameClock::getTicks(m_useRealTime) - m_t;
	} else {
		return m_tick;
	}
}

void Timer::setTime(u32 time) {
	if(m_isStarted) {
		m_t = GameClock::getTicks(m_useRealTime) - time;
	} else {
		m_tick = time;
	}
}

} // namespace gk


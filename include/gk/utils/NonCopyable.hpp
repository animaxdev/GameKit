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
#ifndef GK_NONCOPYABLE_HPP_
#define GK_NONCOPYABLE_HPP_

namespace gk {

class NonCopyable {
	protected:
		NonCopyable() = default;
		NonCopyable(const NonCopyable &) = delete;
		NonCopyable(NonCopyable &&) = default;

		NonCopyable &operator=(const NonCopyable &) = delete;
		NonCopyable &operator=(NonCopyable &&) = default;
};

}

#endif // GK_NONCOPYABLE_HPP_

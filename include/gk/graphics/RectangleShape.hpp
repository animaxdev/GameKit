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
#ifndef GK_RECTANGLESHAPE_HPP_
#define GK_RECTANGLESHAPE_HPP_

#include <array>

#include "gk/graphics/Color.hpp"
#include "gk/gl/Drawable.hpp"
#include "gk/gl/Transformable.hpp"
#include "gk/gl/VertexBuffer.hpp"

namespace gk {

class RectangleShape : public Drawable, public Transformable {
	public:
		RectangleShape();
		RectangleShape(float width, float height, const Color &color = Color::White);

		const Color &color() const { return m_color; }
		void setFillColor(const Color &color) { m_color = color; updateVertexBuffer(); }

		void setWireframeMode(bool wireframeMode) { m_wireframeMode = wireframeMode; }

		float width() const { return m_width; }
		float height() const { return m_height; }

		Vector2f getSize() const { return Vector2f{m_width, m_height}; }

		void setSize(float width, float height) { m_width = width; m_height = height; updateVertexBuffer(); }
		void setSize(const Vector2f &size) { m_width = size.x; m_height = size.y; updateVertexBuffer(); }

		void setOutlineColor(const Color &color) { m_outlineColor = color; updateVertexBuffer(); }
		void setOutlineThickness(int outlineThickness) { m_outlineThickness = outlineThickness; updateVertexBuffer(); }

	private:
		void updateVertexBuffer() const;

		void draw(RenderTarget &target, RenderStates states) const override;

		Color m_color;

		bool m_wireframeMode = false;

		float m_width = 0;
		float m_height = 0;

		VertexBuffer m_vbo;

		Color m_outlineColor{Color::White};
		int m_outlineThickness = 0;

		std::array<GLubyte, 6 * 5> m_indices{
			0, 1, 3,
			3, 1, 2
		};
};

} // namespace gk

#endif // GK_RECTANGLESHAPE_HPP_

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
#include "gk/gl/GLCheck.hpp"
#include "gk/gl/Drawable.hpp"
#include "gk/gl/RenderTarget.hpp"
#include "gk/gl/Shader.hpp"
#include "gk/gl/Texture.hpp"
#include "gk/gl/Vertex.hpp"
#include "gk/gl/VertexBuffer.hpp"

namespace gk {

const RenderStates RenderStates::Default{};

void RenderTarget::draw(const Drawable &drawable, const RenderStates &states) {
	drawable.draw(*this, states);
}

void RenderTarget::draw(const VertexBuffer &vertexBuffer, GLenum mode, std::size_t firstVertex, std::size_t vertexCount, const RenderStates &states) {
	VertexBuffer::bind(&vertexBuffer);
	beginDrawing(states);
	glCheck(glDrawArrays(mode, firstVertex, vertexCount));
	endDrawing(states);
}

void RenderTarget::drawElements(const VertexBuffer &vertexBuffer, GLenum mode, GLsizei count, GLenum type, const GLvoid *indices, const RenderStates &states) {
	VertexBuffer::bind(&vertexBuffer);
	beginDrawing(states);
	glCheck(glDrawElements(mode, count, type, indices));
	endDrawing(states);
}

void RenderTarget::beginDrawing(const RenderStates &states) {
	if (!states.shader) return;

	Shader::bind(states.shader);

	if (!m_view) {
		states.shader->setUniform("u_projectionMatrix", states.projectionMatrix);
		states.shader->setUniform("u_viewMatrix", states.viewMatrix);
	}
	else if (m_viewChanged)
		applyCurrentView(states);

	states.shader->setUniform("u_modelMatrix", states.transform);

	if (states.vertexAttributes & VertexAttribute::Coord3d) {
		states.shader->enableVertexAttribArray("coord3d");
		glCheck(glVertexAttribPointer(states.shader->attrib("coord3d"), 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid *>(offsetof(Vertex, coord3d))));
	}

	if (states.vertexAttributes & VertexAttribute::Normal) {
		states.shader->enableVertexAttribArray("normal");
		glCheck(glVertexAttribPointer(states.shader->attrib("normal"), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid *>(offsetof(Vertex, normal))));
	}

	if (states.vertexAttributes & VertexAttribute::TexCoord) {
		states.shader->enableVertexAttribArray("texCoord");
		glCheck(glVertexAttribPointer(states.shader->attrib("texCoord"), 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid *>(offsetof(Vertex, texCoord))));
	}

	if (states.vertexAttributes & VertexAttribute::Color) {
		states.shader->enableVertexAttribArray("color");
		glCheck(glVertexAttribPointer(states.shader->attrib("color"), 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid *>(offsetof(Vertex, color))));
	}

	if (states.vertexAttributes & VertexAttribute::LightValue) {
		states.shader->enableVertexAttribArray("lightValue");
		glCheck(glVertexAttribPointer(states.shader->attrib("lightValue"), 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid *>(offsetof(Vertex, lightValue))));
	}

	if (states.vertexAttributes & VertexAttribute::BlockType) {
		states.shader->enableVertexAttribArray("blockType");
		glCheck(glVertexAttribPointer(states.shader->attrib("blockType"), 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid *>(offsetof(Vertex, blockType))));
	}

	if (states.vertexAttributes & VertexAttribute::AmbientOcclusion) {
		states.shader->enableVertexAttribArray("ambientOcclusion");
		glCheck(glVertexAttribPointer(states.shader->attrib("ambientOcclusion"), 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid *>(offsetof(Vertex, ambientOcclusion))));
	}

	if (states.texture)
		Texture::bind(states.texture);
}

void RenderTarget::endDrawing(const RenderStates &states) {
	if (!states.shader) return;

	Texture::bind(nullptr);

	if (states.vertexAttributes & VertexAttribute::AmbientOcclusion)
		states.shader->disableVertexAttribArray("ambientOcclusion");
	if (states.vertexAttributes & VertexAttribute::BlockType)
		states.shader->disableVertexAttribArray("blockType");
	if (states.vertexAttributes & VertexAttribute::LightValue)
		states.shader->disableVertexAttribArray("lightValue");
	if (states.vertexAttributes & VertexAttribute::Color)
		states.shader->disableVertexAttribArray("color");
	if (states.vertexAttributes & VertexAttribute::TexCoord)
		states.shader->disableVertexAttribArray("texCoord");
	if (states.vertexAttributes & VertexAttribute::Normal)
		states.shader->disableVertexAttribArray("normal");
	if (states.vertexAttributes & VertexAttribute::Coord3d)
		states.shader->disableVertexAttribArray("coord3d");

	VertexBuffer::bind(nullptr);

	Shader::bind(nullptr);
}

IntRect RenderTarget::getViewport(const View& view) const {
	float width  = static_cast<float>(getSize().x);
	float height = static_cast<float>(getSize().y);
	const FloatRect& viewport = view.getViewport();

	return IntRect(static_cast<int>(0.5f + width  * viewport.x),
	               static_cast<int>(0.5f + height * viewport.y),
	               static_cast<int>(width  * viewport.width),
	               static_cast<int>(height * viewport.height));
}

void RenderTarget::applyCurrentView(const RenderStates &states) {
	IntRect viewport = getViewport(*m_view);
	if (viewport != m_previousViewport) {
		int top = getSize().y - (viewport.y + viewport.height);
		glViewport(viewport.x, top, viewport.width, viewport.height);
		m_previousViewport = viewport;
	}

	states.shader->setUniform("u_projectionMatrix", m_view->getTransform());
	states.shader->setUniform("u_viewMatrix", m_view->getViewTransform());

	m_viewChanged = false;
}

} // namespace gk


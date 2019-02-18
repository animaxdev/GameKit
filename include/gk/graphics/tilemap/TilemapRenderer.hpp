/*
 * =====================================================================================
 *
 *       Filename:  TilemapRenderer.hpp
 *
 *    Description:
 *
 *        Created:  15/02/2019 19:20:57
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_TILEMAPRENDERER_HPP_
#define GK_TILEMAPRENDERER_HPP_

#include "gk/gl/IDrawable.hpp"
#include "gk/gl/VertexBuffer.hpp"
#include "gk/graphics/Tileset.hpp"

namespace gk {

class Tilemap;

class TilemapRenderer : public gk::IDrawable {
	public:
		void init(Tilemap *map, u16 mapWidth, u16 mapHeight, u8 mapLayers);

		void updateTile(u8 layer, u16 tileX, u16 tileY, u16 id, Tilemap &map);

	private:
		void draw(gk::RenderTarget &target, gk::RenderStates states) const override;

		gk::VertexBuffer m_vbo;

		Tilemap *m_map = nullptr;
};

} // namespace gk

#endif // GK_TILEMAPRENDERER_HPP_
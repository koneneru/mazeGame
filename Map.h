#pragma once
#include <vector>
#include <unordered_map>

#include "Tile.h"

namespace Engine {

	class Map {
	private:
		int width;
		int height;
		std::vector<std::vector<TileID>> grid;
		std::unordered_map<TileID, TileProperties> tileRegistry;
		TileID defaultTileID = 0;

	public:
		Map(int w, int h, TileID defaultTileID);

		void registerTile(TileID id, const TileProperties props);

		void fill(TileID tile);
		void setTile(int x, int y, TileID tile);
		TileID getTileID(int x, int y) const;

		bool canMoveTo(int x, int y) const;
		const TileProperties* getProperties(int x, int y) const;

		int getWidth() const { return width; }
		int getHeight() const { return height; }
	};
} // namespace Engine


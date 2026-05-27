#include "Map.h"

#include <vector>

namespace Engine {
	Map::Map(int w, int h, TileID defaultID) : width(w), height(h), defaultTileID(defaultID) {
		grid.assign(height, std::vector<TileID>(width, defaultTileID));
	}

	void Map::registerTile(TileID id, const TileProperties props) {
		tileRegistry[id] = props;
	}

	void Map::fill(TileID tile) {
		for (auto& row : grid) {
			std::fill(row.begin(), row.end(), tile);
		}
	}

	void Map::setTile(int x, int y, TileID tile) {
		if (x >= 0 && x < width && y >= 0 && y < height) {
			grid[y][x] = tile;
		}
	}

	TileID Map::getTileID(int x, int y) const {
		if (x < 0 || x >= width || y < 0 || y >= height) return defaultTileID;
	}

	bool Map::canMoveTo(int x, int y) const {
		TileID id = getTileID(x, y);
		auto it = tileRegistry.find(id);
		if (it != tileRegistry.end()) return it->second.isPassable;
		return false;
	}

	const TileProperties* Map::getProperties(int x, int y) const {
		TileID id = getTileID(x, y);
		auto it = tileRegistry.find(id);
		if (it != tileRegistry.end()) return &(it->second);
		return nullptr;
	}
} // namespace Engine
#pragma once
#include <unordered_map>

namespace Engine {

	using TileID = uint8_t;

	struct TileProperties {
		bool isPassable = true;
		bool dealsDamade = false;
		int damageAmount = 0;
	};
} // namespace Engine


#pragma once
#include <string>
#include <unordered_map>

#include "Tile.h"

namespace Maze {

	enum Tiles : Engine::TileID {
		Wall,
		Floor,
		Exit
	};

	struct Tile {
		std::string name;
		Engine::TileProperties physics;
		char consoleSprite;
	};

	const std::unordered_map<Engine::TileID, Tile> Tiles = {
		{ Tiles::Wall, { "Wall", { false, false, 0 }, '#' } },
		{ Tiles::Floor, { "Floor", { true, false, 0 }, ' ' } },
		{ Tiles::Exit, { "Exit", { true, false, 0 }, '!' } },
	};
} // namespace Maze

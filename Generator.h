#pragma once
#include "Map.h"

namespace Maze {
	
	class Generator {
	public:
		static void generateUsingBFS(Engine::Gameplay::Map& map);
	};
} // namespace Maze


#pragma once
#include <vector>

#include "Map.h"
#include "Entity.h"

namespace Engine {

	class IRenderer {
	public:
		virtual ~IRenderer() = default;

		virtual void clear() = 0;
		virtual void draw(Point2D pos, const std::string& assetID) = 0;
		//virtual void drawMap(const Engine::Map& map) = 0;
		//virtual void drawEntity(const Engine::EntityID) = 0;
		virtual void render() = 0;
	};
} // namespace Engine
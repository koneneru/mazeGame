#pragma once
#include <unordered_map>

#include "Point.h"

namespace Engine {

	class Entity {
	protected:
		Point2D position;
		VisualID 
	};
	
	using EntityID = uint8_t;

	struct EntityProperties {
		Point2D position;
	};
}
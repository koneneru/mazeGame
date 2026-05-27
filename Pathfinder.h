#pragma once

#include <vector>

#include "Point.h"
#include "Map.h"

namespace Maze {
	
	class Pathfinder {
	private:
        std::vector<Point2D> path;

        struct AStarNode {
            Point2D pt;
            int g;
            int f;

            bool operator>(const AStarNode& other) const {
                return f > other.f;
            }
        };

        static int heuristic(Point2D a, Point2D b) {
            return std::abs(a.x - b.x) + std::abs(a.y - b.y);
        }

    public:
        void findPath(const Engine::Map& map, Point2D start, Point2D end);

        const std::vector<Point2D>& getPath() const { return path; }
	};
} // namespace Maze
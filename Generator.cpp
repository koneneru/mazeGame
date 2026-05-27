#include "Generator.h"

#include <vector>
#include <stack>
#include <random>
#include <chrono>

#include "Tiles.h"
#include "point.h"

namespace Maze {
	void Generator::generateUsingBFS(Engine::Map& map) {
        int width = map.getWidth();
        int height = map.getHeight();        
        map.fill(Tiles::Wall);

        const int DX[] = { 0, 0, -1, 1 };
        const int DY[] = { -1, 1, 0, 0 };

        std::stack<Point2D> stack;

        Point2D start = { 1, 1 };
        map.setTile(start.x, start.y, Tiles::Floor);
        stack.push(start);

        unsigned seed = static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count());
        std::mt19937 gen(seed);

        while (!stack.empty()) {
            Point2D cur = stack.top();
            std::vector<int> neighbors;

            for (int i = 0; i < 4; i++) {
                int nx = cur.x + DX[i] * 2;
                int ny = cur.y + DY[i] * 2;

                if (nx > 0 && nx < width - 1 && ny > 0 && ny < height - 1) {
                    if(map.getTileID(nx, ny) == Tiles::Wall) neighbors.push_back(i);
                }
            }

            if (!neighbors.empty()) {
                std::uniform_int_distribution<> dis(0, neighbors.size() - 1);
                int dir = neighbors[dis(gen)];

                int nx = cur.x + DX[dir] * 2;
                int ny = cur.y + DY[dir] * 2;

                map.setTile(cur.x + DX[dir], cur.y + DY[dir], Tiles::Floor);
                map.setTile(nx, ny, Tiles::Floor);

                stack.push({ nx, ny });
            }
            else {
                stack.pop();
            }
        }

        exit = { width - 2, height - 2 };
        grid[1][1] = PATH;
        grid[exit.y][exit.x] = PATH;
	}
} // namespace Maze


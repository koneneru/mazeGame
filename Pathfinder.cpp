#include "Pathfinder.h"

#include <vector>
#include <queue>

#include "Point.h"
#include "Map.h"

namespace Maze {
    void Pathfinder::findPath(const Engine::Map& map, Point2D start, Point2D end) {
        path.clear();

        int width = map.getWidth();
        int height = map.getHeight();

        const int DX[] = { 0, 0, -1, 1 };
        const int DY[] = { -1, 1, 0, 0 };
        
        // Очередь с сортировкой по f-score
        std::priority_queue<AStarNode, std::vector<AStarNode>, std::greater<AStarNode>> openSet;
        // Матрица стоимости g
        std::vector<std::vector<int>> gScore(height, std::vector<int>(width, (std::numeric_limits<int>::max)()));
        // Матрица предков для восстановления пути
        std::vector<std::vector<Point2D>> parent(height, std::vector<Point2D>(width, { -1, -1 }));

        gScore[start.y][start.x] = 0;
        openSet.push({ start, 0, heuristic(start, end) });

        bool found = false;
        while (!openSet.empty()) {
            AStarNode cur = openSet.top();
            openSet.pop();

            if (cur.g > gScore[cur.pt.y][cur.pt.x]) continue;

            if (cur.pt == end) {
                found = true;
                break;
            }

            for (int i = 0; i < 4;i++) {
                int nx = cur.pt.x + DX[i];
                int ny = cur.pt.y + DY[i];

                if (map.canMoveTo(nx, ny)) {
                    int tentative_gScore = cur.g + 1;

                    if (tentative_gScore < gScore[ny][nx]) {
                        parent[ny][nx] = cur.pt;
                        gScore[ny][nx] = tentative_gScore;
                        int fScore = tentative_gScore + heuristic({ ny, nx }, end);
                        openSet.push({ { nx, ny }, tentative_gScore, fScore });
                    }
                }
            }
        }

        if (found) {
            Point2D cur = end;
            while (cur != start) {
                path.push_back(cur);
                cur = parent[cur.y][cur.x];
            }
            std::reverse(path.begin(), path.end());
        }
    }
} // namespace Maze


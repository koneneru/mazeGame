#include "MazeGame.h"
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <limits>
#include <random>
#include <chrono>
#include "GameTypes.h"
#include "ConsoleUtils.h"

const int DX[] = { 0, 0, -1, 1 };
const int DY[] = { -1, 1, 0, 0 };

MazeGame::MazeGame(int w, int h) {
    // Для корректной генерации стен размеры должны быть нечётными
    width = w | 1;
    height = h | 1;

    screenBuffer = new ConsoleBuffer(width * 2, height + 10);
    generateMaze();
}

MazeGame::~MazeGame() {
    delete screenBuffer;
}


int MazeGame::heuristic(Point p1, Point p2) const {
    return std::abs(p1.x - p2.x) + std::abs(p1.y - p2.y);
}

void MazeGame::generateMaze() {
    grid.assign(height, std::vector<char>(width, WALL));
    std::stack<Point> stack;

    Point start = { 1, 1 };
    grid[start.y][start.x] = PATH;
    stack.push(start);

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed);

    while (!stack.empty()) {
        Point cur = stack.top();
        std::vector<int> neighbors;

        for (int i = 0; i < 4; i++) {
            int nx = cur.x + DX[i] * 2;
            int ny = cur.y + DY[i] * 2;

            if (nx > 0 && nx < width - 1 && ny > 0 && ny < height - 1) {
                if (grid[ny][nx] == WALL) neighbors.push_back(i);
            }
        }

        if (!neighbors.empty()) {
            std::uniform_int_distribution<> dis(0, neighbors.size() - 1);
            int dir = neighbors[dis(gen)];

            int nx = cur.x + DX[dir] * 2;
            int ny = cur.y + DY[dir] * 2;

            grid[cur.y + DY[dir]][cur.x + DX[dir]] = PATH;
            grid[ny][nx] = PATH;

            stack.push({ nx, ny });
        }
        else {
            stack.pop();
        }
    }

    player = Player({ 1, 1 });
    exit = { width - 2, height - 2 };
    grid[1][1] = PATH;
    grid[exit.y][exit.x] = PATH;
}

void MazeGame::handlePlayerMove(Point next) {
    if (grid[next.y][next.x] != WALL) player.moveTo(next);
}

void MazeGame::findShortestPath() {
    shortestPath.clear();

    // Очередь с сортировкой по f-score
    std::priority_queue<AStarNode, std::vector<AStarNode>, std::greater<AStarNode>> openSet;
    // Матрица стоимости g
    std::vector<std::vector<int>> gScore(height, std::vector<int> (width, (std::numeric_limits<int>::max)()));
    // Матрица предков для восстановления пути
    std::vector<std::vector<Point>> parent(height, std::vector<Point>(width, { -1, -1 }));

    Point playerPos = player.getPosition();
    gScore[playerPos.y][playerPos.x] = 0;
    openSet.push({ playerPos, 0, heuristic(playerPos, exit) });

    bool found = false;
    while (!openSet.empty()) {
        AStarNode cur = openSet.top();
        openSet.pop();

        if (cur.g > gScore[cur.pt.y][cur.pt.x]) continue;

        if (cur.pt == exit) {
            found = true;
            break;
        }

        for (int i = 0; i < i + 4;i++) {
            int nx = cur.pt.x + DX[i];
            int ny = cur.pt.y + DY[i];

            if (nx >= 0 && nx < width && ny >= 0 && ny < height && grid[ny][nx] != WALL) {
                int tentative_gScore = cur.g + 1;

                if (tentative_gScore < gScore[ny][nx]) {
                    parent[ny][nx] = cur.pt;
                    gScore[ny][nx] = tentative_gScore;
                    int fScore = tentative_gScore + heuristic({ ny, nx }, exit);
                    openSet.push({ { nx, ny }, tentative_gScore, fScore });
                }
            }
        }
    }

    if (found) {
        Point cur = exit;
        while (!(cur == player.getPosition())) {
            shortestPath.push_back(cur);
            cur = parent[cur.y][cur.x];
        }
        std::reverse(shortestPath.begin(), shortestPath.end());
    }
}

void MazeGame::draw() {
    if (showHint) findShortestPath();

    screenBuffer->clear();
    std::string frame = "";

    Point playerPos = player.getPosition();

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (x == playerPos.x && y == playerPos.y) frame += PLAYER;
            else if (x == exit.x && y == exit.y) frame += EXIT;
            else if (showHint
                && std::find(shortestPath.begin(), shortestPath.end(), Point{ x, y }) != shortestPath.end()
                && Point { x, y } != exit) {
                frame += ROUTE;
            }
            else {
                frame += grid[y][x];
            }
            frame += ' ';
        }
        frame += '\n';
    }

    frame += "\n=== Управление ===\n";
    frame += "WASD или стрелочки - Перемещение\n";
    frame += "H - Подсказка\n";
    frame += "R - Сброс\n";
    frame += "Esc - Выход\n";

    screenBuffer->write(frame);
    screenBuffer->swap();
}

void MazeGame::moveUp() { handlePlayerMove(player.getNextUp()); }
void MazeGame::moveDown() { handlePlayerMove(player.getNextDown()); }
void MazeGame::moveLeft() { handlePlayerMove(player.getNextLeft()); }
void MazeGame::moveRight() { handlePlayerMove(player.getNextRight()); }
     
void MazeGame::toggleHint() { showHint = !showHint; }
void MazeGame::resetLevel() { generateMaze(); }
bool MazeGame::isGameOver() const { return player.getPosition() == exit; }
int MazeGame::getConsoleOffset() const { return height + 7; }
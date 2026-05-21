#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <limits>
#include <random>
#include <chrono>
#include <conio.h>
#include <windows.h>
#include "./headers/point.h"
#include "./headers/player.h"

const char WALL = '#';
const char PATH = ' ';
const char PLAYER = '@';
const char EXIT = '!';
const char ROUTE = '.';

struct AStarNode {
    Point pt;
    int g;
    int f;

    bool operator>(const AStarNode& other) const {
        return f > other.f;
    }
};

const int DX[] = { 0, 0, -1, 1 };
const int DY[] = { -1, 1, 0, 0 };


static void goToXY(int x, int y) {
    COORD c = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

class MazeGame {
private:
    int width, height;
    std::vector<std::vector<char>> grid;
    Player player;
    Point exit;
    std::vector<Point> shortestPath;
    bool showHint = false;

    int heuristic(Point p1, Point p2) {
        return std::abs(p1.x - p2.x) + std::abs(p1.y - p2.y);
    }

    void generateMaze() {
        grid.assign(height, std::vector<char>(width, WALL));
        std::stack<Point> stack;

        Point start = { 1, 1 };
        grid[start.y][start.x] = PATH;
        stack.push(start);

        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 gen(seed);

        while (!stack.empty()) {
            Point current = stack.top();
            std::vector<int> neighbors;

            for (int i = 0; i < 4; i++) {
                int nx = current.x + 2 * DX[i];
                int ny = current.y + 2 * DY[i];

                if (nx > 0 && nx < width - 1 && ny > 0 && ny < height - 1) {
                    if (grid[ny][nx] == WALL) {
                        neighbors.push_back(i);
                    }
                }
            }

            if (!neighbors.empty()) {
                std::uniform_int_distribution<> dis(0, neighbors.size() - 1);
                int dir = neighbors[dis(gen)];

                int nx = current.x + 2 * DX[dir];
                int ny = current.y + 2 * DY[dir];

                grid[current.y + DY[dir]][current.x + DX[dir]] = PATH;
                grid[ny][nx] = PATH;

                stack.push({ nx, ny });
            }
            else {
                stack.pop();
            }
        }

        player = Player(1, 1);
        exit = { width - 2, height - 2 };
        Point playerPos = player.getPosition();
        grid[playerPos.y][playerPos.x] = PATH;
        grid[exit.y][exit.x] = PATH;
    }

public:
    MazeGame(int w, int h) {
        // Для корректной генерации стен размеры должны быть нечётными
        width = w | 1;
        height = h | 1;
        generateMaze();
    }

    void findShortestPath() {
        shortestPath.clear();

        // Очередь с сортировкой по f-score
        std::priority_queue<AStarNode, std::vector<AStarNode>, std::greater<AStarNode>> openSet;
        // Матрица стоимости g
        std::vector<std::vector<int>> gScore(height, std::vector<int> (width, (std::numeric_limits<int>::max)()));
        // Матрица предков для восстановления пути
        std::vector<std::vector<Point>> parent(height, std::vector<Point>(width, { -1, -1 }));

        Point playerPos = player.getPosition();
        gScore[playerPos.y][playerPos.x] = 0;
        int hStart = heuristic(playerPos, exit);
        openSet.push({ playerPos, 0, hStart});

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
            Point playerPos = player.getPosition();
            while (!(cur == playerPos)) {
                shortestPath.push_back(cur);
                cur = parent[cur.y][cur.x];
            }
            std::reverse(shortestPath.begin(), shortestPath.end());
        }
    }

    void draw() {
        goToXY(0, 0);

        if (showHint) {
            findShortestPath();
        }

        Point playerPos = player.getPosition();
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (x == playerPos.x && y == playerPos.y) {
                    std::cout << PLAYER << ' ';
                }
                else if (x == exit.x && y == exit.y) {
                    std::cout << EXIT << ' ';
                }
                else if (showHint
                    && std::find(shortestPath.begin(), shortestPath.end(), Point{ x, y }) != shortestPath.end()
                    && Point{ x, y } != exit) {
                    std::cout << ROUTE << ' ';
                }
                else {
                    std::cout << grid[y][x] << ' ';
                }
            }
            std::cout << std::endl;
        }

        std::cout <<std::endl << "Управление: WASD | H - Подсказка | R - Сброс | Q - Выход" << std::endl;
    }

    void handlePlayerMovement(int dx, int dy) {
        Point target = player.getNextPosition(dx, dy);

        if (target.x >= 0 && target.x < width && target.y >= 0 && target.y < height) {
            if (grid[target.y][target.x] != WALL) {
                player.move(dx, dy);
            }
        }
    }

    void moveUp() { handlePlayerMovement(0, -1); }
    void moveDown() { handlePlayerMovement(0, 1); }
    void moveLeft() { handlePlayerMovement(-1, 0); }
    void moveRight() { handlePlayerMovement(1, 0); }

    void toggleHint() { showHint = !showHint; }
    void resetLevel() { generateMaze(); }
    bool isGameOver() const { return player.getPosition() == exit; }
    int getConsoleOffset() const { return height + 7; }
};

int main() {
    std::setlocale(LC_ALL, "");
    MazeGame game(25, 15);

    char input = 0;
    while (input != 27 && input != 32) {
        game.draw();

        if (game.isGameOver()) {
            std::cout << std::endl << "Поздравляем! Вы нашли выход из лабиринта" << std::endl;
            break;
        }

        if (_kbhit()) {
            input = _getch();
            if (input == 0 || input == 224) input = _getch();

            switch (input) {
            case 'w': case 72: game.moveUp(); break;
            case 's': case 80: game.moveDown(); break;
            case 'a': case 75: game.moveLeft(); break;
            case 'd': case 77: game.moveRight(); break;
            case 'h': game.toggleHint(); break;
            case 'r': game.resetLevel(); break;
            }
        }

        Sleep(50);
    }


    goToXY(0, game.getConsoleOffset());
    std::cout << "Игра окончена" << std::endl;

    return 0;
}

//void goToXY(int x, int y) {
//    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
//    COORD cord = { x,y };
//    SetConsoleCursorPosition(hOut, cord);
//}
//
//typedef struct Point {
//    int x, y;
//    bool operator==(const Point& other) const {
//        return x == other.x && y == other.y;
//    }
//} Point;
//
//Point start;
//Point finish;
//vector<string> maze;
//
//typedef struct {
//    Point position;
//} Player;
//
//void player_moveTo(Player* p, int x, int y) {
//    if (x == -1 || y == -1 || x == maze[0].size() || y == maze.size() || maze[y][x] == '#') return;
//
//    goToXY(p->position.x, p->position.y);
//    cout << ' ';
//    goToXY(x, y);
//    cout << '0';
//
//    p->position.x = x;
//    p->position.y = y;
//}
//
//void player_moveUp(Player* p) {
//    player_moveTo(p, p->position.x, p->position.y - 1);
//}
//
//void player_moveLeft(Player* p) {
//    player_moveTo(p, p->position.x - 1, p->position.y);
//}
//
//void player_moveDown(Player* p) {
//    player_moveTo(p, p->position.x, p->position.y + 1);
//}
//
//void player_moveRight(Player* p) {
//    player_moveTo(p, p->position.x + 1, p->position.y);
//}
//
//void loadMaze(string path) {
//    ifstream file(path);
//    if (!file.is_open()) {
//        cerr << "opening file failed" << endl;
//        exit(1);
//    }
//
//    string str;
//    while (str != "start") getline(file, str);
//    file >> start.x >> start.y;
//
//    while (str != "finish") getline(file, str);
//    file >> finish.x >> finish.y;
//
//    while (str != "maze") getline(file, str);
//    while (getline(file, str)) {
//        maze.push_back(str);
//    }
//
//    file.close();
//}
//
//void renderMaze() {
//    for (string s : maze) cout << s << endl;;
//}
//
//int main()
//{
//    string pathToMazeFile = "maze.txt";
//    loadMaze(pathToMazeFile);
//    renderMaze();
//
//    Player player;
//    player_moveTo(&player, start.x, start.y);
//
//    char c = 0;
//    while (c != 27) {
//        if(_kbhit()) while (_kbhit()) c = _getch();
//
//        if (c == 32) break;
//        else if (c == 72 || c == 119) player_moveUp(&player);
//        else if (c == 75 || c == 97) player_moveLeft(&player);
//        else if (c == 80 || c == 115) player_moveDown(&player);
//        else if (c == 77 || c == 100) player_moveRight(&player);
//
//        if (c == 27 || player.position == finish) {
//            goToXY(0, 25);
//            break;
//        }
//        Sleep(100);
//    }
//
//    return 0;
//}
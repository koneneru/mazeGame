#pragma once
#include <vector>
#include "Player.h"
#include "ConsoleBuffer.h"

class MazeGame {
private:
    int width, height;
    std::vector<std::vector<char>> grid;

    Player player;
    Point exit;
    std::vector<Point> shortestPath;
    bool showHint = false;

    ConsoleBuffer* screenBuffer;

    int heuristic(Point p1, Point p2) const;
    void generateMaze();
    void handlePlayerMove(Point next);

public:
    MazeGame(int w, int h);
    ~MazeGame();

    void findShortestPath();
    void draw();

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    void toggleHint();
    void resetLevel();

    bool isGameOver() const;
    int getConsoleOffset() const;
};
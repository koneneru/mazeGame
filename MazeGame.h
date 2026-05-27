#pragma once
#include <vector>
#include "Player.h"
#include "ConsoleBuffer.h"

class MazeGame {
private:
    int width, height;
    std::vector<std::vector<char>> grid;

    Player player;
    Point2D exit;
    std::vector<Point2D> shortestPath;
    bool showHint = false;

    ConsoleBuffer* screenBuffer;

    int heuristic(Point2D p1, Point2D p2) const;
    void generateMaze();
    void handlePlayerMove(Point2D next);

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
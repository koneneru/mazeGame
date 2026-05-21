#include <iostream>
#include <conio.h>
#include <windows.h>
#include "MazeGame.h"
#include "ConsoleUtils.h"

int main() {
    ConsoleCursorConcealer();
    std::setlocale(LC_ALL, "");
    MazeGame game(25, 15);

    char input = 0;
    while (input != 27) {
        game.draw();

        if (game.isGameOver()) {
            std::cout << std::endl << "Поздравляем! Вы нашли выход из лабиринта" << std::endl;
            break;
        }

        //if (_kbhit()) {
            //input = _getch();
            //if (input == 0 || input == 224) input = _getch();
        if (_kbhit()) {
            while (_kbhit()) input = _getch();

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
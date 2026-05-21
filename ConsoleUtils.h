#pragma once
#include <conio.h>
#include <windows.h>

inline static void goToXY(int x, int y) {
    COORD c = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
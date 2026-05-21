#pragma once
#include <conio.h>
#include <windows.h>

inline static void goToXY(int x, int y) {
    COORD c = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

class ConsoleCursorConcealer {
private:
    HANDLE hStdout;
    CONSOLE_CURSOR_INFO oldInfo;

public:
    ConsoleCursorConcealer() {
        hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
        GetConsoleCursorInfo(hStdout, &oldInfo);

        CONSOLE_CURSOR_INFO newInfo = oldInfo;
        newInfo.bVisible = FALSE;
        SetConsoleCursorInfo(hStdout, &newInfo);
    }

    ~ConsoleCursorConcealer() {
        SetConsoleCursorInfo(hStdout, &oldInfo);
    }
};
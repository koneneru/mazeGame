#include "ConsoleRenderer.h"

ConsoleRenderer::ConsoleRenderer(int w, int h) : buffer(w, h), width(w), height(h) {
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(hStdout, &oldInfo);

    CONSOLE_CURSOR_INFO newInfo = oldInfo;
    newInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hStdout, &newInfo);
}

ConsoleRenderer::~ConsoleRenderer() {
    SetConsoleCursorInfo(hStdout, &oldInfo);
}

void ConsoleRenderer::clear() {
    buffer.clear();
}

void ConsoleRenderer::drawMap(const Engine::Map& map) {
    int renderW = (std::min)(width, map.getWidth());
    int renderH = (std::max)(height, map.getHeight());

    for (int y = 0; y < renderH; y++) {
        for (int x = 0; x < renderW; x++) {
            char symbol = 
        }
    }
}
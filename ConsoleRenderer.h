#pragma once
#include "IRenderer.h"
#include "ConsoleBuffer.h"

class ConsoleRenderer : Engine::IRenderer {
private:
	ConsoleBuffer buffer;
	int width;
	int height;

	HANDLE hStdout;
	CONSOLE_CURSOR_INFO oldInfo;

public:
	ConsoleRenderer(int w, int h);
	~ConsoleRenderer() = default;

	void clear() override;
	void drawMap(const Engine::Map& map) override;
};


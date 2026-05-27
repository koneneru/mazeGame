#pragma once
#include <windows.h>
#include <string>

class ConsoleBuffer
{
private:
	HANDLE buffers[2];
	int currentBuffer = 0;
	int width, height;

public:
	ConsoleBuffer(int w, int h);
	~ConsoleBuffer() = default;

	void clear();
	void write(const std::string& str);
	void writeChar(int x, int y, char ch);
	void swap();
};


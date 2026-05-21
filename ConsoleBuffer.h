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
	ConsoleBuffer(int w, int h) : width(w), height(h) {
		buffers[0] = GetStdHandle(STD_OUTPUT_HANDLE);

		buffers[1] = CreateConsoleScreenBuffer(
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			CONSOLE_TEXTMODE_BUFFER,
			NULL
		);

		COORD bufferSize = { static_cast<SHORT>(width), static_cast<SHORT>(height) };
		SMALL_RECT windowSize = { 0, 0, static_cast<SHORT>(width - 1), static_cast<SHORT>(height - 1) };

		for (int i = 0; i < 2; i++) {
			SetConsoleWindowInfo(buffers[i], TRUE, &windowSize);
			SetConsoleScreenBufferSize(buffers[i], bufferSize);
			SetConsoleWindowInfo(buffers[i], TRUE, &windowSize);
		}

		//CONSOLE_CURSOR_INFO cursorInfo;
		//cursorInfo.dwSize = 32;
		//cursorInfo.bVisible = FALSE;
		//SetConsoleCursorInfo(buffers[0], &cursorInfo);
		//SetConsoleCursorInfo(buffers[1], &cursorInfo);
	}

	~ConsoleBuffer() {
		CloseHandle(buffers[1]);
	}

	void clear() {
		COORD coord = { 0, 0 };
		DWORD written;

		FillConsoleOutputCharacter(buffers[currentBuffer], ' ', width * height * 2, coord, &written);
		SetConsoleCursorPosition(buffers[currentBuffer], coord);
	}

	void write(const std::string& str) {
		DWORD written;
		WriteConsoleA(buffers[currentBuffer], str.c_str(), static_cast<DWORD>(str.length()), &written, NULL);
	}

	void swap() {
		SetConsoleActiveScreenBuffer(buffers[currentBuffer]);
		currentBuffer = 1 - currentBuffer;
	}
};


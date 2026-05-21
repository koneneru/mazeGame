#pragma once
#include "point.h"

class Player {
private:
	Point pos;

public:
	Player() : pos({ 1, 1 }) {}
	Player(Point sp) : pos(sp) {}

	Point getPosition() const { return pos; }
	void setPosition(Point p) { pos = p; }

	Point getNextUp() const { return { pos.x, pos.y - 1 }; }
	Point getNextDown() const { return { pos.x, pos.y + 1 }; }
	Point getNextLeft() const { return { pos.x - 1, pos.y }; }
	Point getNextRight() const { return { pos.x + 1, pos.y }; }

	void moveTo(Point np) { pos = np; }
};
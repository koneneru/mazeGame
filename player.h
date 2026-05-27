#pragma once
#include "point.h"

class Player {
private:
	Point2D pos;

public:
	Player() : pos({ 1, 1 }) {}
	Player(Point2D sp) : pos(sp) {}

	Point2D getPosition() const { return pos; }
	void setPosition(Point2D p) { pos = p; }

	Point2D getNextUp() const { return { pos.x, pos.y - 1 }; }
	Point2D getNextDown() const { return { pos.x, pos.y + 1 }; }
	Point2D getNextLeft() const { return { pos.x - 1, pos.y }; }
	Point2D getNextRight() const { return { pos.x + 1, pos.y }; }

	void moveTo(Point2D np) { pos = np; }
};
#pragma once
#include "Point.h"

const char WALL = '#';
const char PATH = ' ';
const char PLAYER = '@';
const char EXIT = '!';
const char ROUTE = '.';

struct AStarNode {
    Point2D pt;
    int g;
    int f;

    bool operator>(const AStarNode& other) const {
        return f > other.f;
    }
};
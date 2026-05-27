#pragma once

struct Point2D {
    int x, y;
    bool operator==(const Point2D& other) const {
        return x == other.x && y == other.y;
    }
    bool operator!=(const Point2D& other) const {
        return x != other.x || y != other.y;
    }
};
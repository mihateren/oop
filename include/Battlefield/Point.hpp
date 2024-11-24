#pragma once
#include <iostream>

class Point
{
public:
    int x;
    int y;

    Point(int x, int y) : x(x), y(y) {}

    void print() const
    {
        std::cout << " (x: " << x << ", y: " << y << ")";
    }

    friend std::ostream &operator<<(std::ostream &os, const Point &point)
    {
        os << " (x: " << point.x << ", y: " << point.y << ")";
        return os;
    }
};
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
};
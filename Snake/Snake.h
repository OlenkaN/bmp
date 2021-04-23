#pragma once
#include "Point.h"
#include<iostream>
#include <list>
using std::list;
enum class direction { UP, DOWN, LEFT, RIGHT, PAUSE };
class Snake {
private:
    int step = 1;
    Point head;
public:
    enum class direction dir = direction::RIGHT;
    list<Point> snake;
    Snake(short x, short y, short length, HANDLE h);
    void Move(HANDLE h);
    Point GetNextPoint();
    bool IsHit(short x, short y);
    bool Eat(Point p, HANDLE h);
};
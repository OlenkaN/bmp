#pragma once
#include "Point.h"
#include <random>
#include <ctime>
#include<list>
class FoodFactory
{
    short x;
    short y;
    char ch;
public:
    Point food;

    FoodFactory(short x, short y, char ch);
    bool checkOnSnake(std::list<Point> snake, Point newo);
    void CreateFood(std::list<Point> snake, HANDLE h);
};
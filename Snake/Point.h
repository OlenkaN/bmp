#pragma once
#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
using std::cout;
class Point
{
public:
    short x;
    short y;
    char ch;
    Point(short x1 = 0, short y1 = 0, char ch1 = '#');
    void Draw(HANDLE h);
    void Clear(HANDLE h);
private:
    void DrawPoint(char _ch, HANDLE h);
};
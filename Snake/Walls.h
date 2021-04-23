#pragma once
#include "Point.h"
class Walls
{
private:
    static void DrawHorizontal(short x, short y, char ch, HANDLE h);
    static void  DrawVertical(short x, short y, char ch, HANDLE h);

public:
    static void  madeWalls(short x, short y, char ch, HANDLE h);

};
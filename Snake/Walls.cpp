#include "Walls.h"
 void Walls::DrawHorizontal(short x, short y, char ch, HANDLE h)
{
    for (short i = 0; i < x; i++)
    {
        SetConsoleCursorPosition(h, { i, y });
        cout << ch;

    }
}
void Walls::  DrawVertical(short x, short y, char ch, HANDLE h)
{
    for (short i = 0; i < y; i++)
    {
        SetConsoleCursorPosition(h, { x, i });
        cout << ch;
    }
}
 void Walls:: madeWalls(short x, short y, char ch, HANDLE h)
    {
        SetConsoleTextAttribute(h, 12);
        DrawHorizontal(x, 0, ch, h);
        DrawHorizontal(x, y, ch, h);
        DrawVertical(0, y, ch, h);
        DrawVertical(x, y + 1, ch, h);
    }
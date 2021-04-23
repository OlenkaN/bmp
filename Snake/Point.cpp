#include "Point.h"
Point::Point(short x1, short y1 , char ch1)
{
    x = x1;
    y = y1;
    ch = ch1;
}

void Point::Draw(HANDLE h) {
    DrawPoint(ch, h);
}
void Point::Clear(HANDLE h) {
    DrawPoint(' ', h);
}
void Point::DrawPoint(char _ch, HANDLE h) {
    SetConsoleCursorPosition(h, { x, y });
    cout << _ch;
}
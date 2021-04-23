#include "Snake.h"
Snake::Snake(short x, short y, short length, HANDLE h)
{
    SetConsoleTextAttribute(h, 10);
    for (short i = x - length; i < x; i++)
    {
        Point p(i, y, '*');
        snake.push_back(p);
        p.Draw(h);
    }
}
void Snake:: Move(HANDLE h)
{
    SetConsoleTextAttribute(h, 10);
    head = GetNextPoint();
    snake.push_back(head);
    snake.front().Clear(h);
    snake.pop_front();
    head.Draw(h);
}
Point Snake:: GetNextPoint()
{
    Point p = snake.back();
    switch (dir)
    {
    case direction::LEFT:
        p.x -= step;
        break;
    case direction::RIGHT:
        p.x += step;
        break;
    case direction::UP:
        p.y -= step;
        break;
    case direction::DOWN:
        p.y += step;
        break;
    }
    return p;
}
bool Snake::IsHit(short x, short y)
{

    head = GetNextPoint();
    for (auto it = snake.begin(); it != snake.end(); ++it) {
        if (it->x == head.x && it->y == head.y)
        {
            return true;
        }
    }
    if (head.x == x || head.x == 0 || head.y == y || head.y == 0)
    {
        return true;
    }

    return false;
}
bool Snake:: Eat(Point p, HANDLE h) {
    head = GetNextPoint();
    if ((head.x == p.x) && (head.y == p.y))
    {
        snake.push_back(head);
        head.Draw(h);
        return true;
    }
    return false;
}
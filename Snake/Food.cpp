#include "Food.h"
FoodFactory::FoodFactory(short x, short y, char ch)
{
    this->x = x;
    this->y = y;
    this->ch = ch;
}
bool FoodFactory::checkOnSnake(std::list<Point> snake, Point newo)
{
    for (auto s : snake)
    {
        if (s.x == newo.x && s.y == newo.y)
        {
            return true;
        }
    }
    return false;
}
void FoodFactory::CreateFood(std::list<Point> snake, HANDLE h)
{
    srand(time(0) + 2344);
    Point newo(0, 0, ch);
    SetConsoleTextAttribute(h, 6);
    do {
        newo.x = int(rand() % (x - 2) + 1);
        newo.y = int(rand() % (y - 2) + 1);
    } while (checkOnSnake(snake, newo));
    food = newo;
    food.Draw(h);
}
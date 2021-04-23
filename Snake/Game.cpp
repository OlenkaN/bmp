#include "Game.h"
unsigned GAME:: run(HANDLE h)
{
    Game(current, h);
    return 1;
}
void GAME::Game(Besties& current, HANDLE h)
{
    system("cls");
    hide_cursor(h);
    const WORD HORIZONTAL_DELAY = 120;
    const WORD VERTICAL_DELAY = 170;
    short x = 40;
    short y = 40;
    int score = 0;
    Walls::madeWalls(x, y, '#', h);
    FoodFactory foodFactory(x, y, '@');
    Snake snake(x / 2, y / 2, 3, h);
    foodFactory.CreateFood(snake.snake, h);
    SetConsoleCursorPosition(h, { static_cast<SHORT>(x + 5), static_cast<SHORT>(5) });
    cout << "Score: " << score << "\n";
    SetConsoleCursorPosition(h, { x, y });
    while (true)
    {
        if (_kbhit())
        {
            char key = _getch();

            switch (key)
            {
            case 'a':
                if (snake.dir != direction::RIGHT)
                    snake.dir = direction::LEFT;
                break;
            case 'd':
                if (snake.dir != direction::LEFT)
                    snake.dir = direction::RIGHT;
                break;
            case 'w':
                if (snake.dir != direction::DOWN)
                    snake.dir = direction::UP;
                break;
            case 's':
                if (snake.dir != direction::UP)
                    snake.dir = direction::DOWN;
                break;
            case 32:
                snake.dir = direction::PAUSE;
                break;
            default:
                break;
            }
        }
        if (snake.dir != direction::PAUSE)
        {
            if (snake.IsHit(x, y))
            {
                break;
            }
            else if (snake.Eat(foodFactory.food, h))
            {
                foodFactory.CreateFood(snake.snake, h);
                ++score;
                SetConsoleCursorPosition(h, { static_cast<SHORT>(x + 5), static_cast<SHORT>(5) });
                cout << "Score: " << score << "\n";
            }
            else
            {
                snake.Move(h);
            }
            if (snake.dir == direction::RIGHT || snake.dir == direction::LEFT)
                Sleep(HORIZONTAL_DELAY);
            else
                Sleep(VERTICAL_DELAY);
        }


    }
    system("cls");
    current.readFile(h);
    char* char_arr;
    string s = "Your score : " + std::to_string(score);
    char_arr = &s[0];
    print_element("Game over", 20, 18, 10, h);
    print_element(char_arr, 20, 23, 10, h);
    system("pause");
}
#include "BestPlayers.h"
unsigned BESTPLAYERS:: run(HANDLE h)
{
    system("cls");
    current.readFile(h);
    short x = 17;
    short y = 10;
    SetConsoleTextAttribute(h, 6);
    for (auto pl : current.players)
    {
        SetConsoleCursorPosition(h, { x,y });
        printf("%s", std::string(42, '-').c_str());
        SetConsoleCursorPosition(h, { x,y + 1 });
        printf("|%10c%-20s| %-8d|\n", ' ', pl.name.c_str(), pl.score);
        SetConsoleCursorPosition(h, { x,y + 2 });
        printf("%s\n", std::string(42, '-').c_str());
        y = y + 3;
    }
    system("pause");
    return 1;
}
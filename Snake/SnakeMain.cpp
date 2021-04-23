#include <cstdlib>
#include <stdio.h>
#include "Game.h"
#include "Menu.h"
#include "BestPlayers.h"

int main()
{
    system("title Snake");
    system("mode con cols=80 lines=41");
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    Scene::hide_cursor(h);
    SetConsoleTextAttribute(h, 12);
    Scene* scenes[] = { new MENU(), new GAME(), new BESTPLAYERS() };
    unsigned scene = 1;
    while (scene)
    {
        scene = scenes[scene - 1]->run(h);
    }
    return 0;
}
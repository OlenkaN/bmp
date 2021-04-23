#pragma once
#include "Scene.h"
class MENU :public Scene
{
    enum class menu { NewGame, BestPlayers, Exit };
    enum class menu m = menu::NewGame;

    void print_menu(short x, short y, short z, HANDLE h);

public:
    unsigned run(HANDLE h);
};

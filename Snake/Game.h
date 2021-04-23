#pragma once
#include "Scene.h"
#include "Snake.h"
#include "Walls.h"
#include "Food.h"
#include <string>
class GAME :public Scene
{
    void Game(Besties& current, HANDLE h);
    unsigned run(HANDLE h);
};
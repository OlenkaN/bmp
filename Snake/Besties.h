#pragma once
#include "Point.h"
#include <fstream>
using namespace std;

class Besties
{
    struct Player
    {
        int score = 0;
        string name = "";
    };
    char* char_arr;

public:
    Player players[5];
    void readFile(HANDLE h);
    void outInFile();
    void fileAnalysis(int score, HANDLE h);
    void ShowPlayers(HANDLE h);
};
#include "Besties.h"
 void Besties::readFile(HANDLE h)
{
    string name;
    int x;
    int amount = 5;
    int i = 0;
    ifstream in("players.txt");
    if (in.is_open())
    {
        while (in >> name >> x && i < amount)
        {
            players[i].name = name;
            players[i].score = x;
            ++i;
        }
    }
    in.close();

}
 void Besties:: outInFile()
 {
     std::ofstream out("players.txt");
     if (out.is_open())
     {
         for (auto pl : players)
         {
             out << pl.name << " " << pl.score << "\n";
         }
     }
     out.close();
 }
 void Besties:: fileAnalysis(int score, HANDLE h)
 {
     bool flag = true;
     for (int i = 0; i < 5; ++i)
     {
         if (players[i].score < score)
         {
             if (flag)
             {
                 SetConsoleCursorPosition(h, { 20,15 });
                 cout << "You are in top 5! Enter your name: \n";
                 SetConsoleCursorPosition(h, { 20,16 });
                 cin >> players[i].name;
                 players[i].score = score;
                 flag = false;
                 ++i;
             }
             players[i] = players[i + 1];
         }
     }

 }
 void Besties:: ShowPlayers(HANDLE h)
 {
     system("cls");
     readFile(h);
     short x = 17;
     short y = 10;
     SetConsoleTextAttribute(h, 6);
     for (auto pl : players)
     {
         char_arr = &pl.name[0];
         SetConsoleCursorPosition(h, { x,y });
         printf("%s", std::string(42, '-').c_str());
         SetConsoleCursorPosition(h, { x,y + 1 });
         printf("|%10c%-20s| %-8d|\n", ' ', char_arr, pl.score);
         SetConsoleCursorPosition(h, { x,y + 2 });
         printf("%s\n", std::string(42, '-').c_str());
         y = y + 3;
     }
 }

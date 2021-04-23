#include "Menu.h"
void MENU:: print_menu(short x, short y, short z, HANDLE h)
{
    system("cls"); // очищаем экран
    print_element("New game", 20, 10, x, h);
    print_element("Best Players", 20, 15, y, h);
    print_element("Exit", 20, 20, z, h);
}
unsigned MENU::run(HANDLE h)
{
    print_menu(10, 6, 6, h);
    m = menu::NewGame;
    while (true)
    {
        if (_kbhit())
        {
            char key = _getch();
            switch (key)
            {
            case 'w':
                if (m == menu::NewGame)
                    m = menu::Exit;
                else if (m == menu::BestPlayers)
                    m = menu::NewGame;
                else
                    m = menu::BestPlayers;

                break;
            case 's':

                if (m == menu::NewGame)
                    m = menu::BestPlayers;
                else if (m == menu::BestPlayers)
                    m = menu::Exit;
                else
                    m = menu::NewGame;

                break;

            }
            switch (m)
            {
            case menu::NewGame:
                print_menu(10, 6, 6, h);
                break;
            case menu::BestPlayers:
                print_menu(6, 10, 6, h);
                break;
            case menu::Exit:
                print_menu(6, 6, 10, h);
                break;

            }
            if (key == 32)
            {

                if (m == menu::NewGame)
                {
                    return 2;
                }
                else if (m == menu::BestPlayers)
                {
                    return 3;
                }
                else
                    return 0;

            }
        }
    }
}
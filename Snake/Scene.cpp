#include "Scene.h"
void Scene:: print_element(const char* el, short x, short y, short z, HANDLE h)
{
    SetConsoleTextAttribute(h, z);
    SetConsoleCursorPosition(h, { x,y });
    printf("%s", std::string(42, '-').c_str());
    SetConsoleCursorPosition(h, { x,y + 1 });
    printf("|%40c|\n", ' ');
    SetConsoleCursorPosition(h, { x,y + 2 });
    printf("|%15c%-25s|\n", ' ', el);
    SetConsoleCursorPosition(h, { x,y + 3 });
    printf("|%40c|\n", ' ');
    SetConsoleCursorPosition(h, { x,y + 4 });
    printf("%s\n", std::string(42, '-').c_str());
}
void  Scene::hide_cursor(HANDLE h)
{
    CONSOLE_CURSOR_INFO crs;
    crs.bVisible = false;
    crs.dwSize = 100;
    SetConsoleCursorInfo(h, &crs);
}
#include "Besties.h"
#pragma once
class Scene
{
public:
    Besties current;
    virtual unsigned run(HANDLE h) = 0;
    void print_element(const char* el, short x, short y, short z, HANDLE h);
    void static hide_cursor(HANDLE h);
};

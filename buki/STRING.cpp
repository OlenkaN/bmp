#include "STRING.h"
void STRING:: resize()
{
    char* temp = new char[size * 2];
    for (int i = 0; i < size; ++i)
        temp[i] = ptr[i];
    capacity = size * 2;
    delete[] ptr;
    ptr = temp;
}
STRING::STRING()
{
    clear();
}
STRING::STRING(char* arr) {
    if (arr == nullptr)
    {
        clear();
    }
    else
    {
        size = strlen(arr) + 1;
        capacity = size * 2;
        ptr = new char[capacity];

        strcpy(ptr, arr);
    }
}

STRING::STRING(STRING& str)
{
    size = strlen(str.ptr) + 1;
    capacity = size * 2;
    ptr = new char[capacity];
    strcpy(ptr, str.ptr);

}
STRING::~STRING()
{
    delete[] ptr;
}
ostream& operator<<(ostream& out, const STRING& s)
{
    out << s.ptr;
    return out;
}
char& STRING:: operator[] (const int index)
{
    return ptr[index];
}
STRING& STRING:: operator=(
    const STRING& str)
{
    if (this == &str)
        return *this;
    delete[] ptr;
    size = strlen(str.ptr) + 1;
    capacity = size * 2;
    ptr = new char[capacity];
    strcpy(ptr, str.ptr);
    return *this;
}
STRING operator+(
    const STRING& lhs,
    const STRING& rhs)
{
    int length = strlen(lhs.ptr)
        + strlen(rhs.ptr);

    char* buff = new char[length + 1];
    strcpy(buff, lhs.ptr);
    strcat(buff, rhs.ptr);
   STRING temp{ buff };
    delete[] buff;
    return temp;
}
void STRING:: insert(int index, char elem)
{
    if (size == capacity)
    {
        resize();
    }

    for (int i = size; i > index; --i)
    {
        ptr[i] = ptr[i - 1];
    }

    ptr[index] = elem;
    ++size;
}
void STRING::erase(int index)
{
    for (int i = index; i < (size - 1); ++i)
    {
        ptr[i] = ptr[i + 1];
    }
    --size;
}
void STRING::pushBack(char elem)
{
    if (size == capacity)
    {
        resize();
    }
    ptr[size - 1] = (char)elem;
    ptr[size] = '\0';

    ++size;

}
void STRING:: popBack()
{
    ptr[size - 2] = '\0';
    --size;
}
void STRING::clear()
{
    if (ptr) delete[] ptr;
    size = 0;
    ptr = new char[1];
    ptr[0] = '\0';
    capacity = 1;
}
int STRING::Size()
{
    return size-1;
}

#pragma once
#pragma warning(disable : 4996)
#include <iostream>
using namespace std;
class STRING
{
private:
    char* ptr;
    int size = 0;;
    int capacity = 0;
    void resize();
public:
   //constructors
    STRING();
    STRING(char* arr);
    STRING(STRING& str);
    ~STRING();
    //operators
    char& operator[] (const int index);
    friend ostream& operator<<(ostream& out, const STRING& s);
    STRING& operator=(const STRING& str);
    friend STRING operator+(
        const STRING& lhs,
        const STRING& rhs);
    //functions
    void insert(int index, char elem);
    void erase(int index);
    void pushBack(char elem);
    void popBack();
    void clear();
    int Size();

};
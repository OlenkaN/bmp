#include <iostream>
using namespace std;


uint16_t pack16(char* v)
{
    cout << "0: " <<( v[0] << 12 )<< "\n";
    cout << "1: " <<( v[1] << 8) << "\n";
    cout << "2: " <<( v[2] << 4) << "\n";
    cout << "3: " << v[3]  << "\n";
    return (v[0] << 12) + (v[1] << 8) + (v[2] << 4) + v[3];
}

void unpack16(uint16_t a, char* v)
{
    v[0] = a >> 12;
    a = a & 4095;
    v[1] = a >> 8;
    a = a & 255;
    v[2] = a >> 4;
    a = a & 15;
    v[3] = a;
}

int main1()
{
    char v[4] = { 1,3,4,6};

    cout << "Original values: ";
    for (int i = 0; i < 4; i++)
        cout << (int)v[i] << " ";
    cout << endl;

    uint16_t test = pack16(v);
    cout << "Packed: " << test << endl;

    unpack16(test, v);
    cout << "Unpacked: ";
    for (int i = 0; i < 4; i++)
        cout << (int)v[i] << " ";

    return 0;
}
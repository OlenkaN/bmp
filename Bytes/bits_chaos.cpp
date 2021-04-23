
#include <iostream>
using namespace std;
void pb(char c)
{
	for (int i = 0; i < 8; ++i)
	{
		cout << (int)((c >> (7 - i)) & 1);
	}
	cout << '\n';
}
unsigned char changeCharToEncrypt(char ch)
{

	unsigned char first4 = ch & 0xf0;
	unsigned char sec4 = ch & 0x0f;
	first4 = ((first4 & 160) >> 1) | ((first4 & 80) << 1);
	sec4 = sec4 ^( first4>>4);
	first4= (first4&0xf0) | (0x0f & sec4);
	return first4;
}
unsigned char changeCharToDecrypt(char ch)
{
	unsigned char first4 = ch & 0xf0;
	unsigned char sec4 = ch & 0x0f;
	sec4 = sec4 ^ (first4 >> 4);
	first4 = ((first4 & 160) >> 1) | ((first4 & 80) << 1);
	first4= (first4&0xf0) | (0x0f & sec4);
	return first4;
}
string bit_encrypt(string toEncrypt)
{
	string result = "";
	for (int i = 0; i < 12; i++) {
		result+=changeCharToEncrypt(toEncrypt[i]);
	}
	return result;

}
string bit_decrypt(string toDecrypt)
{
	string result = "";
	for (int i = 0; i < 12; i++) {
		result+=changeCharToDecrypt(toDecrypt[i]);
	}
	return result;

}

int main() {
	unsigned char test = changeCharToEncrypt('H');
	string encrypted = bit_encrypt("Hello world!");
	cout << "Encrypted" << encrypted<<"\n";
	cout<<"Decrypted" <<bit_decrypt(encrypted)<<"\n";
	return 0;
}
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <list>
using namespace std;
int ToHash(string str)
{
	int number = 31;
	unsigned long long result = 0;
	for (unsigned int i = 0; i < str.size(); ++i)
	{
		result += (str[i] - 'a' + 1) * pow(number, i);
	}
	return (result) % 2000;
}
bool CheckInDict(list<string> current, string str)
{
	list <string> ::iterator it;
	for (it = current.begin(); it != current.end(); ++it)
	{
		if (*it == str)
		{
			return true;
		}
	}
	return false;
}
void Client(list<string>* dictionary, string& k)
{
	int index = ToHash(k);
	if (CheckInDict(dictionary[index], k))
	{
		k = "";
	}
	else
	{
		cout << "Mistake there no word: " << k << "\n";
		k = "";
	}
}
int main()
{

	try
	{
		ifstream f;
		string str;
		int index;
		list<string>* dictionary = new list<string>[2000];
		f.open("info.txt");
		while (!f.eof())
		{
			f >> str;
			index = ToHash(str);
			dictionary[index].push_back(str);
		}
		string k;
		string s;
		cout << "Enter you string: \n";
		getline(cin, s);
		for (char t : s)
		{
			if (t == ' ' && k.length() > 1)
			{
				Client(dictionary, k);
			}
			else if (t != ' ')
				k += t;
		}
		if (!(k == ""))
		{
			Client(dictionary, k);
		}
	}
	catch (exception ex)
	{
		cout << ex.what();
	}

	return 0;
}
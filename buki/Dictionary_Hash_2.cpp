#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <list>
#include <sstream>
using namespace std;
class MyHashDictionary
{
	string alphabet = "abcdefghijklmnopqrstuvwxyz";
public:
	list<string>** dictionary;
	MyHashDictionary(int n)
	{
		dictionary = new list<string> * [n] { nullptr };
	}
	void FillDictionary(string fileName)
	{
		int index;
		ifstream f;
		string str;
		f.open(fileName);
		while (!f.eof())
		{
			f >> str;
			index = ToHash(str);
			if (dictionary[index] == nullptr)
			{
				dictionary[index] = new list<string>[200];
				dictionary[index]->push_back(str);
			}
			else
			{
				dictionary[index]->push_back(str);
			}
		}
	}
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
	bool CheckInDict(string str)
	{
		int index = ToHash(str);
		list <string> ::iterator it;
		for (it = dictionary[index]->begin(); it != dictionary[index]->end(); ++it)
		{
			if (*it == str)
			{
				return true;
			}


		}
		return false;
	}
	void DeleteOneLetter(string str)
	{
		string temp;
		for (int i = 0; i < str.size(); ++i)
		{
			temp = str;
			temp.erase(i, 1);
			if (CheckInDict(temp))
			{
				cout << "Maybe you want (delete): " << temp << "\n";
			}
		}
	}
	void SwapTwoLetter(string str)
	{
		string temp;
		for (int i = 0; i < str.size() - 1; ++i)
		{
			temp = str;
			swap(temp[i], temp[i + 1]);
			if (CheckInDict(temp))
			{
				cout << "Maybe you want (swap): " << temp << "\n";
			}
		}
	}
	void AlphabetReplace(string str)
	{
		string temp;
		for (int i = 0; i < str.size(); ++i)
		{
			temp = str;
			for (int k = 0; k < alphabet.size(); ++k)

			{
				if (alphabet[k] != str[i])
				{
					temp.replace(i, 1, alphabet.substr(k, 1));
					if (CheckInDict(temp))
					{
						cout << "Maybe you want (replace): " << temp << "\n";
					}
				}
			}
		}
	}
	void AlphabetInsert(string str)
	{
		string temp;
		for (int i = 0; i < str.size(); ++i)
		{
			for (int k = 0; k < alphabet.size(); ++k)

			{
				if (alphabet[k] != str[i])
				{
					temp = str;
					temp.insert(i, alphabet.substr(k, 1));
					if (CheckInDict(temp))
					{
						cout << "Maybe you want (insert): " << temp << "\n";
					}
				}
			}
		}

	}
	void Client(string k)
	{
		if (!CheckInDict(k))
		{
			cout << "Mistake there no word: " << k << "\n";
			DeleteOneLetter(k);
			SwapTwoLetter(k);
			AlphabetReplace(k);
			AlphabetInsert(k);
		}
		else
		{
			cout << "Correct!\n";
		}
	}

};


int main()
{

	try
	{
		string str;
		int index;
		MyHashDictionary test(200000);
		test.FillDictionary("info.txt");
		cout << "Enter you string: \n";

		while (getline(cin, str) && str != "")
		{
			stringstream ss(str);
			while (ss >> str)
			{
				test.Client(str);
			}
			cout << "Enter you string: \n";
		}

	}
	catch (exception ex)
	{
		cout << ex.what();
	}

	return 0;
}
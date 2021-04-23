#include <iostream>
#include <fstream>
using namespace std;
int main()
{
	ifstream test("cardRdata.raw", ios::binary);
	if (!test.is_open())
		cout << "File couldn't be open!\n";
	else
	{
		test.seekg(0, ios::end);
		long int length = test.tellg();
		test.seekg(0, ios::beg);
		string counter = "6";
		ofstream file;
		char* buffer = new char[length];
		test.read(buffer, length);
		for (int i = 0; i < length; ++i)
		{

			if (i < length && buffer[i] == (char)0xff)
			{
				++i;
				if (i < length && buffer[i] == (char)0xd8)
				{
					++i;
					if (i < length && buffer[i] == (char)0xff)
					{
						file.open(counter + ".JPEG", ios::binary);
						file << buffer[i] << buffer[i - 1];
						i -= 1;
						do
						{
							++i;
							file << buffer[i];
						} while ((i < length) && !((buffer[i - 1] == (char)0xff) && (buffer[i] == (char)0xd9)));
						file.close();
						counter += "2";
					}
				}

			}
		}
		test.close();
	}
	/*else
	{
		string counter = "2";
		ofstream file;
		char el;
		do
		{
			test.get(el);
			if (el == (char)0xff && !test.eof())
			{
				file.open(counter + ".JPEG", ios::binary);
				file << el;
				test.get(el);
				if (el == (char)0xd8 && !test.eof())
				{
					file << el;
					test.get(el);
					if (el == (char)0xff && !test.eof())
					{

						bool flag, flag1;
						do
						{
							flag = false;
							flag1 = false;
							file << el;
							if (el == (char)0xff)
								flag = true;
							if (test.eof())
							{
								break;
							}
							test.get(el);
							file << el;
							if (el == (char)0xd9)
								flag1 = true;
							test.get(el);
						} while (!(flag && flag1) && !test.eof());
						counter += "1";
					}
				}
				file.close();
			}
		} while (!test.eof());
		test.close();
	}*/
	return 0;
}
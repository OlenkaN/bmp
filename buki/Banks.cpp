#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <stdexcept>
using namespace std;
struct Bank
{
	double balance;
	bool status = true;
};

void CountBalance(double**& banks, const int& limit, Bank*& info, int& size)
{
	double allActives;
	bool flag = 0;
	for (int r = 0; r < size; ++r)
	{
		if (info[r].status == true)
		{
			allActives = info[r].balance;
			for (int c = 0; c < size; ++c)
			{
				allActives += banks[r][c];
			}
			if (allActives < limit)
			{
				info[r].status = false;
				for (int r1 = 0; r1 < size; ++r1)
				{
					banks[r1][r] = 0;
				}
				flag = 1;
			}
		}
	}
	if (flag == 1)
	{
		CountBalance(banks, limit, info, size);
	}


}
void ShowBanks(double**& banks, const int& amount)
{

	for (int r = 0; r < amount; ++r)
	{
		cout << r << ": ";
		for (int c = 0; c < amount; ++c)
		{
			cout.width(7);
			cout << banks[r][c];
		}
		cout << endl;
	}
	cout << endl;
}
int main()
{
	ifstream f;
	f.open("info.txt");
	int amount, limit, num, x;
	double y;
	while (!f.eof())
	{
		f >> amount;
		f >> limit;
		double** banks = new double* [amount];
		Bank* info = new Bank[amount];

		for (int i = 0; i < amount; ++i)
		{
			banks[i] = new double[amount]();
			f >> info[i].balance;
			f >> num;
			for (int k = 0; k < num; ++k)
			{
				f >> x;
				f >> y;
				banks[i][x] = y;
			}
		}
		ShowBanks(banks, amount);
		CountBalance(banks, limit, info, amount);
		ShowBanks(banks, amount);


	}
	f.close();


	return 0;

}

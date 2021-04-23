#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
bool validcheck(long long& a) {
	int sum1 = 0, current = 0;
	int size = (int)(log10(a) + 1);

	for (int i = 0; i < size; i += 2) {
		sum1 += a % 10;
		a /= 10;
		current = 2 * (a % 10);
		if (current >= 10) {
			current -= 9;
		}
		a /= 10;
		sum1 += current;
	}
	if (sum1 % 10 == 0) {
		return 1;
	}

	return 0;
}
int main() {

	cout << "Enter your card number: " << endl;
	long long num;
	cin >> num;
	bool res = validcheck(num);
	cout << "Your card statys is: " << res;


	return 0;
}
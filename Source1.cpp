#include <iostream>
#include <vector>
#include <math.h>
using namespace std;
bool validcheck(vector<int>& a) {
	int sum1 = 0, sum2 = 0, k1, k2;
	if ((a.size() % 2) == 0) {
		k1 = a.size() - 2;
		k2 = k1 + 1;
	}
	else {
		k1 = a.size() - 1;
		k2 = k1 - 1;
	}
	for (int i = k1; i >= 0; i -= 2) {
		a[i] = a[i] * 2;
		if (a[i] >= 10) {
			a[i] -= 9;
		}
		sum1 += a[i];
	}
	for (int m = k2; m >= 0; m -= 2) {
		sum2 += a[m];
	}
	if ((sum1 + sum2) % 10 == 0) {
		return 1;
	}
	return 0;
}
int main() {

	cout << "Enter your card number: " << endl;
	long long num;
	cin >> num;
	cout << (math.log10(num));

	cout << res;
	return 0;
}
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
int main() {
	int par;
	cout << "Enter amount of colums and rows of matrix: ";
	cin >> par;
	char** m = new char* [par];
	for (int i = 0; i < par; ++i) {
		m[i] = new char[par];
	}
	for (int i = 0; i < par; ++i) {
		for (int j = 0; j < par; ++j) {
			if ((i == j) || j == (par - 1 - i)) {
				m[i][j] = 'x';
			}
			else {
				m[i][j] = '0';
			}
		}
	}
	if (par % 2 != 0) {
		m[par / 2][par / 2] = '0';
	}
	for (int i = 0; i < par; ++i) {
		for (int j = 0; j < par; ++j) {
			cout << m[i][j] << ' ';
		}
		cout << endl;
	}
	return 0;
}
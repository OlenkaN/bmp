#include <iostream>
#include <limits>
using namespace std;
int main() {
	int x;
	int count = 0;
	int max_ = INT_MIN;
	int min_ = INT_MAX;
	int sum = 0;
	int average_ = 0;
	cin >> x;
	while (cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Not correct value" << endl;
		cin >> x;
	}
	while (x != 0) {
		
		if (x < 0) {
			cout << "Not correct value,please enter number one more time" << endl;
		}
		else {
			count++;
			if (x < min_) {
				min_ = x;
			}
			if (x > max_) {
				max_ = x;
			}
			sum += x;
			average_ = sum / count;
		}
		cin >> x;
		while (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Not correct value" << endl;
			cin >> x;
		}
	}
	cout << "Amount: " << count << endl << "Maximum and minimum: " << max_ << " " << min_ << endl;
	cout << "Sum and average: " << sum << " " << average_ << endl;
}

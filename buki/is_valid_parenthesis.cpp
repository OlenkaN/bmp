#include <iostream>
#include <stdexcept>
#include "Tstack.h"
using namespace std;
bool is_valid_parenthesis(string & str) {
	Tstack parenthesis;
	for (char c : str) {
		if (c == '(' || c == '{' || c == '[') {
			parenthesis.push(c);
		}
		if (c == ')' || c == '}' || c == ']') {
			if (parenthesis.is_empty()) {
				return 0;
			}
			char current = parenthesis.taketop();
			if ((c == ')' && current == '(') || (c == '}' && current == '{')
				|| (c == ']' && current == '[')) {
				parenthesis.pop();
			}
			else return 0;
		}
	}
	return parenthesis.is_empty();
}

int main() {
	string test;
	cout << "Enter your string: ";
	cin >> test;
	cout << is_valid_parenthesis(test) << "\n";
	return 0;
}
#pragma once
using namespace std;
typedef char T;

class Tstack {
private:
	struct ListElem {
		T data;
		int index;
		ListElem* next;
	};
	ListElem* top = nullptr;
	int size = 0;
public:
	Tstack();
	~Tstack();
	bool push(T elem);
	bool pop();
	bool delete_(int ind);
	T take(int ind);
	T taketop();
	void changeindex(ListElem* k, char x);
	bool is_empty();
};
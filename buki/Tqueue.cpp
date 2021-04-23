#include <iostream>
#include <stdexcept>
using namespace std;
template <typename T>
class Tqueue {
private:
	struct ListElem {
		T data;
		ListElem* previous;
		ListElem* next;
		ListElem(T data, ListElem* previous, ListElem* next) {
			this->data = data;
			this->previous = previous;
			this->next = next;
		}
	};
	ListElem* heap = nullptr;
	ListElem* tail = nullptr;
	int size = 0;
public:
	void enQueue(T data);
	T deQueue();
	int getsize();
	void deleteInd(int index);
	void insert(T data, int index);
	void ShowElements()
	{
		ListElem* temp = tail;
		while (temp)
		{
			cout << temp->data << " ";
			temp = temp->next;
		}
		cout << "Size :" << size;
		cout << endl;


	}
private: void findInd(int index, ListElem*& temp);
};
template <typename T>
void Tqueue<T> ::enQueue(T data)
{
	if (heap == nullptr)
	{
		ListElem* p = new ListElem(data, heap, tail);
		if (p == nullptr)
		{
			throw "NOT SPARE SPACE";

		}
		tail = p;
		heap = p;

	}
	else
	{
		ListElem* p = new ListElem(data, nullptr, tail);
		if (p == nullptr)
		{
			throw "NOT SPARE SPACE";

		}
		tail->previous = p;
		tail = p;
	}
	++size;
}

template <typename T>
T Tqueue<T> ::deQueue()
{
	if (heap == nullptr)
	{
		throw "No elements to delete";
	}
	else
	{
		ListElem* temp = heap;
		heap = heap->previous;
		heap->next = nullptr;
		T returnvalue = temp->data;
		delete temp;
		--size;
		return returnvalue;
	}
}
template <typename T>
int Tqueue<T> ::getsize()
{
	return size;
}
template <typename T>
void Tqueue<T> ::deleteInd(int index)
{
	if (heap == nullptr)
	{
		throw "Queue is empty";
	}
	if (index == 0)
	{
		this->deQueue();
		return;
	}
	ListElem* temp;
	if (index == size - 1)
	{
		temp = tail;
		tail = tail->next;
		tail->previous = nullptr;
		delete temp;
		--size;
		return;
	}
	if (index > (size / 2))
	{
		this->findInd(index, temp);
		ListElem* d = temp->next;
		temp->next = d->next;
		temp->next->previous = temp;
		delete d;
		--size;
		return;
	}
	else
	{
		this->findInd(index, temp);
		ListElem* d = temp->previous;
		temp->previous = d->previous;
		temp->previous->next = temp;
		delete d;
		--size;
		return;
	}

}
template <typename T>
void Tqueue<T>::findInd(int index, ListElem*& temp) {
	int current;
	if (index >= size || index < 0) {
		throw invalid_argument("no such element");
	}
	else if (index > (size / 2))
	{
		temp = tail;
		current = size - 2;
		while (current != index - 1)
		{
			temp = temp->next;
			--current;
		}

	}
	else
	{
		temp = heap;
		current = 1;
		while (current != index)
		{
			temp = temp->previous;
			current++;
		}
	}
}
template <typename T>
void Tqueue<T>::insert(T data, int index)
{

	if (index == size) {
		this->enQueue(data);
		return;
	}
	else {
		ListElem* temp = new ListElem(0, nullptr, nullptr);
		if (index == 0) {
			temp = new ListElem(data, heap, nullptr);
			temp->previous->next = temp;
			heap = temp;
		}
		else if (index > (size / 2))
		{
			this->findInd(index, temp);
			ListElem* d = new ListElem(data, temp, temp->next);
			temp->next = d;
			d->next->previous = d;
		}
		else
		{
			this->findInd(index, temp);
			ListElem* d = new ListElem(data, temp->previous, temp);
			temp->previous = d;
			d->previous->next = d;
		}
	}
	++size;


}


int main() {
	Tqueue<int> test;
	test.enQueue(0);
	test.enQueue(1);
	test.enQueue(2);
	test.enQueue(3);
	test.enQueue(4);
	test.ShowElements();
	test.insert(5, 0);
	test.deQueue();
	test.ShowElements();
	test.insert(6, 2);
	test.ShowElements();
	test.insert(6, 5);
	test.ShowElements();
	test.deleteInd(0);
	test.ShowElements();
	test.deleteInd(1);
	test.ShowElements();
	test.deleteInd(3);
	test.ShowElements();
	return 0;
}

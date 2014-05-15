#include <stdio.h>

using namespace std;

class EmptyQueue{};

template<typename T>
class Queue
{
	T* elemArray;
	int capacity;
	int size;
	int first;

	void checkSize();
public:
	Queue(int cap = 10) : capacity(cap), size(0), first(0) { elemArray = new T[capacity]; }
	~Queue() { delete[] elemArray; }

	bool isEmpty() const { return size == 0; }
	int getSize() const { return size; }
	void enqueue(const T& elem);
	T& dequeue() throw(EmptyQueue);
	const T& front() const throw(EmptyQueue);
};

template<typename T>
void Queue<T>::checkSize()
{
	if (size + 1 > capacity)
	{
		T* oldArray = elemArray;
		int oldCap = capacity;
		capacity = capacity * 2;
		elemArray = new T[capacity];
		for (int i = 0; i < size; ++i) {
			elemArray[i] = oldArray[first % oldCap];
			first++;
		}
		first = 0;
		delete[] oldArray;
	}
}

template<typename T>
void Queue<T>::enqueue(const T& elem)
{
	checkSize();
	elemArray[(first + size) % capacity] = elem;
	size++;
}

template<typename T>
T& Queue<T>::dequeue() throw(EmptyQueue)
{
	if (isEmpty()) throw EmptyQueue();
	int temp = first;
	first = (first + 1) % capacity;
	size--;
	return elemArray[temp];
}

template<typename T>
const T& Queue<T>::front() const throw(EmptyQueue)
{
	if (isEmpty()) throw EmptyQueue();
	return elemArray[first];
}
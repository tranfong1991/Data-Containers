#include <stdio.h>

using namespace std;

class EmptyStack{};

template<typename T>
class Stack
{
	T* elemArray;
	int capacity;
	int size;

	void checkSize();
public:
	Stack(int cap = 10) : capacity(cap), size(0) { elemArray = new T[capacity]; }
	~Stack() { delete[] elemArray; }

	bool isEmpty() const { return size == 0; }
	int getSize() const { return size; }
	T& pop() throw(EmptyStack);
	void push(const T& elem);
	const T& top() const throw(EmptyStack);
};

template<typename T>
void Stack<T>::checkSize()
{
	if (size + 1 > capacity)
	{
		T* oldArray = elemArray;
		capacity *= 2;
		elemArray = new T[capacity];
		for (int i = 0; i < size; ++i)
			elemArray[i] = oldArray[i];
		delete[] oldArray;
	}
}

template<typename T>
T& Stack<T>::pop() throw(EmptyStack)
{
	if (isEmpty()) throw EmptyStack();
	return elemArray[--size];
}

template<typename T>
void Stack<T>::push(const T& elem)
{
	checkSize();
	elemArray[size++] = elem;
}

template<typename T>
const T& Stack<T>::top() const throw(EmptyStack)
{
	if (isEmpty()) throw EmptyStack();
	return elemArray[size - 1];
}
#pragma once
#include "Locator.h"

class EmptyHeap{};		//To throw as exception
class ItemNotFound{};	//To throw as exception

template<typename ElemType, typename Comp>
class BinaryHeap
{
	ElemType* elemArray;
	Comp comp;
	int curSize;
	int capacity;
	int numCompare;
	static const int DEF_SIZE = 9;

	void getNewArray(int newSize)
	{
		elemArray = new ElemType[newSize];
		capacity = newSize;
	}
	void checkSize();
	void walkDown(int hole);
	void walkUp(int hole);
public:
	BinaryHeap(int size = DEF_SIZE)
	{
		curSize = 0;
		numCompare = 0;
		getNewArray(size);
	}

	int getCompare() const { return numCompare; }
	const ElemType& findMin();
	bool isEmpty() const { return curSize == 0; }
	void insert(const ElemType& elem);
	ElemType& removeMin();
	void buildHeap();
	void displayHeap();
};

template<typename ElemType, typename Comp>
void BinaryHeap<ElemType, Comp>::displayHeap()
{
	for (int i = 0; i < curSize; ++i)
		cout << elemArray[i] << " ";
}

template<typename ElemType, typename Comp>
void BinaryHeap<ElemType, Comp>::buildHeap()
{
	for (int i = (curSize - 2) / 2; i >= 0; i--) walkDown(i);
}

template<typename ElemType, typename Comp>
const ElemType& BinaryHeap<ElemType, Comp>::findMin()
{
	if (isEmpty()) throw EmptyHeap();
	return elemArray[0];
}

template<typename ElemType, typename Comp>
void BinaryHeap<ElemType, Comp>::insert(const ElemType& elem)
{
	checkSize();
	int i = curSize++;
	elemArray[i] = elem;
	walkUp(i);
}

template<typename ElemType, typename Comp>
ElemType& BinaryHeap<ElemType, Comp>::removeMin()
{
	ElemType temp;
	temp = elemArray[0];
	elemArray[0] = elemArray[--curSize];
	walkDown(0);
	return temp;
}

template<typename ElemType, typename Comp>
void BinaryHeap<ElemType, Comp>::checkSize()
{
	if (curSize == capacity)
	{
		ElemType* oldArray = elemArray;
		getNewArray(2 * curSize);
		for (int i = 0; i < curSize; i++)
			elemArray[i] = oldArray[i];
		delete[] oldArray;
	}
}

template<typename ElemType, typename Comp>
void BinaryHeap<ElemType, Comp>::walkUp(int hole)
{
	while (comp(elemArray[hole], elemArray[(hole - 1) / 2]) < 0)
	{
		ElemType ItemTemp = elemArray[hole];
		elemArray[hole] = elemArray[(hole - 1) / 2];
		elemArray[(hole - 1) / 2] = ItemTemp;
		hole = (hole - 1) / 2;
	}
}

template<typename ElemType, typename Comp>
void BinaryHeap<ElemType, Comp>::walkDown(int hole)
{
	int child;
	for (; 2 * hole + 1<curSize; hole = child)
	{
		child = 2 * hole + 1;
		if (child != curSize - 1 && comp(elemArray[child], elemArray[child + 1]) > 0)
			child++;
		if (numCompare++, comp(elemArray[hole], elemArray[child]) > 0)
		{
			ElemType ItemTemp = elemArray[hole];
			elemArray[hole] = elemArray[child];
			elemArray[child] = ItemTemp;
		}
		else break;
	}
}








#pragma once
#include <fstream>
#include <string>
#include "BinaryHeap.h"

template<typename ElemType, typename KeyType, typename PQComp>
class BinaryHeapPQ
{
protected:
	typedef Item<ElemType, KeyType> Item;
	typedef Locator<Item> Locator;
private:
	BinaryHeap<Item, PQComp> bh;
	static const int DEF_SIZE = 9;
public:
	BinaryHeapPQ(int size = DEF_SIZE) : bh(size){}

	int getCompare() { return bh.getCompare(); }
	void insert(const KeyType& key, const ElemType& elem, Locator* loc) { bh.insert(Item(key, elem, loc)); }
	Locator* min() { return bh.findMin().getLoc(); }
	Item& removeMin() { return bh.removeMin(); }
	bool isEmpty() const { return bh.isEmpty(); }
	void decreaseKey(Locator* loc, int k) { loc->getItem()->setKey(k); bh.buildHeap(); }
	void showQueue() { bh.displayHeap(); }
};

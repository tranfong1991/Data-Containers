#pragma once
#include <stdio.h>
#include <iostream>

using namespace std;

template<typename ElemType>
class Locator;				//Class declaration

template<typename ElemType, typename KeyType>
class Item
{
protected:
	typedef Locator<Item<ElemType,KeyType>> Locator;
private:
	KeyType key;
	ElemType elem;
	int parentIndex;
	Locator* loc;
public:
	Item(const KeyType& k = KeyType(), const ElemType& e = ElemType(), Locator* l = NULL)
		: key(k), elem(e), loc(l), parentIndex(-1){}
	Item(const Item& i);

	KeyType getKey() const { return key; }
	int getParentIndex() const { return parentIndex; }
	ElemType getElem() const { return elem; }
	Locator* getLoc() const { return loc; }

	void setKey(const KeyType& k) { key = k; }
	void setParentIndex(int p){ parentIndex = p; }
	void setElem(const ElemType& e) { elem = e; }
	void setLoc(Item* i) { loc->setItem(i); }

	Item& operator=(const Item& i);
	friend ostream& operator<<(ostream& os, const Item& i);
};

template<typename ElemType, typename KeyType>
Item<ElemType, KeyType>::Item(const Item& i)
{
	key = i.key;
	elem = i.elem;
	parentIndex = i.parentIndex;
	loc = i.loc;
	loc->setItem(this);
}

template<typename ElemType, typename KeyType>
Item<ElemType, KeyType>& Item<ElemType, KeyType>::operator=(const Item& i)
{
	key = i.key;
	elem = i.elem;
	parentIndex = i.parentIndex;
	loc = i.loc;
	loc->setItem(this);
	return *this;
}

template<typename ElemType, typename KeyType>
ostream& operator<<(ostream& os, const Item<ElemType, KeyType>& i)
{
	os << "(" << i.key << "," << i.elem << ")";
	return os;
}

template<typename ElemType>
class Locator
{
	ElemType* item;
public:
	Locator(ElemType* i = NULL) : item(i){}

	ElemType* getItem() const { return item; }
	void setItem(ElemType* i) { item = i; }
};

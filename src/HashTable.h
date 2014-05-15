#include <stdio.h>
#include <iostream>

using namespace std;

class ElemNotFound{};

template<typename ElemType, typename KeyType>
class Pair
{
	ElemType elem;
	KeyType key;

	template<typename ElemType, typename KeyType, typename Hash>
	friend class HashTable;
public:
	Pair(const ElemType& e = ElemType(), const KeyType& k = KeyType())
		: elem(e), key(k){}
};

template<typename ElemType, typename KeyType, typename Hash>
class HashTable
{
protected:
	typedef Pair<ElemType, KeyType> Pair;
private:
	Pair** elemArray;
	Hash hash;
	int size;
	int capacity;

	void checkCap();
public:
	HashTable(int c = 10) : size(0), capacity(c){
		elemArray = new Pair*[capacity];
		for (int i = 0; i < capacity; ++i)
			elemArray[i] = NULL;
	}
	~HashTable(){ 
		for (int i = 0; i < capacity; ++i)
			delete elemArray[i];
		delete[] elemArray; 
	}
	HashTable(const HashTable& other);
	HashTable& operator=(const HashTable& other);

	bool isEmpty() const { return size == 0; }
	bool isEmptySlot(const KeyType& key) const { return elemArray[hash(key) % capacity] == NULL; }
	int getSize() const { return size; }
	void insert(const ElemType& elem, const KeyType& key);
	void remove(const KeyType& key);
	const ElemType& getElem(const KeyType& key) const { return isEmptySlot(key) ? ElemType() : elemArray[hash(key) % capacity]->elem; }
	ElemType& operator[](const KeyType& key);
	ElemType& emptySlot(const KeyType& key);		//only returns empty slot for modification
	void display();
};

template<typename ElemType, typename KeyType, typename Hash>
HashTable<ElemType, KeyType, Hash>::HashTable(const HashTable& other)
{
	capacity = other.capacity;
	size = other.size;
	hash = Hash();
	elemArray = new Pair*[capacity];
	for (int i = 0; i < capacity; ++i){
		if (other.elemArray[i] != NULL){
			elemArray[i] = new Pair(other.elemArray[i]->elem, other.elemArray[i]->key);
		}
		else elemArray[i] = NULL;
	}
}

template<typename ElemType, typename KeyType, typename Hash>
HashTable<ElemType, KeyType, Hash>& HashTable<ElemType, KeyType, Hash>::operator=(const HashTable& other)
{
	this->~HashTable();
	capacity = other.capacity;
	size = other.size;
	hash = Hash();
	elemArray = new Pair*[capacity];
	for (int i = 0; i < capacity; ++i){
		if (other.elemArray[i] != NULL){
			elemArray[i] = new Pair(other.elemArray[i]->elem, other.elemArray[i]->key);
		}
		else elemArray[i] = NULL;
	}
	return *this;
}

template<typename ElemType, typename KeyType, typename Hash>
void HashTable<ElemType, KeyType, Hash>::checkCap()
{
	if ((size + 1) > capacity)
	{
		Pair** oldArray = elemArray;
		capacity *= 2;
		elemArray = new Pair*[capacity];
		for (int i = 0; i < size; ++i)
			elemArray[i] = oldArray[i];
		for (int i = size; i < capacity; ++i)
			elemArray[i] = NULL;
		delete[] oldArray;
	}
}

template<typename ElemType, typename KeyType, typename Hash>
void HashTable<ElemType, KeyType, Hash>::insert(const ElemType& elem, const KeyType& key)
{
	checkCap();
	for (int i = hash(key) % capacity;; i++){
		if (i == capacity) i = 0;
		if (elemArray[i] == NULL){
			elemArray[i] = new Pair(elem, key);
			size++;
			return;
		}
	}
}

template<typename ElemType, typename KeyType, typename Hash>
void HashTable<ElemType, KeyType, Hash>::remove(const KeyType& key)
{
	int i = hash(key) % capacity;
	if (i < 0 || i >= capacity) throw ElemNotFound();
	while (i < capacity){
		if (key == elemArray[i]->key){
			delete elemArray[i];
			elemArray[i] = NULL;
			size--;
			return;
		}
		i++;
	}
	throw ElemNotFound();
}

template<typename ElemType, typename KeyType, typename Hash>
ElemType& HashTable<ElemType, KeyType, Hash>::operator[](const KeyType& key)
{
	int newIndex = hash(key) % capacity;
	int oldIndex = newIndex;
	if (newIndex < 0 || newIndex >= capacity) throw ElemNotFound();
	do
	{
		if (elemArray[newIndex] != NULL)
		if (key == elemArray[newIndex]->key)
			return elemArray[newIndex]->elem;
		if (newIndex + 1 < capacity) newIndex++;
		else newIndex = 0;
	} while (newIndex != oldIndex);	//See if it checks all elements in a circle
	throw ElemNotFound();
}

template<typename ElemType, typename KeyType, typename Hash>
ElemType& HashTable<ElemType, KeyType, Hash>::emptySlot(const KeyType& key)
{
	int newIndex = hash(key) % capacity;
	int	oldIndex = newIndex;
	if (newIndex < 0 || newIndex >= capacity) throw ElemNotFound();
	do
	{
		if (elemArray[newIndex] == NULL) {
			elemArray[newIndex] = new Pair();
			elemArray[newIndex]->key = key;
			return elemArray[newIndex]->elem;
		}
		if (newIndex + 1 < capacity) newIndex++;
		else newIndex = 0;
	} while (newIndex != oldIndex);
}

template<typename ElemType, typename KeyType, typename Hash>
void HashTable<ElemType, KeyType, Hash>::display()
{
	for (int i = 0; i < capacity; i++){
		if (elemArray[i] != NULL)
			cout << i << ":" << endl
			<< elemArray[i]->elem
			<< endl << endl;
	}
}
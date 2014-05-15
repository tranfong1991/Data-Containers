#include<stdio.h>
#include<iostream>

using namespace std;

template<typename T>
class SinglyLinkedList;

template<typename T>
class SListNode
{
	T elem;
	SListNode* next;

	friend class SinglyLinkedList<T>;
public:
	SListNode(const T& e = T(), SListNode* n = NULL)
		:elem(e), next(n){}
	SListNode(){ delete next; }
};

template<typename T>
class SinglyLinkedList
{
	SListNode<T>* head;
public:
	SinglyLinkedList() :head(NULL){}
	~SinglyLinkedList(){ head->~SListNode(); }

	bool empty() const{ return head == NULL; }
	void insertFirst(const T& elem);
	void removeFirst();
	void display();
};

template<typename T>
void SinglyLinkedList<T>::insertFirst(const T& elem)
{
	SListNode<T>* newNode = new SListNode<T>(elem);
	if (empty()) head = newNode;
	else{
		newNode->next = head;
		head = newNode;
	}
}

template<typename T>
void SinglyLinkedList<T>::removeFirst()
{
	SListNode<T>* temp = head;
	head = temp->next;
	delete temp;
}

template<typename T>
void SinglyLinkedList<T>::display()
{
	SListNode<T>* iter = head;
	while (iter != NULL){
		cout << iter->elem << " ";
		iter = iter->next;
	}
	cout << endl;
}
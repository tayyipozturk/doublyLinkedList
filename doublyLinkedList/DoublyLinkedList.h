#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <iostream>
#include "Node.h"

template<class T>
class DoublyLinkedList {
public:
	DoublyLinkedList();
	DoublyLinkedList(const T arr[], int arrSize);
	DoublyLinkedList(const DoublyLinkedList<T>& obj);
	DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>& rhs);

	~DoublyLinkedList();

	void insertFront(const T& data);				//insert node as head
	void insertBack(const T& data);					//insert node as tail
	void insertSorted(const T& data);				//insert node in a ascending order list from head to tail

	void removeNode(Node<T>* node);					//remove node with specified adress
	void removeNode(const T& data);					//remove node with specified data
	void removeAllNodes();

	int getSize() const;							//returns size of the list
	bool isEmpty() const;							//returns true if list is empty
	bool contains(Node<T>* node) const;				//returns true if list contains node specified with adress
	bool contains(const T& data) const;				//returns true if list contains node with specified data

	Node<T>* getFront() const;						//returns a node pointer to head of list
	Node<T>* getBack() const;						//returns a node pointer to tail of list
	Node<T>* getNode(const T& data) const;			//returns a node pointer to specified data if exists, nullptr otherwise

	T* copyToArray() const;							//copies data in the nodes to an array and returns the addres of its first element

	void print() const;								//prints the content of list

private:
	Node<T>* head;
	Node<T>* tail;
	int size;
};

template<class T>
DoublyLinkedList<T>::DoublyLinkedList() {
	this->head = nullptr;
	this->tail = nullptr;
	this->size = 0;
}

template<class T>
DoublyLinkedList<T>::DoublyLinkedList(const T arr[], int arrSize) {
	this->head = nullptr;
	this->tail = nullptr;
	for (int i = 0; i < arrSize; i++) {
		insertBack(arr[i]);
	}
	size = arrSize;
}

template<class T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& obj) {
	*this = obj;
}

template<class T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& rhs) {
	Node<T>* r = rhs.head;
	removeAllNodes();
	while (r) {
		insertBack(r->data);
		r = r->next;
	}
	return *this;
}

template<class T>
DoublyLinkedList<T>::~DoublyLinkedList() {
	removeAllNodes();
}

template<class T>
void DoublyLinkedList<T>::insertFront(const T& data) {
	Node<T>* temp = new Node<T>(data, nullptr, head);
	if (!head) {
		head = tail = temp;
	}
	else {
		head->prev = temp;
		head = temp;
	}
	size++;
}

template<class T>
void DoublyLinkedList<T>::insertBack(const T& data) {
	Node<T>* temp = new Node<T>(data, tail, nullptr);
	if (!tail) {
		head = tail = temp;
	}
	else {
		tail->next = temp;
		tail = temp;
	}
	size++;
}

template<class T>
void DoublyLinkedList<T>::insertSorted(const T& data) {
	if (!head) {
		insertFront(data);
	}
	else if (data <= head->data) {
		insertFront(data);
	}
	else if (data >= tail->data) {
		insertBack(data);
	}
	else {
		Node<T>* temp = new typename Node<T>::Node();
		Node<T>* p = this->head;
		while (data > p->data) {			//find the proper location
			p = p->next;
		}
		temp->data = data;					//establish neighbor connections
		temp->prev = p->prev;
		temp->next = p;
		p->prev->next = temp;
		p->prev = temp;
		size++;
	}
}

template<class T>
void DoublyLinkedList<T>::removeNode(Node<T>* node) {
	if (node == head && node == tail) {		//if node is the only node in list
		delete node;
		head = tail = nullptr;
	}
	else if (node == head) {				//if node is head and not the only node in the list
		node->next->prev = nullptr;
		head = node->next;
		delete node;
	}
	else if (node == tail) {				//if node is tail and not the only node in the list
		node->prev->next = nullptr;
		tail = node->prev;
		delete node;
	}
	else if (node->next && node->prev) {	//base case
		node->prev->next = node->next;
		node->next->prev = node->prev;
		delete node;
	}
	size--;
}

template<class T>
void DoublyLinkedList<T>::removeNode(const T& data) {
	Node<T>* node = getNode(data);
	removeNode(node);
}

template<class T>
void DoublyLinkedList<T>::removeAllNodes() {
	Node<T>* temp, * p = this->head;
	while (p) {
		temp = p;
		p = p->next;
		delete temp;
	}
	this->head = nullptr;
	this->tail = nullptr;
	this->size = 0;
}

template<class T>
int DoublyLinkedList<T>::getSize() const {
	return size;
}

template<class T>
bool DoublyLinkedList<T>::isEmpty() const {
	return size == 0;
}

template<class T>
bool DoublyLinkedList<T>::contains(Node<T>* node) const {
	Node<T>* p = head;
	while (p) {
		if (p == node) {
			return true;
		}
		p = p->next;
	}
	return false;
}

template<class T>
bool DoublyLinkedList<T>::contains(const T& data) const {
	Node<T>* p = head;
	while (p) {
		if (p->data == data) {
			return true;
		}
		p = p->next;
	}
	return false;
}

template<class T>
Node<T>* DoublyLinkedList<T>::getFront() const {
	return this->head;
}

template<class T>
Node<T>* DoublyLinkedList<T>::getBack() const {
	return this->head;
}

template<class T>
Node<T>* DoublyLinkedList<T>::getNode(const T& data) const {
	Node<T>* p = this->head;
	while (p) {
		if (p->data == data) {
			return p;
		}
		p = p->next;
	}
	return nullptr;
}

template<class T>
T* DoublyLinkedList<T>::copyToArray() const {
	if (size == 0) {
		return nullptr;
	}
	Node<T>* p = head;
	T* arr = new T[size];
	for (int i = 0; i < size; i++) {
		arr[i] = p->data;
		p = p->next;
	}
	return arr;
}

template<class T>
void DoublyLinkedList<T>::print() const {
	std::cout << "Printing the doubly linked list ..." << std::endl;

	if (this->isEmpty()) {
		std::cout << "empty" << std::endl;
		return;
	}

	Node<T>* node = this->head;

	while (node) {
		std::cout << *node << std::endl;
		node = node->next;
	}
}

#endif // !DOUBLY_LINKED_LIST_H
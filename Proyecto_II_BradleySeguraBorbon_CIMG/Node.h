#pragma once
#include <iostream>
using namespace std;

template<typename T>
class Node {
private:
	T* data;
	Node<T>* next;
	Node<T>* previous;
public:
	Node(T* value) : data(value), next(nullptr), previous(nullptr) {}
	~Node() {
		delete data;
	}
	void setData(T* data) {
		this->data = data;
	}
	void setNext(Node<T>* next) {
		this->next = next;
	}
	void setPrev(Node<T>* prev) {
		this->previous = prev;
	}
	T* getData() {
		return data;
	}
	Node<T>* getNext() {
		return next;
	}
	Node<T>* getPrev() {
		return previous;
	}
}; 
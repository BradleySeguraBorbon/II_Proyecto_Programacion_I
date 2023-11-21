#pragma once
#include <iostream>
using namespace std;

template<typename T>
class Node {
public:
	T* data;
	Node<T>* next;
	Node<T>* previous;
	Node(T* value) : data(value), next(nullptr), previous(nullptr) {}
	~Node() {
		delete data;
	}
};
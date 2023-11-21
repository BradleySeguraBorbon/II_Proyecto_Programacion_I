#pragma once
#include <iostream>
#include "Node.h"
using namespace std;

template <typename T>
class List {
	Node<T>* head;
	Node<T>* back;
public:
	List() : head(nullptr), back(nullptr) {}
	~List() {}
	void pushBack(T* value) {
		Node<T>* newNode = new Node<T>(value);
		if (!head) {
			head = newNode;
			back = newNode;
			return;
		}
		back->next = newNode;
		newNode->previous = back;
		back = newNode;
	}
	void deleteElement(T* value) {
		if (!head)
			return;
		Node<T>* currentNode = head;
		if (currentNode->data == value) {
			head = currentNode->next;
			if (head)
				head->previous = nullptr;
			else 
				back = nullptr; 
			delete currentNode;
		}
		else {
			while (currentNode) {
				if (currentNode->data == value) {
					currentNode->previous->next = currentNode->next;
					if (currentNode->next) 
						currentNode->next->previous = currentNode->previous;
					else {
						back = currentNode->previous;
						back->next = nullptr;
					}
					delete currentNode;
					return;
				}
				currentNode = currentNode->next;
			}
		}
	}
	void clean() {
		Node<T>* currentNode = head;
		while (currentNode) {
			head = head->next;
			delete currentNode;
			currentNode = head;
		}
	}
	T* getFirstElement() {
		return head->data;
	}
	T* getLastElement() {
		return back->data;
	}
	Node<T>* getHeadNode() {
		return head;
	}
	Node<T>* getBackNode() {
		return back;
	}
	void toString() {
		Node<T>* currentNode = head;
		while (currentNode) {
			currentNode->data->toString();
			currentNode = currentNode->next;
		}
	}
	int getSize() {
		int size = 0;
		Node<T>* currentNode = head;
		while (currentNode) {
			size++;
			currentNode = currentNode->next;
		}
		return size;
	}
};

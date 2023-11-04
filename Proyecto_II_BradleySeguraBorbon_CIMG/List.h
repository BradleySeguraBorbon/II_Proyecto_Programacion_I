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
		}
		else {
			while (currentNode) {
				if (currentNode->data == value) {
					currentNode->previous->next = currentNode->next;
					if (currentNode->next) currentNode->next->previous = currentNode->previous;
					else back = currentNode->previous;
				}
				currentNode = currentNode->next;
			}
		}
		delete currentNode;

		/*
		Node<T>* deletingNode = nullptr;
		if (value == head->data) {
			deletingNode = head;
			if (head->next) {
				head = head->next;
				head->previous = nullptr;
			}
			delete deletingNode;
			return;
		}
		Node<T>* currentNode = head;
		while (currentNode) {
			if (currentNode->data == value) {
				deletingNode = currentNode;
				currentNode->previous->next = currentNode->next;
				if(currentNode->next)
					currentNode->next->previous = currentNode->previous;
				delete currentNode;
				return;
			}
			currentNode = currentNode->next;
		}*/

		//optimizar
	}
	void show() {
		Node<T>* currentNode = head;
		cout << endl << endl;
		while (currentNode) {
			cout << currentNode->data << " ";
			currentNode = currentNode->next;
		}
		cout << endl << endl;
	}
	T operator[](int position) {
		Node<T>* currentNode = head;
		int currentPosition = 0;
		while (currentNode) {
			if (currentPosition == position)
				return currentNode->data;
			currentNode = currentNode->next;
			currentPosition++;
		}
		return -1;
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
};

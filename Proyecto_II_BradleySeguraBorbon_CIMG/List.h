#pragma once
#include <iostream>
#include "Node.h"
using namespace std;

template <typename T>
class List {
	Node<T>* head;
	Node<T>* back;
	int size;

public:
	List() : head(nullptr), back(nullptr) {}
	~List() {
		clean();
	}
	void pushBack(T* value) {
		Node<T>* newNode = new Node<T>(value);
		if (!head) {
			head = newNode;
			back = newNode;
			size++;
			return;
		}
		back->setNext(newNode);
		newNode->setPrev(back);
		back = newNode;
		size++;
	}
	void deleteElement(T* value) {
		if (!head)
			return;
		Node<T>* currentNode = head;
		if (currentNode->getData() == value) {
			head = currentNode->getNext();
			if (head)
				head->setPrev(nullptr);
			else 
				back = nullptr; 
			delete currentNode;
			size--;
		}
		else {
			while (currentNode) {
				if (currentNode->getData() == value) {
					currentNode->getPrev()->setNext(currentNode->getNext());
					if (currentNode->getNext())
						currentNode->getNext()->setPrev(currentNode->getPrev());
					else {
						back = currentNode->getPrev();
						back->setNext(nullptr);
					}
					delete currentNode;
					size--;
					return;
				}
				currentNode = currentNode->getNext();
			}
		}
	}
	void clean() {
		Node<T>* currentNode = head;
		while (currentNode) {
			head = head->getNext();
			delete currentNode;
			currentNode = head;
		}
		back = nullptr;
		size = 0;
	}
	T* getFirstElement() {
		return head->getData();
	}
	T* getLastElement() {
		return back->getData();
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
			currentNode->getData()->toString();
			currentNode = currentNode->getNext();
		}
	}
	int getSize() {
		return size;
	}
};

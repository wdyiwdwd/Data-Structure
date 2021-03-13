#pragma once
#include <iostream>
#include <stdexcept>
#include <sstream>
#include "Stack.h"
#include "chainNode.h"
using namespace std;

template <class T>
class linkedStack : public Stack<T>
{
public:
	linkedStack(int initialCapacity = 10){
		stackSize = 0;
		stackTop = NULL;
	}
	~linkedStack(){
		while (stackTop != NULL){
			chainNode<T>* nextNode = stackTop->next;
			delete stackTop;
			stackTop = nextNode;
		}
	}
	bool empty() const{
		return this->stackSize == 0;
	}
	int size() const{
		return this->stackSize;
	}
	T& top(){
		if (stackSize == 0){
			throw out_of_range("must not be 0");
		}
		return stackTop->element;
	}
	void pop(){
		if (this->stackSize == 0){
			throw out_of_range("must not be 0");
		}
		chainNode<T>* nextNode = stackTop->next;
		delete stackTop;
		stackTop = nextNode;
		stackSize--;
	}
	void push(const T& theElement){
		stackTop = new chainNode<T>(theElement,stackTop);
		stackSize++;
	}

private:
	chainNode<T>* stackTop;
	int stackSize;
};

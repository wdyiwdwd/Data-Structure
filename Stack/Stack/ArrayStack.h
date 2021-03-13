#pragma once
#include <iostream>
#include <stdexcept>
#include <sstream>
#include "Stack.h"
using namespace std;

template <class T>
class arrayStack : public Stack<T>
{
public:
	arrayStack(int initialCapacity=10);
	~arrayStack(){
		delete[] stack;
	}
	bool empty() const{
		return this->arrayLenghth == 0;
	}
	int size() const{
		return this->arrayLenghth;
	}
	T& top(){
		if (stackTop == 1){
			throw out_of_range();
		}
		return stack[stackTop];
	}
	void pop(){
		if (stackTop == -1){
			throw  out_of_range();
		}
		stack[stackTop--].~T();
	}
	void push(const T& theElement);

private:
	int stackTop;   //栈顶
	int arrayLenghth;  //栈的大小
	T* stack;
};

template <class T>
arrayStack<T>::arrayStack(int initialCapacity)
{
	if (initialCapacity < 1){
		stringstream ss;
		ss << "Initial capacity must > 0";
		throw invalid_argument(ss.str());
	}
	arrayLenghth = initialCapacity;
	stack = new T[arrayLenghth];
	stackTop = -1;
}

template <class T>
void arrayStack<T>::push(const T& theElement)
{
	if (stackTop == arrayLenghth - 1){
		//空间已满 加倍空间
		T* _stack = new T[arrayLenghth * 2];
		copy(stack, stack+arrayLenghth, _stack);
		delete[] stack;
		stack = _stack;
		arrayLenghth *= 2;
	}
	stack[++stackTop] = theElement;
}

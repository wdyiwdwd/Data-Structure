#pragma once
#include<iostream>
using namespace std;

template <class T>
class Stack
{
public:
	virtual ~Stack(){}
	//返回是否为空
	virtual bool empty() const = 0;
	//返回栈的大小
	virtual int size() const = 0;
	//返回栈顶元素
	virtual T& top() = 0;
	//删除栈顶元素
	virtual void pop() = 0;
	//将元素推入栈中
	virtual void push(const T& theElement) = 0;

};

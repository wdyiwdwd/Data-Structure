#pragma once
#include<iostream>
using namespace std;

template <class T>
class Stack
{
public:
	virtual ~Stack(){}
	//�����Ƿ�Ϊ��
	virtual bool empty() const = 0;
	//����ջ�Ĵ�С
	virtual int size() const = 0;
	//����ջ��Ԫ��
	virtual T& top() = 0;
	//ɾ��ջ��Ԫ��
	virtual void pop() = 0;
	//��Ԫ������ջ��
	virtual void push(const T& theElement) = 0;

};

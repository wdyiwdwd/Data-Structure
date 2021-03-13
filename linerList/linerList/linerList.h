#pragma once
#include <iostream>
using namespace std;
template <class T>
class linerList
{
public:
	virtual ~linerList(){};
	//查看线性表是否为空
	virtual bool empty() const = 0;
	//返回线性表的大小
	virtual int size() const = 0;
	//返回第n个值
	virtual T& get(int theIndex) const = 0;
	//返回某个元素第一次出现时的所隐瞒
	virtual int indexof(const T& theElement) const = 0;
	//删除某个元素
	virtual void erase(int theIndex) = 0;
	//插入元素
	virtual void insert(int theIndex, const T& theElement) = 0;
};


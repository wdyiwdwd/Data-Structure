#pragma once
#include "linerList.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
using namespace std;
template <class T>
class arrayList :public linerList<T>
{
public:
	arrayList(int initialCapacity = 10){
		if (initialCapacity < 1){
			ostringstream s;
			s << "Must > 0 !";
			throw  invalid_argument(s.str());
		}
		arrayLength = initialCapacity;
		element = new T[arrayLength];
		listSize = 0;
	}
	arrayList(const arrayList<T>&){
		arrayLength = theList.arrayLength;
		listSize = theList.listSize;
		element = new T[arrayLength];
		//这个copy函数貌似是自带的！
		copy(theList.element, theList.element + listSize, element);
	}
	~arrayList(){
		delete[] element;
	}
	//ADT
	bool empty() const{
		return listSize == 0;
	}
	int size() const{
		return listSize;
	}
	T& get(int theIndex) const{
		checkIndex(theIndex);
		return element[theIndex];
	}
	int indexof(const T& theElement) const{
		//查找元素，用自带的find(),返回找到的那个地址，减去原地址
		int theIndex = (int)(find(element, element + listSize, theElement) - element);
		if (theIndex == listSize){
			return -1;  //没找到返回-1
		}
		else return theIndex;
	}
	void erase(int theIndex){
		checkIndex(theIndex);
		//索引有效，则后面所有东西向前挪一位
		copy(element + theIndex + 1, element + listSize, element + theIndex);
		if (listSize < arrayLength / 4){
			if (arrayLength / 2>100){
				arrayLength /= 2;
			}
			else{
				arrayLength = 100;
			}
			T* element2 = new T[arrayLength];
			copy(element, element + listSize, element2);
			delete[] element;
			element = element2;
		}
		element[--listSize].~T();
	}
	void insert(int theIndex, const T& theElement){
		if (theIndex<0 || theIndex>listSize){
			ostringstream s;
			s << "theIndex error";
			throw out_of_range(s.str());
		}
		//查看元素是否满了
		if (listSize == arrayLength){
			T* element2 = new T[arrayLength * 2];
			copy(element, element + listSize, element2);
			delete[] element;
			element = element2;
			arrayLength *= 2;
		}
		//向右移动一个位置
		copy_backward(element + theIndex, element + listSize, element + theIndex + 1);
		element[theIndex] = theElement;
		listSize++;
	}
	friend ostream& operator << (ostream& out,const arrayList<T>& arraylist){
		for (int i = 0; i < arraylist.listSize; i++){
			out << arraylist.element[i] << " ";
		}
		return out;
	}
	//其他方法
	int capacity() const {
		return arrayLength;
	}

	class iterator
	{
	public:
		typedef bidirectional_iterator_tag iterator_categroy;
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef T* pointer;
		typedef T& reference;

		//构造
		iterator(T* thePosition){
			position = thePosition;
		}
		T& operator*() const{
			return *position;
		}
		T* operator ->() const{
			return &*position;
		}
		iterator& operator ++(){
			++position;
			return *this;
		}
		iterator operator ++(int){
			iterator old = *this;
			++position;
			return old;
		}
		iterator& operator--(){
			--position;
			return *this;
		}
		iterator operator --(int){
			iterator old = *this;
			--position;
			return old;
		}
		bool operator !=(const iterator right) const{
			return position != right.position;
		}
		bool operator ==(const iterator right) const{
			return position == right.position;
		}
	protected:
		T* position;
	};
	iterator begin(){
		return iterator(this->element);
	}
	iterator end(){
		return iterator(this->element + this->listSize);
	}
protected:
	void checkIndex(int theIndex) const{
		if (theIndex < 0 || theIndex >= listSize){
			ostringstream s;
			s << "index error!";
			throw out_of_range(s.str());
		}
	}
	T* element;
	int arrayLength; //数组长度
	int listSize;  //元素个数
};


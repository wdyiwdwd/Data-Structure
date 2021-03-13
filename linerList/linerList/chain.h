#pragma once
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "chainNode.h"
#include "linerList.h"
using namespace std;
template <class T>
class chain : public linerList<T>
{
public:
	chain(int initialCapacity = 10){
		if (initialCapacity < 1){
			ostringstream s;
			s << "Must > 0 !";
			throw invalid_argument(s.str());
		}
		firstNode = NULL;
		listSize = 0;
	}
	chain(const chain<T>&){
		this->listSize = theList.listSize;
		if (theList.listSize == 0){
			//链表为空
			this->firstNode = NULL;
			return;
		}
		//链表非空
		//复制目标链表的每一个节点
		chainNode<T>* sourceNode = theList.firstNode;
		//复制首元素
		this->firstNode = new chainNode<T>(sourceNode->element);
		sourceNode = sourceNode->next;
		//当前链表*this的最后一个节点
		chainNode<T>* targetNode = this->firstNode;
		while (souceNode != Null){
			//复制剩余元素
			targetNode->next = new chainNode<T>(sourceNode->element);
			targetNode = targetNode->next;
			sourceNode = sourceNode->next;
		}
		targetNode->next = NULL;
	}
	~chain(){
		while (this->firstNode != NULL){
			chainNode<T>* nextNode = this->firstNode->next;
			delete this->firstNode;
			this->firstNode = nextNode;
		}
	}
	//ADT
	bool empty() const {
		return listSize == 0;
	}
	int size() const {
		return listSize;
	}
	T& get(int theIndex) const{
		this->checkIndex(theIndex);
		//移向所需节点
		chainNode<T>* currentNode = this->firstNode;
		for (int i = 0; i < theIndex; i++){
			currentNode = currentNode->next;
		}
		return currentNode->element;
	}
	int indexof(const T& theElement) const{
		chainNode<T>* currentNode = this->firstNode;
		int index = 0;
		while (currentNode != NULL && currentNode->element != theElement){
			currentNode = currentNode->next;
			index++;
		}
		if (currentNode == NULL){
			//没有找到返回-1
			return -1;
		}
		else{
			return index;
		}
	}
	void erase(int theIndex){
		this->checkIndex(theIndex);
		chainNode<T>* deleteNode;
		if (theIndex == 0){
			deleteNode = this->firstNode;
			this->firstNode = this->firstNode->next;
		}
		else{
			//用指针p之乡删除节点的前驱结点
			chainNode<T>* p = this->firstNode;
			for (int i = 0; i < theIndex - 1; i++){
				p = p->next;
			}
			deleteNode = p->next;
			p->next = p->next->next;
		}
		this->listSize--;
		delete deleteNode;
	}
	void insert(int theIndex, const T& theElement){
		if (theIndex<0 || theIndex>this->listSize){
			//无效索引
			ostringstream s;
			s << "index error";
			throw out_of_range(s.str());
		}
		if (theIndex == 0){
			this->firstNode = new chainNode<T>(theElement, this->firstNode);
		}
		else{
			//寻找新元素的前驱
			chainNode<T>* p = this->firstNode;
			for (int i = 0; i < theIndex - 1; i++){
				p = p->next;
			}
			p->next = new chainNode<T>(theElement, p->next);
		}
		this->listSize++;
	}
	friend ostream& operator << (ostream& out, chain<T>& linklist){
		//按顺序输出p
		chainNode<T>* p = linklist.firstNode;
		while (p != NULL){
			out << p->element << " ";
			p = p->next;
		}
		return out;
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
		iterator(chainNode<T>* theNode = null){
			node = theNode;
		}
		T& operator*() const{
			return node->element;
		}
		T* operator ->() const{
			return &(node->element);
		}
		iterator& operator ++(){
			node = node->next;
			return *this;
		}
		iterator operator ++(int){
			iterator old = *this;
			node = node->next;
			return old;
		}
		bool operator !=(const iterator right) const{
			return node != right.node;
		}
		bool operator ==(const iterator right) const{
			return node == right.node;
		}

	protected:
		chainNode<T>* node;
	};
	iterator begin(){
		return iterator(this->firstNode);
	}
	iterator end(){
		return iterator(NULL);
	}
protected:
	//若索引无效抛出异常
	void checkIndex(int theIndex) const{
		if (theIndex < 0 || theIndex >= listSize){
			ostringstream s;
			s << "index error!";
			throw out_of_range(s.str());
		}
	}
	//指向链表第一个节点的指针
	chainNode<T>* firstNode;
	int listSize;
};


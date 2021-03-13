#include <iostream>
#include <stdexcept>
#include "queue.h"
using namespace std;

template <class T>
class arrayQueue : public queue
{
public:
	arrayQueue(int initialCapacity = 10);
	arrayQueue(const arrayQueue<T>&);
	~arrayQueue(){
		delete[] queue;
	}
	bool empty() const{
		return theFront == theBack;
	}
	int size() const{
		return theBack - theFront;
	}
	T& front() const{
		if (empty()){
			throw invalid_argument();
		}
		return queue[theFront];
	}
	T& back() const{
		if (empty()){
			throw invalid_argument();
		}
		return queue[theBack];
	}
	void push(const T& theElement);
	void pop();
private:
	int arrayLength;
	int theFront;
	int theBack;
	T* queue;
};

template <class T>
arrayQueue<T>::arrayQueue(int initialCapacity)
{
	arrayLength = initialCapacity;
	queue = new T[arrayLength];
	theFront = 0;
	theBack = 0;
}

template <class T>
arrayQueue<T>::arrayQueue(const arrayQueue<T>& m)
{
	queue = new T[m.arrayLength];
	theFront =0;
	theBack = m.theBack-m.theFront;
	//没有形成环
	if (theFront>theBack){
		for (int i = theFront + 1, j = 0; i < m.arrayLength; i++, j++){
			queue[j] = m.queue[i];
		}
		for (int i = 0, j = arrayLength - theFront; i < theBack + 1; i++, j++){
			queue[j] = m.queue[i];
		}
	}
	else{
		for (int i = theFront+1, j = 0; i <= m.size(); i++, j++){
			queue[j] = m.queue[i];
		}
	}
}

template <class T>
void arrayQueue<T>::pop()
{
	if (empty()){
		throw invalid_argument();
	}
	theFront = (theFront + 1) % arrayLength;
	queue[theFront].T()~;
}

template <class T>
void arrayQueue<T>::push(const T& theElement)
{
	//如果需要增加数组长度
	if ((theBack + 1) % arrayLength == theFront){
		T* newQueue = new T[2 * arrayLength];
		int start = (theFront + 1) % arrayLength;
		//没有形成环
		if (start < 2){
			for (int i = start, j = 0; i < start + arrayLength; i++,j++){
				newQueue[j] = queue[i]
			}
		}
		//形成队列环
		else{
			for (int i = start, j = 0; i < start + arrayLength; i++, j++){
				newQueue[j] = queue[i];
			}
			for (int i = 0, j = arrayLength - start; i < theBack + 1; i++, j++){
				newQueue[j] = queue[i];
			}
		}
		theFront = 2 * arrayLength - 1;
		theBack = arrayLength - 2;
		arrayLength *= 2;
		delete[] queue;
		queue = newQueue;
	}
	//把元素插入尾部
	theBack = (theBack + 1) % arrayLength;
	queue[theBack] = theElement;
}
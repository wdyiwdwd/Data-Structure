#include <iostream>
#include <stdexcept>
using namespace std;

template <class T>
class doubleQueue
{
	friend ostream& operator <<(ostream& out, doubleQueue<T>& q){
		if (q.isEmpty()){
			out << ' ' << endl;
			return out;
		}
		for (int i = q.theFront + 1 ; i < q.theFront + q.size() + 1; i++){
			out << q.queue[i%q.arrayLength] << " ";
		}
		out << endl;
		return out;
	}
public:
	doubleQueue(int initialCapacity = 10);
	doubleQueue(const doubleQueue<T>&);
	~doubleQueue(){
		delete[] queue;
	}
	bool isEmpty() const{
		return theFront == theBack;
	}
	bool isFull() const{
		return (theBack + 1) % arrayLength == theFront;
	}
	int size() const{
		if (theBack > theFront)
			return theBack - theFront;
		else
			return theBack + arrayLength - theFront;
	}
	T& front() const{
		if (isEmpty()){
			throw invalid_argument("front error");
		}
		return queue[theFront + 1];
	}
	T& back() const{
		if (isEmpty()){
			throw invalid_argument("back error");
		}
		return queue[theBack];
	}
	void addRight(const T& theElement);
	void addLeft(const T& theElement);
	void deleteLeft();
	void deleteRight();
private:
	int arrayLength;
	int theFront;
	int theBack;
	T* queue;
};

template <class T>
doubleQueue<T>::doubleQueue(int initialCapacity)
{
	arrayLength = initialCapacity;
	queue = new T[arrayLength];
	theFront = 0;
	theBack = 0;
}

template <class T>
doubleQueue<T>::doubleQueue(const doubleQueue<T>& m)
{
	queue = new T[m.arrayLength];
	theFront = m.theFront;
	theBack = m.theBack;
	arrayLength = m.arrayLength;
	for (int i = 0; i < m.arrayLength; i++){
		queue[i] = m.queue[i];
	}
}

template <class T>
void doubleQueue<T>::deleteLeft()
{
	if (isEmpty()){
		throw invalid_argument("deleteLeft error");
	}
	theFront = (theFront + 1) % arrayLength;
	queue[theFront].~T();
}

template <class T>
void doubleQueue<T>::deleteRight()
{
	if (isEmpty()){
		throw invalid_argument("deleteRight error");
	}
	queue[theBack].~T();
	theBack = (theBack - 1);
	if (theBack < 0){
		theBack += arrayLength;
	}
}

template <class T>
void doubleQueue<T>::addRight(const T& theElement)
{
	//如果需要增加数组长度
	if (isFull()){
		T* newQueue = new T[2 * arrayLength];
		int start = (theFront + 1) % arrayLength;
		//没有形成环
		if (start < 2){
			for (int i = start, j = 0; j < arrayLength ; i++, j++){
				newQueue[j] = queue[i];
			}
		}
		//形成队列环
		else{
			for (int i = start, j = 0; i < arrayLength; i++, j++){
				newQueue[j] = queue[i];
			}
			for (int i = 0, j = arrayLength - start ; i < theBack + 1; i++, j++){
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

template <class T>
void doubleQueue<T>::addLeft(const T& theElement)
{
	//如果需要增加数组长度
	if (isFull()){
		T* newQueue = new T[2 * arrayLength];
		int start = (theFront + 1) % arrayLength;
		//没有形成环
		if (start < 2){
			for (int i = start, j = 0; j < arrayLength; i++, j++){
				newQueue[j] = queue[i];
			}
		}
		//形成队列环
		else{
			for (int i = start, j = 0; i < arrayLength; i++, j++){
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
	queue[theFront] = theElement;
	theFront = (theFront - 1);
	if (theFront < 0){
		theFront += arrayLength;
	}
}
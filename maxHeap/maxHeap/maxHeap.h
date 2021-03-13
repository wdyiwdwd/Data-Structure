#pragma once
#include <iostream>
#include <stdexcept>
using namespace std;

template <class T>
class maxHeap
{
public:
	maxHeap(const int initialCapacity = 10){
		heap = new T[initialCapacity];
		arrayLength = initialCapacity;
		heapSize = 0;
	}
	~maxHeap(){
		delete[] heap;
	}
	bool empty() const{
		return heapSize == 0;
	}
	int size() const{
		return heapSize;
	}
	const T& top(){
		return heap[0];
	}
	void push(const T& theElement);
	void pop();
	//初始化一个堆，在[1:theSize]中建立一个堆
	void initialize(T* theHeap, int theSize);
	//保留传入队中的数组 核心思想是 heap不在指向initialize中传入的数组啦~
	void deactivateArray(){
		heap = new T[1];
	}
private:
	T* heap;
	int heapSize;
	int arrayLength;
};

template <class T>
void maxHeap<T>::push(const T& theElement)
{
	//必要时增加数组长度
	if (heapSize == arrayLength - 1){
		arrayLength = arrayLength * 2;
		T* newHeap = new T[arrayLength];
		for (int i = 0; i < arrayLength / 2; i++){
			newHeap[i] = heap[i];
		}
		delete heap;
		heap = newHeap;
	}
	//为元素theElement寻找插入位置
	//currentNode从子叶向上移动
	int currentNode = heapSize++;
	while (currentNode != 0 && heap[(currentNode - 1) / 2] < theElement){
		//不能把元素插到heap[currentNode]
		heap[currentNode] = heap[(currentNode - 1) / 2];
		currentNode = (currentNode - 1) / 2;
	}
	//插到合适的位置
	heap[currentNode] = theElement;
}

template <class T>
void maxHeap<T>::pop()
{
	//如果堆为空则抛出异常
	if (heapSize == 0){
		throw invalid_argument("pop error");
	}
	//删除最大元素
	heap[0].~T();
	//把最后一个元素记录起来
	T theLastElement = heap[--heapSize];
	//从根开始 为最后一个元素找位置
	int currentNode = 0;
	//currentNode的儿子
	int child = 1;
	while (child < heapSize){
		//找两个孩子中较大的一个
		if (child < heapSize - 1 && heap[child] < heap[child + 1]){
			child++;
		}
		//是否可以把theLastElement放在这个currentNode里面
		if (theLastElement >= heap[child]){
			//可以
			break; 
		}
		//不可以
		//大儿子赋值给当前结点
		heap[currentNode] = heap[child];
		//把currentNode向他的大儿子移动
		currentNode = child;
		//把child向下一层移动
		child = 2 * child + 1;
	}
	//把theLastElemnet赋值哥currentNode
	heap[currentNode] = theLastElement;
}

template <class T>
void maxHeap<T>::initialize(T* theHeap, int theSize)
{
	//删除原来的堆
	delete[] heap;
	heap = theHeap;
	heapSize = theSize;
	//堆化
	for (int root = heapSize / 2 - 1; root >= 0; root--){
		T rootElement = heap[root];
		//为元素rootElemnet寻找位置
		int child = root * 2 + 1;
		while (child < heapSize){
			//找出大儿子
			if (child < heapSize - 1 && heap[child] < heap[child + 1]){
				child++;
			}
			//可以把rootElement放在（child-1)/2的位置上吗
			if (rootElement >= heap[child]){
				//可以
				break;
			}
			//不可以 把大儿子放在（child-1)/2的位置上 然后child*2+1 循环
			heap[(child - 1) / 2] = heap[child];
			child = child * 2 + 1;
		}
		//赋值
		heap[(child - 1) / 2] = rootElement;
	}
}
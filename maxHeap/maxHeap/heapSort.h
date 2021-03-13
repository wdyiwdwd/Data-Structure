#pragma once
#include "maxHeap.h"
using namespace std;
template <class T>
void heapSort(T* theArray, int size)
{
	//给数组theArray[0:size-1]进行排序
	maxHeap<T> theHeap;
	//初始化成堆
	theHeap.initialize(theArray, size);
	//逐个从大根堆上提取首元素
	for (int i = size - 2; i >= 0; i--){
		T theElement = theHeap.top();
		theHeap.pop();
		theArray[i + 1] = theElement;
	}
	//别析构,保存数组
	theHeap.deactivateArray();
}
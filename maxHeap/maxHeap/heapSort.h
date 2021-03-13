#pragma once
#include "maxHeap.h"
using namespace std;
template <class T>
void heapSort(T* theArray, int size)
{
	//������theArray[0:size-1]��������
	maxHeap<T> theHeap;
	//��ʼ���ɶ�
	theHeap.initialize(theArray, size);
	//����Ӵ��������ȡ��Ԫ��
	for (int i = size - 2; i >= 0; i--){
		T theElement = theHeap.top();
		theHeap.pop();
		theArray[i + 1] = theElement;
	}
	//������,��������
	theHeap.deactivateArray();
}
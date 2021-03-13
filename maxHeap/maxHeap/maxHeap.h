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
	//��ʼ��һ���ѣ���[1:theSize]�н���һ����
	void initialize(T* theHeap, int theSize);
	//����������е����� ����˼���� heap����ָ��initialize�д����������~
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
	//��Ҫʱ�������鳤��
	if (heapSize == arrayLength - 1){
		arrayLength = arrayLength * 2;
		T* newHeap = new T[arrayLength];
		for (int i = 0; i < arrayLength / 2; i++){
			newHeap[i] = heap[i];
		}
		delete heap;
		heap = newHeap;
	}
	//ΪԪ��theElementѰ�Ҳ���λ��
	//currentNode����Ҷ�����ƶ�
	int currentNode = heapSize++;
	while (currentNode != 0 && heap[(currentNode - 1) / 2] < theElement){
		//���ܰ�Ԫ�ز嵽heap[currentNode]
		heap[currentNode] = heap[(currentNode - 1) / 2];
		currentNode = (currentNode - 1) / 2;
	}
	//�嵽���ʵ�λ��
	heap[currentNode] = theElement;
}

template <class T>
void maxHeap<T>::pop()
{
	//�����Ϊ�����׳��쳣
	if (heapSize == 0){
		throw invalid_argument("pop error");
	}
	//ɾ�����Ԫ��
	heap[0].~T();
	//�����һ��Ԫ�ؼ�¼����
	T theLastElement = heap[--heapSize];
	//�Ӹ���ʼ Ϊ���һ��Ԫ����λ��
	int currentNode = 0;
	//currentNode�Ķ���
	int child = 1;
	while (child < heapSize){
		//�����������нϴ��һ��
		if (child < heapSize - 1 && heap[child] < heap[child + 1]){
			child++;
		}
		//�Ƿ���԰�theLastElement�������currentNode����
		if (theLastElement >= heap[child]){
			//����
			break; 
		}
		//������
		//����Ӹ�ֵ����ǰ���
		heap[currentNode] = heap[child];
		//��currentNode�����Ĵ�����ƶ�
		currentNode = child;
		//��child����һ���ƶ�
		child = 2 * child + 1;
	}
	//��theLastElemnet��ֵ��currentNode
	heap[currentNode] = theLastElement;
}

template <class T>
void maxHeap<T>::initialize(T* theHeap, int theSize)
{
	//ɾ��ԭ���Ķ�
	delete[] heap;
	heap = theHeap;
	heapSize = theSize;
	//�ѻ�
	for (int root = heapSize / 2 - 1; root >= 0; root--){
		T rootElement = heap[root];
		//ΪԪ��rootElemnetѰ��λ��
		int child = root * 2 + 1;
		while (child < heapSize){
			//�ҳ������
			if (child < heapSize - 1 && heap[child] < heap[child + 1]){
				child++;
			}
			//���԰�rootElement���ڣ�child-1)/2��λ������
			if (rootElement >= heap[child]){
				//����
				break;
			}
			//������ �Ѵ���ӷ��ڣ�child-1)/2��λ���� Ȼ��child*2+1 ѭ��
			heap[(child - 1) / 2] = heap[child];
			child = child * 2 + 1;
		}
		//��ֵ
		heap[(child - 1) / 2] = rootElement;
	}
}
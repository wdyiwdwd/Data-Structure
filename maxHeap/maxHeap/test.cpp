#include <iostream>
#include <cstdlib>
#include <time.h>
#include "heapSort.h"
#include "maxHeap.h"
using namespace std;
int main()
{
	srand(time(0));
	int a[20];
	for (int i = 0; i < 20; i++){
		a[i] = rand() % 100;
	}
	maxHeap<int> heap;
	heap.initialize(a, 20);
	heap.push(5);
	heap.push(100);
	for (int i = 0; i < 22; i++){
		cout << a[i] << " ";
	}
	cout << endl;
	heapSort<int>(a, 22);
	for (int i = 0; i < 22; i++){
		cout << a[i] <<  " ";
	}
	system("pause");
	return 0;
}
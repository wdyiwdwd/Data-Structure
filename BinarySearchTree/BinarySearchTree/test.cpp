#include <iostream>
#include "binarySearchTree.h"
#include "AVLTree.h"
int main()
{
	myPair<int, char> p2(35, 'b');
	myPair<int, char> p1(26, 'a');
	myPair<int, char> p3(27, 'c');
	myPair<int, char> p4(28, 'd');
	myPair<int, char> p5(29, 'e');
	myPair<int, char> p6(30, 'f');
	myPair<int, char> p7(31, 'g');
	myPair<int, char> p8(32, 'h');
	myPair<int, char> p9(33, 'i');
	myPair<int, char> p0(34, 'g');
	//binarySearchTree<int, char> a;
	AVLTree<int, char> a;
	a.insert(p1);
	a.insert(p2);
	a.insert(p3);
	a.insert(p4);
	a.insert(p5);
	a.insert(p6);
	a.insert(p7);
	a.insert(p8);
	a.insert(p9);
	a.insert(p0);
	a.rightTreeOutput();
	cout << endl << endl;
	a.erase(29);
	a.rightTreeOutput();
	cout << endl << endl;
	a.erase(33);
	a.rightTreeOutput();
	cout << endl << endl;
	cout << *(a.closeLeaf());
	/*a.erase(32);
	a.rightTreeOutput();
	cout << endl << endl;
	a.erase(26);
	a.erase(33);
	a.erase(28);
	a.rightTreeOutput();
	cout << endl << endl;
	cout << a.height();*/
	system("pause");
	return 0;
}
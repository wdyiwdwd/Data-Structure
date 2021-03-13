#include "binaryTree.h"
#include <iostream>
using namespace std;

/*int main()
{
	binaryTree<int> a1;
	binaryTree<int> a2;
	binaryTree<int> a3;
	binaryTree<int> a4;
	binaryTree<int> a5;
	binaryTree<int> a6;
	binaryTree<int> a7;
	binaryTree<int> a8;
	binaryTree<int> a9;
	a7.makeTree(7, a8, a9);
	a6.makeTree(6, a8, a9);
	a5.makeTree(5, a8, a9);
	a4.makeTree(4, a6, a7);
	a3.makeTree(3, a5, a8);
	a2.makeTree(2, a3, a4);
	//binaryTree<int> a2;
	//a2.input();
	binaryTree<int> a10(a2);
	a10.infix();
	a2.infix();
	cout << endl;
	a2.postOutput();
	cout << endl;
	a2.inOutput();
	cout << endl;
	a2.preOutput();
	cout << endl;
	a2.levelOutput();
	cout << endl;
	cout << a2.numOfLeaves() << endl;
	cout << a2.size() << endl;
	a2.exchangeBothSide();
	a2.infix();
	cout << endl;
	 a2.rightTreeOutput();
	cout << a2.height() << endl;
	cout << a2.width() << endl;
	system("pause");
	return 0;
}*/



//判断括号层数
void bracket(string& str, int order[]){
	for (int i = 0; i < str.length(); i++){
		if (str[i] == '('){
			order[i] = -1;
		}
		if (str[i] == ')'){
			order[i] = 1;
		}
	}
}

//判断括号 匹配
bool matchBracket(string& str){
	int mark = 0;
	for (int i = 1; i < str.length() - 1; i++){
		if (str[i] == '('){
			mark++;
		}
		if (str[i] == ')'){
			mark--;
		}
		//如果mark==-1 说明有第一个匹配的括号了 这样与最后一个就不匹配了
		if (mark == -1){
			return false;
		}
	}
	return true;
}

int countBracket(int order[],int num){
	int sum = 0;
	for (int i = 0; i < num; i++){
		if (order[i] < 10){
			sum += order[i];
		}
	}
	if (sum>0){
		return -1;
	}
	else{
		return abs(sum);
	}
}

binaryTree<char> mySpiltString(string str)
{
	int order[20] = { 0 };
	bracket(str, order);
	//去掉最两边的括号  俩别都有括号且括号配对
	if (str[0] == '(' && str[str.length() - 1] == ')' && matchBracket(str) == true){
		char strCopy[20];
		for (int i = 1; i < str.length() - 1; i++){
			strCopy[i - 1] = str[i];
		}
		strCopy[str.length() - 2] = '\0';
		str = strCopy;
	}
	int low = 100000;  //记录加减的顺序
	int mid = 10000;   //记录乘除的顺序
	int high = 2000;   //记录括号的顺序
	for (int i = 0; i < str.length(); i++){
		//如果存在加减 记录位置 并且叠加顺序
		if (str[i] == '+' || str[i] == '-'){
			order[i] += low;
			low++;
			if (countBracket(order, i) != 0){
				order[i] = high - countBracket(order, i) * 200 + 10;
			}
		}
		//如果存在乘除 记录位置 并且叠加顺序
		if (str[i] == '*' || str[i] == '/'){
			order[i] += mid;
			mid++;
			if (countBracket(order, i) != 0){
				order[i] = high - countBracket(order, i) * 200 + 1;
			}
		}
	}
	//给order排序，选最大的，当做这一层树中的最叼的
	int max = 0; //记录最大值
	int wheremax = 0;  //记录最大值的位置
	for (int i = 0; i < str.length(); i++){
		if (order[i]>max){
			max = order[i];
			wheremax = i;
		}
	}
	//如果没有带符号的表达式了
	if (max == 0){
		binaryTree<char> b;
		//创建两个空节点
		binaryTree<char> valid1;
		binaryTree<char> valid2;
		b.makeTree(str[0], valid1, valid1);
		return b;
	}
	else{
		char left[20]; 
		char right[20];
		for (int i = 0; i < wheremax; i++){
			left[i] = str[i];
		}
		left[wheremax] = '\0';
		for (int i = wheremax + 1; i < str.length(); i++){
			right[i-wheremax-1] = str[i];
		}
		right[str.length() - wheremax - 1] = '\0';
		string leftstr(left);
		string rightstr(right);
		binaryTree<char> b;
		b.makeTree(str[wheremax], mySpiltString(leftstr), mySpiltString(rightstr));
		return b;
	}
}

int main()
{
	string str = "(a-b*(a-c))+(d*e)";
  	binaryTree<char> result = mySpiltString(str);
	result.inOutput();
	cout << endl;
	result.preOutput();
	cout << endl;
	result.postOutput();
	cout << endl;
	result.rightOutput();
	cout << endl;
	result.rightTreeOutput();
	system("pause");
	return 0;
}
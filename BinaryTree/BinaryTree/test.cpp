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



//�ж����Ų���
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

//�ж����� ƥ��
bool matchBracket(string& str){
	int mark = 0;
	for (int i = 1; i < str.length() - 1; i++){
		if (str[i] == '('){
			mark++;
		}
		if (str[i] == ')'){
			mark--;
		}
		//���mark==-1 ˵���е�һ��ƥ��������� ���������һ���Ͳ�ƥ����
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
	//ȥ�������ߵ�����  �������������������
	if (str[0] == '(' && str[str.length() - 1] == ')' && matchBracket(str) == true){
		char strCopy[20];
		for (int i = 1; i < str.length() - 1; i++){
			strCopy[i - 1] = str[i];
		}
		strCopy[str.length() - 2] = '\0';
		str = strCopy;
	}
	int low = 100000;  //��¼�Ӽ���˳��
	int mid = 10000;   //��¼�˳���˳��
	int high = 2000;   //��¼���ŵ�˳��
	for (int i = 0; i < str.length(); i++){
		//������ڼӼ� ��¼λ�� ���ҵ���˳��
		if (str[i] == '+' || str[i] == '-'){
			order[i] += low;
			low++;
			if (countBracket(order, i) != 0){
				order[i] = high - countBracket(order, i) * 200 + 10;
			}
		}
		//������ڳ˳� ��¼λ�� ���ҵ���˳��
		if (str[i] == '*' || str[i] == '/'){
			order[i] += mid;
			mid++;
			if (countBracket(order, i) != 0){
				order[i] = high - countBracket(order, i) * 200 + 1;
			}
		}
	}
	//��order����ѡ���ģ�������һ�����е�����
	int max = 0; //��¼���ֵ
	int wheremax = 0;  //��¼���ֵ��λ��
	for (int i = 0; i < str.length(); i++){
		if (order[i]>max){
			max = order[i];
			wheremax = i;
		}
	}
	//���û�д����ŵı��ʽ��
	if (max == 0){
		binaryTree<char> b;
		//���������սڵ�
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
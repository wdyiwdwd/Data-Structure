#include <iostream>
#include <fstream>
#include "ArrayStack.h"
#include "LinkedStack.h"
using namespace std;

/*template <class T>
void deleteall(linkedStack<T>& stack, const T& theVal)
{
	linkedStack<T> s(stack.size());
	while (!stack.empty()){
		if (stack.top() != theVal){
			s.push(stack.top());
		}
		stack.pop();
	}
	while (!s.empty()){
		stack.push(s.top());
		s.pop();
	}
}

int main()
{
	ifstream in;
	string filename = "input.txt";
	in.open(filename);
	if (!in){
		cout << "Wrong File!";
		return 1;
	}
	linkedStack<char> stack;
	char ch;
	char theValue;
	in >> theValue;
	while (in >> ch){
		stack.push(ch);
	}
	deleteall(stack, theValue);
	while (!stack.empty()){
		cout << stack.top() << " ";
		stack.pop();
	}
	cout << endl;
	system("pause");
	return 0;
}*/
template<class T>
void onestep(linkedStack<T>&s1, linkedStack<T>& s2, int *list, int count, int listsize)
//注意 s1,s2必须为引用！！！！保持其唯一性！！！！
{//将一个对象放入list中或者放入堆栈中等待输出
	int temp;
	if (!s1.empty()){
		temp = s1.top();
		s1.pop();
		s2.push(temp);
		onestep(s1, s2, list, count, listsize);
		temp = s2.top();
		s2.pop();
		s1.push(temp);
	}
	if (!s2.empty()){
		temp = s2.top();
		s2.pop();
		list[count - 1] = temp;
		onestep(s1, s2, list, count + 1, listsize);
		s2.push(temp);
		list[count - 1] = 0;
	}//当原堆栈和中专堆栈都为空时，输出list
	if (s1.empty() && s2.empty()){
		for (int i = 0; i<listsize; i++)
			cout << list[i];
		cout << endl;
	}
}

void main(){
	linkedStack<int>s1, s2, s3;
	int n;
	cout << 'n' << ':';
	cin >> n;
	for (int i = 1; i <= n; i++)
		s1.push(i);
	int *list = new int[n];

	onestep(s1, s2, list, 1, n);
	system("pause");
}
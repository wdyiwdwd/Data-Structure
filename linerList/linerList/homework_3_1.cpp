#include <iostream>
#include <fstream>
#include "arrayList.h"
#include "chain.h"
using namespace std;

int main()
{
	ifstream in;
	string filename = "input.txt";
	in.open(filename);
	if (!in){
		cout << "Wrong File";
		return 1;
	}
	int m, n;
	in >> n >> m;
	if (n<3 || n>100 || m < 0){
		cout << "WRONG\n";
		return 1;
	}
	arrayList<int> array(n);
	chain<int> chain(n);
	for (int i = 0; i < n; i++){
		array.insert(i, i + 1);
		chain.insert(i, i + 1);
	}
	int result[100] = { 0 };
	int count=0;
	int i = 0;
	while (!array.empty()){
		count += m-1;
		while(count>=array.size()){
			count -= array.size();
		}
		result[i] = array.get(count);
		array.erase(count);
		i++;
	}
	for (int j = 0; j < n; j++){
		cout << result[j];
		if (j < n - 1){
			cout << " ";
		}
	}
	cout << endl;
	while (!chain.empty()){
		count += m - 1;
		while (count >= chain.size()){
			count -= chain.size();
		}
		result[i] = chain.get(count);
		chain.erase(count);
		i++;
	}
	for (int j = 0; j < n; j++){
		cout << result[j];
		if (j < n - 1){
			cout << " ";
		}
	}
	cout << endl;
	system("pause");
	return 0;
}
#include "doubleQueue.h"
#include <iostream>
#include <fstream>
#include <string>
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
	doubleQueue<int> a;
	string x;
	while (in >> x){
		if (x == "AddLeft"){
			int y;
			in >> y;
			a.addLeft(y);
			cout << a;
		}
		else if (x == "AddRight"){
			int y;
			in >> y;
			a.addRight(y);
			cout << a;
		}
		else if (x == "DeleteRight"){
			a.deleteRight();
			cout << a;
		}
		else if (x == "DeleteLeft"){
			a.deleteLeft();
			cout << a;
		}
		else if (x == "IsFull"){
			bool y = a.isFull();
			cout << y << endl;
		}
		else if (x == "IsEmpty"){
			bool y = a.isEmpty();
			cout << y << endl;
		}
		else if (x == "END"){
			break;
		}
	}
	system("pause");
	return 0;
}
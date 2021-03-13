#pragma once
#include <stdexcept>
#include <iostream>
#include "pair.h"
using namespace std;

template <class K, class E>
struct redBlackNode
{
	friend ostream& operator << (ostream& out, redBlackNode<K, E>& theNode){
		out << theNode.pair;
		return out;
	}


	myPair<K, E> pair;

	bool color;  //0ºì 1ºÚ falseºì trueºÚ

	redBlackNode(){
		height = 0;
	}
	redBlackNode(const redBlackNode<K, E>& theNode){
		pair = theNode.pair;
		height = 0;
	}
	redBlackNode(const K theKey, const E theElement){
		pair(theKey, theElement);
		height = 0;
	}
	redBlackNode(const myPair<K, E> thePair){
		pair = thePair;
		height = 0;
	}
};
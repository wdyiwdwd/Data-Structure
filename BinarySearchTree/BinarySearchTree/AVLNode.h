#pragma once
#include <stdexcept>
#include <iostream>
#include "pair.h"
using namespace std;

template <class K, class E>
struct AVLNode
{
	friend ostream& operator << (ostream& out, AVLNode<K, E>& theNode){
		out << theNode.pair;
		return out;
	}


	myPair<K, E> pair;

	int height;

	AVLNode(){
		height = 0;
	}
	AVLNode(const AVLNode<K, E>& theNode){
		pair = theNode.pair;
		height = 0;
	}
	AVLNode(const K theKey, const E theElement){
		pair(theKey,theElement);
		height = 0;
	}
	AVLNode(const myPair<K,E> thePair){
		pair = thePair;
		height = 0;
	}
};
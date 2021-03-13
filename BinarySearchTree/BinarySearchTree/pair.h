#pragma once
#include <stdexcept>
#include <iostream>
using namespace std;

template <class K, class E>
struct myPair
{

	friend ostream& operator << (ostream& out, myPair<K, E>& thePair){
		out << thePair.key << "->" << thePair.element;
		return out;
	}


	K key;
	E element;

	myPair(){}
	myPair(const myPair<K, E>& thePair){
		key = thePair.key;
		element = thePair.element;
	}
	myPair(const K theKey, const E theElement){
		key = theKey;
		element = theElement;
	}

};
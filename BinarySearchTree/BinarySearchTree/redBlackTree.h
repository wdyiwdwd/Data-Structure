#pragma once
#include <iostream>
#include <stdexcept>
#include "binarySearchTree.h"
#include "redBlackNode.h"
using namespace std;
template <class K,class E>
class redBlackTree : public binaryTree<redBlackNode<K, E> >
{
public:
	redBlackTree(){}
	~redBlackTree(){}
	//���Һ���
	myPair<K, E>* find(const K& theKey) const;
	//����һ������thePair
	void insert(const myPair<K, E>& thePair);
	//ɾ���ؼ��ֵ���theKey������
	void erase(const K& theKey);
	//��������˳���������
	void ascend() const{
		this->inOutput();
	}
private:
	//Ӧ���ڲ���ɾ����¼�ڵ�
	static binaryTreeNode<redBlackNode<K, E> > *X;  //��ǰ���
	static binaryTreeNode<redBlackNode<K, E> > *P;  //X�İְ�
	static binaryTreeNode<redBlackNode<K, E> > *GP;	//X��үү
	static binaryTreeNode<redBlackNode<K, E> > *GGP;	//X������
	//�������������ת
	binaryTreeNode<redBlackNode<K, E> >* rotation(binaryTreeNode<redBlackNode<K, E> > *theNode, binaryTreeNode<redBlackNode<K, E> > *parent);
	//����ת
	binaryTreeNode<redBlackNode<K, E> >* singleRotationLeft(binaryTreeNode<redBlackNode<K, E> > *t);
	binaryTreeNode<redBlackNode<K, E> >* singleRotationRight(binaryTreeNode<redBlackNode<K, E> > *t);
	//����������
	void handleReorient(binaryTreeNode<redBlackNode<K, E> > *theNode, binaryTreeNode<redBlackNode<K, E> > *parent);
};

template <class K, class E>
redBlackTree<K, E>::X = NULL;
template <class K, class E>
redBlackTree<K, E>::P = NULL;
template <class K, class E>
redBlackTree<K, E>::GP = NULL;
template <class K, class E>
redBlackTree<K, E>::GGP = NULL;

template <class K,class E> 
myPair<K, E>* redBlackTree<K, E>::find(const K& theKey) const
{
	//����ֵ��ƥ�����Ե�ָ�룬���û��ƥ�����ԣ��򷵻�NULL
	binaryTreeNode<redBlackNode<K, E> > *p = root;
	while (p != NULL){
		//���Ԫ��p->element
		if (theKey < p->element.pair.key){
			p = p->leftNode;
		}
		else if (theKey > p->element.pair.key){
			p = p->rightNode;
		}
		else{
			//����һ��pair�ĵ�ַ
			return &(p->element.pair);
		}
	}
	return NULL;
}

template<class K,class E>
void redBlackTree<K, E>::insert(const myPair<K, E>& thePair){
	binaryTreeNode<redBlackNode<K, E> > *newNode = new binaryTreeNode<redBlackNode<K, E> >(thePair);
	GGP = NULL;
	X = P = GP = newNode;
	while (X->element)
}

template <class K, class E>
void redBlackTree<K, E>::handleReorient(binaryTreeNode<redBlackNode<K, E> > *theNode, binaryTreeNode<redBlackNode<K, E> > *parent){
	X->element.color = 0;
	X->leftNode->element.color = 1;
	X->rightNode->element.color = 1;
	if (P->element.color == 0){
		GP->element.color = 0;
		if ((theNode->element.pair.key < GP->element.pair.key) != (theNode->element.pair.key < P->element.pair.key)){
			P = Rotation(theNode, GP);
		}
		X = rotation(theNode, GGP);
		X->element.color = 1;
	}
	parent->leftNode->element.color = 1;
}

template <class K, class E>
binaryTreeNode<redBlackNode<K, E> >* redBlackTree<K, E>::rotation(binaryTreeNode<redBlackNode<K, E> > *theNode, binaryTreeNode<redBlackNode<K, E> > *parent){
	if (theNode->element.pair.key < parent->element.pair.key){
		if (theNode->element.pair, key < parent->leftNode->element.key){
			parent->leftNode = singleRotationLeft(parent->leftNode);
		}
		else{
			parent->leftNode = singleRotationRight(parent->leftNode);
		}
		return parent->leftNode;
	}
	else{
		if (theNode->element.pair, key < parent->rightNode->element.key){
			parent->rightNode = singleRotationLeft(parent->rightNode);
		}
		else{
			parent->rightNode = singleRotationRight(parent->rightNode);
		}
		return parent->rightNode;
	}
}

template <class K, class E>
binaryTreeNode<redBlackNode<K, E> >* redBlackTree<K, E>::singleRotationLeft(binaryTreeNode<redBlackNode<K, E> > *t){
	//newMidʹԭ��t�����������������µ���ߵĵĽڵ�
	binaryTreeNode<AVLNode<K, E> >* newMid;
	newMid = t->leftNode;
	t->leftNode = newMid->rightNode;
	newMid->rightNode = t;
	return newMid;
}

template <class K, class E>
binaryTreeNode<redBlackNode<K, E> >* redBlackTree<K, E>::singleRotationRight(binaryTreeNode<redBlackNode<K, E> > *t){
	binaryTreeNode<redBlackNode<K, E> >* newMid;
	newMid = t->rightNode;
	t->rightNode = newMid->leftNode;
	newMid->leftNode = t;
	return newMid;
}

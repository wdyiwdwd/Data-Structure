#pragma once
#include <iostream>
#include <stdexcept>
#include "pair.h"
#include "binaryTree.h"
using namespace std;

template<class K, class E>
class binarySearchTree : public binaryTree<myPair<K, E> >
{
public:
	binarySearchTree(){
		root = NULL;
	}
	//binarySearchTree(binarySearchTree<K, E>&);
	~binarySearchTree(){}
	//�ҵ��ؼ��ֵ���theKey������,����ֵΪ���Ե�ָ��
	myPair<K, E>* find(const K& theKey) const;
	//����һ������thePair
	void insert(const myPair<K, E>& thePair);
	//ɾ���ؼ��ֵ���theKey������
	void erase(const K& theKey);
	//��������˳���������
	void ascend() const{
		this->inOutput();
	}
};

template <class K, class E>
myPair<K, E>* binarySearchTree<K, E>::find(const K& theKey) const
{
	//����ֵ��ƥ�����Ե�ָ�룬���û��ƥ�����ԣ��򷵻�NULL
	binaryTreeNode<myPair<K, E> > *p = root;
	while (p != NULL){
		//���Ԫ��p->element
		if (theKey < p->element.key){
			p = p->leftNode;
		}
		else if (theKey>p->element.key){
			p = p->rightNode;
		}
		else{
			//����һ��pair�ĵ�ַ
			return &(p->element);
		}
	}
	return NULL;
}

template <class K, class E>
void binarySearchTree<K, E>::insert(const myPair<K, E>& thePair){
	//Ѱ�Ҳ���λ��
	//pp��p�ĸ��ڵ�
	binaryTreeNode<myPair<K, E> > *p = root;
	binaryTreeNode<myPair<K, E> > *pp = NULL;
	//��ʼѭ����λ��
	while (p != NULL){
		pp = p;
		//��pָ�����ĺ��ӽڵ�
		if (thePair.key < p->element.key){
			p = p->leftNode;
		}
		else if (thePair.key > p->element.key){
			p = p->rightNode;
		}
		else{
			//����ԭ����ֵ
			p->element.element = thePair.element;
			return;
		}
	}
	//ΪthePair����һ���µĽڵ� Ȼ�����������ʵ�λ�� pp�����ӻ����Һ���
	binaryTreeNode<myPair<K, E> > *newNode = new binaryTreeNode<myPair<K, E> >(thePair);
	//���û��rootֱ�ӷ���root��
	if (root != NULL){
		if (thePair.key < pp->element.key){
			pp->leftNode = newNode;
		}
		else{
			pp->rightNode = newNode;
		}
	}
	else{
		root = newNode;
	}
}

template <class K, class E>
void binarySearchTree<K, E>::erase(const K& theKey){
	//���ҹؼ���ΪtheKey�Ľڵ�
	//pp��p�ĸ��ڵ�
	binaryTreeNode<myPair<K, E> > *p = root;
	binaryTreeNode<myPair<K, E> > *pp = NULL;
	//��ʼѭ��
	while (p != NULL && p->element.key != theKey){
		pp = p;
		if (theKey < p->element.key){
			p = p->leftNode;
		}
		else if (theKey > p->element.key){
			p = p->rightNode;
		}
	}
	//ѭ�����������������һ����pΪNULL,һ����p����Ҫ�ҵĽڵ�
	if (p == NULL){
		//���pΪNULL��������
		return;
	}
	//������֯���Ľṹ
	//p���������ӵ�ʱ��
	if (p->leftNode != NULL && p->rightNode != NULL){
		//ת��Ϊֻ��һ�����ӻ���û����
		//��p���������Ѱ������ҡ�������Ԫ��
		binaryTreeNode<myPair<K, E> > *s = p->leftNode;
		//ps��s�İְ�
		binaryTreeNode<myPair<K, E> > *ps = p;
		//ѭ��Ѱ����ҵĽڵ�s
		while (s->rightNode != NULL){
			ps = s;
			s = s->rightNode;
		}
		//�����Ԫ��s�Ƶ�p
		binaryTreeNode<myPair<K, E> > *q = new binaryTreeNode<myPair<K, E> >(s->element, p->leftNode, p->rightNode);
		//���p�Ǹ��ڵ�
		if (pp == NULL){
			root = q;
		}
		//���p��pp�������
		else if (p == pp->leftNode){
			pp->leftNode = q;
		}
		//�Ҷ���
		else{
			pp->rightNode = q;
		}
		//����⼸���ĺ���˼���ǰ�s��ֵ��p,sp��ֵ��pp Ȼ���ȥ���if���ɾ���Ǹ���δɾȥ���ظ��ڵ�
		//�����������ҵĽڵ����pp�����ӣ����ʱ����µ�q��pp s��p ��Ϊ���ʱ��ps==p��ָ��ɵ���
		if (ps == p){
			pp = q;
		}
		//��֮��ps��pp������
		else{
			pp = ps;
		}
		delete p;
		p = s;
	}
	//��p��һ�����ӵĻ���û�к��ӵ�ʱ��
	//���c�������Ѻ��ӵ�ָ����ʱ�浽c��
	binaryTreeNode<myPair<K, E> > *c;
	if (p->leftNode != NULL){
		c = p->leftNode;
	}
	else{
		c = p->rightNode;
	}

	//ɾ��p
	if (p == root){
		root = c;
	}
	else{
		//�ж�p��pp�����ӻ����Һ���
		if (p == pp->leftNode){
			pp->leftNode = c;
		}
		else{
			pp->rightNode = c;
		}
	}
	delete p;
}
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
	//找到关键字等于theKey的数对,返回值为数对的指针
	myPair<K, E>* find(const K& theKey) const;
	//插入一个数对thePair
	void insert(const myPair<K, E>& thePair);
	//删除关键字等于theKey的数对
	void erase(const K& theKey);
	//按照升序顺序输出函数
	void ascend() const{
		this->inOutput();
	}
};

template <class K, class E>
myPair<K, E>* binarySearchTree<K, E>::find(const K& theKey) const
{
	//返回值是匹配数对的指针，如果没有匹配数对，则返回NULL
	binaryTreeNode<myPair<K, E> > *p = root;
	while (p != NULL){
		//检查元素p->element
		if (theKey < p->element.key){
			p = p->leftNode;
		}
		else if (theKey>p->element.key){
			p = p->rightNode;
		}
		else{
			//返回一个pair的地址
			return &(p->element);
		}
	}
	return NULL;
}

template <class K, class E>
void binarySearchTree<K, E>::insert(const myPair<K, E>& thePair){
	//寻找插入位置
	//pp是p的父节点
	binaryTreeNode<myPair<K, E> > *p = root;
	binaryTreeNode<myPair<K, E> > *pp = NULL;
	//开始循环找位置
	while (p != NULL){
		pp = p;
		//把p指向到他的孩子节点
		if (thePair.key < p->element.key){
			p = p->leftNode;
		}
		else if (thePair.key > p->element.key){
			p = p->rightNode;
		}
		else{
			//覆盖原来的值
			p->element.element = thePair.element;
			return;
		}
	}
	//为thePair创造一个新的节点 然后把它放入合适的位置 pp的左孩子或者右孩子
	binaryTreeNode<myPair<K, E> > *newNode = new binaryTreeNode<myPair<K, E> >(thePair);
	//如果没有root直接放在root中
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
	//查找关键字为theKey的节点
	//pp是p的父节点
	binaryTreeNode<myPair<K, E> > *p = root;
	binaryTreeNode<myPair<K, E> > *pp = NULL;
	//开始循环
	while (p != NULL && p->element.key != theKey){
		pp = p;
		if (theKey < p->element.key){
			p = p->leftNode;
		}
		else if (theKey > p->element.key){
			p = p->rightNode;
		}
	}
	//循环出来有两种情况，一种是p为NULL,一种是p就是要找的节点
	if (p == NULL){
		//如果p为NULL，出函数
		return;
	}
	//重新组织树的结构
	//p有两个孩子的时候
	if (p->leftNode != NULL && p->rightNode != NULL){
		//转化为只有一个孩子或者没孩子
		//在p的左边子树寻找最“靠右”即最大的元素
		binaryTreeNode<myPair<K, E> > *s = p->leftNode;
		//ps是s的爸爸
		binaryTreeNode<myPair<K, E> > *ps = p;
		//循环寻找最靠右的节点s
		while (s->rightNode != NULL){
			ps = s;
			s = s->rightNode;
		}
		//将最大元素s移到p
		binaryTreeNode<myPair<K, E> > *q = new binaryTreeNode<myPair<K, E> >(s->element, p->leftNode, p->rightNode);
		//如果p是根节点
		if (pp == NULL){
			root = q;
		}
		//如果p是pp的左儿子
		else if (p == pp->leftNode){
			pp->leftNode = q;
		}
		//右儿子
		else{
			pp->rightNode = q;
		}
		//最后这几部的核心思想是把s赋值给p,sp赋值给pp 然后出去这个if后会删掉那个还未删去的重复节点
		//如果左子树最靠右的节点就是pp的左孩子，这个时候把新的q给pp s给p 因为这个时候ps==p还指向旧的呢
		if (ps == p){
			pp = q;
		}
		//反之把ps给pp就行了
		else{
			pp = ps;
		}
		delete p;
		p = s;
	}
	//当p有一个孩子的或者没有孩子的时候
	//这个c是用来把孩子的指针暂时存到c中
	binaryTreeNode<myPair<K, E> > *c;
	if (p->leftNode != NULL){
		c = p->leftNode;
	}
	else{
		c = p->rightNode;
	}

	//删除p
	if (p == root){
		root = c;
	}
	else{
		//判断p是pp的左孩子还是右孩子
		if (p == pp->leftNode){
			pp->leftNode = c;
		}
		else{
			pp->rightNode = c;
		}
	}
	delete p;
}
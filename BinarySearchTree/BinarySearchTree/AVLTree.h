#pragma once
#include <iostream>
#include <stdexcept>
#include "AVLNode.h"
#include "binaryTree.h"
using namespace std;
int max(int a, int b){
	if (a > b){
		return a;
	}
	else{
		return b;
	}
}

template <class K,class E>
class AVLTree : public binaryTree<AVLNode<K, E> >
{
public:
	AVLTree(){
		root = NULL;
	}
	~AVLTree(){}

	//返回AVL树的高度 重写父类的高度函数 因为AVL树的高度有规律
	int height() const{
		return height(root);
	}
	//查找函数
	myPair<K, E>* find(const K& theKey) const;
	//插入一个数对thePair
	void insert(const myPair<K, E>& thePair){
		root = recursiveInsert(thePair, root);
	}
	//删除关键字等于theKey的数对
	void erase(const K& theKey){
		root = recursiveErase(theKey, root);
	}
	//按照升序顺序输出函数
	void ascend() const{
		this->inOutput();
	}
	//输出离根节点最近的叶节点的值
	myPair<K, E>* closeLeaf() const;

protected:
	int height(const binaryTreeNode<AVLNode<K, E> > *t) const;
	//插入函数的重中之重，用递归的思想解决了垃圾平衡因子的方法
	binaryTreeNode<AVLNode<K, E> >* recursiveInsert(const myPair<K, E>& thePair, binaryTreeNode<AVLNode<K, E> > *t);
	//找到删除的位置，并递归回来旋转平衡
	binaryTreeNode<AVLNode<K, E> >* recursiveErase(const K& theKey, binaryTreeNode<AVLNode<K, E> > *t);
	//找到删除节点换了之后要删除的多余节点（叶子节点），并递归回来保持平衡
	binaryTreeNode<AVLNode<K, E> >* recursiveDeleteNode(binaryTreeNode<AVLNode<K, E> > *theNode, binaryTreeNode<AVLNode<K, E> > *t);

private:
	binaryTreeNode<AVLNode<K, E> >* singleRotationLeft(binaryTreeNode<AVLNode<K, E> > *t);
	binaryTreeNode<AVLNode<K, E> >* doubleRotationLeft(binaryTreeNode<AVLNode<K, E> > *t);
	binaryTreeNode<AVLNode<K, E> >* singleRotationRight(binaryTreeNode<AVLNode<K, E> > *t);
	binaryTreeNode<AVLNode<K, E> >* doubleRotationRight(binaryTreeNode<AVLNode<K, E> > *t);
};

template <class K,class E>
int AVLTree<K, E>::height(const binaryTreeNode<AVLNode<K, E> > *t) const
{
	if (t != NULL){
		return t->element.height;
	}
	return 0;
}

template <class K,class E>
myPair<K, E>* AVLTree<K, E>::find(const K& theKey) const
{
	//返回值是匹配数对的指针，如果没有匹配数对，则返回NULL
	binaryTreeNode<AVLNode<K,E> > *p = root;
	while (p != NULL){
		//检查元素p->element
		if (theKey < p->element.pair.key){
			p = p->leftNode;
		}
		else if (theKey > p->element.pair.key){
			p = p->rightNode;
		}
		else{
			//返回一个pair的地址
			return &(p->element.pair);
		}
	}
	return NULL;
}

//递归插入的函数
template <class K,class E>
binaryTreeNode<AVLNode<K, E> >* AVLTree<K, E>::recursiveInsert(const myPair<K, E>& thePair, binaryTreeNode<AVLNode<K, E> > *t)
{
	//当t递归到最底层的时候
	if (t == NULL){
		//创造一个新节点链接到t这个位置
		t = new  binaryTreeNode<AVLNode<K, E> >(thePair);
		t->element.height = 1;
		t->leftNode = t->rightNode = NULL;
	}
	//当key值小于t的值的时候 向左递归 递归回来的时候判断这个节点的高度差是否有问题 这样一个节点一个节点的回来 就可以遍历所有相关节点
	else if (thePair.key < t->element.pair.key){
		t->leftNode = recursiveInsert(thePair, t->leftNode);
		if (height(t->leftNode) - height(t->rightNode) == 2){
			if (thePair.key < t->leftNode->element.pair.key){
				//私有函数 单次旋转 下文同理
				t = singleRotationLeft(t);
			}
			else{
				t = doubleRotationLeft(t);
			}
		}
	}
	else if (thePair.key > t->element.pair.key){
		t->rightNode = recursiveInsert(thePair, t->rightNode);
		if (height(t->leftNode) - height(t->rightNode) == -2){
			if (thePair.key > t->rightNode->element.pair.key){
				t = singleRotationRight(t);
			}
			else{
				t = doubleRotationRight(t);
			}
		}
	}
	//相等的时候修改该节点的值，就好
	else{
		t->element.pair.element = thePair.element;
	}
	//重新调高度
	t->element.height = max(height(t->leftNode), height(t->rightNode)) + 1;
	//这样的返回机制保证了单旋转双旋转的简便性
	return t;
}

//递归删除的函数 这个函数的目的是找到该删除的那个节点 然后传递到下一个函数中 递归回来的时候调整结构进行旋转
template <class K, class E>
binaryTreeNode<AVLNode<K, E> >* AVLTree<K, E>::recursiveErase(const K& theKey, binaryTreeNode<AVLNode<K, E> > *t){
	//没有找到
	if (t == NULL){
		return t;
	}
	else if (t->element.pair.key == theKey){
		t = recursiveDeleteNode(t,t);
	}
	else if (theKey < t->element.pair.key){
		t->leftNode = recursiveErase(theKey, t->leftNode);
		if (height(t->leftNode) - height(t->rightNode) == -2){
			if (height(t->rightNode->rightNode) > height(t->rightNode->leftNode)){
				//私有函数 单次旋转 下文同理
				t = singleRotationRight(t);
			}
			else{
				t = doubleRotationRight(t);
			}
		}
	}
	else if (theKey > t->element.pair.key){
		t->rightNode = recursiveErase(theKey, t->rightNode);
		if (height(t->leftNode) - height(t->rightNode) == 2){
			if (height(t->rightNode->rightNode) > height(t->rightNode->leftNode)){
				t = singleRotationRight(t);
			}
			else{
				t = doubleRotationRight(t);
			}
		}
	}
	//重新调高度
	if (t != NULL){
		t->element.height = max(height(t->leftNode), height(t->rightNode)) + 1;
	}
	//这样的返回机制保证了单旋转双旋转的简便性
	return t;
}


//递归删除节点的函数 这个函数已经找到了该删除的节点 目标是在保证树的结构不变的情况下 删除一个节点 它要找的目标是要删除的叶节点
template <class K, class E>
binaryTreeNode<AVLNode<K, E> >* AVLTree<K, E>::recursiveDeleteNode(binaryTreeNode<AVLNode<K, E> > *theNode, binaryTreeNode<AVLNode<K, E> > *t){
	//我们要删除的节点根本没有左子树，直接把他删了，把它的右子树给它爸爸
	if (theNode == t && t->leftNode == NULL){
		binaryTreeNode<AVLNode<K, E> > *theRightNodes = t->rightNode;
		delete t;
		t = theRightNodes;
	}
	//这就是我们要找的值，要删除的节点，并把这个值赋值给找到的要删除的地方
	else if (theNode != t && t->rightNode == NULL){
		theNode->element.pair = t->element.pair;
		binaryTreeNode<AVLNode<K, E> > *theLeftNodes = t->leftNode;
		delete t;
		t = theLeftNodes;
	}
	else{
		if (t != theNode){
			t->rightNode = recursiveDeleteNode(theNode, t->rightNode);
		}
		else{
			if (t->leftNode != NULL){
				t->leftNode = recursiveDeleteNode(theNode, t->leftNode);
			}
		}
		if (height(t->leftNode) - height(t->rightNode) == 2){
			if (height(t->leftNode->leftNode) > height(t->leftNode->rightNode)){
				//私有函数 单次旋转 下文同理
				t = singleRotationLeft(t);
			}
			else{
				t = doubleRotationLeft(t);
			}
		}
		if (height(t->leftNode) - height(t->rightNode) == -2){
			if (height(t->rightNode->rightNode) > height(t->rightNode->leftNode)){
				//私有函数 单次旋转 下文同理
				t = singleRotationRight(t);
			}
			else{
				t = doubleRotationRight(t);
			}
		}
	}
	//重新调高度
	if (t != NULL){
		t->element.height = max(height(t->leftNode), height(t->rightNode)) + 1;
	}
	return t;
}

template <class K,class E>
myPair<K, E>* AVLTree<K, E>::closeLeaf() const
{
	if (root == NULL){
		return NULL;
	}
	binaryTreeNode<AVLNode<K, E>> *t = root;
	// Level-order traversal of *t.
	linkedQueue<binaryTreeNode<AVLNode<K, E>>*> Q;
	Q.push(t);
	while (!Q.empty()) {
		// put t's children on queue
		if (t->leftNode != NULL){
			Q.push(t->leftNode);
		}
		if (t->rightNode != NULL){
			Q.push(t->rightNode);
		}
		if (t->leftNode == NULL && t->rightNode == NULL){
			break;
		}
		Q.pop();
		try{
			t = Q.front();
		}
		catch (invalid_argument){
			return NULL;
		}
		// get next node to visit
		//删除队列中当前结点
	}
	return &(t->element.pair);
}

template <class K, class E>
binaryTreeNode<AVLNode<K, E> >* AVLTree<K, E>::singleRotationLeft(binaryTreeNode<AVLNode<K, E> > *t){
	//newMid使原来t的左子树，现在是新的最高的的节点
	binaryTreeNode<AVLNode<K, E> >* newMid;
	newMid = t->leftNode;
	t->leftNode = newMid->rightNode;
	newMid->rightNode = t;
	//重新算高度
	t->element.height = max(height(t->leftNode), height(t->rightNode)) + 1;
	newMid->element.height = max(height(newMid->leftNode), height(newMid->rightNode)) + 1;
	return newMid;
}

template <class K, class E>
binaryTreeNode<AVLNode<K, E> >* AVLTree<K, E>::singleRotationRight(binaryTreeNode<AVLNode<K, E> > *t){
	binaryTreeNode<AVLNode<K, E> >* newMid;
	newMid = t->rightNode;
	t->rightNode = newMid->leftNode;
	newMid->leftNode = t;

	t->element.height = max(height(t->leftNode), height(t->rightNode)) + 1;
	newMid->element.height = max(height(newMid->leftNode), height(newMid->rightNode)) + 1;
	return newMid;
}

template <class K,class E>
binaryTreeNode<AVLNode<K, E> >* AVLTree<K, E>::doubleRotationLeft(binaryTreeNode<AVLNode<K, E> > *t){
	//自己画一画就知道双旋转是两个单旋转构成的
	t->leftNode = singleRotationRight(t->leftNode);
	return singleRotationLeft(t);
}

template <class K, class E>
binaryTreeNode<AVLNode<K, E> >* AVLTree<K, E>::doubleRotationRight(binaryTreeNode<AVLNode<K, E> > *t){
	t->rightNode = singleRotationLeft(t->rightNode);
	return singleRotationRight(t);
}
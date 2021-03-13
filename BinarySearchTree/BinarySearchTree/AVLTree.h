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

	//����AVL���ĸ߶� ��д����ĸ߶Ⱥ��� ��ΪAVL���ĸ߶��й���
	int height() const{
		return height(root);
	}
	//���Һ���
	myPair<K, E>* find(const K& theKey) const;
	//����һ������thePair
	void insert(const myPair<K, E>& thePair){
		root = recursiveInsert(thePair, root);
	}
	//ɾ���ؼ��ֵ���theKey������
	void erase(const K& theKey){
		root = recursiveErase(theKey, root);
	}
	//��������˳���������
	void ascend() const{
		this->inOutput();
	}
	//�������ڵ������Ҷ�ڵ��ֵ
	myPair<K, E>* closeLeaf() const;

protected:
	int height(const binaryTreeNode<AVLNode<K, E> > *t) const;
	//���뺯��������֮�أ��õݹ��˼����������ƽ�����ӵķ���
	binaryTreeNode<AVLNode<K, E> >* recursiveInsert(const myPair<K, E>& thePair, binaryTreeNode<AVLNode<K, E> > *t);
	//�ҵ�ɾ����λ�ã����ݹ������תƽ��
	binaryTreeNode<AVLNode<K, E> >* recursiveErase(const K& theKey, binaryTreeNode<AVLNode<K, E> > *t);
	//�ҵ�ɾ���ڵ㻻��֮��Ҫɾ���Ķ���ڵ㣨Ҷ�ӽڵ㣩�����ݹ��������ƽ��
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
	//����ֵ��ƥ�����Ե�ָ�룬���û��ƥ�����ԣ��򷵻�NULL
	binaryTreeNode<AVLNode<K,E> > *p = root;
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

//�ݹ����ĺ���
template <class K,class E>
binaryTreeNode<AVLNode<K, E> >* AVLTree<K, E>::recursiveInsert(const myPair<K, E>& thePair, binaryTreeNode<AVLNode<K, E> > *t)
{
	//��t�ݹ鵽��ײ��ʱ��
	if (t == NULL){
		//����һ���½ڵ����ӵ�t���λ��
		t = new  binaryTreeNode<AVLNode<K, E> >(thePair);
		t->element.height = 1;
		t->leftNode = t->rightNode = NULL;
	}
	//��keyֵС��t��ֵ��ʱ�� ����ݹ� �ݹ������ʱ���ж�����ڵ�ĸ߶Ȳ��Ƿ������� ����һ���ڵ�һ���ڵ�Ļ��� �Ϳ��Ա���������ؽڵ�
	else if (thePair.key < t->element.pair.key){
		t->leftNode = recursiveInsert(thePair, t->leftNode);
		if (height(t->leftNode) - height(t->rightNode) == 2){
			if (thePair.key < t->leftNode->element.pair.key){
				//˽�к��� ������ת ����ͬ��
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
	//��ȵ�ʱ���޸ĸýڵ��ֵ���ͺ�
	else{
		t->element.pair.element = thePair.element;
	}
	//���µ��߶�
	t->element.height = max(height(t->leftNode), height(t->rightNode)) + 1;
	//�����ķ��ػ��Ʊ�֤�˵���ת˫��ת�ļ����
	return t;
}

//�ݹ�ɾ���ĺ��� ���������Ŀ�����ҵ���ɾ�����Ǹ��ڵ� Ȼ�󴫵ݵ���һ�������� �ݹ������ʱ������ṹ������ת
template <class K, class E>
binaryTreeNode<AVLNode<K, E> >* AVLTree<K, E>::recursiveErase(const K& theKey, binaryTreeNode<AVLNode<K, E> > *t){
	//û���ҵ�
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
				//˽�к��� ������ת ����ͬ��
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
	//���µ��߶�
	if (t != NULL){
		t->element.height = max(height(t->leftNode), height(t->rightNode)) + 1;
	}
	//�����ķ��ػ��Ʊ�֤�˵���ת˫��ת�ļ����
	return t;
}


//�ݹ�ɾ���ڵ�ĺ��� ��������Ѿ��ҵ��˸�ɾ���Ľڵ� Ŀ�����ڱ�֤���Ľṹ���������� ɾ��һ���ڵ� ��Ҫ�ҵ�Ŀ����Ҫɾ����Ҷ�ڵ�
template <class K, class E>
binaryTreeNode<AVLNode<K, E> >* AVLTree<K, E>::recursiveDeleteNode(binaryTreeNode<AVLNode<K, E> > *theNode, binaryTreeNode<AVLNode<K, E> > *t){
	//����Ҫɾ���Ľڵ����û����������ֱ�Ӱ���ɾ�ˣ������������������ְ�
	if (theNode == t && t->leftNode == NULL){
		binaryTreeNode<AVLNode<K, E> > *theRightNodes = t->rightNode;
		delete t;
		t = theRightNodes;
	}
	//���������Ҫ�ҵ�ֵ��Ҫɾ���Ľڵ㣬�������ֵ��ֵ���ҵ���Ҫɾ���ĵط�
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
				//˽�к��� ������ת ����ͬ��
				t = singleRotationLeft(t);
			}
			else{
				t = doubleRotationLeft(t);
			}
		}
		if (height(t->leftNode) - height(t->rightNode) == -2){
			if (height(t->rightNode->rightNode) > height(t->rightNode->leftNode)){
				//˽�к��� ������ת ����ͬ��
				t = singleRotationRight(t);
			}
			else{
				t = doubleRotationRight(t);
			}
		}
	}
	//���µ��߶�
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
		//ɾ�������е�ǰ���
	}
	return &(t->element.pair);
}

template <class K, class E>
binaryTreeNode<AVLNode<K, E> >* AVLTree<K, E>::singleRotationLeft(binaryTreeNode<AVLNode<K, E> > *t){
	//newMidʹԭ��t�����������������µ���ߵĵĽڵ�
	binaryTreeNode<AVLNode<K, E> >* newMid;
	newMid = t->leftNode;
	t->leftNode = newMid->rightNode;
	newMid->rightNode = t;
	//������߶�
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
	//�Լ���һ����֪��˫��ת����������ת���ɵ�
	t->leftNode = singleRotationRight(t->leftNode);
	return singleRotationLeft(t);
}

template <class K, class E>
binaryTreeNode<AVLNode<K, E> >* AVLTree<K, E>::doubleRotationRight(binaryTreeNode<AVLNode<K, E> > *t){
	t->rightNode = singleRotationLeft(t->rightNode);
	return singleRotationRight(t);
}
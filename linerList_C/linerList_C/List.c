#include <stdlib.h>
#include "List.h"

struct Node
{	
	int Element;
	Position Next;
};

int IsEmpty(List L){
	return L->Next == NULL;
}

//如果p是最后一个节点返回1
int IsLast(Position P,List L){
	return P->Next == NULL;
}

//返回一个节点 与传入X值相同的节点
Position Find(int X, List L){
	Position P;

	P = L->Next;
	while (P!=NULL&&P->Element!=X){
		P = P->Next;
	}
	return P;
}

void Delete(int X, List L){
	Position P, TmpCell;
	//找到删除位置的前一个位置
	P = FindPrevious(X, L);
	if (!IsLast(P, L)){
		TmpCell = P->Next;
		P->Next = TmpCell->Next;
		free(TmpCell);
	}
}

//找到一个值为X的位置的前一个位置
Position FindPrevious(int X, List L){
	Position P;
	P = L;
	while (P->Next != NULL&&P->Next->Element != X){
		P = P->Next;
	}
	return P;
}

//插入到P节点的后面
void Insert(int X, List L, Position P){
	Position TemCell;
	TemCell = malloc(sizeof(struct Node));
	if (TemCell != NULL){
		FatalError("Out of space!");
	}
	TemCell->Element = X;
	TemCell->Next = P->Next;
	P->Next = TemCell;
}

//删除链表
void DeleteList(List L){
	Position P,TemCell;
	P = L->Next;
	L->Next = NULL;
	while (P != NULL){
		TemCell = P->Next;
		free(P);
		P = TemCell;
	}
}

//返回头指针
Position Header(List L){
	return L;
}

//返回第一个元素
Position First(List L){
	return L->Next;
}

//返回下一个元素
Position Advance(Position P){
	return P->Next;
}

//返回P的值
int Retrieve(Position P){
	return P->Element;
}
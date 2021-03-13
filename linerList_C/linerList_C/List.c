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

//���p�����һ���ڵ㷵��1
int IsLast(Position P,List L){
	return P->Next == NULL;
}

//����һ���ڵ� �봫��Xֵ��ͬ�Ľڵ�
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
	//�ҵ�ɾ��λ�õ�ǰһ��λ��
	P = FindPrevious(X, L);
	if (!IsLast(P, L)){
		TmpCell = P->Next;
		P->Next = TmpCell->Next;
		free(TmpCell);
	}
}

//�ҵ�һ��ֵΪX��λ�õ�ǰһ��λ��
Position FindPrevious(int X, List L){
	Position P;
	P = L;
	while (P->Next != NULL&&P->Next->Element != X){
		P = P->Next;
	}
	return P;
}

//���뵽P�ڵ�ĺ���
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

//ɾ������
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

//����ͷָ��
Position Header(List L){
	return L;
}

//���ص�һ��Ԫ��
Position First(List L){
	return L->Next;
}

//������һ��Ԫ��
Position Advance(Position P){
	return P->Next;
}

//����P��ֵ
int Retrieve(Position P){
	return P->Element;
}
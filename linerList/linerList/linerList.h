#pragma once
#include <iostream>
using namespace std;
template <class T>
class linerList
{
public:
	virtual ~linerList(){};
	//�鿴���Ա��Ƿ�Ϊ��
	virtual bool empty() const = 0;
	//�������Ա�Ĵ�С
	virtual int size() const = 0;
	//���ص�n��ֵ
	virtual T& get(int theIndex) const = 0;
	//����ĳ��Ԫ�ص�һ�γ���ʱ��������
	virtual int indexof(const T& theElement) const = 0;
	//ɾ��ĳ��Ԫ��
	virtual void erase(int theIndex) = 0;
	//����Ԫ��
	virtual void insert(int theIndex, const T& theElement) = 0;
};


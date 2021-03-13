using namespace std;

template <class T>
class queue
{
public:
	virtual ~queue(){}
	//�ж��Ƿ�Ϊ��
	virtual bool empty() = 0 const;
	//�ж϶��д�С
	virtual int size() = 0 const;
	//���ض���front
	virtual T& front() = 0 const;
	//���ض���β
	virtual T& back() = 0 const;
	//ɾ����Ԫ��
	virtual void pop() = 0;
	//��Ԫ��theElement�ƽ�����
	virtual void push(const T& theElement) = 0;
};
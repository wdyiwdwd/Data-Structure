using namespace std;

template <class T>
class queue
{
public:
	virtual ~queue(){}
	//判断是否为空
	virtual bool empty() = 0 const;
	//判断队列大小
	virtual int size() = 0 const;
	//返回队列front
	virtual T& front() = 0 const;
	//返回队列尾
	virtual T& back() = 0 const;
	//删除首元素
	virtual void pop() = 0;
	//把元素theElement推进队列
	virtual void push(const T& theElement) = 0;
};
#include<iostream>
#include<windows.h>
#include<stack>
#include<queue>

using namespace std;

//模拟实现一个栈
template<class T>
class Stack
{
public:
	Stack()
		:_size(0)
		, _capicity(20)
		, sptr(NULL)
	{
		sptr = new T[_capicity];
	}

	~Stack()
	{
		if (sptr != NULL){
			delete[] sptr;
			sptr = NULL;
		}
	}

	size_t Size()
	{
		return _size;
	}

	size_t Capicity()
	{
		return _capicity;
	}

	void  CheckCapicity()
	{
		if (_size == _capicity){
			T* temp_sptr = new T[_size * 2 + 1];
			for (size_t i = 0; i < _size; ++i){
				temp_sptr[i] = sptr[i];
			}
			_capicity = _size * 2 + 1;
			delete[] sptr;
			sptr = temp_sptr;
		}
	}

	void Push(const T& value)
	{
		CheckCapicity();
		sptr[_size++] = value;
	}

	void Pop()
	{
		_size--;
		//sptr[_size - 1] = 0;
	}

	T& Top()
	{
		return sptr[_size - 1];
	}

private:
	T* sptr;
	size_t _size;
	size_t _capicity;
};

//两个队列实现一个栈
template<class T>
class two_stack_Queue
{
public:
	void Enqueue(T value)
	{
		_in.push(value);
	}

	void Dequeue()
	{
		if (!_out.empty())
		{
			T tmp = _out.top();
			_out.pop();
			return tmp;
		}
		else{
			size_t size = _in.size();
			while (--size){
				_out.push(_in.top());
				_in.pop();
			}
			if (!_in.empty()){
				T tmp = _in.top();
				_in.pop();
				return tmp;
			}
		}
	}

	bool Empty()
	{
		return (_in.empty() && _out.empty());
	}

private:
	stack<T> _in;
	stack<T> _out;
};

//使用两个队列实现一个栈
template<class T>
class two_queue_Stack
{
public:
	void Push(const T& value)
	{
		if (q1.empty() && !q2.empty()){
			q2.push(value);
		}
		else
		{
			q1.push(value);
		}
	}

	void Pop()
	{
		if (!q1.empty() && q2.empty())
		{
			size_t size = q1.size();
			while (--size){
				q2.push(q1.front());
				q1.pop();
			}
			if (!q1.empty())
				q1.pop();
			
		}
		else
		{
			size_t size = q2.size();
			while (--size){
				q1.push(q2.front());
				q1.pop();
			}
			if (!q2.empty())
				q2.pop();
		}
	}

	bool Enpty()
	{
		return (q1.empty() && q2.empty);
	}

	T Top()
	{
		if (!q1.empty())
		{
			return q1.back();
		}
		else{
			return q2.back();
		}
	}

private:
	queue<T> q1;
	queue<T> q2;

};


//用一个数组实现两个栈
template<class T>
class ArryMakeTwoStack
{
public:
	ArryMakeTwoStack(size_t N)
		:_s1(new T[N])
		, _capacity(N)
	{
		_top1 = 0;
		_top2 = _capacity;
	}

	void Push1(const T& v)
	{
		ChackCapacity();
		_s[_top] = v;
		_top++;

	}
	//_top1 是从零开始的栈的栈顶元素下一个位置
	void Push2(const T& v)
	{
		ChackCapacity();
		_top--;
		_s[_top] = v;
	}
	//_top2是从_capacity-1开始的栈的栈顶元素所在位置
	void Pop1()
	{
		if (_top > 0){
			_top--;
		}
	}

	void Pop2()
	{
		if (_top <= _capacity){
			_top++:
		}
	}

	T& Top1()
	{
		if (!Empty1())
			return _s[_top1 - 1];
	}

	T& Top2()
	{
		if (!Empty())
			return _s[_top2];
	}

	bool Empty1()
	{
		return _top1 <= 0;
	}

	bool Empty2()
	{
		return _top >= _capacity;
	}

	~ArryMakeTwoStack()
	{
		if (_s){
			delete[] _s;
			_s = NULL;
		}
	}
private:
	void ChackCapacity()
	{
		if (_top1 >= _top2){
			size_t newsize = _capacity * 2 + 3;
			ArryMakeTwoStack<T> s1(newsize);
			while (!Empty1()){
				T top = Top1();
				Pop1();
				s1.Push1(top);
			}
			while (!Empty2()){
				T top = Top2();
				Pop2();
				s1.Push2(top);
			}
		}
		swap(*this, s1);
	}

	T* _s;
	size_t _top1;
	size_t _top2;
	size_t _capacity;

};
int main()
{
	

	system("pause");
	return 0;
}

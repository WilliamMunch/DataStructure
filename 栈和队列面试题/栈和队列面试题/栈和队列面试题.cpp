#include<iostream>
#include<windows.h>
#include<stack>
#include<queue>

using namespace std;

//template<class T>
//class Stack
//{
//public:
//	Stack(size_t size)
//		:start(NULL)
//	    ,_size(size)
//		, _capacity(size_t * 2 + 1)
//	{
//		ptr = new T[_size];
//	}
//
//	~Stack()
//	{
//		delete[] ptr;
//	}
//
//	T PushBack(T s)
//	{
//		
//	}
//	
//private:
//	T* start;
//	T* finnish;
//	T* end_of_storage;
//	size_t _size;
//	size_t _capacity;
//};
//用两个栈实现一个队列

template<class T>
class Queue
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
class Stack
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

int main()
{
	

	system("pause");
	return 0;
}

//#ifndef STACK_H_
//#define STACK_H_

#include<iostream>
#include<windows.h>

using namespace std;

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

int main()
{
	Stack<int> s;
	s.Push(1);
	s.Push(2);
	s.Push(3);
	cout << s.Top() << endl;
	s.Pop();
	cout << s.Top() << endl;

	system("pause");
	return 0;
}

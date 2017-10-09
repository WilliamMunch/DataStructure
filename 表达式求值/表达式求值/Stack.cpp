#include<iostream>
#include<assert.h>
#include<stdlib.h>
#include<string.h>

using namespace std;

//使用类型萃取来拷贝栈内元素

struct _TrueType
{
	bool Get()
	{
		return true;
	}
};

struct _FalseType
{
	bool Get()
	{
		return false;
	}
};

template<class _Tp>
struct TypeTraits
{
	typedef _FalseType _IsPODType;
};

template<>
struct TypeTraits<bool>
{
	typedef _TrueType _IsPODType;
};

template<>
struct TypeTraits<int>
{
	typedef _TrueType _IsPODType;
};

template<>
struct TypeTraits<float>
{
	typedef _TrueType _IsPODType;
};

template<>
struct TypeTraits<char>
{
	typedef _TrueType _IsPODType;
};

template<>
struct TypeTraits<unsigned char >
{
	typedef _TrueType _IsPODType;
};

template<>
struct TypeTraits< double >
{
	typedef _TrueType _IsPODType;
};

template<>
struct TypeTraits<long>
{
	typedef _TrueType _IsPODType;
};

template<>
struct TypeTraits< unsigned long>
{
	typedef _TrueType _IsPODType;
};

template<class T>
void Copy(T* dst, T* src, size_t size)
{
	if (TypeTraits<T>::_IsPODType().Get())
	{
		memcpy(dst, src, size);
	}
	else
	{
		for (size_t i = 0; i < size; ++i)
		{
			dst[i] = src[i];
		}
	}
}

template<class T>
struct TypeTraits< T* >
{
	typedef _TrueType _IsPODype;
};

//自主栈的实现
template<class T>
class Stack
{
public:

	Stack()
		:_capacity(0)
		, _size(0)
		, _pData(0)
	{};

	Stack(size_t& capacity)
		:_capacity(capacity)
		, _size(0)
		, _pData(NULL)
	{
		_pData = new T[_capacity]
	}

	Stack(const Stack<T>& s)
		:_capacity(s._capacity)
		, _size(s._size)
		, _pData(new T[s._capacity])
	{
		for (size_t i = 0; i < _size; ++i)
		{
			_pData[i] = s._pData[i];
		}
	}

	~Stack()
	{
		if (_pData != NULL){
			delete[] _pData;
			_pData = NULL;
		}
	}

	void Push(const T& value)
	{
		ChackCapacity();
		_pData[_size++] = value;
	}

	void Pop()
	{
		if (!Empty())
			_size--;
	}

	bool Empty()
	{
		return _size == 0;
	}

	T& Top()
	{
		if (!Empty())
			return _pData[_size - 1];
	}
	
	size_t Size()
	{
		return _size;
	}

	Stack& operator = (Stack<T> s)
	{
		swap(_pData, s._pData);
		_size = s._size;
		_capacity = s._capacity;
		return *this;
	}

private:
	void ChackCapacity()
	{
		if (_size >= _capacity){
			_capacity = 2 * _capacity + 3;
			T* tmp = new T[_capacity];
			/*for (size_t i = 0; i < _size; i++){
				tmp[i] = _pData[i]
			}*/
			Copy<T>(tmp, _pData, _size);
			delete[] _pData;
			_pData = tmp;
		}
	}
	T* _pData;
	size_t _size;
	size_t _capacity;

};

//表达式转换所用到的接口
int GetPriority(char ch, int flag);//获取优先级
bool IsOperator(char ch);//判断是否为操作符
void prefixionToSuffixion(char* dst, char* src);//中缀表达式转后缀表达式
int  SuffixionToValue(char *suffix, char *prefixion);//后缀表达式求值
//int main()
//{
//
//	system("pause");
//	return 0;
//}
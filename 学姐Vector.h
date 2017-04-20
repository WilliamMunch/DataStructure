#include<iostream>  
#include<stdlib.h>  
#include<assert.h>  
using namespace std;
typedef int DataType;
class Vector
{
public:
	explicit Vector(size_t capacity = 3)//C++提供了关键字explicit，可以阻止不应该允许的经过转换构造函数进行的隐式转换的发生dndhh  
	{
		_pData = (DataType*)malloc(capacity*sizeof(DataType));
		_capacity += 3;
		_size = 0;
	}
	// 有size个值为data的元素  
	Vector(size_t n, const DataType& data)
	{
		_pData = (DataType*)malloc(n*sizeof(DataType));
		_size = n;
		_capacity = n;
		for (size_t idx = 0; idx < _size; ++idx)
			_pData[idx] = data;
	}

	Vector(const Vector& v)
		: _capacity(v._capacity)
		, _size(v._size)
	{
		_pData = (DataType*)malloc(_capacity*sizeof(DataType));

		// 比较1和2的优缺点？  
		// 1采用memcpy是如果src和dst所指的内存区域重叠,那么这个函数并不能够确保source所在重叠区域在拷贝之前不被覆盖  
		//memcpy(_pData, v._pData, sizeof(DataType)*_size);  

		// 2采用for循环可能效率低，没有使用库函数的效率高，但是不会进行覆盖  
		for (size_t idx = 0; idx < _size; ++idx)
			_pData[idx] = v._pData[idx];
	}

	Vector& operator=(const Vector& v)
	{
		if (this != &v)
		{
			_pData = v._pData;
			_size = v._size;
			_capacity = v._capacity;
		}
		return *this;
	}
	~Vector()
	{
		if (_pData != NULL)
		{
			free(_pData);
			_pData = NULL;
			_size = _capacity = 0;

		}
	}

	/////////////////////////////////////  
	void PushBack(const DataType& data);
	void PopBack();
	void Insert(size_t pos, const DataType& data);
	void Erase(size_t pos);
	int Find(const DataType& data)const;
	void Clear();
	size_t Size()const;
	void ReSize(size_t size, const DataType& data);
	size_t Capacity()const;
	bool Empty()const;//不会改变顺序表的内容只是判断是否为空  
	DataType& Front();
	const DataType& Front()const;
	DataType& Back();
	const DataType& Back()const;
	void Assign(size_t n, const DataType& data);//赋num个值为val的元素到vector中.这个函数将会清除掉为vector赋值以前的内容.  
	DataType& operator[](size_t index);
	const DataType& operator[](size_t index)const;
	DataType& At(size_t index);//c++标准不要求vector<T>::operator[]进行下标越界检查，原因是为了效率，总是强制下标越界检查会增加程序的性能开销。设计vector是用来代替内置数组的，所以效率问题也应该考虑。不过使用operator[]就要自己承担越界风险了。  
	//如果需要下标越界检查，请使用at  
	const DataType& At(size_t index)const;

private:
	void _CheckCapacity();
	friend std::ostream& operator<<(std::ostream& _cout, const Vector& v);
private:
	DataType* _pData;//数组指针  
	size_t _capacity;//容量  
	size_t _size;//有效元素的个数  
};
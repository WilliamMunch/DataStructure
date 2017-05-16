#pragma once
#include <assert.h>
#include <iostream>

// 动态的
typedef int DataType;
class Vector
{
public:
	explicit Vector(size_t capacity = 3)
		: _capacity(capacity)
		, _size(0)
	{
		_pData = new DataType[_capacity];
	}

	Vector(DataType arr[], size_t size);

	// 有size个值为data的元素
	Vector(size_t n, const DataType& data);

	Vector(const Vector& v)
		: _capacity(v._capacity)
		, _size(v._size)
	{
		_pData = new DataType[_capacity];

		// 比较1和2的优缺点？
		// 1
		//memcpy(_pData, v._pData, sizeof(DataType)*_size);

		// 2
		for(size_t idx = 0; idx < _size; ++idx)
			_pData[idx] = v._pData[idx];
	}

	Vector& operator=(const Vector& v)
	{
		if(this != &v)
		{
			// 类似String
		}

		return *this;
	}

	~Vector()
	{
		if(_pData)
		{
			delete[] _pData;
			_pData = NULL;
			_capacity = 0;
			_size = 0;
		}
	}

	/////////////////////////////////////
	void PushBack(const DataType& data);
	void PopBack();
	void PushFront(const DataType& data);
	void PopFront();
	void Insert(size_t pos, const DataType& data);
	void Erase(size_t pos);
	int Find(const DataType& data)const;
	void Clear();

	size_t Size()const
	{
		return _size;
	}

	void ReSize(size_t size, const DataType& data = DataType());

	size_t Capacity()const
	{
		return _capacity;
	}

	bool Empty()const
	{
		return 0 == _size;
	}

	DataType& Front()
	{
		return _pData[0];
	}

	const DataType& Front()const
	{
		return _pData[0];
	}

	DataType& Back()
	{
		return _pData[_size-1];
	}

	const DataType& Back()const
	{
		return _pData[_size-1];
	}

	void Assign(size_t n, const DataType& data = DataType());

	DataType& operator[](size_t index)
	{
		assert(index >= _size);
		return _pData[index];
	}

	const DataType& operator[](size_t index)const
	{
		assert(index >= _size);
		return _pData[index];
	}

	DataType& At(size_t index)
	{
		assert(index >= _size);
		return _pData[index];
	}

	const DataType& At(size_t index)const
	{
		assert(index >= _size);
		return _pData[index];
	}

	private:
		void _CheckCapacity()
		{
			if(_size >= _capacity)
			{
				DataType* pTemp = new DataType[_capacity*2];
				_capacity *= 2;
				for (size_t idx = 0; idx < _size; ++idx)
					pTemp[idx] = _pData[idx];

				delete[] _pData;
				_pData = pTemp;
			}
		}
	friend std::ostream& operator<<(std::ostream& _cout, const Vector& v);
private:
	DataType* _pData;
	size_t _capacity;
	size_t _size;
};


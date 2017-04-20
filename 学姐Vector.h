#include<iostream>  
#include<stdlib.h>  
#include<assert.h>  
using namespace std;
typedef int DataType;
class Vector
{
public:
	explicit Vector(size_t capacity = 3)//C++�ṩ�˹ؼ���explicit��������ֹ��Ӧ������ľ���ת�����캯�����е���ʽת���ķ���dndhh  
	{
		_pData = (DataType*)malloc(capacity*sizeof(DataType));
		_capacity += 3;
		_size = 0;
	}
	// ��size��ֵΪdata��Ԫ��  
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

		// �Ƚ�1��2����ȱ�㣿  
		// 1����memcpy�����src��dst��ָ���ڴ������ص�,��ô������������ܹ�ȷ��source�����ص������ڿ���֮ǰ��������  
		//memcpy(_pData, v._pData, sizeof(DataType)*_size);  

		// 2����forѭ������Ч�ʵͣ�û��ʹ�ÿ⺯����Ч�ʸߣ����ǲ�����и���  
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
	bool Empty()const;//����ı�˳��������ֻ���ж��Ƿ�Ϊ��  
	DataType& Front();
	const DataType& Front()const;
	DataType& Back();
	const DataType& Back()const;
	void Assign(size_t n, const DataType& data);//��num��ֵΪval��Ԫ�ص�vector��.����������������Ϊvector��ֵ��ǰ������.  
	DataType& operator[](size_t index);
	const DataType& operator[](size_t index)const;
	DataType& At(size_t index);//c++��׼��Ҫ��vector<T>::operator[]�����±�Խ���飬ԭ����Ϊ��Ч�ʣ�����ǿ���±�Խ��������ӳ�������ܿ��������vector������������������ģ�����Ч������ҲӦ�ÿ��ǡ�����ʹ��operator[]��Ҫ�Լ��е�Խ������ˡ�  
	//�����Ҫ�±�Խ���飬��ʹ��at  
	const DataType& At(size_t index)const;

private:
	void _CheckCapacity();
	friend std::ostream& operator<<(std::ostream& _cout, const Vector& v);
private:
	DataType* _pData;//����ָ��  
	size_t _capacity;//����  
	size_t _size;//��ЧԪ�صĸ���  
};
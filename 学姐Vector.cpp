

#include"Vector.h"  
void Vector::_CheckCapacity()
{
	if (_size >= _capacity)
	{
		_pData = (DataType*)realloc(_pData, _capacity * 2 * (sizeof(DataType)));
		assert(_pData);
		_capacity *= 2;
	}
}
ostream& operator<<(ostream& _cout, const Vector& v)
{
	for (size_t index = 0; index < v._size; index++)
	{
		_cout << v._pData[index] << endl;
	}
	return _cout;
}
void Vector::PushBack(const DataType& data)
{
	_CheckCapacity();
	_pData[_size] = data;
	_size += 1;
}
void Vector::PopBack()
{
	assert(_size > 0);
	--_size;
}
void Vector::Insert(size_t pos, const DataType& data)
{
	assert(pos <= _size);
	int end = _size - 1;
	_CheckCapacity();
	while (end >= ((int)pos))
	{
		_pData[end + 1] = _pData[end];
		--end;
	}
	_pData[pos] = data;
	++_size;
}
void Vector::Erase(size_t pos)
{
	if (pos >= _size || _size == 0)
	{
		return;
	}
	int end = _size - 1;
	while ((int)pos <end)
	{
		_pData[pos] = _pData[pos + 1];
		pos++;
	}
	--_size;
}
int Vector::Find(const DataType& data)const
{
	int i = 0;
	for (int i = 0; i < (int)_size; i++)
	{
		if (_pData[i] == data)
		{
			return i;
		}
	}
	return 0;
}
void Vector::Clear()//将顺序表里的有效元素清空  
{
	if (_size == 0)
	{
		return;
	}
	_size = 0;
}
size_t Vector::Size()const
{
	return _size;
}
void Vector::ReSize(size_t size, const DataType& data)
{
	_CheckCapacity();
	if (size < _size)
	{
		_size = size;
	}
	if (size>_size)
	{

		for (size_t i = _size; i < size; i++)
		{
			_pData[i] = data;
		}
		_size = size;
	}

}
size_t Vector::Capacity()const
{
	return _capacity;
}
bool  Vector::Empty()const//不会改变顺序表的内容只是判断是否为空  
{
	if (_size == 0)
	{
		return true;
	}
	return false;
}
DataType&Vector::Front()//返回第一个元素的引用  
{
	return (*this)._pData[0];
}
const DataType& Vector::Front()const
{
	return (*this)._pData[0];
}
DataType& Vector::Back()//返回最后一个元素的引用  
{
	return (*this)._pData[_size - 1];
}
const DataType& Vector::Back()const
{
	return (*this)._pData[_size - 1];
}
void Vector::Assign(size_t n, const DataType& data)//赋num个值为val的元素到vector中.这个函数将会清除掉为vector赋值以前的内容.  
{
	free(_pData);
	_pData = NULL;
	_size = _capacity = 0;
	_pData = (DataType*)malloc(n*sizeof(DataType));
	for (int i = 0; i < n; i++)
	{
		_pData[i] = data;
	}
	_size = n;
	_capacity = n;
}
DataType& Vector::operator[](size_t index)
{
	return _pData[index];
}
const DataType& Vector::operator[](size_t index)const
{
	return _pData[index];
}
DataType& Vector::At(size_t index)
{
	assert(index <= _size);
	return _pData[index];
}
const DataType& Vector::At(size_t index)const
{

	assert(index <= _size);
	return _pData[index];
}


int main()
{
	Vector s1(5, 10);
	Vector s2(s1);
	s1.Insert(1, 6);
	s1.PushBack(11);
	s1.Erase(1);
	int i = s1.Capacity();
	/*s1.ReSize(12, 4);*/
	cout << i << endl;
	cout << s2 << endl;
	cout << s2.At(2) << endl;
	cout << "****" << endl;
	s2.ReSize(2, 2);
	cout << s2 << endl;
	system("pause");
	return 0;
}
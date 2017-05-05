#include<iostream>
#include<vector>
#include<stdlib.h>

using namespace std;

template<class T>
struct Trituple
{
	Trituple(size_t row, size_t col, const T& data)
	: _row(row)
	, _col(col)
	, _data(data)
	{}

	Trituple()
	{}
	
	size_t _row;
	size_t _col;
	T _data;
};

template<class T>
class SparseMatrix
{
public:
	SparseMatrix()
	{};

	template<typename T>
	friend ostream& operator<< (ostream& _cout, SparseMatrix<T>& s);
	

	SparseMatrix(int* arr, size_t row, size_t col, const T& invalid)
		: _row(row)
		, _col(col)
		, _invalid(invalid)
	{
		for (size_t i = 0; i < row; ++i)
		{
			for (size_t j = 0; j < col; ++j)
			{
				if (arr[i*row + j] != invalid)
					_sm.push_back(Trituple<T>(i, j, arr[i*row + j]));
			}
		}
	}

	T& Access(int row, int col)
	{
		/*for (size_t i = 0; i < _sm.size(); ++i)
		{
			if (_sm[i]._row == row && _sm[i]._col == col)
				return _sm[i]._data;
		}
		return _invalid;*/
		vector<Trituple<T>>::iterator it = _sm.begin();
		while (it != _sm.end())
		{
			if (it->_row == row && it->_col == col)
				return it->_data;
			++it;
		}
		return _invalid;
	}
	SparseMatrix<T> Transport()
	{
		SparseMatrix<T> sm;
		sm._col = _row;
		sm._row = _col;
		sm._invalid = invalid;
		for (size_t i = 0; i < col; i++){
			vector<Trituple<T>>::iterator it = _sm.begin();
			while (i != _sm.end()){
				if (i == it->_col){
					sm._sm.push_back(Trituple<T>(i, it->_row, it->_data));
					++it;
				}
			}
			return sm;
		}
	}

	SparseMatrix<T> FastTransport()
	{
		SparseMatrix<T> sm;
		sm._col = _row;
		sm._row = _col;
		sm._invalid = _invalid;
		sm._sm.resize(_sm.size());
		//统计每列有效元素个数
		int* pCount = new int[_col];
		memset(pCount, 0, sizeof(pCount[0] * _col));
		for (size_t i = 0; i < _sm.size(); ++i)
		{
			pCount[_sm[i]._col]++;
		}
		//定位每列起始位置
		int* pAddr = new int[_col];
		for (size_t i = 1; i < _col; i++)
		{
			pAddr[i] = pAddr[i - 1] + pCount[i - 1];
		}
		//放置元素到新空间
		for (size_t i = 0; i < _sm.size(); ++i)
		{
			int& addr = pAddr[_sm[i]._col];
			sm._sm[addr] = Trituple<T>(_sm[i]._col, _sm[i]._row, _sm[i]._data);
				addr++;
		}
		return sm;
	}
	
	SparseMatrix operator+(SparseMatrix& s)
	{
		//结果的行数、列数、无效元素与两操作数的相同
		SparseMatrix<T> res;
		res._row = _row;
		res._col = _col;
		res._invalid = _invalid;

		//定义两个迭代器分别指向两个操作数的_sm域
		vector<Trituple<T>>::iterator it1 = _sm.begin();
		vector<Trituple<T>>::iterator it2 = s._sm.begin();

		//1.只要没有读取到容器结尾就一直循环
		while (it1 != _sm.end() && it2 != s._sm.end())
		{
			//1.行数列数相等的情况下
			if (it1->_col == it2->_col && it1->_row == it2->_row)
			{
				//1.data的和有效，则将和push进去
				if (_invalid != (it1->_data + it2->_data))
				{
					res._sm.push_back(Trituple<T>(it1->_row, it2->_col, (it1->_data + it2->_data)));
				}
				++it1;
				++it2;
			}
			else
			{
				//2.it1的位置在it2的前面，则先push	it1，并将it1向后移动，it2不动
				if (it1->_row <= it2->_row
					&& it1->_col <= it2->_col)
				{
					res._sm.push_back(Trituple<T>(it1->_row, it1->_col, it1->_data));
					++it1;
				}
				//3.否则就剩下最后一种情况，it1在it2后面，将it2	push，it2后移，it1不动
				else
				{
					res._sm.push_back(Trituple<T>(it2->_row, it2->_col, it2->_data));
					++it2;
				}
			}
		}
		return res;
	}
	
private:
	vector< Trituple<T> > _sm;
	size_t _row;
	size_t _col;
	T _invalid;
};

template<typename T>
 ostream& operator<< (ostream& _cout, SparseMatrix<T>& s)
{
	for (size_t i = 0; i < s._row; ++i)
	{
		for (size_t j = 0; j < s._col; ++j)
		{
			_cout << s.Access(i, j) << " ";
		}
		_cout << endl;
	}
	return _cout;
}



void FunTest()
{
	int arr[][5] = {
		{ 2, 0, 5, 0, 0 },
		{ 0, 0, 0, 1, 0 },
		{ 0, 5, 7, 0, 0 },
		{ 0, 0, 0, 0, 0 },
		{ 9, 0, 0, 6, 0 } };
	int brr[][5] = {
		{ 1, 0, 1, 0, 0 },
		{ 0, 0, 0, 1, 0 },
		{ 0, 1, 1, 0, 0 },
		{ 0, 0, 0, 0, 0 },
		{ 1, 0, 0, 1, 0 },

	};
	SparseMatrix<int>  s1((int*)arr, 5, 5, 0);
	SparseMatrix<int>  s2((int*)brr, 5, 5, 0);
	SparseMatrix<int>  s3;
	s3 = s1 + s2;

	cout << s1 << endl;
	//s1.FastTransport();
	cout << s2 << endl;
	cout << s3 << endl;

		

	
}

int main()
{
	FunTest();
	system("pause");
	return 0;
}
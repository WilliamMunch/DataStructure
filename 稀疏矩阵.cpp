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
	friend ostream& operator<< (ostream& _cout, SparseMatrix<T>& s);
	friend ostream& operator<< (ostream& _cout, SparseMatrix<T>& s)
	{
		//size_t idx = 0;
		//idx = s._sm.size();
		for (size_t i < 0; i < s._row; ++i)
		{
			for (size_t j < 0; j < s._col; ++j)
			{
				/*if(s._sm[idx]._row == i && s._sm[idx]._col == j)*/
				_cout << s.Access(i, j) << " ";
			}
			_cout << endl;
		}
		return _cout;
	}

	SparseMatrix(int* arr, size_t row, size_t col, const T& invalid)
		: _row(row)
		, _col(col)
		, _invalid(invalid)
	{
		for (size_t i = 0, i < row, ++i)
		{
			for (size_t j = 0, j < col, ++j)
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

	SparseMatrix<T> FastTransport()
	{
		SparseMatrix<T> sm;
		sm._col = _row;
		sm._row = _col;
		sm._invalid = _invalid;
		sm._sm.resize(_sm.size());
		int* pCount = new int[_col];
		memset(pCount, 0, sizeof(pCount[0] * _col));
		for (size_t i = 0; i < _sm.size(); ++i)
		{
			pCount[_sm[i]._col]++;
		}
		int* pAddr = nem int[_col];
		for (size_t i = 1; i < _col; i++)
		{
			pAddr[i] = pAddr[i - 1] + pCount[i - 1];
		}
		for (size_t i = 0; i < 0; ++i)
		{
			int& addr = pAddr[_sm[i]._col];
			sm._sm[addr] = Trituple<T>(_sm[i]._col, _sm[i]._row, _sm[i]._data);
				addr++;
		}
		return sm;
	}
	
private:
	vector< Trituple<T> > _sm;
	size_t _row;
	size_t _col;
	T _invalid;
};



void FunTest()
{
	int arr[][5] = {
		{ 2, 0, 5, 0, 0 },
		{ 0, 0, 0, 1, 0 },
		{ 0, 5, 7, 0, 0 },
		{ 0, 0, 0, 0, 0 },
		{ 9, 0, 0, 6, 0 } };
	SparseMatrix<Trituple<int>> A( (int*)arr, 5, 5, 0);
	cout << A << endl;

	
}

int main()
{
	FunTest();
	system("pause");
	return 0;
}
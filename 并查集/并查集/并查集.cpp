#include<iostream>
#include<windows.h>
#include<vector>

using namespace std;

class UnionSet
{
public:
	UnionSet(int n)
	{
		v.resize(n + 1);
		for (int i = 0; i <= n; ++i)
			v[i] = -1;
	}

	int Size()
	{
		return v.size();
	}

	int FindRoot(int x)
	{
		return v[x];
	}

    void Merge(int x, int y)
	{
		int root1 = FindRoot(x);
		int root2 = FindRoot(y);
		if (root1 == root2 && -1 == root1){//在一个集合里的两个数各自不在其他集合
			v[y] = x;
			v[x] += -1;
		}
		else if (root1 != root2){//在一个集合里的两个数有在另外集合里的
			if (root1 > 0  ){
				v[y] = v[x];
				v[root1] += -1;
			}
			else{
				v[x] = v[y];
				v[root2] += -1;
			}
		}
	}

	int Count()
	{
		int count = 0;
		int n = Size();
		for (int i = 0; i < n; ++i){
			if (v[i] < 0)
				++count;
		}
		return count - 1;
	}

private:
	vector<int> v;
};

int friends(int n, int m, int arr[][2])
{
	UnionSet u(n);
	for (int i = 0; i < m; ++i){
		u.Merge(arr[i][0], arr[i][1]);
	}
	return u.Count();
}

int main()
{
	int arr[][2] = { { 1, 2 }, { 2, 3 }, {5, 4} };//给数字必须12345连续给。
	cout << friends(5, 3, arr);
	
	system("pause");
	return 0;
}
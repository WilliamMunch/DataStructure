#include<iostream>
#include<windows.h>
#include<vector>
#include<map>
#include<string>

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

	int FindRoot(int index)//找到这个数据成员所属组的根 
	{
		int root = index;
		while (v[root] >= 0){
			root = v[root];
		}
		return root;
	}

    void Merge(int x, int y)
	{
		int root1 = FindRoot(x);
		int root2 = FindRoot(y);

		if (root1 != root2){//代表数据成员的索引 x 与代表数据成员的索引y 不属于同一组
			v[root1] += v[root2];//第一组加上第二组的成员数量
			v[root2] = root1;//第二组组长把第一组根标识为自己的根。
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

int friends(int n, int m, string arr[][2])//int arr[][2])
{
	UnionSet u(n);
	map<string, int> StringMapIndex;
	StringMapIndex["小红"] = 5;
	StringMapIndex["小白"] = 1;
	StringMapIndex["小绿"] = 2;
	StringMapIndex["小黑"] = 3;
	StringMapIndex["小黄"] = 4;
	for (int i = 0; i < m; ++i){
		u.Merge(StringMapIndex[arr[i][0]], StringMapIndex[arr[i][1]]);
	}
	return u.Count();
}

int main()
{
	int arr[][2] = { { 1, 2 }, { 2, 3 }, {5, 4} };//给数字必须12345连续给。
	
	string srr[][2] = { { "小白", "小绿" }, { "小白", "小黑" }, { "小黄", "小红" } };

	//cout << friends(5, 3, arr) << endl;;
	cout << friends(5, 3, srr) << endl;
	system("pause");
	return 0;
}
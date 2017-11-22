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

	int FindRoot(int index)//�ҵ�������ݳ�Ա������ĸ� 
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

		if (root1 != root2){//�������ݳ�Ա������ x ��������ݳ�Ա������y ������ͬһ��
			v[root1] += v[root2];//��һ����ϵڶ���ĳ�Ա����
			v[root2] = root1;//�ڶ����鳤�ѵ�һ�����ʶΪ�Լ��ĸ���
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
	StringMapIndex["С��"] = 5;
	StringMapIndex["С��"] = 1;
	StringMapIndex["С��"] = 2;
	StringMapIndex["С��"] = 3;
	StringMapIndex["С��"] = 4;
	for (int i = 0; i < m; ++i){
		u.Merge(StringMapIndex[arr[i][0]], StringMapIndex[arr[i][1]]);
	}
	return u.Count();
}

int main()
{
	int arr[][2] = { { 1, 2 }, { 2, 3 }, {5, 4} };//�����ֱ���12345��������
	
	string srr[][2] = { { "С��", "С��" }, { "С��", "С��" }, { "С��", "С��" } };

	//cout << friends(5, 3, arr) << endl;;
	cout << friends(5, 3, srr) << endl;
	system("pause");
	return 0;
}
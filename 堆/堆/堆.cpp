#pragma once

#include<iostream>
#include<string.h>
#include<vector>
#include<assert.h>

using namespace std;

//利用仿函数代替比较运算符 
//Compare()(_v[child], _v[]parent) 其实是Compare( ) 创建一个临时对象 调用其operator()
template<class T>
struct Greater
{
	bool operator ()(const T& l, const T& r)
	{
		return l > r;
	}
};

template<class T>
struct Less
{
	bool operator ()(const T& l, const T& r)
	{
		return l < r;
	}
};

template<class T, class Compare = Greater<T>>
class Heap
{
public:
	Heap()
	{}

	bool Empty()
	{
		return _v.empty();
	}

	size_t Size()
	{
		return _v.size();
	}

	Heap(const T* arr,int n)
	{
		_v.reserve(n);//为了提高效率 一次性申请够空间 防止插入时空间不够再次申请。
		for (int i = 0; i < n; ++i)
		{
			_v.push_back(arr[i]);//一般和reserve()函数配合使用
		}

		for (int i = (int)(_v.size() - 2) / 2; i >= 0; --i)
		{
			AdjustDown(i);//请注意向下调整是被循环调用的 最早从树的最后一个父亲结点开始
			//目的是为了将原本vector中无规律的数变为符合堆的规律。
			//每一次调用完AdjustDown(i)只保证 i下子树是堆 
		}
	}

	void Pop()//移除堆顶方法
	{
		swap(_v[_v.size() - 1], _v[0]);//先将堆顶结点和堆最后结点互换位置 
		_v.pop_back();//之后移除原本是对顶的最后一个结点
		//之所以这么做是为了让原对顶的左右子树保持堆的性质。
		AdjustDown(0);//把原来是最后结点的现堆顶搞一次向下调整。
	}

	void Push(const T& data)//新插入结点
	{
		_v.push_back(data);//先将新结点权且放在最后以保证堆内其他结点符合堆的性质
		AdjustUp(_v.size() - 1);//注意调用向上调整时只调一次 向上调整是为了Push而存在的
	}

    const T& Top()
	{
		return _v[0];
	}

	void Printheap()
	{
		for (size_t i = 0; i < _v.size(); ++i){
			cout << _v[i] << " ";
		}
		cout << endl;
	}
private:
	void AdjustDown(int root)//向下调整
	{
		int parent = root;//已有最后一个父亲结点
		int child = parent * 2 + 1;//默认找到其左孩子
		while (child < _v.size()){
			if (child + 1 < _v.size() && Compare()(_v[child + 1], _v[child]))
			{
				child++;//这里是为了找到两个孩子里较大的准备和父亲换
			}
			else if (Compare()(_v[child], _v[parent])){
				swap(_v[child], _v[parent]);//如果大孩子比父亲大 则换
				parent = child;
				child = parent * 2 + 1;//向下继续
			}
			else{
				break;//大孩子比父亲小 次树是堆出循环  
			}
		}
	}

	void AdjustUp(int index)//向上调整
	{//注意此时除index外其余结点符合堆的性质
		int child = index;
		int parent = (child - 1) / 2;
		while (child > 0){
			if (Compare()(_v[child], _v[parent])){
				swap(_v[child], _v[parent]);//比父亲大和父亲换
				child = parent;
				parent = (child - 1) / 2;//向上调整
			}
			else{
				break;//比父亲小了 出循环
			}
		}
	}

	vector<int> _v;
};


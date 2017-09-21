#pragma once

#include<iostream>
#include<string.h>
#include<vector>
#include<assert.h>

using namespace std;

//���÷º�������Ƚ������ 
//Compare()(_v[child], _v[]parent) ��ʵ��Compare( ) ����һ����ʱ���� ������operator()
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
		_v.reserve(n);//Ϊ�����Ч�� һ�������빻�ռ� ��ֹ����ʱ�ռ䲻���ٴ����롣
		for (int i = 0; i < n; ++i)
		{
			_v.push_back(arr[i]);//һ���reserve()�������ʹ��
		}

		for (int i = (int)(_v.size() - 2) / 2; i >= 0; --i)
		{
			AdjustDown(i);//��ע�����µ����Ǳ�ѭ�����õ� ������������һ�����׽�㿪ʼ
			//Ŀ����Ϊ�˽�ԭ��vector���޹��ɵ�����Ϊ���϶ѵĹ��ɡ�
			//ÿһ�ε�����AdjustDown(i)ֻ��֤ i�������Ƕ� 
		}
	}

	void Pop()//�Ƴ��Ѷ�����
	{
		swap(_v[_v.size() - 1], _v[0]);//�Ƚ��Ѷ����Ͷ�����㻥��λ�� 
		_v.pop_back();//֮���Ƴ�ԭ���ǶԶ������һ�����
		//֮������ô����Ϊ����ԭ�Զ��������������ֶѵ����ʡ�
		AdjustDown(0);//��ԭ�����������ֶѶ���һ�����µ�����
	}

	void Push(const T& data)//�²�����
	{
		_v.push_back(data);//�Ƚ��½��Ȩ�ҷ�������Ա�֤�������������϶ѵ�����
		AdjustUp(_v.size() - 1);//ע��������ϵ���ʱֻ��һ�� ���ϵ�����Ϊ��Push�����ڵ�
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
	void AdjustDown(int root)//���µ���
	{
		int parent = root;//�������һ�����׽��
		int child = parent * 2 + 1;//Ĭ���ҵ�������
		while (child < _v.size()){
			if (child + 1 < _v.size() && Compare()(_v[child + 1], _v[child]))
			{
				child++;//������Ϊ���ҵ�����������ϴ��׼���͸��׻�
			}
			else if (Compare()(_v[child], _v[parent])){
				swap(_v[child], _v[parent]);//������ӱȸ��״� ��
				parent = child;
				child = parent * 2 + 1;//���¼���
			}
			else{
				break;//���ӱȸ���С �����Ƕѳ�ѭ��  
			}
		}
	}

	void AdjustUp(int index)//���ϵ���
	{//ע���ʱ��index����������϶ѵ�����
		int child = index;
		int parent = (child - 1) / 2;
		while (child > 0){
			if (Compare()(_v[child], _v[parent])){
				swap(_v[child], _v[parent]);//�ȸ��״�͸��׻�
				child = parent;
				parent = (child - 1) / 2;//���ϵ���
			}
			else{
				break;//�ȸ���С�� ��ѭ��
			}
		}
	}

	vector<int> _v;
};


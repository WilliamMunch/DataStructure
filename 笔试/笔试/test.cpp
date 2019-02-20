#pragma once

#include<iostream>
#include<vector>
#include<string>
#include<stdlib.h>
#include<assert.h>
#include<time.h>
#include<algorithm>
#include<unordered_map>


using namespace std;
//头条面试题，商品买卖

int max(int a, int b)
{
	return a > b ? a : b;
}

int get_max_p(const vector<int>& _v)
{
	int ret = 0;
	for (size_t i = 1; i < _v.size(); ++i){
		ret += max(_v[i] - _v[i - 1], 0);
	}
	return ret;
}
//只能够进行k次交易  动态规划问题
class A{
    virtual void func()
	{

	}
};

class B : public A{
    virtual void func2(int a)
	{

	}
};

int find_half(int* arr, unsigned int len)
{
	if (nullptr == arr || len <= 0)
		return -1;
	int cur = 0;
	int count = 0;
	for (unsigned int i = 0; i < len; ++i)
	{
		if (0 == count){
			cur = arr[i];
			count = 1;
		}
		if (cur == arr[i]){
			++count;
		}
		else {
			--count;
		}
	}
	return cur;
}

//洗牌算法
void shuffle1(vector<int>& arr)
{
	for (int i = arr.size() - 1; i >= 0; ++i)
	{
		srand((unsigned int)time(NULL));
		swap(arr[rand() % (i + 1)], arr[i]);
	}
	return;
}

//单链表的排序

//节点结构
struct node
{
	int val;
	struct node * next;
	node(int _val, struct node* _next)
		:val(_val)
		,next(_next)
	{}
};

typedef struct node  node;

//打印函数
void printList(node* mylist);
//排序函数
//插入排序
void insertSort(node* mylist);
//冒泡排序
void bubbleSort(node* mylist);
//简单选择
void selectSort(node* mylist);
//快速排序
void list_quick_sort(node* mylist);

void printList(node* mylist)
{
	node * cur = mylist->next;
	while (cur != NULL)
	{
		printf("%d ", cur->val);
		cur = cur->next;
	}
	printf("\n");
}

node*  sort_part(node* pstart, node* pend)
{
	if (pstart->next == pend || pstart == pend)
		return pstart;
	node* pprev = pstart;
	node* pcur = pstart;
	node* pkey = pcur;
	while (pcur != pend)
	{
		if (pcur->val < pkey->val)
		{
			pprev = pprev->next;
			swap(pcur->val, pprev->val);
		}
		pcur = pcur->next;
	}
	swap(pprev->val, pkey->val);
	return pprev;
}

void _list_quick_sort(node* pstart , node* pend)
{
	if (pstart == pend || pstart->next == pend)
		return;
	node* mid = sort_part(pstart, pend);
	_list_quick_sort(pstart, mid);
	_list_quick_sort(mid->next, pend);
}

void list_quick_sort(node*  listhead)
{
	if (nullptr == listhead || nullptr == listhead->next)
		return;
	node* pstart = listhead->next;
	node* pend = nullptr;
	_list_quick_sort(pstart, pend);
}

int _quick_sort(int* arr, int begin,  int end)
{
	if (nullptr == arr )
		return 0;
	int key = arr[end];
	int cur = begin;
    int prev = cur - 1;
	while (cur != end)
	{
		if (arr[cur] < key && ++prev != cur)
			swap(arr[cur], arr[prev]);
		++cur;
	}
	swap(arr[++prev], arr[end]);
	return prev;
}

void quick_sort(int* arr, int begin, int end)
{
	if (nullptr == arr || begin > end)
		return;

	int mid = _quick_sort(arr, begin, end);
	quick_sort(arr, begin, mid - 1);
	quick_sort(arr, mid + 1, end);
}

#define  COUNT_OF(x)  sizeof(x)/sizeof(x[0])


void adjustdown(int* arr, int root, int size)
{
	int parent = root;
	int child = parent * 2 + 1;
	while (child < size)
	{
		if (child + 1 < size && arr[child] < arr[child + 1])
			swap(arr[child], arr[child + 1]);
		if (arr[child] > arr[parent])
		{
			swap(arr[child], arr[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
			break;
	}
}

void heap_sort(int* arr, int size)
{
	if (arr == nullptr)
		return;
	int end = size - 1;
	for (int i = (size - 1) >> 1; i >= 0; --i)
	{
		adjustdown(arr, i, size);
	}
	while (end > 0)
	{
		swap(arr[0], arr[end]);
		adjustdown(arr, 0, end);
		--end;
	}
}


void Fullsort(int* arr, int size, int n)
{
	if (size == n)
	{
		for (int i = 0; i < size; ++i)
			printf("%d ", arr[i]);
		printf("\n");
	}
	for (int i = n; i < size; ++i)
	{
		swap(arr[i], arr[n]);
		Fullsort(arr, size, n + 1);
		swap(arr[i], arr[n]);
	}
}

bool IsEmptyStr = false;

int my_atoi(char* str)
{
	int ret = 0;
	char* fristf   = nullptr;
	bool  issigned = true;
	if (nullptr == str)
	{
		IsEmptyStr = true;
		return 0;
	}
	if (*str == '-')
	{
		issigned = false;
		++str;
	}
	else if (*str == '+')
	{
		++str;
	}
	while (*str++ == ' ')
	fristf = str;
	while (*fristf != '\0')
	{
		ret = (int)((*fristf - '0')  + (ret * 10));
		++fristf;
	}
	return  issigned ? ret : 0 - ret;
}

//两个有序序列中第K大的数

int find_kth_elem(int* arr, int aleft, int aright, \
	int* brr, int bleft, int bright, int k)
{
	//递归出口  两个有序队列中的一个 至此已经完全被淘汰了   另一个队列的第Kth就是答案
	if (aleft > aright)
		return brr[bleft + k - 1];
	if (bleft > bright)
		return arr[aleft + k - 1];

	int amid = (aright - aleft) >> 1;
	int bmid = (bright - bleft) >> 1;

	int halflen = amid - aleft + bmid - bleft + 2;
	if (arr[amid] < brr[bmid])
	{
		if (halflen > k)
			return find_kth_elem(arr, aleft, aright,\
			brr, bleft, bmid - 1, k);
		else
			return find_kth_elem(arr, amid + 1, aright, \
			brr, bleft, bright, k - (amid - aleft + 1));
	}
	else
	{
		if (halflen > k)
			return find_kth_elem(arr, aleft, amid - 1, \
			brr, bleft, bright, k);
		else
			return find_kth_elem(arr, aleft, aright, \
			brr, bleft, bmid - 1, k - (bmid - bleft, +1));
	}
}

//寻找已经排好序的数组的某个数的起止下标

vector<int> serachrange(vector<int>& _v, int target)
{
	if (_v.empty())
		return vector<int>{-1, -1};
	int left = 0;
	int right = _v.size() - 1;
	while (left < right)
	{
		int mid = (right - left) >> 1;
		if (_v[mid] < target) left = mid + 1;
		else                  right = mid;
	}
	int start = left;
	int end = left;
	for (; _v[start] == target && start >= 0; --start);
	for (; _v[end] == target && end < _v.size(); ++end);
	
	return  vector<int>{start + 1, end - 1};
}

// a + b + c = 0;
vector<vector<int>> tree_sum(vector<int>&  nums)
{
	sort(nums.begin(), nums.end());
	vector<vector<int>> ret;
	for (int i = 0; i < nums.size(); ++i)
	{
		if (i > 0 && nums[i] == nums[i + 1])
			continue;
		int left = i + 1;
		int right = nums.size() - 1;
		while (left < right)
		{
			int tar = nums[i] + nums[left] + nums[right];
			if (tar > 0)  --right;
			else if (tar < 0)  ++left;
			else
			{
				ret.push_back(vector<int> {nums[i], nums[left], nums[right]});
				while (nums[left] == nums[left + 1]) ++left;
				while (nums[right] == nums[right - 1]) --right;
				++left;
				--right;
			}
		}
	}
	return ret;
}

//跳台阶问题

int climbStairs(int n) {
	climb_Stairs(0, n);
}

int climb_Stairs(int i, int n) {
	if (i > n) {
		return 0;
	}
	if (i == n) {
		return 1;
	}
	return climb_Stairs(i + 1, n) + climb_Stairs(i + 2, n);
}



void func1()
{
	int arr[] = { 5, 1, 7, 4, 2, 9, 6, 3, 8 };
	//	//程序都是针对有头结点的单向链表
	node* mylist = new node(0, NULL);
	int len = sizeof(arr) / sizeof(arr[0]);
	int i = 0;
	node* cur = mylist;
	while (i < len)
	{
		node* newnode = new node(arr[i], NULL);
		cur->next = newnode;
		cur = newnode;
		++i;
	}
	list_quick_sort(mylist);
	printList(mylist);
}

void func2()
{
	int arr[] = { 2, 5, 1, 9, 4, 3, 6, 8, 7, 0 };
	int brr[] = { 1, 2, 3 };
	printf("%d \n", COUNT_OF(arr));
	int size = COUNT_OF(arr);
	//quick_sort(arr, 0, size - 1);
	heap_sort(arr, COUNT_OF(arr));
	Fullsort(brr, COUNT_OF(brr), 0);
	for (int i = 0; i < COUNT_OF(arr); ++i)
		printf("%d  ", arr[i]);
	printf("\n");
	char* str = "-   19265";
	printf("%d", my_atoi(str));
}

void func3()
{
	int arr[] = { 4, 7, 9, 10, 29, 30, 57, 99 };
	int brr[] = { 2, 3, 6, 7, 9, 44, 66, };
	int ret = find_kth_elem(arr, 0, COUNT_OF(arr) - 1, brr, 0, COUNT_OF(brr) - 1, 6);
	cout << ret << endl;
	int crr[] = { 2, 4, 5, 7, 7, 7, 9, 20, 29 };
	vector<int> _v(crr, crr + 8);
	vector<int> range = serachrange(_v, 7);
}

int main()
{
	//func1();
	//func2();
	func3();
	system("pause");
	return 0;
}

#include<assert.h>
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<iostream>

using namespace std;

//#pragma warning (disable:4996);

typedef int DataType;

typedef struct Node{
	struct Node* next;
	DataType data;

	Node(DataType value)
		:data(value)
		,next(nullptr)
	{}
}Node, *PNode, ListNode;

//初始化单链表
void InitList(PNode* pHead);
//创建一个新节点
PNode BueNode(DataType data);
//尾插一个节点
void PushBack(PNode* pHead, DataType data);
//尾删一个节点
void PopBack(PNode* pHead);
//打印链表
void PrintList(PNode pHead);
//从尾到头打印单链表
void PrintListFromTailtoHead(PNode pHead);
//头插一个节点
void PushFront(PNode* pHead, DataType data);
//头删一个节点
void PopFront(PNode* pHead);
//寻找链表中第一个值域是data的节点
PNode Find(PNode pHead, DataType data);
//在pos位置后插入
void Insert(PNode pos, DataType data);
//在pos位置前插入
void InsertNotHeadNode(PNode pos, DataType data);
//删除一个节点
void Erase(PNode* pHead, PNode pos);
void Remove(PNode* pHead, DataType data);
//删除一个无头单链表的非尾节点
void DeleteNotTailNode(PNode pos);
//删除所有值为data的节点
void RemoveAll(PNode* pHead, DataType data);
//得出链表大小
int Size(PNode pHead);
//找最后一个节点
PNode Back(PNode pHead);
//判断两个个链表是否交叉 
int IsListCross(PNode pHead1, PNode pHead2);
//判断两个个链表是否交叉 并求交点
PNode GetCrossNode(PNode pHead1, PNode pHead2);
//是否带环
PNode HasCircle(PNode pHead);
//环周长
int GetCircleLen(PNode pMeetNode);
//判断两个可能带环的链表是否相交。
int IfCrossWithCricle(PNode pHead1, PNode pHead2);
//获得带环单链表的入口点
PNode GetEnterNode(PNode pHead, PNode pMeetNode);
//逆置单链表
PNode Reverse(PNode pHead);
//单链求解拟约瑟夫环（表已成环）
PNode Josephcircle(PNode pHead, int n);

void MergeSort(PNode* pNode);







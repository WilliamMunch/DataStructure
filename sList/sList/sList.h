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

//��ʼ��������
void InitList(PNode* pHead);
//����һ���½ڵ�
PNode BueNode(DataType data);
//β��һ���ڵ�
void PushBack(PNode* pHead, DataType data);
//βɾһ���ڵ�
void PopBack(PNode* pHead);
//��ӡ����
void PrintList(PNode pHead);
//��β��ͷ��ӡ������
void PrintListFromTailtoHead(PNode pHead);
//ͷ��һ���ڵ�
void PushFront(PNode* pHead, DataType data);
//ͷɾһ���ڵ�
void PopFront(PNode* pHead);
//Ѱ�������е�һ��ֵ����data�Ľڵ�
PNode Find(PNode pHead, DataType data);
//��posλ�ú����
void Insert(PNode pos, DataType data);
//��posλ��ǰ����
void InsertNotHeadNode(PNode pos, DataType data);
//ɾ��һ���ڵ�
void Erase(PNode* pHead, PNode pos);
void Remove(PNode* pHead, DataType data);
//ɾ��һ����ͷ������ķ�β�ڵ�
void DeleteNotTailNode(PNode pos);
//ɾ������ֵΪdata�Ľڵ�
void RemoveAll(PNode* pHead, DataType data);
//�ó������С
int Size(PNode pHead);
//�����һ���ڵ�
PNode Back(PNode pHead);
//�ж������������Ƿ񽻲� 
int IsListCross(PNode pHead1, PNode pHead2);
//�ж������������Ƿ񽻲� ���󽻵�
PNode GetCrossNode(PNode pHead1, PNode pHead2);
//�Ƿ����
PNode HasCircle(PNode pHead);
//���ܳ�
int GetCircleLen(PNode pMeetNode);
//�ж��������ܴ����������Ƿ��ཻ��
int IfCrossWithCricle(PNode pHead1, PNode pHead2);
//��ô������������ڵ�
PNode GetEnterNode(PNode pHead, PNode pMeetNode);
//���õ�����
PNode Reverse(PNode pHead);
//���������Լɪ�򻷣����ѳɻ���
PNode Josephcircle(PNode pHead, int n);

void MergeSort(PNode* pNode);







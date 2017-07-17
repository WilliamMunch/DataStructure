//#include<iostream>
//#include<assert.h>

//template<class T>
//struct ListNode{
//	ListNode<T>* next;
//	T _data;
//	Node(const T& data)
//		:_data(data)
//		, next(NULL)
//	{}
//};
//
//template<class T>
//class SIMPLE_LIST
//{
//	typedef ListNode<T> Node;
//	typedef ListNode<T>* PNode;
//public:
//	void InitList(PNode* pHead)
//	{
//		assert(pHead);
//		*pHead = NULL;
//	}
//
//	PNode BueNode(T data)
//	{
//		PNode pTemp = new Node(data);
//		
//		return pTemp;
//	}
//
//	void PushBack(PNode* pHead, T data)
//	{
//		assert(pHead);
//
//		if (NULL == *pHead)
//			*pHead = BueNode(data);
//		else{
//			/*  PNode pCur = *pHead;
//			while(pCur->next){
//			pCur = pCur->next;
//			}
//			pCur->next = BueNode(data);*/
//			PNode pCur = *pHead;
//			PNode pPre = pCur;
//			while (pCur){
//				pPre = pCur;
//				pCur = pCur->next;
//			}
//			pPre->next = BueNode(data);
//		}
//
//		SIMPLE_LIST(T data,PNode   )
//		{
//			InitList()
//		}
//
//	};
//private:
//	PNode pHead;
//
//};

#include<assert.h>
#include<iostream>
#include<stdlib.h>
#include<malloc.h>

//#pragma warning (disable:4996);

typedef int DataType;

typedef struct Node{
	struct Node* next;
	DataType data;
}Node, *PNode;

//初始化单链表
void InitList(PNode* pHead);
//创建一个新节点
PNode BueNode(DataType data);
//尾插一个节点
void PushBack(PNode* pHead, DataType data);

void PrintList(PNode pHead);
//合并两个有序单链表，合并后依然有序
PNode ComBineList(PNode pHead1, PNode pHead2);



void InitList(PNode* pHead)
{
	assert(pHead);
	*pHead = NULL;
}

PNode BueNode(DataType data)
{
	PNode pTemp = (PNode)malloc(sizeof(Node));
	if (pTemp)
	{
		pTemp->data = data;
		pTemp->next = NULL;
	}
	return pTemp;
}

void PushBack(PNode* pHead, DataType data)
{
	assert(pHead);

	if (NULL == *pHead)
		*pHead = BueNode(data);
	else{
		/*  PNode pCur = *pHead;
		while(pCur->next){
		pCur = pCur->next;
		}
		pCur->next = BueNode(data);*/
		PNode pCur = *pHead;
		PNode pPre = pCur;
		while (pCur){
			pPre = pCur;
			pCur = pCur->next;
		}
		pPre->next = BueNode(data);
	}
}

void PrintList(PNode pHead)
{
	PNode pCur = pHead;
	while (pCur){
		printf("%d->", pCur->data);
		pCur = pCur->next;
	}
	printf("NULL");
	printf("\n");
}

PNode ComBineList(PNode pHead1, PNode pHead2)
{
	if (!pHead1) return pHead2;
	if (!pHead2) return pHead1;
	PNode pL1 = pHead1;
	PNode pL2 = pHead2;
	PNode pNewHead = NULL;
	
	if (pL1->data < pL2->data){
		pNewHead = pHead1;
		pL1 = pL1->next;
	}
	else{
		pNewHead = pHead2;
		pL2 = pL2->next;
	}
	PNode pNewListNode = pNewHead;
	while (pL1 && pL2){
		if (pL1->data < pL2->data){
			pNewListNode->next = pL1;
			pL1 = pL1->next;
		}
		else{
			pNewListNode->next = pL2;
			pL2 = pL2->next;
		}
		pNewListNode = pNewListNode->next;
	}
	if (pL1){
		pNewListNode->next = pL1;
	}
	if (pL2){
		pNewListNode->next = pL2;
	}
	return pNewHead;
}

template<typename T>
T add(T a)
{
	return ((1 + a)*a) >> 1;
}

int main()
{
	printf("%d",add(5));
	system("pause");
	return 0;
}

//int main()
//{
//	PNode A ;
//	PNode B ;
//	InitList(&A);
//	InitList(&B);
//	PushBack(&A, 1);
//	PushBack(&A, 4 );
//	PushBack(&A, 5);
//	PushBack(&A, 7);
//	PushBack(&A, 9);
//	PushBack(&A, 11);
//	PushBack(&A, 13);
//	PushBack(&B, 3);
//	PushBack(&B, 6);
//	PushBack(&B, 7);
//	PushBack(&B, 8);
//	PushBack(&B, 10);
//	PushBack(&B, 15);
//	PushBack(&B, 16);
//	PrintList(A);
//	PrintList(B);
//	PrintList(ComBineList(A, B));
//	system("pause");
//	return 0;
//}


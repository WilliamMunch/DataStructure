#include"sList.h"

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
	if (NULL == *pHead)
		*pHead = BueNode(data);
	else{
		/*	PNode pCur = *pHead;
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

void PushFront(PNode* pHead, DataType data)
{
	PNode pNewNode = BueNode(data);
	assert(pHead);
	if (pNewNode){
		pNewNode->next = *pHead;
		*pHead = pNewNode;
	}
}

void PopFront(PNode* pHead)
{
	PNode pDel = NULL;
	assert(pHead);
	if (NULL == *pHead)
		return;

	pDel = *pHead;
	*pHead = (*pHead)->next;
	free(pDel);

}

void PopBack(PNode* pHead)
{
	assert(pHead);
	if (NULL == *pHead){
		return;
	}
	else if (NULL == (*pHead)->next){
		free(*pHead);
		*pHead = NULL;
	}
	else{
		PNode pCur = *pHead;
		PNode pNewTail = NULL;
		while (pCur->next->next){
			pCur = pCur->next;
		}
		pNewTail = pCur;
		free(pCur->next);
		pNewTail->next = NULL;
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

void PrintListFromTailtoHead(PNode pHead)
{
	//if(NULL == pHead){return ;}
	//PrintListFromTailtoHead(pHead->next);
	//printf("%d->",pHead->data);

	if (pHead){
		PrintListFromTailtoHead(pHead->next);
		printf("%d->", pHead->data);
	}
}

PNode Find(PNode pHead, DataType data)
{
	PNode pCur = pHead;
	assert(pHead);
	while (pCur){
		if (pCur->data == data)
			return pCur;
		pCur = pCur->next;
	}
	return NULL;
}

void Insert(PNode pos, DataType data)
{
	PNode pNewNode = NULL;
	assert(pos);
	if (NULL == pos){ return; }
	pNewNode = BueNode(data);
	pNewNode->next = pos->next;
	pos->next = pNewNode;
}

void Erase(PNode* pHead, PNode pos)
{
	assert(pHead);
	if (NULL == *pHead || NULL == pos)
		return;
	if (pos == *pHead){
		*pHead = pos->next;
		free(pos);
	}
	else{
		PNode pPre = *pHead;
		while (pPre->next != pos){
			pPre = pPre->next;
		}
		pPre->next = pos->next;
		free(pos);
	}
}

void DeleteNotTailNode(PNode pos)
{
	assert(pos);
	if (NULL == pos || NULL == pos->next)
		return;
	pos->data = pos->next->data;
	pos->next = pos->next->next;

}

void InsertNotHeadNode(PNode pos, DataType data)
{
	PNode pNewNode = BueNode(pos->data);
	if (NULL == pos)
		return;
	if (pNewNode){
		pNewNode->next = pos->next;
		pos->next = pNewNode;
		pos->data = data;
	}

}

void Remove(PNode* pHead, DataType data)
{
	assert(pHead);
	Erase(pHead, Find(*pHead, data));
}

void RemoveAll(PNode* pHead, DataType data)
{
	PNode pPre = *pHead;
	PNode pCur = (*pHead)->next;
	assert(pHead);
	while (pCur)
	{
		if (pCur->data == data){
			pPre->next = pCur->next;
			free(pCur);
			pCur = pPre->next;
		}
		else{
			pCur = pCur->next;
		}
	}
	if ((*pHead)->data == data)
	{
		pCur = *pHead;
		*pHead = (*pHead)->next;
		free(pCur);
	}
}

int Size(PNode pHead)
{
	PNode pCurNode = pHead;
	int count = 0;
	while (pCurNode){
		count++;
		pCurNode = pCurNode->next;
	}
	return count;
}

PNode Back(PNode pHead)
{
	assert(pHead);
	while (pHead->next){
		pHead = pHead->next;
	}
	return pHead;
}

//////////////////////////////////////////
int IsListCross(PNode pHead1, PNode pHead2)
{
	PNode pTailNode1 = pHead1;
	PNode pTailNode2 = pHead2;
	if (NULL == pHead1 || NULL == pHead2)
		return 0;
	while (pTailNode1->next)
		pTailNode1 = pTailNode1->next;
	while (pTailNode2->next)
		pTailNode2 = pTailNode2->next;
	if (pTailNode1 == pTailNode2)
		return 1;
	return 0;
}

PNode GetCrossNode(PNode pHead1, PNode pHead2)
{
	int count1 = 0;
	int count2 = 0;
	PNode pL1 = pHead1;
	PNode pL2 = pHead2;
	int gap = 0;
	if (NULL == pHead1 || NULL == pHead2)
		return 0;
	if (0 == IsListCross(pHead1, pHead2))
		return NULL;

	count1 = Size(pHead1);
	count2 = Size(pHead2);
	gap = count1 - count2;
	if (gap>0){
		while (gap--){
			pL1 = pL1->next;
		}
	}
	else{
		while (gap++){
			pL2 = pL2->next;
		}
	}
	while (pL1 != pL2){
		pL1 = pL1->next;
		pL2 = pL2->next;
	}
	return pL2;
}

PNode HasCircle(PNode pHead)
{
	PNode pFast = pHead;
	PNode pSlow = pHead;
	assert(pHead);
	while (pFast &&  pFast->next)
	{
		pFast = pFast->next->next;
		pSlow = pSlow->next;
		if (pFast == pSlow){
			return pFast;
		}
	}
	return NULL;
}

int GetCircleLen(PNode pMeetNode)
{
	PNode pCurNode = pMeetNode;
	int count = 1;
	if (NULL == pMeetNode)
		return 0;
	while (pCurNode->next != pMeetNode){
		count++;
		pCurNode = pCurNode->next;
	}
	return count;
}

PNode GetEnterNode(PNode pHead, PNode pMeetNode)
{
	PNode pH = pHead;
	PNode pM = pMeetNode;
	if (NULL == pHead || NULL == pHead->next)
		return 0;
	while (pH != pM){
		pH = pH->next;
		pM = pM->next;
	}
	return pH;
}

int IfCrossWithCricle(PNode pHead1, PNode pHead2)//判断两个可能带环的链表是否相交。
{
	PNode pMeetNode1 = HasCircle(pHead1);
	PNode pMeetNode2 = HasCircle(pHead2);
	if (NULL == pMeetNode1 && NULL == pMeetNode2){
		return IsListCross(pHead1, pHead2);//判断两个个链表是否交叉 
	}
	else if (pMeetNode1 && pMeetNode2){
		PNode pCur = pMeetNode1;
		while (pCur->next != pMeetNode2){
			if (pCur == pMeetNode2){
				return 2;
			}
			pCur = pCur->next;
			if (pCur == pMeetNode1)
				return 0;
		}
		if (pCur->next == pMeetNode2)
			return 2;
	}
	return 0;
}

PNode Reverse(PNode phead)
{
	if (nullptr == phead && nullptr == phead->next)
		return phead;
	PNode pPre = phead;
	PNode pCur = pPre->next;
	PNode pNext = pCur->next;
	while (pNext){
		pCur->next = pPre;
		pPre = pCur;
		pCur = pNext;
		pNext = pNext->next;
	}
	pCur->next = pPre;
	phead->next = nullptr;
	return pCur;
}

PNode Josephcircle(PNode pHead, int n)
{
	if (NULL == pHead)
		return NULL;
	PNode pCur = pHead;
	while (pCur->next != pCur){
		PNode pDel = pCur->next;
		int count = n;
		while (--count){
			pCur = pCur->next;
			pDel = pDel->next;
		}
		pCur->data = pDel->data;
		pCur->next = pDel->next;
		free(pDel);
	}
	return pCur;
}

PNode GetListMid(PNode pNode)
{
	if (pNode == NULL)
		return NULL;
	PNode pFast = pNode->next;
	PNode pSlow = pNode;
	while (pFast != NULL){
		pFast = pFast->next;
		if (pFast != NULL){
			pFast = pFast->next;
			pSlow = pSlow->next;
		}
	}
	return pSlow;
}
//
//PNode MergeList(PNode p1, PNode p2)
//{
//	if (p1 == NULL)
//		return p2;
//	if (p2 == NULL)
//		return p1;
//	PNode plist1 = p1;
//	PNode plist2 = p2;
//	PNode pTemp = NULL;
//	if (plist1->data <= plist2->data){
//		pTemp = plist1;
//		plist1 = plist1->next;
//	}
//	else{
//		pTemp = plist2;
//		plist2 = plist2->next;
//	}
//	PNode pHead = pTemp;
//	while (plist1 && plist2){
//		if (plist1->data <= plist2->data){
//			pTemp->next = plist1;
//			pTemp = plist1;
//			plist1 = plist1->next;
//		}
//		else
//		{
//			pTemp->next = plist2;
//			pTemp = plist2;
//			plist2 = plist2->next;
//		}
//	}
//	pTemp->next = plist1 ? plist1 : plist2;
//	return pHead;
//}


PNode merge_list(PNode plist1, PNode plist2)
{
	if (nullptr == plist1)
		return plist2;
	if (nullptr == plist2)
		return plist1;
	PNode ptemp = nullptr;
	if (plist1->data < plist2->data)
	{
		ptemp = plist1;
		plist1 = plist1->next;
	}
	else
	{
		ptemp  = plist2;
		plist2 = plist2->next;
	}
	PNode phead = ptemp;
	while (plist1 && plist2)
	{
		if (plist1->data <= plist2->data)
		{
			ptemp->next = plist1;
			plist1 = plist1->next;
			ptemp = ptemp->next;
		}
		else
		{
			ptemp->next = plist2;
			plist2 = plist2->next;
			ptemp = ptemp->next;
		}
	}
	ptemp->next = plist1 ? plist1 : plist2;
	return phead;
}

PNode merge_lists(PNode lists[], int n)
{
	if (NULL == lists)
		return NULL;
	while (n > 1)
	{
		int k = (n + 1) >> 1;
		for (int i = 0; i < k; ++i)
			lists[i] = merge_list(lists[i], lists[i + k]);
		n = k;
	}
	return lists[0];
}

PNode sort_part(PNode pbegin, PNode pend)
{
	if (pbegin->next == pend || pbegin == pend)
		return pbegin;
	PNode pkey = pbegin;
	PNode pcur = pbegin;
	PNode pprev = pbegin;
	while (pcur != pend)
	{
		if (pcur->data < pkey->data)
		{
			pprev = pprev->next;
			if (pcur != pprev)
				swap(pcur->data, pprev->data);
		}
		pcur = pcur->next;
	}
	swap(pprev->data, pkey->data);
	return pprev;
}

void _quick_sort(PNode pbegin, PNode pend)
{
	if (pbegin == pend || pbegin->next == pend)
		return;
	PNode pmid = sort_part(pbegin, pend);
	_quick_sort(pbegin, pmid);
	_quick_sort(pmid->next, pend);
}

void quick_sort(PNode pHead)
{
	if (nullptr == pHead || pHead->next == nullptr)
		return;
	_quick_sort(pHead, nullptr);
}

PNode MergeSort(PNode pNode)
{
	if (pNode == NULL || pNode->next == NULL)
		return pNode;
	PNode pBegin1 = pNode;
	PNode pMid = GetListMid(pNode);
	PNode pBegin2 = pMid->next;
	pMid->next = NULL;
	pBegin1 = MergeSort(pBegin1);
	////pBegin2 = MergeSort(pBegin2);
	return MergeList(pBegin1, pBegin2);
}

//单链表每K个拟制
PNode K_Group_Reverse(PNode phead, int k)
{
	if (nullptr == phead || nullptr == phead->next && k <= 1)
		return phead;
	int num = 0;
	PNode preheader = new Node(-1);
	preheader->next = phead;
	PNode pre = preheader, cur = preheader,/* tmp*/ nex;
	while (cur = cur->next)
		++num;
	while (num >= k){
		cur = pre->next;
		nex = cur->next;
		for (int i = 1; i < k; ++i){
			cur->next = nex->next;
			nex->next = pre->next;
			pre->next = nex;
			nex = cur->next;
		}
		pre = cur;
		num -= k;
	}
    delete preheader;
	return preheader->next;
}

PNode Rotate_K(PNode phead, int k)
{
	if (nullptr == phead || nullptr == phead->next)
		return phead;
	int len = 1;
	PNode newH = phead;
	PNode tail = phead;
	while (tail->next){
		tail = tail->next;
		len++;
	}
	tail->next = phead;
	if (k % len){
		for (auto i = 0; i < len - k; ++i)
			tail = tail->next;
	}
	newH = tail->next;
	tail->next = NULL;
	return newH;
}

//根据有序链表构建搜索树

struct TreeNode
{
	int _value;
	struct TreeNode* _pleft;
	struct TreeNode* _pright;
	TreeNode(int value)
		:_value(value)
		, _pleft(NULL)
		, _pright(NULL)
	{}
};

typedef struct TreeNode TreeNode;

TreeNode* _sortlist_to_bstree(Node*& phead, int left, int right)
{
	if (left > right)
		return NULL;
	int mid = left + ((right - left) >> 1);
	TreeNode* pleft = _sortlist_to_bstree(phead, left, mid);
	TreeNode* node = new TreeNode(phead->data);
	node->_pleft = pleft;
	phead = phead->next;
	TreeNode* pright = _sortlist_to_bstree(phead, mid + 1, right);
	node->_pright = pright;
	return node;
}

TreeNode* sortlist_to_bstree(Node* phead)
{
	if (phead == NULL)
		return NULL;
	int len = 0;
	for (Node* p = phead; p != NULL; p = p->next)
		++len;
	return _sortlist_to_bstree(phead, len - 1, 0);
}


int ADD(int num1, int num2)
{
	int tmp = 0;
	while (tmp = (num1 & num2)){
		num1 = (num1 ^ num2);
		num2 = tmp << 1;
	}
	return num1 ^ num2;
}

int main()
{
	cout << ADD(2, 3) << endl;
	PNode pHead = BueNode(7);
	//PNode pHead = NULL;
	//InitList(phead);
	PNode* phead = &pHead;
	PushBack(phead, 6);
	PushBack(phead, 7);
	PushBack(phead, 2);
	PushBack(phead, 6);
	PushBack(phead, 5);
	//PushBack(phead, 1);
	PushBack(phead, 9);
	PushBack(phead, 4);
	PushBack(phead, 8);
	PrintList(pHead);
	//QuickSort(pHead);
	quick_sort(pHead);
	PrintList(pHead);
	//PNode pret = K_Group_Reverse(pHead, 3);
	//pHead = MergeSort(pHead);
	//PNode pret = Rotate_K(pHead, 3);
	//PrintList(pret);
	//PrintList(pHead);
	getchar();
	return 0;
}
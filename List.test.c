#include"List.h"

void InitList(PNode* pHead)
{
	assert(pHead);
	*pHead = NULL;
}

PNode BueNode(DataType data)
{
   PNode pTemp = (PNode)malloc(sizeof(Node));
	   if(pTemp)
	   {
		   pTemp->data = data;
		   pTemp->next = NULL;
	   }
	   return pTemp;
}

void PushBack(PNode* pHead,DataType data)
{
	assert(pHead);

	if(NULL == *pHead)
		*pHead = BueNode(data);
	else{
	/*	PNode pCur = *pHead;
		while(pCur->next){
			pCur = pCur->next;
		}
		pCur->next = BueNode(data);*/
		PNode pCur = *pHead;
		PNode pPre = pCur;
		while(pCur){
			pPre = pCur;
			pCur = pCur->next;
		}
		pPre->next = BueNode(data);
	}

}

void PushFront(PNode* pHead,DataType data)
{
	PNode pNewNode = BueNode(data);
    assert(pHead);
	if(pNewNode){
	pNewNode->next = *pHead;
	*pHead = pNewNode;
	}
}

void PopFront(PNode* pHead)
{
	PNode pDel = NULL;
    assert(pHead);
	if(NULL == *pHead)
		return ;

	pDel = *pHead;
	*pHead = (*pHead)->next;
    free(pDel);

}

void PopBack(PNode* pHead)
{
	assert(pHead);
	if(NULL == *pHead){
          return ;
	}
	else if(NULL == (*pHead)->next){
		free(*pHead);
		*pHead = NULL;
	}
	else{
		PNode pCur = *pHead;
		PNode pNewTail = NULL;
		while(pCur->next->next){
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
	while(pCur){
		printf("%d->",pCur->data);
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

	if(pHead){
	PrintListFromTailtoHead(pHead->next);
	printf("%d->",pHead->data);
	}
}	

PNode Find(PNode pHead,DataType data)
{
	PNode pCur = pHead;
    assert(pHead);
	while(pCur){
		if(pCur->data == data)
			return pCur;
		pCur = pCur->next;
	}
	return NULL;
}

void Insert(PNode pos,DataType data)
{
	PNode pNewNode = NULL;
	assert(pos);
	if(NULL == pos){return;}
	pNewNode = BueNode(data);
	pNewNode->next = pos->next;
	pos->next = pNewNode;
}

void Erase(PNode* pHead,PNode pos)
{
	assert(pHead);
	if(NULL == *pHead || NULL == pos)
		return;
	if(pos == *pHead){
		*pHead = pos->next;
		free(pos);
	}
	else{
		PNode pPre = *pHead;
		while(pPre->next != pos){
			pPre = pPre->next;
		}
		pPre->next = pos->next;
		free(pos);
	}
	    
}
void DeleteNotTailNode(PNode pos)
{
	assert(pos);
	if(NULL == pos || NULL == pos->next)
		return ;
	pos->data = pos->next->data;
	pos->next = pos->next->next;
	
}

void InsertNotHeadNode(PNode pos,DataType data)
{    
	PNode pNewNode = BueNode(pos->data);
	if(NULL == pos )
		return ;
	if(pNewNode){
		pNewNode->next = pos->next;
        pos->next = pNewNode;
		pos->data = data;
	}

}

void Remove(PNode* pHead , DataType data)
{
	assert(pHead);
	Erase(pHead,Find(*pHead,data));
}

void RemoveAll(PNode* pHead , DataType data)
{
	PNode pPre = *pHead;
	PNode pCur = (*pHead)->next;
	assert(pHead);
	while(pCur)
	{
		if(pCur->data == data){
			pPre->next = pCur->next;
			free(pCur);
			pCur = pPre->next;
		}
		else{
		pCur = pCur->next;
		}
	}
	if((*pHead)->data == data)
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
	while(pCurNode){
		count++;
		pCurNode = pCurNode->next;
	}
	return count;
}

PNode Back(PNode pHead)
{
	assert(pHead);
	while(pHead->next){
		pHead = pHead->next;
	}
	return pHead;
}

//////////////////////////////////////////
int IsListCross(PNode pHead1,PNode pHead2)
{
	PNode pTailNode1 = pHead1;
	PNode pTailNode2 = pHead2;
	if(NULL == pHead1||NULL == pHead2)
		return 0;
	while(pTailNode1->next)
		pTailNode1 = pTailNode1->next;
	while(pTailNode2->next)
		pTailNode2 = pTailNode2->next;
	if(pTailNode1 == pTailNode2)
		return 1;
	return 0;
}

PNode GetCrossNode(PNode pHead1,PNode pHead2)
{
	int count1 = 0;
	int count2 = 0;
	PNode pL1 = pHead1;
	PNode pL2 = pHead2;
	int gap = 0;
     if(NULL == pHead1||NULL == pHead2)
		return 0;
	 if(0 == IsListCross( pHead1, pHead2))
		 return NULL;

	 count1 = Size(pHead1);
	 count2 = Size(pHead2);
	 gap = count1 - count2;
	 if(gap>0){
		 while(gap--){
			 pL1 = pL1->next;
		 }
	 }
	 else{
		 while(gap++){
			 pL2 = pL2->next;
		 }
   	 }
	 while(pL1 != pL2){
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
	while(pFast &&  pFast->next)
	{
		pFast = pFast->next->next;
		pSlow = pSlow->next;
		if(pFast == pSlow){
		return pFast;
	    }
	}
	return NULL;
}

int GetCircleLen(PNode pMeetNode)
{
	PNode pCurNode = pMeetNode ;
	int count = 1;
	if(NULL == pMeetNode)
		return 0;
	while(pCurNode->next != pMeetNode){
		count++;
		pCurNode = pCurNode->next;
	}
	return count;
}

PNode GetEnterNode(PNode pHead,PNode pMeetNode)
{
	PNode pH = pHead;
	PNode pM = pMeetNode;
	if(NULL == pHead||NULL == pHead->next)
		return 0;
	while(pH != pM){
		pH = pH->next;
		pM = pM->next;
	}
	return pH;
}

int IfCrossWithCricle(PNode pHead1,PNode pHead2)//判断两个可能带环的链表是否相交。
{
	PNode pMeetNode1 = HasCircle(pHead1);
	PNode pMeetNode2 = HasCircle(pHead2);
	if(NULL == pMeetNode1 && NULL == pMeetNode2){
        return IsListCross(pHead1,pHead2);//判断两个个链表是否交叉 
   	}
	else if(pMeetNode1 && pMeetNode2){
			PNode pCur = pMeetNode1;
			while(pCur->next != pMeetNode2){
				if(pCur == pMeetNode2){
					return 2;
				}
				pCur = pCur->next;
				if(pCur == pMeetNode1)
					return 0;
			}
			if(pCur->next == pMeetNode2)
				return 2;
		}
    return 0;
}

PNode Reverse(PNode pHead)
{
	PNode pPre = pHead;
	PNode pCur = pHead->next;
	PNode pnext = pCur->next;
	if(NULL == pHead || NULL == pHead->next )
		return 0;
	while(pnext){
		pCur->next = pPre;
		pPre = pCur;
		pCur = pnext;
		pnext = pnext->next;
	}
	pCur->next = pPre;
	pHead->next = NULL;
	return pCur;
}

PNode Josephcircle(PNode pHead,int n)
{
	PNode pCur = pHead;
	
	if(NULL == pHead)
		return NULL;
	while(pCur->next != pCur){
		PNode pDel = pCur->next;
		int count = n;
		while(--count){
			pCur = pCur->next;
			pDel = pDel->next;
		}
		pCur->data = pDel->data;
		pCur->next = pDel->next;
		free(pDel);
	}
	return pCur;
}



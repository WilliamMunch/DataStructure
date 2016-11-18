#include <stdio.h>    
#include <stdlib.h>    
#include <malloc.h>    
    
typedef struct polyn    
{    
    float coef;    
    int expn;    
    struct polyn* next;    
}PolyNode,*PLinkList;    
    
PLinkList CreatePolyn();//创建一元多项式，使一元多项式呈指数递减    
void OutPut(PLinkList head);//输出一元多项式    
PLinkList Addition(PLinkList L1,PLinkList L2);//多项式的加法    
PLinkList Subtraction(PLinkList L1,PLinkList L2);//多项式的减法    
PLinkList Reverse(PLinkList head);//将生成的链表逆置，使一元多项式呈指数递增形式    
PLinkList MultiplyPolyn(PLinkList L1,PLinkList L2);//多项式的乘法   
  
  
  
  
  
//#include "test.h"    
    
    
PLinkList CreatePolyn()//创建一元多项式，使一元多项式呈指数递减    
{    
    PolyNode *p,*q,*s;    
    PolyNode *head = NULL;    
    int expn2;    
    float coef2;    
    head = (PLinkList)malloc(sizeof(PolyNode));//动态生成头结点    
    if(!head)    
    {    
        return NULL;    
    }    
    head->coef = 0.0;//初始化    
    head->expn = 0;    
    head->next = NULL;    
    do    
    {    
        printf("输入系数coef(系数和指数都为0结束)");    
        scanf("%f",&coef2);    
        printf("输入指数数exp(系数和指数都为0结束)");    
        scanf("%d",&expn2);    
        if((long)coef2 == 0 && expn2 == 0)    
        {    
            break;    
        }    
        s = (PLinkList)malloc(sizeof(PolyNode));    
        if(!s)    
        {    
            return NULL;    
        }    
        s->expn = expn2;    
        s->coef = coef2;    
        q = head->next ;    
        p = head;    
        while(q && expn2 < q->expn)    
        {    
            p = q;    
            q = q->next ;    
        }    
        if(q == NULL || expn2 > q->expn)    
        {    
            p->next = s;    
            s->next = q;    
        }    
        else    
        {    
            q->coef += coef2;    
        }    
    }while(1);    
    return head;    
}    
    
void OutPut(PLinkList head)//输出一元多项式    
{    
    PolyNode *p = head->next ;    
    while(p)    
    {    
        printf("%1.1f",p->coef);    
        if(p->expn)    
        {    
            printf("*x^%d",p->expn);    
        }    
        if(p->next && p->next->coef > 0)    
        {    
            printf("+");    
        }    
        p = p->next ;    
    }    
}    
    
PolyNode *Addition(PLinkList L1,PLinkList L2)//多项式的加法    
{    
    PolyNode *pa,*pb,*pc,*u,*head;    
    head = (PLinkList)malloc(sizeof(PolyNode));    
    if(!head)    
    {    
        return NULL;    
    }    
    head->coef = 0.0;    
    head->expn = 0;    
    head->next = NULL;    
    pc = head;    
    L2 = Reverse(L2);    
    pa = L1->next ;    
    pb = L2->next ;    
    while(pa != NULL && pb != NULL)    
    {    
        if(pa->expn == pb->expn)    
        {    
            u = (PLinkList)malloc(sizeof(PolyNode));    
            if(!u)    
            {    
                return NULL;    
            }    
            u->coef = pa->coef + pb->coef ;    
            u->expn = pa->expn ;    
            pa = pa->next ;    
            pb = pb->next ;    
            u->next = pc->next ;    
            pc->next = u;    
            pc = u;    
        }    
        else if(pa->expn > pb->expn)    
        {    
            u = (PLinkList)malloc(sizeof(PolyNode));    
            if(!u)    
            {    
                return NULL;    
            }    
            u->coef = pa->coef ;    
            u->expn = pa->expn ;    
            pa = pa->next ;    
            u->next = pc->next ;    
            pc->next = u;    
            pc = u;    
        }    
        else    
        {    
            u = (PLinkList)malloc(sizeof(PolyNode));    
            if(!u)    
            {    
                return NULL;    
            }    
            u->coef = pb->coef ;    
            u->expn = pb->expn ;    
            pb = pb->next ;    
            u->next = pc->next ;    
            pc->next = u;    
            pc = u;    
        }    
    }    
    L2 = Reverse(L2);    
    return head;    
}    
    
PolyNode *Subtraction(PLinkList L1,PLinkList L2)//多项式的减法    
{    
    PolyNode *pa,*pb,*pc,*u,*head;    
    head = (PLinkList)malloc(sizeof(PolyNode));    
    if(!head)    
    {    
        return NULL;    
    }    
    head->coef = 0.0;    
    head->expn = 0;    
    head->next = NULL;    
    pc = head;    
    pa = L1->next ;    
    pb = L2->next ;    
    while(pa != NULL && pb != NULL)    
    {    
        if(pa->expn == pb->expn)    
        {    
            u = (PLinkList)malloc(sizeof(PolyNode));    
            if(!u)    
            {    
                return NULL;    
            }    
            u->coef = pa->coef - pb->coef ;    
            u->expn = pa->expn ;    
            pa = pa->next ;    
            pb = pb->next ;    
            u->next = pc->next ;    
            pc->next = u;    
            pc = u;    
        }    
        else if(pa->expn > pb->expn)    
        {    
            u = (PLinkList)malloc(sizeof(PolyNode));    
            if(!u)    
            {    
                return NULL;    
            }    
            u->coef = pa->coef ;    
            u->expn = pa->expn ;    
            pa = pa->next ;    
            u->next = pc->next ;    
            pc->next = u;    
            pc = u;    
        }    
        else    
        {    
            u = (PLinkList)malloc(sizeof(PolyNode));    
            if(!u)    
            {    
                return NULL;    
            }    
            u->coef = pb->coef ;    
            u->expn = pb->expn ;    
            pb = pb->next ;    
            u->next = pc->next ;    
            pc->next = u;    
            pc = u;    
        }    
    }    
    return head;    
}    
    
PolyNode *Reverse(PLinkList head)//将生成的链表逆置，使一元多项式呈指数递增形式    
{    
    PolyNode *q,*r,*p = NULL;    
    q = head->next ;    
    while(q)    
    {    
        r = q->next ;    
        q->next = p;    
        p = q;    
        q = r;    
    }    
    head->next = p;    
    return head;    
}    
    
PolyNode *MultiplyPolyn(PLinkList L1,PLinkList L2)//多项式的乘法    
{    
    PolyNode *pa,*pb,*pc,*u,*head;    
    int k,maxExp;    
    float coef;    
    head = (PLinkList)malloc(sizeof(PolyNode));    
    if(!head)    
    {    
        return NULL;    
    }    
    head->coef = 0.0;    
    head->expn = 0;    
    head->next = NULL;    
    if(L1->next != NULL && L2->next != NULL)    
    {    
        maxExp = L1->next->expn +L2->next->expn ;    
    }    
    else    
    {    
        return head;    
    }    
    pc = head;    
    L2 = Reverse(L2);    
    for(k = maxExp;k >= 0;k--)    
    {    
        pa = L1->next ;    
        while(pa != NULL && pa->expn > k)    
        {    
            pa = pa->next ;    
        }    
        pb = L2->next ;    
        while(pb != NULL && pa != NULL && pa->expn+pb->expn < k)    
        {    
            pb= pb->next ;    
        }    
        coef = 0.0;    
        while(pa != NULL && pb != NULL)    
        {    
            if(pa->expn +pb->expn == k)    
            {    
                coef += pa->coef *pb->coef ;    
                pa = pa->next ;    
                pb = pb->next ;    
            }    
            else if(pa->expn +pb->expn > k)    
            {    
                pa = pa->next ;    
            }    
            else    
            {    
                pb = pb->next ;    
            }    
        }    
        if(coef != 0.0)    
        {    
            u = (PLinkList)malloc(sizeof(PolyNode));    
            u->coef = coef;    
            u->expn = k;    
            u->next = pc->next ;    
            pc->next = u;    
            pc = u;    
        }    
    }    
    L2 = Reverse(L2);    
    return head;    
}    
  
  
  
  
  
//#include "test.h"    
    
int main(void)    
{    
    PLinkList A,B,C,D,E;    
    A = CreatePolyn();    
    printf("A(x) =");    
    OutPut(A);    
    printf("\n");    
    B = CreatePolyn();    
    printf("B(x) =");    
    OutPut(B);    
    printf("\n");    
    C = MultiplyPolyn(A,B);    
    printf("C(x) = A(x)*B(x) =");    
    OutPut(C);    
    printf("\n");    
    D = Addition(A,B);    
    printf("D(x) = A(x)+B(x) =");    
    OutPut(D);    
    printf("\n");    
    E = Subtraction(A,B);    
    printf("E(x) = A(x)-B(x) =");    
    OutPut(E);    
    printf("\n");    
    return 0;    
}
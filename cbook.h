#ifndef _TXL_H
#define _TXL_H

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#pragma warning(disable:4996)

#define INIT_TXL_SIZE 64
#define INC_SIZE 32
#define FILE_NAME "file.txt"

typedef struct person{
    char name[50];
	char sex[10];
	unsigned char age;
	char phone[19];
	char addr[30];
}person_t,*person_p,**person_pp;

typedef struct txl{
    int cap;
	int size;
	person_p txllist;
}txl_t,*txl_p,**txl_pp;

void addTxl(txl_p c,person_p p);
void initTxl(txl_pp c);
//void delTxl();
void clearTxl(txl_p c);
//void mysortTxl();
void destoryTxl(txl_p c);
void delTxl(txl_p c,const char* namekey);
void showTxl(txl_p c);

int fileLoad(txl_p c);
int flieStore(txl_p c);


#endif
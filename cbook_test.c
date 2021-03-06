#include"cbook.h"
#include<string.h>

void initTxl(txl_pp c)
{
	assert(c);
	*c = (txl_p)malloc(sizeof(txl_t));
	if(NULL == *c){
		printf("perror");
		exit(1);
	}
    (*c)->txllist = (person_p)malloc(sizeof(person_t)*INIT_TXL_SIZE);
	if(NULL == (*c)->txllist){
		printf("perror");
		exit(2);
	}
	(*c)->cap = INIT_TXL_SIZE;
	(*c)->size = 0;
    
	fileLoad(*c);
}
static int Txlfull(txl_p c)
{
	assert(c);
	return (c->cap == c->size)? 0:1;
}

static int incTxl(txl_p c)
{
	person_p new_c = (person_p)realloc(c->txllist,\
		(c->cap+INC_SIZE)*sizeof(person_t));
	assert(c);
	if(NULL == new_c){
	    printf("perror");
		exit(3);
	}

	c->cap += INC_SIZE;
	c->txllist = new_c;
	printf("new expand room init succese\n");
	return 1;
}

int fileload(txl_p c)
{
	FILE* fp = fopen(FILE_NAME,"rb");
	person_t pe;
	assert(c);
	if(NULL == fp){
	    perror("fopen");
		return -2;
	}
	while(1){
	    fread(&pe,sizeof(person_t),1,fp);
		if(feof(fp)){
			break;
		}
		addTxl(c,&pe);
	}
	fclose(fp);
}

int fileStore(txl_p c)
{
	int i = 0;
	FILE* fp = fopen(FILE_NAME,"wb");
	assert(c);
	if(NULL == fp){
		perror("fopen");
		return -1;
	}
	for(;i<c->size;i++){
		fwrite(c->txllist+i,sizeof(person_t),1,fp);
	}
	fclose(fp);
}

void addTxl(txl_p c,person_p p)
{
	int pos = c->size;
	assert(c);
	assert(p);
	
	if(!Txlfull(c) || incTxl(c)){
	    c->txllist[pos] = *p;
        c->size++;
	}
}
void clearTxl(txl_p c)
{
	assert(c);
	c->size = 0;
}

void destoryTxl(txl_p c)
{
	assert(c);


	free(c->txllist);
	c->txllist = NULL;
	free(c);
	c = NULL;
}

static void swap(person_p xp,person_p yp)
{
	person_t tmp = *xp;
	*yp = tmp;
	*xp = *yp;
}

void delTxl(txl_p c,const char* namekey)
{
	int i = 0;
	assert(c);
	assert(namekey);
	for(;i<c->size;i++){
		if(0 == strcmp(c->txllist[i].name,namekey)){
			swap(c->txllist+i,c->txllist+c->size-1);
			c->size--;
		}
	}
}

void showTxl(txl_p c)
{
	int i = 0;
	assert(c);
	for(;i<c->size;i++){
        printf("%-6s  |  %-6c  |  %-6d  |   %-12s   |   %-12s   |\n",\
			c->txllist[i].name,c->txllist[i].sex,\
			c->txllist[i].age,c->txllist[i].phone,c->txllist[i].addr);
	}
}
	

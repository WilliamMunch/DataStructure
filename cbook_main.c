#include"cbook.h"

static void useage()
{
	printf("Please Enter A digit in menu");
}

static void myadd(txl_p c)
{
	person_t p;
	assert(c);
    printf("Please Enter<name, sex, age, phone, addr> ");
	scanf("%s %c %d %s %s",p.name,&p.sex,&p.age,p.phone,p.addr);
	addTxl(c,&p);
}

static mydelet(txl_p c)
{
	char name[32];
	assert(c);
	printf("Please Enter who you what to delet ");
	scanf("%s",name);
	delTxl(c,name);

}

int main()
{
	txl_p mytxl ;
	volatile int done = 0;
	int flag = -1;
	initTxl(&mytxl);
	while(!done){
	printf("####################################\n");
	printf("##1.add#####################2.delete\n");
	printf("##3.modify##################4.search\n");
	printf("##5.show####################6.clear#\n");
	printf("##7.sort####################0.exit##\n");
	printf("####################################\n");
	printf("Please Enter your election:");
    scanf("%d",&flag);
	switch(flag){
		case 1:
             myadd(mytxl);
			 break;
		case 2:
             mydelet(mytxl);
			 break;
		case 3:
             //modifyTxl();
			 break;
		case 4: 
             //searchTxl();
			 break;
		case 5:
             showTxl(mytxl);
			 break;
		case 6:
			 clearTxl(mytxl);
			 break;
		default: 
			 useage();
			 break;
		

	  }
	}
	destoryTxl(mytxl);
	system("pause");
	return 0;
}
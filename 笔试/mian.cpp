
#include"test.cpp"

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

int main()
{
	func1();
	
	system("pause");
	return 0;
}






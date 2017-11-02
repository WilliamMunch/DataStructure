#include"hashtable.cpp"


void Test()
{
	//HashTable::HashTable<int, int> ht;
	/*int arr[] = {  1, 2 ,  3, 4 ,  5, 6,  7, 8  };
	ht.Insert(1, 2);
	ht.Insert(59, 4);
	ht.Insert(5, 6);
	ht.Insert(6, 8);*/

	HashBucket::HashTable<int, int> ht;
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	ht.Insert(1, 2);
	ht.Insert(59, 4);
	ht.Insert(5, 6);
	ht.Insert(6, 8);
 }

int main()
{
	Test();
	system("pause");
	return 0;
}
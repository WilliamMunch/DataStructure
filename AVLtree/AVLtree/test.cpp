#include"AVLtree.h"

	void TestAVLTree()
	{
		int a1[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
		AVLtree<int, int> t1;
		for (size_t i = 0; i < sizeof(a1) / sizeof(int); ++i)
		{
			t1.Insert(a1[i], i);
			cout << "IsBalance?" << t1.IsBalance() << "->Insert:" << a1[i] << endl;
		}

		t1.InOrder();
	}


int main()
{
	TestAVLTree();
	system("pause");
	return 0;
}
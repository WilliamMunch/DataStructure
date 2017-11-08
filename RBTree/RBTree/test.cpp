#include"RBTree.h"

void TestRBTree()
{
	int a1[] = {5,3,4,1,7,8,2,6,0,9};
	RBTree<int, int> t1;
	RBTree<int, pair<int, int>> t2;
	t1.Insert(3);
	t1.Insert(2);
	t1.Insert(1);
	t1.Insert(4);

	RBTree<int, int>::Iterator it = t1.Begin();
	while (it != t1.End())
	{
	cout<<*it<<" ";
	++it;
	}
	cout<<endl;

	RBTree<int, int>::Iterator rit = t1.RBegin();
	while (rit != t1.REnd())
	{
	cout<<*rit<<" ";
	--rit;
	}
	cout<<endl;
}

int main()
{
	TestRBTree();
	system("pause");
	return 0;
}
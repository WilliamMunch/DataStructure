#include"MySet.h"
#include"MyMap.h"

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

void TestMySet()
{
	MySet<int> st;
	st.Insert(1);
	st.Insert(5);
	st.Insert(7);
	st.Insert(2);

	MySet<int>::Iterator it = st.Begin();
	while (it != st.End()){
		cout << *it << " ";
		++it;
	}
	cout << endl;
}

void TestMyMap()
{
	MyMap<int, double> mp;
	mp.Insert(make_pair(1, 1.1));
	mp.Insert(make_pair(2, 2.2));

	MyMap<int, double>::Iterator it = mp.Begin();
	while (it != mp.End()){
		cout << it->first << ":" << it->second << endl;
		++it;
	}

	//ÊµÏÖdictionary
	MyMap<string, string> strmp;
	strmp["xzuidiao"] = "yiming";
	strmp["huhuhu"] = "hahaha";

	cout << strmp["xzuidiao"].c_str() << endl;
}

int main()
{
	TestRBTree();
	TestMySet();
	TestMyMap();
	system("pause");
	return 0;
}
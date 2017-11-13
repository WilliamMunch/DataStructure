#include"HashBucket.h"
#include"unorderSet.h"
#include"unorderMap.h"
#include<string>

void TestHashBucket()
{
	int a[] = { 51, 105, 52, 3, 55, 2, 106, 53, 0 };
	HashBucket<int, int> hashset;
	for (size_t i = 0; i < sizeof(a) / sizeof(a[0]); ++i)
	{
		hashset.Insert(a[i]);
	}


	HashBucket<int, int>::Iterator setIt = hashset.Begin();
	while (setIt != hashset.End())
	{
		cout << *setIt << " ";
		++setIt;
	}
	cout << endl;

	HashBucket<string, string> dictset;
	dictset.Insert("sort");
	dictset.Insert("string");
	dictset.Insert("int");

	HashBucket<string, string>::Iterator dicit = dictset.Begin();
	while (dicit != dictset.End())
	{
		cout << (*dicit).c_str() << " ";
		++dicit;
	}
	cout << endl;

	HashBucket<int, pair<int, int>, HashFunc<int>, PairKeyOfValue<int, pair<int, int>>> hashmap;
	hashmap.Insert(make_pair(1, 255));
	hashmap.Insert(make_pair(100, 1300));
	HashBucket<int, pair<int, int>, HashFunc<int>, PairKeyOfValue<int, pair<int, int>> >::Iterator mapit = hashmap.Begin();
	while (mapit != hashmap.End())
	{
		cout << (*mapit).second << " ";
		++mapit;
	}
	cout << endl;
}

void TestUnOrderSet()
{
	UnorderSet<int> ht;
	ht.Insert(3);
	ht.Insert(1);
	ht.Insert(6);
	ht.Insert(3);

	UnorderSet<int>::Iterator it = ht.Begin();
	while (it != ht.End())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	
	ht.Erase(1);

	it = ht.Begin();
	while (it != ht.End())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}

void TestUnOrderMap()
{
	UnorderMap<string, string> dict;
	dict["sort"] = "hahaha";
	dict["string"] = "gnirts";
	dict["map"] = "pam";
	dict["left"] = "tfel";
	dict["left"] = "tfel";

	UnorderMap<string, string>::Iterator it = dict.Begin();
	while (it != dict.End())
	{
		cout << it->first << ":" << it->second << endl;
		++it;
	}
}

int main()
{
	TestHashBucket();
	TestUnOrderSet();
	TestUnOrderMap();
	system("pause");
	return 0;
}
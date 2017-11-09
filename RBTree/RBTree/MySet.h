#pragma once

#include"RBTree.h"

template<class K>
class MySet
{
public:
	struct SetKeyOfValue{
		K operator()(const K& key)
		{
			return key;
		}
	};

	typedef typename RBTree<K, K, SetKeyOfValue>::Iterator Iterator;

	pair<Iterator, bool> Insert(const K& key)
	{
		return _t.Insert(key);
	}

	Iterator Begin()
	{
		return _t.Begin();
	}

	Iterator End()
	{
		return _t.End();
	}

	Iterator Find(const K& key)
	{
		return _t.Find(key);
	}

private:
	RBTree<K, K, SetKeyOfValue> _t;
	
};
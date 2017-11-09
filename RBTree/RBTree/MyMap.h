#pragma once

#include"RBTree.h"



template<class K,class V>
class MyMap
{
public:
	typedef pair<K, V> ValueType;

	struct MapKeyOfValue{
		K operator()(const ValueType& kv){
			return kv.first;
		}
	};

	typedef typename RBTree<K, ValueType, MapKeyOfValue>::Iterator Iterator;
	
	pair<Iterator, bool> Insert(const ValueType& kv)
	{
		return _t.Insert(kv);
	}

	Iterator Find(const K& key)
	{
		return _t.Find(key);
	}

	Iterator Begin()
	{
		return _t.Begin();
	}

	Iterator End()
	{
		return _t.End();
	}

	V& operator[](const K& key)
	{
		return (_t.Insert(make_pair(key, V())).first)->second;
	}
private:
	RBTree<K, ValueType, MapKeyOfValue> _t;
};
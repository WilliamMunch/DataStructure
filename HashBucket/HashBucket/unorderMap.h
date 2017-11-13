#pragma once

#include"HashBucket.h"

template<class K, class V, class _HashFunc = HashFunc<K>, class KeyOfValue = PairKeyOfValue<K, pair<K, V> > >
class UnorderMap
{
	typedef HashBucket<K, pair<K, V>, _HashFunc, KeyOfValue> HASH;
public:
	typedef typename HASH::Iterator Iterator;

	pair<Iterator, bool> Insert(const pair<K, V>& kv)
	{
		return _hash.Insert(kv);
	}

	Iterator Find(const V& kv)
	{
		return _hash.Find(kv);
	}

	Iterator Erase(const V& kv)
	{
		Iterator it = Find(kv);
		return _hash.Erase(it);
	}

	Iterator Begin()
	{
		return _hash.Begin();
	}

	Iterator End()
	{
		return _hash.End();
	}

	V& operator[](const K& key)
	{
		return (Insert(make_pair(key, V())).first)->second;
	}

	void Rserver(size_t n)
	{
		return _hash.Reserve(n);
	}

private:
	HASH _hash;
};


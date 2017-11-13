#pragma once

#include"HashBucket.h"

template<class K, class _HashFunc = HashFunc<K>>
class UnorderSet
{
	typedef HashBucket<K, K, _HashFunc, OneKeyOfValue<K, K> > HASH;
public:
	typedef typename HashBucket<K, K, _HashFunc, OneKeyOfValue<K, K> >::Iterator Iterator;

	pair<Iterator, bool> Insert(const K& key)
	{
		return _hash.Insert(key);
	}

	Iterator Erase(const K& key)
	{
		Iterator pos = Find(key);
		return _hash.Erase(pos);
	}

	Iterator Find(const K& key)
	{
		return _hash.Find(key);
	}

	Iterator Begin()
	{
		return _hash.Begin();
	}

	Iterator End()
	{
		return _hash.End();
	}

private:
	HASH _hash;
};

#pragma once

#include<iostream>
#include<stdlib.h>
#include<vector>

using namespace std;

template<class K>
struct HashFunc{
	size_t operator()(const K& key){
		return key;
	}
};

template<>
struct HashFunc<string>{
	size_t operator()(const string& s)
	{
		return BKDRfunc(s.c_str());
	}

	static size_t BKDRfunc(const char* str)
	{
		unsigned int hash = 0;
		unsigned int seed = 131;
		while (*str){
			hash = hash * seed + (*str++);
		}
		return (hash & 0x7FFFFFFF);
	}
};

template<class K,class V>
struct OneKeyOfValue{
	const K& operator()(const V& key){
		return key;
	}
};

template<class K,class V>
struct PairKeyOfValue{
	const K& operator()(const V& kv){
		return  kv.first;
	}
};


template<class ValueType>
struct HashNode
{
	ValueType _valueField;
	HashNode<ValueType>* _next;
	HashNode(const ValueType& valueField)
		:_next(NULL)
		, _valueField(valueField)
	{}
};

template<class K, class V, class _HashFunc ,class KeyOfValue >
class HashBucket;

template<class K, class V, class _HashFunc = HashFunc<K> , class KeyOfValue = OneKeyOfValue<K,K> >
struct HashBucketIterator
{
	typedef HashNode<V> Node;
	typedef HashBucketIterator<K, V, _HashFunc , KeyOfValue> Self;
	
	HashBucket<K, V, _HashFunc, KeyOfValue>* _hash;
	Node* _node;
	
	HashBucketIterator(Node* node, HashBucket<K, V, _HashFunc, KeyOfValue>* hash)
		:_node(node)
		, _hash(hash)
	{}

	V& operator*()
	{
		return _node->_valueField;
	}

	V* operator->()
	{
		return &( operator*() );
	}

	bool operator == (const Self& s)const
	{
		return _node == s._node;
	}

	bool operator != (const Self& s)const
	{
		return _node != s._node;
	}

	Self& operator++()
	{
		if (_node->_next){
			_node = _node->_next;
		}
		else{
			size_t index = _hash->__HashFunc(KeyOfValue()(_node->_valueField), _hash->_table.size());
			Node* cur = NULL;
			for (size_t i = index + 1; i < _hash->_table.size(); ++i){
				cur = _hash->_table[i];
				if (cur) break;
			}
			_node = cur;
		}
		return *this;
	}
};

template<class K, class V, class _HashFunc = HashFunc<K>, class KeyOfValue = OneKeyOfValue<K,V> >
class HashBucket
{
	typedef V ValueType;
	typedef HashNode<V> Node;
public:
	typedef HashBucketIterator<K, V, _HashFunc, KeyOfValue> Iterator;
	friend struct Iterator;
	
	HashBucket()
		:_size(0)
	{}

	~HashBucket()
	{
		Node* cur = NULL;
		for (size_t i = 0; i < _table.size(); ++i){
			cur = _table[i];
			while (cur){
				Node* next = cur->_next;
				delete cur;
				cur = next;
			}
			_table[i] = NULL;
		}
	}

	Iterator Begin()
	{
		Node* cur = NULL;
		for (size_t i = 0; i < _table.size(); ++i)
		{
			cur = _table[i];
			if (cur) break;
		}
		return Iterator(cur, this);
	}

	Iterator End()
	{
		return Iterator(NULL, this);
	}

	void ChackCapacity()
	{
		if (_size == _table.size())
		{
			KeyOfValue _KeyOfValue;
			vector<Node*> newtable;
			newtable.resize(GetNextPrime(_table.size()), NULL);
			Node* cur = NULL;
			Node* next = cur;
			for (size_t i = 0; i < _table.size(); ++i){
				cur = _table[i];
				while (cur){
					next = cur->_next;
					size_t index = __HashFunc(_KeyOfValue(cur->_valueField), newtable.size());
					cur->_next = newtable[i];
					newtable[i] = cur;
					cur = next;
				}
			}
			_table.swap(newtable);
		}
	}

	pair<Iterator, bool> Insert(const ValueType& v)
	{
		ChackCapacity();
		KeyOfValue _KeyOfValue;
		size_t index = __HashFunc(_KeyOfValue(v),_table.size());
		Node* pExist = _table[index];
		while (pExist){
			if (_KeyOfValue(pExist->_valueField) == _KeyOfValue(v))
				return make_pair(Iterator(pExist, this), false);
			pExist = pExist->_next;
		}
		Node* cur = new Node(v);
		cur->_next = _table[index];
		_table[index] = cur;
		_size++;

		return make_pair(Iterator(cur, this), true);
	}

	Iterator Erase(Iterator pos)
	{
		KeyOfValue _KeyOfValue;
		Iterator nit = pos;
		++nit;

		size_t index = __HashFunc(_KeyOfValue(*pos), _table.size());
		Node* cur = _table[index];
		Node* prev = NULL;
		while (cur){
			if (_KeyOfValue(cur->_valueField) == _KeyOfValue(*pos)){
				if (prev == NULL){
					_table[index] = cur->_next;
				}
				else{
					prev->_next = cur->_next;
				}
				delete cur;
				--_size;
				return nit;
			}
			else{
				prev = cur;
				cur = cur->_next;
			}
		}
		return Iterator(NULL, this);
	}

	void Reserve(size_t newsize)
	{
		return _table.resize(newsize, NULL);
	}

	Iterator Find(const V& valueField)
	{
		KeyOfValue _KeyOfValue;
		size_t index = __HashFunc(_KeyOfValue(valueField), _table.size());
		Node* cur = _table[index];
		while (cur){
			if (_KeyOfValue(cur->_valueField) == _KeyOfValue(valueField)){
				return Iterator(cur, this);
			}
			else{
				cur = cur->_next;
			}
		}
		return Iterator(NULL, this);
	}
	
	
protected:


	size_t __HashFunc(const K& key, size_t size)
	{
		return _HashFunc()(key) % size;
	}

	size_t GetNextPrime(size_t size)
	{
		const int _PrimeSize = 28;
		static const unsigned long _PrimeList[_PrimeSize] =
		{
			53ul, 97ul, 193ul, 389ul, 769ul,
			1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
			49157ul, 98317ul, 196613ul, 393241ul, 786433ul,
			1572869ul, 3145739ul, 6291469ul, 12582917ul, 25165843ul,
			50331653ul, 100663319ul, 201326611ul, 402653189ul, 805306457ul,
			1610612741ul, 3221225473ul, 4294967291ul
		};

		for (int i = 0; i < _PrimeSize; ++i)
		{
			if (_PrimeList[i] > size)
			{
				return _PrimeList[i];
			}
		}
		return _PrimeList[_PrimeSize - 1];
	}

private:
	vector<Node*> _table;
	size_t _size;
};
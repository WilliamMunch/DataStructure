#include<iostream>
#include<string>
#include<stdlib.h>
#include<vector>

using namespace std;



namespace HashTable{

	enum Status{ EMPTY, DELETE, EXIST };//枚举类型用于表示hashNode的状态
	template<class K, class V>
	struct HashNode
	{
		K _key;//用于标识该value的标志
		V _value;//结点中保存的值
		Status _status;//表中该HashNode的状态
	
		HashNode(const K& key = K(), const V& value = V())
			: _key(key)
			, _value(value)
			, _status(EMPTY)
			
		{}
	};

	template<class K>
	struct  __HashFunc
	{
		size_t operator()(const K& key)
		{
			return key;
		}
	};

	template <>
	struct __HashFunc<string>//这里用到模板类的特化 
	{//BKDR算法 专门用与string这样不可以取模的类型的哈希函数算法。
		size_t operator()(const char* str)
		{
			size_t seed = 131;
			size_t hash = 0;
			while (*str){
				hash = seed*hash + (*str++);
			}
			return (hash & 0X7FFFFFFF);
		}
	};

	template<class K, class V, class HashFunc = __HashFunc<K> >
	class HashTable
	{
		typedef HashNode<K, V> Node;
	public:
		HashTable()
			:_size(0)
		{
			_table.resize(GetPrime(_size));
		}

		HashTable(const HashTable<K, V, HashFunc>& hash)
		{
			size_t newSize = hash._table.size();
			_table.resize(newSize);

			for (size_t i = 0; i < _table.size(); ++i)
			{
				if (hash._table[i]._status == EXIST){
					_table[i]._key  = hash._table[i]._key;
					_table[i]._value  = hash._table[i]._value;
					_table[i]._status  = EXIST;
				}
				_size = hash._size;
			}
		}

		HashTable<K, V, HashFunc>& operator = (const HashTable<K, HashFunc>& hash)
		{
			if (this != &hash){
				HashTable<K, V, HashFunc> h(hash);
				Swap(h);
			}
			return *this;
		}



		void Swap(HashTable<K, V, HashFunc>& hash)
		{
			if (this != &hash){
				_table.swap(hash._table);
				swap(_size, hash._size);
			}
		}

		bool Insert(const K& key, const V& value)
		{
			_ChackSize();//插入前先检查表的负载是否超负荷 如果是则需要重新开票表空间
			size_t index = _HashFunc(key);

			if (index >= 0){
				while (_table[index]._status == EXIST){
					index++;//线性探测
					if (index == _table.size())
						index = 0;
				}
				_table[index]._key = key;
				_table[index]._value = value;
				_table[index]._status = EXIST;
				_size++;

				return true;
			}
			return false;
		}

		Node* Find(const K& key)
		{
			int index = _HashFunc(key);
			if (index < 0)
				return NULL;
			int start = index;
			while (_table[indeex]._status != EMPTY){//依照Insert的逻辑 如果插入时这个位置为空
								//则该位置已经插入  查找时若找到EMPTY位 其后一定没有_key符合的项
				if (_table[index]._key == key && _table[index]._status == EXIST){
					return &_table[index];
				}
					
				index++;
				if (index == _table.size())
					index = 0;
				if (index == start)
					break;
			}
			return NULL;
		}

		bool Remove(const K& key)
		{
			Node* del = Find(key);
			if (del){
				del->_status = DELETE;
				_size--;
				return true;
			}
			return false;
		}



	protected:
		void _ChackSize()
		{//
			if (_table.size() == 0 || _size * 10 / _table.size() > 8)
			{
				HashTable<K, V, HashFunc> hash;//创建一个临时hash表对象
				size_t newSize = GetPrime(_table.size());
				hash._table.resize(newSize);
				for (size_t i = 0; i < _table.size(); ++i){
					if (_table[i]._status == EXIST){//将原表中节点重新计算位置后插入新表
						hash.Insert(_table[i]._key, _table[i]._value);
					}
				}
				Swap(hash);
			}
		}

		int _HashFunc(const K& key)
		{
			if (_table.size())
				return HashFunc()(key) % _table.size();
			return -1;
		}

		static unsigned long GetPrime(const unsigned long size)
		{
			const int Primesize = 28;
			const unsigned long PrimeList[] = {
				53ul, 97ul, 193ul, 389ul, 769ul,
				1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
				49157ul, 98317ul, 196613ul, 393241ul,
				786433ul,
				1572869ul, 3145739ul, 6291469ul, 12582917ul,
				25165843ul,
				50331653ul, 100663319ul, 201326611ul, 402653189ul,
				805306457ul,
				1610612741ul, 3221225473ul, 4294967291ul
			};
			for (size_t i = 0; i < Primesize; ++i){
				if (size < PrimeList[i])
					return PrimeList[i];
			}
			return PrimeList[Primesize - 1];
		}

	private:
		vector<Node> _table;
		size_t _size;
	};
}

namespace HashBucket
{
	//enum Status{ EMPTY, DELETE, EXIST };

	template<class K , class V>
	struct HashNode
	{
		K _key;
		V _value;
		HashNode<K, V>* _next;
		
		HashNode(const K& key = K(), const V& value = V())
			:_key(key)
			, _value(value)
			, _next(NULL)
		{}
	};

	template<class K>
	struct __HashFunc
	{
		int operator()(const K& key)
		{
			return key ;
		}
	};

	template<>
	struct __HashFunc<string>
	{
		int operator ()(const string& str)
		{
			size_t num = 0;
			for (size_t i = 0; i < str.size(); ++i)
			{
				num += num * 131 + str[i];
			}
			return num;
		}
	};

	template<class K, class V, class HashFunc = __HashFunc<K> >
	class HashTable
	{
		typedef HashNode<K, V> Node;
	public:
		HashTable()
			:_size(0)
		{
			_table.resize(GetPrime(_size));
		}

		HashTable<K, V, HashFunc>& operator=(const HashTable<K, V, HashFunc>& hash)
		{
			if (*this != &hash){
				Hashtable<K, V, HashFunc> tmp(hash);
				Swap(tmp);
			}
		}

		void Swap(HashTable<K, V, HashFunc>& hash)
		{
			_table.swap(hash._table);
			swap(_size, hash._size);
		}

		Node* Find(const K& key)
		{
			int index = _HashFunc(key); 
			if (index >= 0){
				Node* cur = _table[index];
				while (cur){
					if (cur->_key == key)
						return cur;
					cur = cur->_next;
				}
				return NULL;
			}
			return NULL;
		}

		~HashTable()
		{
			for (size_t i = 0; i < _table.size(); ++i)
			{
				Node* cur = _table[i];
				Node* del = cur;
				while (cur){
					 del = cur;
					 cur = cur->_next;
					 delete del;
				}
			}
		}

		bool Insert(const K& key, const V& value)
		{
			_ChackSize();
			Node* insertnode = Find(key);
			if (insertnode)
				return false;

			int index = _HashFunc(key);
			Node* cur = new Node(key, value);
			cur->_next = _table[index];
			_table[index] = cur;
			_size++;
			return true;
		
		}

		void _ChackSize()
		{
			if (_table.size() != 0 && _size / _table.size() != 1)
				return;
			HashTable<K, V, HashFunc> hash;
			hash._table.resize(GetPrime(_table.size()));
			for (size_t i = 0; i < _table.size(); ++i)
			{
				Node* cur = _table[i];
				while (cur){
					Insert(cur->_key, cur->_value);
					cur = cur->_next;
				}
			}
			Swap(hash);
		}

		bool Remove(const K& key)
		{
			int index = _HashFunc(key);
			Node* cur = _table[index];
			Node* prev = NULL;
			while (cur){
				if (cur->_key == key){
					if (prev == NULL){//说明第一个节点就是有删除的结点
						_table[index] = cur->_next;
					}
					else{
						prev->_next = cur->_next;
					}
					--_size;
					delete cur;
					return tue;
				}
				prev = cur;
				cur = cur->_next;
			}
			return false;
		}
		


	protected:
		int _HashFunc(const K& key)
		{
			if (_table.size()){
				return (HashFunc()(key)) % _table.size();
			}
			return -1;
		}

		static unsigned long GetPrime(const unsigned long size)
		{
			const int Primesize = 28;
			const unsigned long PrimeList[] = {
				53ul, 97ul, 193ul, 389ul, 769ul,
				1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
				49157ul, 98317ul, 196613ul, 393241ul,
				786433ul,
				1572869ul, 3145739ul, 6291469ul, 12582917ul,
				25165843ul,
				50331653ul, 100663319ul, 201326611ul, 402653189ul,
				805306457ul,
				1610612741ul, 3221225473ul, 4294967291ul
			};
			for (size_t i = 0; i < Primesize; ++i){
				if (size < PrimeList[i])
					return PrimeList[i];
			}
			return PrimeList[Primesize - 1];
		}
	private:
		vector<Node*> _table;
		size_t _size;
	};
}

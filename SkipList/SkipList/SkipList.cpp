#include<iostream>
#include<cstring>
#include<string>
#include<stdlib.h>
#include<vector>

using namespace std;

const size_t MAXLEVEL = 8;

template<class K, class V>
class SkipNode{
public:
	K _key;
	V _value;
	size_t _level;
	vector<SkipNode<K, V>* > _plevel;
	SkipNode(K key = K(), V value = V(), size_t level = 0)
		:_key(key)
		, _value(value)
		, _level(level)
	{
		_plevel.reserve(0);
		for (size_t i = 0; i < _level; ++i){
			_plevel.push_back(NULL);
		}
	}

	~SkipNode(){
		_key = -1;
		_value = -1;
		_size = -1;
		_plevel.clear();
	}
};

template<class K, class V>
class SkipList{
public:
	typedef SkipNode<K, V> Node;
	SkipList();
	~SkipList();
	bool Find(K key, V& value);
	bool Insert(K key, V value);
	bool Erease(K key);
	void Print();
	size_t Getlevel();
	size_t Size();
private:
	int Random();
	Node* _head;
	size_t _maxlevel;             //最大层数
	size_t _size;                //最底层多少个结点
protected:
	SkipList(SkipList<K, V>& skl);
	SkipList<K, V>& operator = (SkipList<K, V>& skl);
};

template<class K, class V>
size_t SkipList<K, V>::Size()
{
	return _size;
}

template<class K, class V>
size_t SkipList<K, V>::Getlevel()
{
	return _maxlevel;
}

template<class K, class V>
int SkipList<K, V>::Random()
{
	int level = 1;
	while (rand() % 2 && level <= MAXLEVEL){
		level++;
	}
	return level;
}

template<class K, class V>
SkipList<K, V>::SkipList(){
	_size = 0;
	_maxlevel = 1;
	_head = new SkipNode(-1, -1, _maxlevel);
}

template<class K, class V>
bool SkipList<K, V>::Insert(K key, V value)
{
	int i = _maxlevel - 1;
	int j = 0;
	Node* cur = _head;
	Node* tmp[MAXLEVEL] = NULL;
	while (i >= 0){
		while (cur->_plevel[i]){
			if (key >= cur->_plevel[i]->_key)
				cur = cur->_plevel[i];
			else
				break;
		}
		tmp[j++] = cur;
		i--;
	}
	i = 0;
	int level = Random();
	_maxlevel = _maxlevel > level ? _maxlevel : level;
	Node* newNode = new SkipNode(key, value, level);
	for (i = 0; i < level; ++i){
		if (i < j){
			newNode->_plevel[i] = tmp[j - i - 1]->_plevel[i];
			tmp[j - i - i]->_plevel[i] = newNode;
		}
		else{
			_head = newNode->_plevel[i];
		}
	}
	_size++;
}

template<class K, class V>
bool SkipList<K, V>::Erease(K key)
{
	int i = _maxlevel - 1;
	Node* cur = _head;
	Node* s[MAXLEVEL] = NULL;
	int j = 0;
	while (i >= 0){
		while (cur->_plevel[i]){
			if (key > cur->_plevel[i]->_key)
				cur = cur->_level[i];
			else
				break;
		}
		s[j++] = cur;
		--i;
	}
	i = 0;

	if (cur->_plevel[0] && cur->_plevel[i]->_key == key)
	{
		cur = cur->_plevel[0];
		Node* del = NULL;
		del = cur;
		int level = cur->_level;
		for (int i = 0; i < level; ++i){
			s[j - i - 1]->_plevel[i] = cur->_plevel[i];
			delete del;
		}
		while (_maxlevel > 1){
			if (NULL == _head->_plevel[i])
				_maxlevel--;
			else
				break;
		}
		if (_size > 1)
			--_size;
	}
	return false;
}

template<class K, class V>
bool SkipList<K, V>::Find(K key, V& value){
	int i = _maxlevel - 1;
	Node* cur = _head;
	while (i >= 0){
		while (cur->_plevel[i]){
			if (key >= cur->_plevel[i]->_key)
				cur = cur->_plevel[i];
			else
				break;
		}
		--i;
	}
	i = 0;
	if (key == cur->_key){
		value = cur->value;
		return true;
	}
	return false;
}

template<class K, class V>
void SkipList<K, V>::Print()
{
	int i = _maxlevel - 1;
	Node* cur = _head;
	while (i >= 0){
		cout << "this is" << i + 1 << "level";
		while (cur->_plevel[i]){
			cout << cur->_key << ":" << "[" << cur->_value << "]" << " ";
			cur = cur->_plevel[i];
		}
		--i;
		printf("\n");
	}
}



template<class K, class V>
SkipList<K, V>::~SkipList(){
	Node* cur = _head;
	Node* del = cur;
	while (cur){
		del = cur;
		cur = cur->_plevel[0];
		delete del;
	}
	_head = NULL;
}

int main()
{
	system("pause");
	return 0;
}
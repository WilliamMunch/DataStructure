#pragma once

template<class K, class V>
struct AVLTreeNode
{
	AVLTreeNode<K, V>* _pRight;
	AVLTreeNode<K, V>* _pParent;
	AVLTreeNode<K, V>* _pLeft;
	K _key;
	V _value;
	int _bf;

	AVLTreeNode(const K& key, const V& value)
	:_key(key)
	, _value(value)
	, _pLeft(NULL)
	, _pRight(NULL)
	, _pParent(NULL)
	, _bf(0);
	{}
};

template<class K, class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	AVLTree()
		:_pRoot(NULL)
	{}

	AVLTree<K, V>& operator = (const AVLTree<K, V>& bst)
	{
		if (this != &bt){
			_DestoryBinaryTree(_pRoot);
			_pRoot = _CopyBinaryTree(bt._pRoot);
		}
		return *this;
	}

	Node* _CopyBinaryTee(Node* pRoot)
	{
		Node* pNewRoot = NULL;
		if (pRoot){
			pNewRoot = new Node(pRoot->_key, pRoot->_value);
			pNewRoot->_pLeft = _CopyBinaryTee(pRoot->_pLeft);
			pNewRoot->_pRight = _CopyBinaryTee(pRoot->_pRight);
		}
		return pNewRoot;
	}

	AVLTree(const AVLTree<K, V>& bt)
	{
		_pRoot = _CopyBinaryTree(bt._pRoot);
	}

	~AVLTree()
	{
		_DestoryBinarySTree(_pRoot);
	}

	void _DestoryBinarySTree(Node*& pRoot)
	{
		if (pRoot){
			_DestoryBinarySTree(pRoot->_pLeft);
			_DestoryBinarySTree(pRoot->_pRight);
			delete pRoot;
			pRoot = NULL;
		}
	}

	bool Insert(const K& key, const V& value)
	{
		if (NULL == _pRoot){
			_pRoot = new Node(key, value);
			return true;
		}
		Node* pCur = _pRoot;
		Node* pParent = pCur;
		while (pCur){
			if (key < pCur->_key)
			{
				pParent = pCur;
				pCur = pCur->_pLeft;
			}
			else if (key > pCur->_key)
			{
				pParent = pCur;
				pCur = pCur->_pRight;
			}
			else return false;
		}
		pCur = new Node(key, value);
		if (key < pParent->_key){
			pParent->_pRight = pCur;
			pParent = pCur->_pParent;
		}
		if (key > pParent->_key){
			pParent->_pRight = pCur;
			pParent = pCur->_pParent;
		}
		while (pParent){
			if (pParent->_pRight == pCur)
				pParent->_bf++;
			else
				pParent->_bf--;
		    else if ()
		}
	}

protected:
	Node* _pRoot;

};
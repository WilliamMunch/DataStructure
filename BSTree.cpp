#pragma once

#include<iostream>
#include<windows.h>

using namespace std;

template<class K, class V >
class BSTNode
{
public:
	BSTNode(const K& key, const V& value)
	: _pLeft(NULL)
	, _pRight(NULL)
	, _key(key)
	, _value(value)
	{}

private:
	BSTNode<K, V>* _pLeft;
	BSTNode<K, V>* _pRight;
	K _key;
	V _value;
	
};

template<class K,class V>
class BSTree
{
	typedef BSTNode<K, V> Node;
public:
	BSTree()
		:_pRoot(NULL)
	{}

	BSTree<K, V>& operator = (const BSTree<K, V>& bst)
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
			pNewRoot = new Node(pRoot->_value);
			pNewRoot->_pleft = _CopyBinaryTee(pRoot->_pleft);
			pNewRoot->_pright = _CopyBinaryTee(pRoot->_pright);
		}
		return pNewRoot;
	}

	BSTree(const BSTree<K,V>& bt)
	{
		_pRoot = _CopyBinaryTree(bt._pRoot);
	}

	~BSTree()
	{
		_DestoryBinarySTree(_pRoot);
	}

	void _DestoryBinarySTree(Node*& pRoot)
	{
		if (pRoot){
			_DestoryBinarySTree(pRoot->_pleft);
			_DestoryBinarySTree(pRoot->_pright);
			delete pRoot;
			pRoot = NULL;
		}
	}

	bool Insert(const K& key, const V& value)
	{
		if (NULL = _pRoot){
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
			if (key < pParent->_key)
				pParent->_pLeft = pCur;
			if (key > pParent->_key)
				pParent->_pRight = pCur;
   	}

	Node* Find(const K& key)
	{
		Node* pCur = _pRoot;
		while (pCur)
		{
			if (key < pCur->_key)
			{
				pCur = pCur->_pLeft;
			}
			else if (key > pCur->_key)
			{
				pCur = pCur->_pRight;
			}
			else return pCur;
		}
		return NULL;
	}

	const K& GetMaxKey()const
	{
		Node* pCur = _pRoot;
		while (pCur->_pRight)
			pCur = pCur->_pRight;
		return pCur;
	}

	bool Remove(const K& key)
	{
		Node* pCur = _pRoot;
		Node* pParent = pCur;
		if (NULL == _pRoot)
			return false;
		if (NULL == _pRoot->_pLeft && NULL == _pRoot->_pRight && key == _pRoot->_key)
		{
			delete _pRoot;
			_pRoot = NULL;
			return true;
		}
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
			else break;
		}
		if (NULL == pCur)
			return false;
		if (pCur)
		{
			if (NULL == pCur->_pLeft){
				if (pCur != _pRoot){
					if (pParent->_pRight == pCur)
						pParent->_pRight = pCur->_pRight;
					else
						pParent->_pLeft = pCur->_pRight;
				}
				else
					_pRoot = pCur->_pRight;
			}
			else if (NULL = pCur->_pRight){
				if (pCur != _pRoot){
					if (pParent->_pLeft = pCur)
						pParent->_pLeft = pCur->_pLeft;
					else
						pParent->_pRight = pCur->_pLeft;
				}
				else
					_pRoot = pCur->_pLeft;
			}
			else{
				pParent = pCur;
				Node* pDel = pCur->_pRight;
				while (pDel->_pRight){
					pParent = pDel;
					pDel = pDel->_pLeft;
				}
				pCur->_key = pDel->_key;
				pCur->_value = pDel->_value;
				if (pParent->_pLeft == pDel)
					pParent->_pLeft = pDel->_pRight;
				else
					pParent->_pRight = pDel->_pRight;
				pCur = pDel;

			}
			delete pDel;
			pDel = NULL;
		}

	}
protected:
	Node _pRoot;
};
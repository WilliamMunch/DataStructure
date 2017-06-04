#pragma once
#include<iostream>
#include<windows.h>

using namespace std;

enum COLOR{RED, BLACK};

template<class K, class V>
struct RBTreeNode
{
	RBTreeNode<K, V>* _pLeft;
	RBTreeNode<K, V>* _pRight;
	RBTreeNode<K, V>* _pParent;
	K _key;
	V _value;
	COLOR _color;
	RBTreeNode(const K& key, const V& value, const COLOR& _color = RED)
		: _key(key)
		, _value(value)
		, _pLeft(NULL)
		, _pRight(NULL)
		, _pParent(NULL)
		, _color(RED)
	{}
};

template<class K, class V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
public:
	RBTree()
		:_pRoot(NULL)
	{}

	RBTree<K, V>& operator = (const RBTree<K, V>& bst)
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

	RBTree(const RBTree<K, V>& bt)
	{
		_pRoot = _CopyBinaryTree(bt._pRoot);
	}

	~RBTree()
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
	//左单旋
	void _RotateLeft(Node* pParent)
	{
		Node* pSubR = pParent->_pRight;
		Node* pSubRL = pSubR->_pLeft;
		pParent->_pRight = pSubRL;
		if (pSubRL)
			pSubRL->_pParent = pParent;
		pSubR->_pLeft = pParent;
		Node* pPParent = pParent->_pParent;
		pParent->_pParent = pSubR;
		if (NULL == pPParent)
			_pRoot = pSubR;
		else{
			if (pPParent->_pLeft == pParent)
				pPParent->_pLeft = pSubR;
			else
				pPParent->_pRight = pSubR;
		}
		pSubR->_pParent = pPParent;
			
	}
	//右单旋
	void _RotateRight(Node* pParent)
	{
		Node* pSubL = pParent->_pLeft;
		Node* pSubLR = pSubL->_pRight;
		pParent->_pLeft = pSubLR;
		if (pSubLR)
			pSubLR->_pParent = pParent;
		pSubL->_pRight = pParent;
		Node* pPParent = pParent->_pParent;
		pParent->_pParent = pSubL;
		if (NULL == pPParent)
			_pRoot = pSubL;
		else{
			if (pParent == pPParent->_pLeft)
				pPParent->_pLeft = pSubL;
			else
				pPParent->_pRight = pSubL;
		}
		pSubL->_pParent = pPParent;
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
				delete pCur;
			}
			else if (NULL == pCur->_pRight){
				if (pCur != _pRoot){
					if (pParent->_pLeft = pCur)
						pParent->_pLeft = pCur->_pLeft;
					else
						pParent->_pRight = pCur->_pLeft;
				}
				else
					_pRoot = pCur->_pLeft;
				delete pCur;
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
				delete pDel;
				pDel = NULL;
			}
			return true;
		}
		return false;
	}

	bool Insert(const K& key ,const V& value, const COLOR& _color = RED)
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
			pParent->_pLeft = pCur;
		}
		if (key > pParent->_key){
			pParent->_pRight = pCur;
		}
		pCur->_pParent = pParent;
		//调整使插入后的节点符合红黑树的要求
		while (RED == pParent->_color &&  _pRoot != pParent)
		{
			Node* pPParent = pParent->_pParent;
			if (pParent == pPParent->_pLeft)
			{
				Node* pU = pPParent->_pRight;
				if (pU && RED == pU->_color)
				{
					pParent->_color = BLACK;
					pU->_color = BLACK;
					pPParent->_color = RED;
					pCur = pPParent;
				}
				else
				{
					if (pCur == pParent->_pRight)
					{
						_RotateLeft(pParent);
						std::swap(pParent, pCur);
					}
					pPParent->_color = RED;
					pParent->_color = BLACK;
					_RotateRight(pPParent);
				}
			}
			else
			{
				Node* pU = pPParent->_pLeft;
				if (pU && RED == pU->_color)
				{
					pParent->_color = BLACK;
					pU->_color = BLACK;
					pPParent->_color = RED;
					pCur = pPParent;
				}
				else
				{
					if (pCur = pParent->_pLeft)
					{
						_RotateRight(pParent);
						std::swap(pParent, pCur);
					}
					pPParent->_color = RED;
					pParent->_color = BLACK;
					_RotateLeft(pPParent);
				}
			}
		}
		_pRoot->_color = BLACK;
		return true;
	}

	bool CheckRBTree()
	{
		if (NULL == _pRoot)
			return true;
		if (BLACK != _pRoot->_color)
		{
			cout << "违反性质二" << endl;
			return false;
		}
		//保存一条路的黑色节点数量
		size_t blackcount = 0;
		Node* pCur = _pRoot;
		//查任意一条路的黑色节点数量
		while (pCur){
			if (BLACK == pCur->_color)
				blackcount++;
			pCur = pCur->_pLeft;
		}
		return _CheckRBTree(_pRoot, blackcount, 0);
	}

	bool _CheckRBTree(Node* pRoot, const size_t blackcount, size_t k)
	{
		if (NULL == pRoot)
			return true;
		if (BLACK == pRoot->_color)
			k++;
		Node* pParent = pRoot->_pParent;
		if (pParent && RED == pParent->_color && RED == pRoot->_color)
		{
			cout << "违反性质三" << endl;
			return false;
		}
		if (NULL == pRoot->_pLeft && NULL == pRoot->_pRight)
		{
			if (k != blackcount){
				cout << "违反性质四" << endl;
				return false;
			}
		}
		return _CheckRBTree(pRoot->_pLeft, blackcount, k)\
			&& _CheckRBTree(pRoot->_pRight, blackcount, k);

	}

	void MidOrder()
	{
		printf("MidOrder:\n"); //<< endl;
		_MidOrder(_pRoot);
		printf("\n");
	}
protected:

	void _MidOrder(Node* pRoot)
	{
		if (pRoot){
			_MidOrder(pRoot->_pLeft);
			printf("%d  ", pRoot->_key);
			_MidOrder(pRoot->_pRight);
		}
	}
protected:
	Node* _pRoot;
};



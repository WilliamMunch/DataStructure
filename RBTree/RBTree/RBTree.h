#include<iostream>
#include<stdlib.h>

using namespace std;

#pragma once

enum Color{RED, BLACK};

template<class ValueType>
struct RBTreeNode
{
	ValueType _valueField;
	Color _color;
	RBTreeNode<ValueType> _pLeft;
	RBTreeNode<ValueType> _pRight;
	RBTreeNode<ValueType> _pParent;

	RBTreeNode(const ValueType& valueField)
		: _valueField(valueField)
		, _pLeft(NULL)
		, _pRight(NULL)
		, _pParent(NULL)
		, _color(RED)
	{}
};

template<class T>
class RBTreeIterator
{
	typedef RBTreeNode<T> Node;
	typedef RBTreeIterator<T> Self;
public:
	RBTreeIterator()
		:_node(NULL)
	{}

	RBTreeIterator(const Node* node)
		:_node(node)
	{}

	T& operator*()
	{
		return _node->_valuefield;
	}

	T* operator->()
	{
		return &(operator*());
	}

	bool operator == (const Self& s)const
	{
		return _node == s._node;
	}

	bool operator != (const Self& s)const
	{
		return _node != s._node;
	}

	Self& operator ++()//找中序遍历情境下下一个该遍历的结点
	{
		//不用考虑当前结点的左子树 因为其已经被遍历过
		if (_node->_pRight){//已经遍历的结点有右子树
			Node* pSubleft = _node->_pRight;
			while (pSubleft->_pLeft){
				pSubleft = pSubleft->_pLeft;
			}
			_node = pSubleft;//++之后的结点为其右子树的最左结点
		}
		else{//已经遍历得结点无右子树
			Node* cur = _node; 
			Node* pParent = cur->_pParent;
			while (pParent && pParent->_pRight == cur){//寻找距离最近的_node作其为左子孙的祖先
				cur = pParent;//如果当前结点是其父亲的右孩子 说明其父亲的中序遍历顺序在他之前
				pParent = cur->_pParent;
			}
			//如果当前结点是其父亲的左孩子 说明中序遍历的下一个结点是其父亲
			_node = pParent;
		}
	}

	Self& operator --()//从最右结点开始 按 右、 中、 左 顺序找下一个该遍历的结点 逻辑同上
	{
		if (_node->_pLeft){
			Node* pSubRight = _node->_pLeft;
			while (pSubRight->_pRight){
				pSubRight = pSubRight->_pParent;
			}
			_node = pSubRight;
		}
		else{
			Node* cur = _node;
			Node* pParent = _node->_pParent;
			while (pParent && pParent->_pLeft = cur){
				cur = pParent;
				pParent = cur->_pParent;
			}
			_node = pParent;
		}
		return *this;
	}
private:
	Node* _node;
};

template<class K, class T, class KeyofValue>
class RBTree
{
	typedef RBTreeNode<T> Node;
	typedef RBTreeIterator<T> Iterator;
public:
	RBTree()
		:_node(NULL)
	{}

	Iterator Begin()
	{
		Node* cur = _root;
		while (cur && cur->pleft){
			cur = cur->_pLeft;
		}
		return Iterator(cur);
	}

	Iterator End()
	{
		return Iterator(NULL);
	}

	Iterator RBegin()
	{
		Node* cur = _root;
		while (cur && cur->_pRight){
			cur = cur->_pRight;
		}
		return Iterator(cur);
	}

	Iterator REnd()
	{
		return Iterator(NULL);
	}

	Iterator Find(const K& key)
	{
		Node* cur = _root;
		while (cur){
			if (KeyofValue()(cur->_valueField) < key){
				cur = cur->_pLeft;
			}
			else if (KeyofValue()(cur->_valueField) > key){
				cur = cur->_pRight;
			}
			else{
				return Iterator(cur);
			}
		}
		return End();
	}

	pair<Iterator, bool> Insert(const T& v)
	{
		if (_root == NULL){
			Node* cur = Node(v);
			cur->_color = BLACK;
			return make_pair(Iterator(cur), true);
		}
		Node* pParent = NULL;
		Node* cur = _root;
		while (cur){
			if (KeyofValue()(cur->_valueField) < KeyofValue()(v)){
				pParent = cur;
				cur = cur->_pLeft;
			}
			else if (KeyofValue()(cur->_valueField) > KeyofValue()(v)){
				pParent = cur;
				cur = cur->_pRight;
			}
			else{
				return make_pair(Iterator(cur), false);
			}
		}
		Node* pnewNode = Node(v);
		pnewNode->_color = RED;
		if (cur == pParent->_pLeft){
			pParent->_pLeft = pnewNode;
			pnewNode->_pParent = pParent;
		}
		else
		{
			pParent->_pRight = pnewNode;
			pnewNode->_pParent = pParent;
		}

		while (pParent && pParent->_color == RED)
		{
			Node* pParentParent = pParent->_pParent;
			if (pParent = pParentParent->_pLeft)
			{
				Node* pUncle = pParent->_pRight;
				if (pUncle->_color == RED){
					pUncle->_color = pParent->_color = BLACK;
					pParentParent->_color = RED;
					cur = pParentParent;
				}
				else{
					if (pnewNode == pParent->_pRight){
						RotateL(pParent);
						swap(pParent, cur);
					}
					RotateR(pParentParent);
					pParent->_color = BLACK;
					pParentParent->_color = RED;
					break;
				}
				
			}
			else{
				Node* pUncle = pParent->_pLeft;
				if (pUncle->_color == RED){
					pUncle->_color = pParent->_color = BLACK;
					pParentParent->_color = RED;
					cur = pParentParent;
				}
				else{
					if (pnewNode == pParent->_pLeft){
						RotateR(pParent);
						swap(pParent, cur);
					}
					RotateL(pParentParent);
					pParent->_color = BLACK;
					pParentParent->_color = RED;
					break;
				}

			}
		}
		_root->_color = BLACK;
		return make_pair(Iterator(pnewNode), true);
	}

	
protected:
	void RotateR(Node* pParent)
	{
		Node* pSubL = pParent->_pLeft;
		Node* pSubLR = pSubL->_pRight;

		pParent->_pLeft = pSubLR;//处理pParent和pSubLR的关系
		if (pSubLR)
			pSubLR->_pParent = pParent;

		Node* pParentParent = pParent->_pParent;
		pSubL->_pRight = pParent;//处理pParent 和pSubL 的关系
		pParent->_pParent = pSubL;
		if (pParentParent == NULL){//处理pParentParent 和 pSubL的关系
			_root = pSubL;
			pSubL->_pParent = NULL;
		}
		else{
			if (pParentParent->_pLeft == pParent){
				pParentParent->_pLeft = pSubL;
			}
			else{
				pParentParent->_pRight = pSubL;
			}
			pSubL->_pParent = pParentParent;
		}
	}

	void RotateL(Node* pParent)//思路与RotateR一样
	{
		Node* pSubR = pParent->_pRight;
		Node* pSubRL = pSubR->_pLeft;

		pParent->_pRight = pSubRL;
		if (pSubRL)
			pSubRL->_pParent = pParent;
		
		Node* pParentParent = pParent->_pParent;
		pParent->_pParent = pSubR;
		pSubR->_pLeft = pParent;
		if (NULL == pParentParent){
			_node = pSubR;
			pSubR->_pParent == NULL;
		}
		else{
			if (pParentParent->_pLeft == pParent)
				pParentParent->_pLeft = pSubR；
			else{
				pParentParent->_pRight = pSubR;
			}
			pSubR->_pParent = pParent;
		}
	}
		
private:
	Node* _root;
};



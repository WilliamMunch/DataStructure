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
	RBTreeNode<ValueType>* _pLeft;
	RBTreeNode<ValueType>* _pRight;
	RBTreeNode<ValueType>* _pParent;

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

	RBTreeIterator(Node* node)
		:_node(node)
	{}

	T& operator*()
	{
		return _node->_valueField;
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
		return *this;
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
			while (pParent && pParent->_pLeft == cur){
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

template<class T>
struct KeyOfValue
{
	T operator()(const T& key)
	{
		return key;
	}
};

//Set使用时 T 为 K， Map使用时 T 为 ValueType-------pair<K, V> 一份红黑树代码让Set Map都可以用
template<class K, class T, class KeyofValue = KeyOfValue<T>>
class RBTree
{
	typedef RBTreeNode<T> Node; //T 就是RBTreeNode中的 ValueField， Set中的K，Map中的pair<K, V>
	
public:
	typedef RBTreeIterator<T> Iterator;

	RBTree()
		:_root(NULL)
	{}

	Iterator Begin()
	{
		Node* cur = _root;
		while (cur && cur->_pLeft){
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
			_root = new Node(v);
			_root->_color = BLACK;
			return make_pair(Iterator(_root), true);
		}
		Node* pParent = NULL;
		Node* cur = _root;
		while (cur){
			if (KeyofValue()(cur->_valueField) > KeyofValue()(v)){
				pParent = cur;
				cur = cur->_pLeft;
			}
			else if (KeyofValue()(cur->_valueField) < KeyofValue()(v)){
				pParent = cur;
				cur = cur->_pRight;
			}
			else{
				return make_pair(Iterator(cur), false);
			}
		}
		Node* pnewNode = new Node(v);
		cur = pnewNode;
		if (KeyofValue()(pParent->_valueField) > KeyofValue()(v)){
			pParent->_pLeft = cur;
			cur->_pParent = pParent;
		}
		else
		{
			pParent->_pRight = cur;
			cur->_pParent = pParent;
		}

		while (pParent && pParent->_color == RED)
		{
			Node* pParentParent = pParent->_pParent;
			if (pParent == pParentParent->_pLeft)
			{
				Node* pUncle = pParentParent->_pRight;
				if (pUncle && pUncle->_color == RED){
					pUncle->_color = pParent->_color = BLACK;
					pParentParent->_color = RED;
					cur = pParentParent;
					pParent = cur->_pParent;
				}
				else{
					if (cur == pParent->_pRight){
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
				Node* pUncle = pParentParent->_pLeft;
				if (pUncle && pUncle->_color == RED){
					pUncle->_color = pParent->_color = BLACK;
					pParentParent->_color = RED;
					cur = pParentParent;
					pParent = cur->_pParent;
				}
				else{//pUncle为空或 pUncle为黑色
					if (cur == pParent->_pLeft){
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


	bool IsBalance()//判断该树是否按照红黑树的规则是平衡的平衡
	{
		if (_root && _root->_color == RED)
			return false;
		size_t k = 0; 
		size_t blacknum = 0;//blacknum 为每一路径中的黑节点个数
		Node* cur = _root;
		while (cur){
			if (cur->_color == BLACK)
				++k;//计算其中一条路径的黑节点个数 以它为基准
			cur = cur->_pLeft;
		}
		return _IsBalance(_root, blacknum, k);
	}
		
protected:
	bool _IsBalance(Node* root, size_t blacknum, size_t k)
	{
		if (root == NULL){//当 root == NULL 时 递归走完了一条树的路径 这时候算这条路径中黑节点个数是否等于基准
			if (blacknum == k)
				return true;
			else
				return false;
		}

		if (root->_color == BLACK)
			++blacknum;

		if (root->_color == RED && root->_pParent->_color == RED){
			return false;
		}

		return _IsBalance(root->_pLeft, blacknum, k) && _IsBalance(root->_pRight, blacknum, k);
	}

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
			_root = pSubR;
			pSubR->_pParent = NULL;
		}
		else{
			if (pParentParent->_pLeft == pParent)
				pParentParent->_pLeft = pSubR;
			else{
				pParentParent->_pRight = pSubR;
			}
			pSubR->_pParent = pParent;
		}
	}
		
private:
	Node* _root;
};



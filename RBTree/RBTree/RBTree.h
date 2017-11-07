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

	Self& operator ++()//����������龳����һ���ñ����Ľ��
	{
		//���ÿ��ǵ�ǰ���������� ��Ϊ���Ѿ���������
		if (_node->_pRight){//�Ѿ������Ľ����������
			Node* pSubleft = _node->_pRight;
			while (pSubleft->_pLeft){
				pSubleft = pSubleft->_pLeft;
			}
			_node = pSubleft;//++֮��Ľ��Ϊ����������������
		}
		else{//�Ѿ������ý����������
			Node* cur = _node; 
			Node* pParent = cur->_pParent;
			while (pParent && pParent->_pRight == cur){//Ѱ�Ҿ��������_node����Ϊ�����������
				cur = pParent;//�����ǰ������丸�׵��Һ��� ˵���丸�׵��������˳������֮ǰ
				pParent = cur->_pParent;
			}
			//�����ǰ������丸�׵����� ˵�������������һ��������丸��
			_node = pParent;
		}
	}

	Self& operator --()//�����ҽ�㿪ʼ �� �ҡ� �С� �� ˳������һ���ñ����Ľ�� �߼�ͬ��
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

		pParent->_pLeft = pSubLR;//����pParent��pSubLR�Ĺ�ϵ
		if (pSubLR)
			pSubLR->_pParent = pParent;

		Node* pParentParent = pParent->_pParent;
		pSubL->_pRight = pParent;//����pParent ��pSubL �Ĺ�ϵ
		pParent->_pParent = pSubL;
		if (pParentParent == NULL){//����pParentParent �� pSubL�Ĺ�ϵ
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

	void RotateL(Node* pParent)//˼·��RotateRһ��
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
				pParentParent->_pLeft = pSubR��
			else{
				pParentParent->_pRight = pSubR;
			}
			pSubR->_pParent = pParent;
		}
	}
		
private:
	Node* _root;
};



#pragma once
#include<string.h>
#include<iostream>
#include<queue>
#include<stack>

using namespace std;

template<class T>
struct BinaryTreeNode
{
	T _value;
	BinaryTreeNode<T>* _pleft;
	BinaryTreeNode<T>* _pright;
	BinaryTreeNode(const T& value)
		: _value(value)
		, _pleft(NULL)
		, _pright(NULL)
	{}
};

template<class T>
class BinaryTree
{
	typedef BinaryTreeNode<T> Node;
public:
	void _CreateBinaryTree(Node*& pRoot, const T arr[], size_t size, size_t& index, const T invalid)
	{
		if (index < size && invalid != arr[index])
		{
			pRoot = new Node(arr[index]);
			_CreateBinaryTree(pRoot->_pleft, arr, size, ++index, invalid);
			_CreateBinaryTree(pRoot->_pright, arr, size, ++index, invalid);

		}
	}
		 
	BinaryTree()
		:_pRoot(NULL)
	{}

	BinaryTree(const T arr[], size_t size,const T& invalid)
	{
		size_t index = 0;
		_CreateBinaryTree(_pRoot, arr, size, index, invalid);
	}

	Node* _CopyBinaryTree(Node* pRoot)
	{
		Node* pNewRoot = NULL;
		if (pRoot){
			pNewRoot = new Node(pRoot->_value);
			pNewRoot->_pleft = _CopyBinaryTree(pRoot->_pleft);
			pNewRoot->_pright = _CopyBinaryTree(pRoot->_pright);
		}
		return pNewRoot;
	}

	BinaryTree(const BinaryTree<T>& bt)
	{
		_pRoot = _CopyBinaryTree(bt._pRoot);
	}  

	~BinaryTree()
	{
		_DestoryBinaryTree(_pRoot);
	}

	void _DestoryBinaryTree(Node*& pRoot)
	{
		if (pRoot){
			_DestoryBinaryTree(pRoot->_pleft);
			_DestoryBinaryTree(pRoot->_pright);
			delete pRoot;
			pRoot = NULL;
		}
	}
	Node* Find(const T& value)
	{
		return _Find(_pRoot, value);
	}

	Node* _Find(Node* pRoot, const T& value)
	{
	
		if (NULL == pRoot)
			return NULL;
		if (pRoot->_value == value)
			return pCur;
		Node* pCur = pRoot;
		if (pCur == _Find(pCur->_pleft, value))
			return pCur;
		return _Find(pCur->_pright, value);
		
	}

	BinaryTree<T>& operator = (const BinaryTree<T>& bt)
	{
		if (this != &bt){
			_DestoryBinaryTree(_pRoot);
			_pRoot = _CopyBinaryTree(bt._pRoot);
		}
		return *this;
	}

	void _PreOrder(Node* pRoot)
	{
		if (pRoot){
			cout << pRoot->_value <<" ";
			_PreOrder(pRoot->_pleft);
			_PreOrder(pRoot->_pright);
		}
		
	}

	void PreOrder()
	{
		cout << "PreOrder" << endl;
		_PreOrder(_pRoot);
		cout << endl;
	}

	void MidOrder()
	{
		cout << "MidOrder" << endl;
		_MidOrder(_pRoot);
		cout << endl;
	}

	void _MidOrder(Node* pRoot)
	{
		if (pRoot){
			_MidOrder(pRoot->_pleft);
			cout << pRoot->_value <<" ";
			_MidOrder(pRoot->_pright);
		}

	}

	void PostOrder()
	{
		cout << "PostOrder" << endl;
		_PostOrder(_pRoot);
		cout << endl;
	}

	void _PostOrder(Node* pRoot)
	{
		if (pRoot){
			_PostOrder(pRoot->_pleft);
			_PostOrder(pRoot->_pright);
			cout << pRoot->_value <<" ";
		}
	}

	void levelOrder()
	{
		if (NULL == _pRoot)
			return ;
		queue<Node*> q;
		q.push(_pRoot);
		while (!q.empty())
		{
			Node* pCur = q.front();
			q.pop();
			if (pCur->_pleft)
				q.push(pCur->_pleft);
			if (pCur->_pright)
				q.push(pCur->_pright);
			cout << pCur->_value << " ";
		}
		cout << endl;
	}
	//求二叉树的高度
	size_t TreeHeight()
	{
		return _TreeHeight(_pRoot);
	}
	size_t _TreeHeight(Node* pRoot)
	{
		if (NULL == pRoot)
			return 0;
		if (NULL == pRoot->_pleft && NULL == pRoot->_pright)
			return 1;
		size_t LeftHeight  = _TreeHeight(pRoot->_pleft);
		size_t RightHeight = _TreeHeight(pRoot->_pright);
		
		return (LeftHeight > RightHeight) ? LeftHeight + 1 : RightHeight + 1;
 
	}
	//非递归遍历法
	void Pre_Order()
	{
		cout << "Pre_Order" << endl;
		if (NULL == _pRoot)
			return;
		stack<Node*> s;
		s.push(_pRoot);
		while (!s.empty())
		{
			Node* pTop = s.top();
			cout << pTop->_value << " ";
			s.pop();
			if (NULL != pTop->_pright)
				s.push(pTop->_pright);
			if (NULL != pTop->_pleft)
				s.push(pTop->_pleft);
		}
		cout << endl;
	}

	void Mid_Order()
	{
		cout << "Mid_Order" << endl;
		if (NULL == _pRoot)
			return;
		stack<Node*> s;
		Node* pCur = _pRoot;
		while (pCur || !s.empty()){
			while (pCur)
			{
				s.push(pCur);
				pCur = pCur->_pleft;
			}
			pCur = s.top();
			cout << pCur->_value << " ";
			s.pop();			
			while (NULL == pCur->_pright && !s.empty())
			{
				pCur = s.top();
				cout << pCur->_value << " ";
				s.pop();
			}
			pCur = pCur->_pright;
		}
		cout << endl;
	}

	void Post_Order()
	{
		cout << "Post_Order" << endl;
		if (NULL == _pRoot)
			return;
		stack<Node*> s;
		Node* pCur = _pRoot;
		Node* prev = _pRoot;
		while (pCur || !s.empty()){
			while (pCur){
				s.push(pCur);
				pCur = pCur->_pleft;
			}
			Node* pTop = s.top();
			if (NULL == pTop->_pright || prev == pTop->_pright){
				cout << pTop->_value << " ";
				s.pop();
				prev = pTop;
			}
			else{ pCur = pTop->_pright; }
		}
		cout << endl;
	}



private:
	Node* _pRoot;
};

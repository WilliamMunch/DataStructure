#pragma once
//#include"BSTreeiterator.cpp"
#include<iostream>
#include<assert.h>
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

//protected:
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
			pNewRoot = new Node(pRoot->_key,pRoot->_value);
			pNewRoot->_pLeft = _CopyBinaryTee(pRoot->_pLeft);
			pNewRoot->_pRight = _CopyBinaryTee(pRoot->_pRight);
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
			if (key < pParent->_key)
				pParent->_pLeft = pCur;
			if (key > pParent->_key)
				pParent->_pRight = pCur;
   	}

	bool InsertR(const K& key,const V& value)
	{
		_InsertR(_pRoot,key,value)
	}

	bool _InsertR(Node*& pRoot, const K& key)
	{
		if (pRoot == NULL){
			pRoot = new Node(key, value);
			return true;
		}
		if (pRoot->_key > key)
			pRoot = pRoot->_pLeft;
		else if (pRoot->_key < key)
			pRoot = pRoot->_pRight;
		else{
			pRoot = new Node(key, value);
		}
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
		Node* pParent = _pRoot;
		Node* pCur = _pRoot;
		while (pCur){
			if (pCur->_key > key){
				pParent = pCur;
				pCur = pCur->_pLeft;
			}
			else if (pCur->_key < key){
				pParent = pCur;
				pCur = pCur->_pRight;
			}
			else{
				break;
			}
		}
		if (pCur)
		{
			if (pCur->_pLeft == NULL){
				if (pCur != _pRoot){
					if (pParent->_pLeft == pCur)
						pParent->_pLeft = pCur->_pRight;
					else
						pParent->_pRight = pCur->_pRight;
				}
				else
					_pRoot = pCur->_pRight;
				delete pCur;
				pCur = NULL;
			}
			else if (pCur->_pRight == NULL){
				if (pCur != _pRoot){
					if (pParent->_pLeft == pCur)
						pParent->_pLeft = pCur->_pLeft;
					else
						pParent->_pRight = pCur->_pRight;
				}
				else
					_pRoot = pCur->_pLeft;
				delete pCur;
				pCur = NULL;
			}
			else{
				Node* pParent = pCur;
				Node* pDel = pCur->_pRight;
				while (pDel->_pLeft){
					pParent = pDel;
					pDel = pDel->_pLeft;
				}
				pCur->_key = pDel->_key;
				pCur->_value = pDel->_value;
				if (pParent->_pLeft == pDel)
					pParent->_pLeft = pDel->_pRight;
				else
					pParent->_pRight = pDel->_pRight;
				delete pDel;
				pDel = NULL;
			}
			return true;
		}
		return false;
	}

	Node* Find1(const K& value)
	{
		return _Find1(_pRoot, value);
	}

	Node* _Find1(Node* pRoot, const K& value)
	{
		Node* pCur = pRoot;
		if (NULL == pRoot)
			return NULL;
		if (pRoot->_value == value)
			return pCur;
		if (NULL == _Find1(pCur->_pLeft, value))
		{
			return _Find1(pCur->_pRight, value);
		}
	}

	Node* _GetLastCommonAncestor(Node* pRoot, Node* pNode1, Node* pNode2)
	{
		if (pRoot == NULL)
			return NULL;
		if (pNode1->_value < pRoot->_value && pNode2->_value < pRoot->_value)
			_GetLastCommonAncestor(pRoot->_pLeft, pNode1, pNode2);
		else if (pNode1->_value > pRoot->_value && pNode2->_value > pRoot->_value)
			_GetLastCommonAncestor(pRoot->_pRight, pNode1, pNode2);
		else {
			return pRoot;
		}
	}

	Node* GetLastCommonAncestor(Node* pNode1, Node* pNode2)
	{
		assert(pNode1 && pNode2);
		if (_pRoot == NULL)
			return NULL;
		return _GetLastCommonAncestor(_pRoot, pNode1, pNode2);
	}

 //   bool Remove(const K& key)
	//{
	//	Node* pRoot = _pRoot;
	//	bool ret = _Remove(key, pRoot);
	//	return ret;
	//}
	//bool _Remove(const K& key,Node* pCur)
	//{
	//	//Node* pCur = _pRoot;
	//	Node* pParent = pCur;
	//	if (NULL == _pRoot)
	//		return false;
	//	if (NULL == _pRoot->_pLeft && NULL == _pRoot->_pRight && key == _pRoot->_key)
	//	{
	//		delete _pRoot;
	//		_pRoot = NULL;
	//		return true;
	//	}
	//
	//	if (pCur)
	//	{
	//		if (NULL == pCur->_pLeft){
	//			if (pCur != _pRoot){
	//				if (pParent->_pRight == pCur)
	//					pParent->_pRight = pCur->_pRight;
	//				else
	//					pParent->_pLeft = pCur->_pRight;
	//			}
	//			else
	//				_pRoot = pCur->_pRight;
	//			delete pCur;
	//		}
	//		else if (NULL == pCur->_pRight){
	//			if (pCur != _pRoot){
	//				if (pParent->_pLeft = pCur)
	//					pParent->_pLeft = pCur->_pLeft;
	//				else
	//					pParent->_pRight = pCur->_pLeft;
	//			}
	//			else
	//				_pRoot = pCur->_pLeft;
	//			delete pCur;
	//		}
	//		else{
	//			pParent = pCur;
	//			Node* pDel = pCur->_pRight;
	//			while (pDel->_pLeft){
	//				pParent = pDel;
	//				pDel = pDel->_pLeft;
	//			}
	//			pCur->_key = pDel->_key;
	//			pCur->_value = pDel->_value;
	//			if (pParent->_pLeft == pDel)
	//				pParent->_pLeft = pDel->_pRight;
	//			else
	//				pParent->_pRight = pDel->_pRight;
	//			pCur = pDel;
	//			delete pDel;
	//			pDel = NULL;
	//		}

	//		return true;
	//	}
	//	if (key < pCur->_key)
	//	bool ret = _Remove(key, pCur->_pLeft);
	//	else
	//	bool ret = _Remove(key, pCur->_pRight);
	//	return false;
	//}

	void MidOrder()
	{
		cout << "MidOrder" << endl;
		_MidOrder(_pRoot);
		cout << endl;
	}
	
	//判断一棵树是否是二叉搜索树
	bool _IsSerachTree(Node* pRoot,  bool flag, int& prev)
	{
		if (nullptr == pRoot)
			return true;
		if (pRoot->_pLeft == nullptr && flag)
		{
			_IsSerachTree(pRoot->_pLeft, flag, prev);
		}
		if (pRoot->_value <= prev)
		{
			flag = false;
		}
		prev = pRoot->_value;
		if (pRoot->_pRight == nullptr && flag)
		{
			_IsSerachTree(pRoot->_pRight, flag, prev);
		}
		return flag;
	}
	
	bool IsSerachTree()
	{
		Node* pRoot = _pRoot;
		bool flag = true;
		int min = INT_MIN;
		return _IsSerachTree(pRoot , flag, min);
	}
	
protected:

	void _MidOrder(Node* pRoot)
	{
		if (pRoot){
			_MidOrder(pRoot->_pLeft);
			cout << pRoot->_key << " ";
			_MidOrder(pRoot->_pRight);
		}
	}
protected:
	Node* _pRoot;
};

void Test()
{
	int arr[] = { 5, 3, 7, 4, 9, 6, 2, 8, 1, 0 };
	BSTree<int,int> tree;
	for (int i = 0; i < 10;i++)
	   tree.Insert(arr[i], i);
	cout << tree.GetLastCommonAncestor(tree.Find1(5), tree.Find1(9))->_value << endl;;
	tree.MidOrder();
	//tree.Remove(5);
	//tree.Remove(4);
	//tree.MidOrder();
	cout << tree.IsSerachTree() << endl;
}
//查找 排序 去重 、
//判断一个单词是否合法   将合法单词加在树中 在书中找
//统计一个文本中单词出现的次数  
//实现中英文互翻  ----K V 模型 二叉树用来查找
int main()
{
	
	Test();
	system("pause");
	return 0;
}
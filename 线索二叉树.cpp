#include<iostream>
#include<string.h>

using namespace std;

enum PointInfo{LINK, THREAD};

template<typename T>
struct Binary
{
	T _data;
	Binary<T>* _pleft;
	Binary<T>* _pright;
	PointInfo _leftThread;
	PointInfo _rightThread;
	Binary(const T& data)
		:_data(data)
		, _pleft(NULL)
		, _pright(NULL)
		, _leftThread(LINK)
		, _rightThread(LINK)
	{}
};

template<typename T>
class BinaryTree
{
	typedef Binary<T> Node;
protected:
	Node* _pRoot;
public:
	BinaryTree()
		:_pRoot(NULL)
	{}

	void CreateTree(Node*& pRoot, const T arr[], size_t& index, size_t size, const T& invalid)
	{
		if (index < size && invalid != arr[index])
		{
			pRoot = new Node(arr[index]);
			_CreateTree(pRoot->_pleft, arr, size, ++index, invalid);
			_CreateTree(pRoot->_pright, arr, size, ++index, invalid);

		}
	}
	//递归构造二叉树
	BinaryTree(const T arr[], size_t size, const T& invalid)
	{
		size_t index = 0;
		CreateTree(_pRoot, arr, size, index, invalid);
	}

	//前序线索化
	void _PreThread(Node* pRoot, Node*& prev)
	{
		if (pRoot){
			if (NULL == pRoot->_pleft){
				pRoot->_pleft = prev;
				pRoot->_leftThread = THREAD;
			}
			if (prev && NULL == pRoot->_pright){
				prev->_pright = pRoot;
				prev->_rightThread = THREAD;
			}
			prev = pRoot;
			if (LINK == pRoot->_leftThread)
				_PreThread(pRoot->_pleft, prev);
			if (LINK = pRoot->_rightThread)
				_PreThread(pRoot->_pright, prev);
		}
	}

	void PreThread()
	{
		Node* prev = NULL;
		_PreThread(_pRoot, prev);
	}

	void  _MidThread(Node* pRoot, Node*& prev)
	{
		if (pRoot){
			_MidThread(pRoot->_pleft, prev);
			prev = pRoot;
			if (NULL == pRoot->_pleft){
				pRoot->_pleft = prev;
				pRoot->_leftThread = THREAD;
			}
			if (prev && NULL == pRoot->_pright){
				prev->_pright = pRoot;
				prev->_rightThread = THREAD;
			}
										
			if (LINK = pRoot->_rightThread)
				_MidThread(pRoot->_pright, prev);
		}
	}

	void MidThread()
	{
		Node* prev = NULL;
		_MidThread(_pRoot, prev);
	}

	void  _PostThread(Node* pRoot, Node*& prev)
	{
		if (pRoot){
			_PostThread(pRoot->_pleft, prev);
			_PostThread(pRoot->_pright, prev);
			prev = pRoot;
			if (NULL == pRoot->_pleft){
				pRoot->_pleft = prev;
				pRoot->_leftThread = THREAD;
			}
			if (prev && NULL == pRoot->_pright){
				prev->_pright = pRoot;
				prev->_rightThread = THREAD;
			}
						
		}
	}
	
	void PostThread()
	{
		Node* prev = NULL;
		_PostThread(_pRoot, prev);
	}

};
 
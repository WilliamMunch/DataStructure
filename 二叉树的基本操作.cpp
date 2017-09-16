#pragma once
#include<string.h>
#include<iostream>
#include<queue>
#include<stack>
#include<assert.h>
#include<list>

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
	//void  _CreateBinaryTree1(Node*& pRoot, const T arr[], size_t size, size_t& index, const T invalid)
	//{
	//	if (index < size && invalid != arr[index])
	//	{
	//		pRoot = new Node(arr[index]);
	//		_CreateBinaryTree(pRoot->_pleft, arr, size, ++index, invalid);
	//		_CreateBinaryTree(pRoot->_pright, arr, size, ++index, invalid);

	//	}
	//}

	Node*  _CreateBinaryTree2(const T arr[], size_t size, size_t& index, const T invalid)
	{
		Node* pRoot = NULL;
		if (index < size && invalid != arr[index])
		{
			pRoot = new Node(arr[index]);
			pRoot->_pleft = _CreateBinaryTree2( arr, size, ++index, invalid);
			pRoot->_pright = _CreateBinaryTree2( arr, size, ++index, invalid);

		}
		return pRoot;
	}
		 
	BinaryTree()
		:_pRoot(NULL)
	{}

	BinaryTree(const T arr[], size_t size,const T& invalid)
	{
		assert(arr);
		size_t index = 0;
		//_CreateBinaryTree1(_pRoot, arr, size, index, invalid);
		_pRoot = _CreateBinaryTree2(arr, size, index, invalid);
	}

	Node*  _CopyBinaryTree(Node* pRoot)
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
	//层序遍历
	

	void level_Order()
	{
		queue<Node*> q;
		if (_pRoot == NULL)
			return;
		q.push(_pRoot);
		while (!q.empty()){
			Node* pcur = q.front();
			q.pop();
			if (pcur->_pleft != NULL)
				q.push(pcur->_pleft);
			if (pcur->_pright != NULL)
				q.push(pcur->_pright);
			cout << pcur->_value << " ";
		}
		cout << endl;
	}
	//判断一棵二叉树是否是完全二叉树
	bool IsTotalTree()
	{
		queue<Node*> q;
		bool flag = true;
		if (_pRoot == NULL)
 			return true;
		q.push(_pRoot);
		while (!q.empty()){
			Node* pcur = q.front();
			q.pop();
			if (pcur->_pleft != NULL){
				q.push(pcur->_pleft);
				if (flag == false){
					return false;
				}
			}
			else{
				flag = false;
			}
			if (pcur->_pright != NULL){
				q.push(pcur->_pright);
				if (flag == false){
					return false;
				}

			}
			else{
				flag = false;
			}
		}
		return true;

  	}

	//求二叉树的高度
	size_t TreeHeight()
	{
		return _TreeHeight(_pRoot);
	}
	size_t _TreeHeight(Node*& pRoot)
	{
		if (NULL == pRoot)
			return 0;
		/*if (NULL == pRoot->_pleft && NULL == pRoot->_pright)
			return 1;*/
		size_t LeftHeight  = _TreeHeight(pRoot->_pleft);
		size_t RightHeight = _TreeHeight(pRoot->_pright);
		
		return (LeftHeight > RightHeight) ? LeftHeight + 1 : RightHeight + 1;
 
	}
	//非递归遍历法

	//把问题分成 树的左路 与 树的其他部分 两块
	//先将节点压栈 遍历后再出栈 以此模仿递归
	void Pre_Order()
	{
		stack<Node*> s;
		Node* cur = _pRoot;
		if (_pRoot == NULL)
			return;
		
		while (cur || !s.empty()){
			while (cur){
				cout << cur->_value << " ";
				s.push(cur);
				cur = cur->_pleft;
			}
			Node* top = s.top();//top 的左边不可能有还没遍历的节点
			s.pop();
			if (top->_pright != NULL)
				cur = top->_pright;
		}
		cout << endl;
	}
	//相较于先序遍历 只需要改变访问节点的时机
	void Mid_Order()
	{
		Node* cur = _pRoot;
		stack<Node*> s;
		if (_pRoot == NULL)
			return;
		while (cur || !s.empty()){
			while (cur){
				s.push(cur);
				cur = cur->_pleft;
			}
			Node* top = s.top();
			cout << top->_value << " ";
			s.pop();

			if (top->_pright != NULL)
				cur = top->_pright;
		}
		cout << endl;
 	}

	/*void Mid_Order()
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
	}*/


	void Post_Order()
	{
		Node* cur = _pRoot;
		Node* prev = NULL;//用prev记录下来已经遍历过的节点
		stack<Node*> s;
		while (cur || !s.empty()){
			while (cur){
				s.push(cur);
				cur = cur->_pleft;
			}
			Node* top = s.top();
			if (top->_pright == NULL || top->_pright == prev){
				//为防止死循环 已遍历的右子树不会再被遍历
				cout << top->_value << " ";
				s.pop();
				prev = top;
			}
			else{//遍历未被遍历的右子树
				cur = top->_pright;
			}
		}
		cout << endl;
	}

	//求二叉树的镜像
	void _Mirror(Node* pRoot)
	{
		if (pRoot == NULL)
			return;
		std::swap(pRoot->_pleft, pRoot->_pright);
		_Mirror(pRoot->_pleft);
		_Mirror(pRoot->_pright);
	}

	void Mirror()
	{
		_Mirror(_pRoot);
	}

	void  _Size(Node* pRoot,int& count)
	{
		
		if (pRoot == NULL )
			return ;
		
	    _Size(pRoot->_pleft, count);
		_Size(pRoot->_pright,count);
		count++;
		/*if (pRoot == NULL)
			return 0;
		return _Size(pRoot->_pleft) + _Size(pRoot->_pright) + 1;*/

	}

	size_t Size()
	{
		int i = 0;
		_Size(_pRoot,i);
		return i;
	}

	size_t _k_nodes(Node*& pRoot, size_t k)
	{
		if (pRoot == NULL)
			return 0;
		if (k == 1)
			return 1;
		return _k_nodes(pRoot->_pleft, k-1) + _k_nodes(pRoot->_pright,k-1);
	}

	size_t k_nodes(size_t k)
	{
		if (k < 0)
			return 0;
	
		return _k_nodes(_pRoot, k);
	}

	//求二叉树两个结点的最低公共父节点（辅助内存）



	//求二叉树两个结点的最低公共父节点（递归）

	//判断一棵树是不是另外一棵树的子树


private:
	Node* _pRoot;
};

int main()
{
	char arr[] = {'1','2','3','#','#','4','#','#','5','6'}; 

	BinaryTree<char> BiTree(arr,sizeof(arr)/sizeof(arr[0]),'#');
	BiTree.Post_Order();
	BiTree.Pre_Order();
	BiTree.Mid_Order();
	BiTree.level_Order();
	if (BiTree.IsTotalTree())
		cout << "shi" << " ";
	else
		cout << "no" << " ";
	//BiTree.Mirror();
	//BiTree.PreOrder();
	//cout << BiTree.Size() << endl;
	//cout << BiTree.TreeHeight() << endl;
	//cout << BiTree.k_nodes(3) << endl;
	system("pause");
	return 0;
}

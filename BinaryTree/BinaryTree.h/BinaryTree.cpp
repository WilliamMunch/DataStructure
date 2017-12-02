#pragma once
#include<string.h>
#include<iostream>
#include<queue>
#include<stack>
#include<assert.h>


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
			pRoot->_pleft = _CreateBinaryTree2(arr, size, ++index, invalid);
			pRoot->_pright = _CreateBinaryTree2(arr, size, ++index, invalid);

		}
		return pRoot;
	}

	BinaryTree()
		:_pRoot(NULL)
	{}

	BinaryTree(const T arr[], size_t size, const T& invalid)
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
			cout << pRoot->_value << " ";
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
			cout << pRoot->_value << " ";
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
			cout << pRoot->_value << " ";
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

	//求二叉树的高度  递归法
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
		size_t LeftHeight = _TreeHeight(pRoot->_pleft);
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

	void  _Size(Node* pRoot, int& count)
	{

		if (pRoot == NULL)
			return;

		_Size(pRoot->_pleft, count);
		_Size(pRoot->_pright, count);
		count++;
		/*if (pRoot == NULL)
		return 0;
		return _Size(pRoot->_pleft) + _Size(pRoot->_pright) + 1;*/

	}

	size_t Size()
	{
		int i = 0;
		_Size(_pRoot, i);
		return i;
	}

	size_t _k_nodes(Node*& pRoot, size_t k)
	{
		if (pRoot == NULL)
			return 0;
		if (k == 1)
			return 1;
		return _k_nodes(pRoot->_pleft, k - 1) + _k_nodes(pRoot->_pright, k - 1);
	}

	size_t k_nodes(size_t k)
	{
		if (k < 0)
			return 0;

		return _k_nodes(_pRoot, k);
	}

	//求二叉树两个结点的最低公共父节点（无辅助内存）
	Node* Find1(const T& value)
	{
		return _Find1(_pRoot, value);
	}

	Node* _Find1(Node* pRoot, const T& value)
	{
		Node* pCur = pRoot;
		if (NULL == pRoot)
			return NULL;
		if (pRoot->_value == value)
			return pCur;
		if (NULL == _Find1(pCur->_pleft, value))
		{
			return _Find1(pCur->_pright, value);
		}

	}

	bool _Find2(Node* pRoot, const T& value)
	{
		Node* pCur = pRoot;
		if (NULL == pCur)
			return false;
		if (pCur->_value == value)
			return true;
		if (_Find2(pRoot->_pleft, value))
			return true;
		return _Find2(pRoot->_pright, value);
	}
	Node* _GetLastCommonAncestor(Node* pRoot, Node* pNode1, Node* pNode2)
	{
		if (pRoot == NULL)
			return NULL;
		if (pNode1 == pRoot || pNode2 == pRoot)
			return pRoot;
		bool Node1Inleft = false, Node2Inright = false, \
			Node1Inright = false, Node2Inleft = false;
		Node1Inleft = _Find2(pRoot->_pleft, pNode1->_value);
		if (!Node1Inleft){
			Node1Inright = _Find2(pRoot->_pright, pNode1->_value);
		}
		Node2Inleft = _Find2(pRoot->_pleft, pNode2->_value);
		if (!Node2Inleft){
			Node2Inright = _Find2(pRoot->_pright, pNode2->_value);
		}
		if (Node1Inright && Node2Inleft || Node1Inleft && Node2Inright){
			return pRoot;
		}
		else if (Node1Inleft && Node2Inleft){
			return _GetLastCommonAncestor(pRoot->_pleft, pNode1, pNode2);
		}
		else if (Node1Inright && Node2Inright){
			return _GetLastCommonAncestor(pRoot->_pright, pNode1, pNode2);
		}
		else{
			assert(false);
		}

	}
	Node* GetLastCommonAncestor(Node* pNode1, Node* pNode2)
	{
		assert(pNode1 && pNode2);
		if (_pRoot == NULL)
			return NULL;
		return _GetLastCommonAncestor(_pRoot, pNode1, pNode2);
	}

	//求二叉树两个结点的最低公共父节点（有辅助内存）
	bool Find3(Node* pNode, stack<Node*>& path)
	{
		return _Find3(_pRoot, pNode, path);
	}
	bool _Find3(Node* pRoot, Node* pNode, stack<Node*>& path)
	{
		if (pRoot == NULL) return false;
		path.push(pRoot);

		if (pRoot == pNode) return true;
		if (true == _Find3(pRoot->_pleft, pNode, path))
			return true;
		if (true == _Find3(pRoot->_pright, pNode, path))
			return true;
		path.pop();//走到这里说明在一条从根到叶子的路径中没有找到要找的节点 出栈去上一层找
		return false;
	}

	Node* GetLastCommonAncestor2(Node* pNode1, Node* pNode2)
	{
		assert(pNode1 && pNode2);
		stack<Node*> path1;
		stack<Node*> path2;
		Find3(pNode1, path1);
		Find3(pNode2, path2);
		while (path1.size() != path2.size()){
			if (path1.size() > path2.size()){
				path1.pop();
			}
			else
				path2.pop();
		}
		while (!path1.empty() && !path2.empty() && path1.top() != path2.top())
		{
			path1.pop();
			path2.pop();
		}
		if (path1.top() == path2.top()) return path1.top();
		return NULL;
	}
	//求二叉树的两个节点之间的最远距离
	//O(n) 方
	size_t GetMaxLength()
	{
		size_t maxlength = 0;
		//_GetMaxLength(_pRoot, maxlength);
		_GetMaxLength2(_pRoot, maxlength);
		return maxlength;
	}
	void _GetMaxLength(Node* pRoot, size_t& maxlength)
	{
		if (pRoot == NULL)
			return;
		size_t leftDepth = _TreeHeight(pRoot->_pleft);
		size_t rightDepth = _TreeHeight(pRoot->_pright);
		if (leftDepth + rightDepth > maxlength)
			maxlength = leftDepth + rightDepth;

		_GetMaxLength(pRoot->_pleft, maxlength);
		_GetMaxLength(pRoot->_pright, maxlength);
	}
	//O(n)
	size_t _GetMaxLength2(Node* pRoot, size_t& maxlength)
	{
		if (pRoot == NULL)
			return 0;
		size_t leftLength = _GetMaxLength2(pRoot->_pleft, maxlength);
		size_t rightLength = _GetMaxLength2(pRoot->_pright, maxlength);

		if (leftLength + rightLength > maxlength)
			maxlength = leftLength + rightLength;
		return leftLength > rightLength ? leftLength + 1 : rightLength + 1;
	}
	//判断一棵树是不是另外一棵树的子树



private:
	Node* _pRoot;
};

////重建二叉树
//输入某二叉树的前序 中序 遍历结果重建出该二叉树
//设前序遍历序列{1，2，4，7，3，5，6，8} 中序遍历序列{4，7，2，1，5，3，8，6}

struct TreeNode
{
	char _value;
	TreeNode* _pleft;
	TreeNode* _pright;

	TreeNode(char value)
		:_value(value)
		, _pleft(NULL)
		, _pright(NULL)
	{}
};

//这里一定要传引用 否则退回这一层后preindex还是之前的值
TreeNode* _ReBulidBinaryTree(int& preindex, int inBegin, int inEnd, const vector<char>& preOrder \
	, const vector<char>& inOrder)
{
	if (inBegin > inEnd)
		return NULL;
	TreeNode* root = new TreeNode(preOrder[preindex]);//创建一个树的节点
	int rootindex = inBegin;
	while (rootindex <= inEnd){
		if (root->_value == inOrder[rootindex])
			break;
		++rootindex;
	}//程序走到这里 找到中序遍历序列中的根节点的值的位置 该位置左边的数是左子树节点 右边的值是右字数节点 
	assert(rootindex <= inEnd);

	if (inBegin <= rootindex - 1)//构建左子树 连到根的左指针上去
		root->_pleft = _ReBulidBinaryTree(++preindex, inBegin, rootindex - 1, preOrder, inOrder);
	else                                  //每一个preindex都可以看成一棵子树的根
		root->_pleft = NULL;
	if (rootindex + 1 <= inEnd)//构建右子树  连到根的右指针上去
		root->_pright = _ReBulidBinaryTree(++preindex, rootindex + 1, inEnd, preOrder, inOrder);
	else
		root->_pright = NULL;
	return root;
}

TreeNode* ReBulidBinaryTree(const vector<char>& preOrder, const vector<char>& inOrder)
{
	if (preOrder.size() != inOrder.size())
		return NULL;
	int preindex = 0;
	int inBegin = 0;
	int inEnd = inOrder.size() - 1;
	return _ReBulidBinaryTree(preindex, inBegin, inEnd, preOrder, inOrder);
}

//把二叉搜索树转化成双向链表
void _TreeToList(TreeNode* cur, TreeNode*& prev)
{
	if (cur == NULL)
		return;
	_TreeToList(cur->_pleft, prev);
	cur->_pleft = prev;
	if (prev)
		prev->_pright = cur;
	prev = cur;
	_TreeToList(cur->_pright, prev);
}

TreeNode* TreeToList(TreeNode* root)
{
	if (root == NULL)
		return NULL;
	TreeNode* prev = NULL;
	_TreeToList(root, prev);
	TreeNode* head = root;
	while (head && head->_pleft){
		head = head->_pleft;
	}
	return head;
}

void Test()
{
	vector<char> prev;
	vector<char> in;

	prev.push_back('1');
	prev.push_back('2');
	prev.push_back('3');
	prev.push_back('4');
	prev.push_back('5');
	prev.push_back('6');
	in.push_back('2');
	in.push_back('3');
	in.push_back('4');
	in.push_back('1');
	in.push_back('6');
	in.push_back('5');
	TreeNode* root = ReBulidBinaryTree(prev, in);
}

int main()
{
	char arr[] = { '1', '2', '3', '#', '#', '4', '#', '#', '5', '6' };

	BinaryTree<char> BiTree(arr, sizeof(arr) / sizeof(arr[0]), '#');

	//BiTree.Post_Order();
	BiTree.Pre_Order();
	cout << BiTree.GetLastCommonAncestor(BiTree.Find1('5'), BiTree.Find1('3'))->_value << endl;;
	cout << BiTree.GetLastCommonAncestor2(BiTree.Find1('4'), BiTree.Find1('3'))->_value << endl;;
	cout << BiTree.GetMaxLength() << endl;
	Test();
	//BiTree.Mid_Order();
	//BiTree.level_Order();
	//if (BiTree.IsTotalTree())
	//	cout << "shi" << " ";
	//else
	//	cout << "no" << " ";
	//BiTree.Mirror();
	//BiTree.PreOrder();
	//cout << BiTree.Size() << endl;
	//cout << BiTree.TreeHeight() << endl;
	//cout << BiTree.k_nodes(3) << endl;
	//int Prearr[] = { 1, 2, 3 };//前序遍历结果
	//int Inarr[] = { 2,1,3 };//中序遍历结果
	//BinaryTree<int> tree;
	//tree.ReConstruct(Prearr, Inarr,sizeof(Prearr));
	//tree.Pre_Order();
	//tree.Mid_Order();

	system("pause");
	return 0;
}

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
	//变量invalid代表该节点为空                           //数组的索引必须传引用 
	Node*  _CreateBinaryTree2(const T arr[], size_t size, size_t& index, const T invalid)
	{
		Node* pRoot = NULL;
		if (index < size && invalid != arr[index])
		{
			pRoot = new Node(arr[index]);
			pRoot->_pleft = _CreateBinaryTree2(arr, size, ++index, invalid);
			pRoot->_pright = _CreateBinaryTree2(arr, size, ++index, invalid);
			//在这里接住下一层的返回值
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
			Node* cur = q.front();
			q.pop();
			if (cur->_pleft != NULL)
				q.push(cur->_pleft);
			if (cur->_pright != NULL)
				q.push(cur->_pright);
			cout << cur->_value << " ";
		}
		cout << endl;
	}
	
	//判断一棵二叉树是否是完全二叉树
	bool IsTotalTree()
	{
		queue<Node*> q;
		if (_pRoot == NULL)
			return false;
		bool flag = true;
		q.push(_pRoot);
		while (!q.empty()){
			Node* cur = q.front();
			q.pop();
			if (cur->_pleft != NULL){
				q.push(cur->_pleft);
				if (flag == false)
					return false;
			}
			else{
				flag = false;
			}
			if (cur->_pright != NULL){
				q.push(cur->_pleft);
				if (flag == false)
					return false;
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
		return _TreeHeight2(_pRoot);
	}
	size_t _TreeHeight(Node*& pRoot)
	{
		if (nullptr == pRoot)
			return 0;
		/*if (NULL == pRoot->_pleft && NULL == pRoot->_pright)
		return 1;*/
		size_t LeftHeight = _TreeHeight(pRoot->_pleft);
		size_t RightHeight = _TreeHeight(pRoot->_pright);

		return (LeftHeight > RightHeight) ? LeftHeight + 1 : RightHeight + 1;
	}
	//二叉树高度，非递归

	size_t _TreeHeight2(Node*& pRoot)
	{
		if (nullptr == pRoot)
			return 0;
		queue<Node*> q;
		q.push(pRoot);
		size_t height = 0;
		while (!q.empty()){
			++height;
			int curlevelcount = q.size();
			int cnt = 0;
			while (cnt < curlevelcount){
				Node* pCur = q.front();
				++cnt;
				q.pop();
				if (pCur->_pleft != nullptr){
					q.push(pCur->_pleft);
				}
				if (pCur->_pright != nullptr){
					q.push(pCur->_pright);
				}
			}
		}
		return height;
	}
	//二叉树左视图
	
	void TreeLeftView()
	{
		_TreeLeftView(_pRoot);
	}
	
	void _TreeLeftView(Node*& pRoot)
	{
		if (pRoot == nullptr)
			return;
		queue<Node*> q;
		q.push(pRoot);
		while(!q.empty())
		{
			int curlevelcount = q.size();
			int cnt = 0;
			while (cnt < curlevelcount)
			{
				Node* pCur = q.front();
				q.pop();
				++cnt;
				if (1 == cnt)
				{
					cout << pCur->_value << " ";
				}
				if (pCur->_pleft != nullptr)
				{
					q.push(pCur->_pleft);
				}
				if (pCur->_pright != nullptr)
				{
					q.push(pCur->_pright);
				}
			}
		}
	}
	//二叉树按层打印
	void PrintLevel()
	{
		if (_pRoot == NULL)
			return;
		queue<Node*> q;
		q.push(_pRoot);
		int tobeprint = 1;
		int nextlevel = 0;
		while (!q.empty()){
			Node* pCur = q.front();
			cout << pCur->_value << " ";
			tobeprint--;
			if (pCur->_pleft != NULL){
				q.push(pCur->_pleft);
				nextlevel++;
			}
			if (pCur->_pright != NULL){
				q.push(pCur->_pright);
				nextlevel++;
			}
			q.pop();
			if (tobeprint == 0){
				cout << endl;
				tobeprint = nextlevel;
				nextlevel = 0;
			}
		}
	}
	//之字形打印二叉树
	void Zhi_print()
	{
		if (_pRoot == NULL)
			return;
		stack<Node*> s[2];
		int cur = 0;
		int next = 1;
		s[cur].push(_pRoot);
		while (!s[0].empty() || !s[1].empty()){
			Node* pCur = s[cur].top();
			s[cur].pop();
			cout << pCur->_value << " ";
			if (cur == 0){
				if (pCur->_pleft != NULL)
					s[next].push(pCur->_pleft);
				if (pCur->_pright != NULL)
					s[next].push(pCur->_pright);
			}
			else{
				if (pCur->_pright != NULL)
					s[next].push(pCur->_pright);
				if (pCur->_pleft != NULL)
					s[next].push(pCur->_pleft);
			}
			if (s[cur].empty()){
				cout << endl;
				cur = 1 - cur;
				next = 1 - next;
			}
		}
		cout << endl;
	}
	
	//非递归遍历二叉树
	//把问题分成 树的左路 与 树的其他部分 两块
	//先将节点压栈 遍历后再出栈 以此模仿递归
	void Pre_Order()
	{
		stack<Node*> s;
		Node* cur = _pRoot;
		if (_pRoot == NULL)
			return;

		while (cur || !s.empty()){//栈不空说明还有节点未遍历
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
		while (cur || !s.empty()){//如果 cur为真 !s.empty() 为假 是为了程序第一次进入循环
									//如果 cur为假 !s.empty()为真程序退回到遍历它的父节点
			while (cur){//找最左边的节点
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

	void Post_Order()
	{
		if (NULL == _pRoot)
			return;
		Node* pCur = _pRoot;
		Node* pRev = NULL;
		stack<Node*> s;
		s.push(pCur);
		while (pCur || !s.empty()){
			while (pCur != NULL){
				s.push(pCur);
				pCur = pCur->_pleft;
			}
			Node* pTop = s.top();
			if (pTop->_pright == NULL || pTop->_pright == pRev){
				cout << pTop->_value << " ";
				s.pop();
				pRev = pTop;
			}
			else{
				pCur = pTop->_pright;
			}
		}
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
		return NULL;
	}

	bool Find2(Node* pRoot, Node* pNode)
	{
		Node* cur = pRoot;
		if (cur == NULL)
			return NULL;
		if (cur == pNode)
			return true;
		if (Find2(cur->_pleft, pNode))
			return true;
		return Find2(cur->_pright, pNode);
	}

	Node* _GetLastCommonAncestor(Node* pRoot, Node* pNode1, Node* pNode2)
	{
		if (pRoot == NULL)
			return NULL;
		if (pNode1 == pRoot && pNode2 == pRoot)
			return pRoot;
		bool Node1InLeft = false, Node2InLeft = false, Node1InRight = false, Node2InRight = false;
		Node1InLeft = Find2(pRoot->_pleft, pNode1);
		if (!Node1InLeft)
			Node1InRight = Find2(pRoot->_pright, pNode1);
		Node2InLeft = Find2(pRoot->_pleft, pNode2);
		if (!Node2InLeft)
			Node2InRight = Find2(pRoot->_pright, pNode2);
		if ((Node1InLeft && Node2InRight) || (Node2InLeft && Node1InRight))
			return pRoot;
		else if (Node1InLeft && Node2InLeft)
			_GetLastCommonAncestor(_pRoot->_pleft, pNode1, pNode2);
		else if (Node2InLeft && Node2InRight)
			_GetLastCommonAncestor(_pRoot->_pright, pNode1, pNode2);
		else{
			assert(false);
		}
		return NULL;
	}

	Node* GetLastCommonAncestor(Node* pNode1, Node* pNode2)
	{
		assert(pNode1 && pNode2);
		if (_pRoot == NULL)
			return NULL;
		return _GetLastCommonAncestor(_pRoot, pNode1, pNode2);
	}

	//求二叉树两个结点的最低公共父节点（有辅助内存）
	bool Find3(Node* pNode, stack<Node*>& s)
	{
		if (_pRoot == NULL)
			return false;
		return _Find3(_pRoot, pNode, s);
	}

	bool _Find3(Node* pRoot, Node* pNode, stack<Node*>& s)
	{
		if (pRoot == NULL)
			return false;
		s.push(pRoot);
		if (pRoot == pNode)
			return true;
		if (true == _Find3(pRoot->_pleft, pNode, s))
			return true;
		if (true == _Find3(pRoot->_pright, pNode, s))
			return true;
		s.pop();//走到这里说明在一条从根到叶子的路径中没有找到要找的节点 出栈去上一层找
		return false;
	}

	Node* GetLastCommonAncestor2(Node* pNode1, Node* pNode2)
	{
		//assert(pNode1 && pNode2);
		if (_pRoot == NULL)
			return NULL;
		Node* pRoot = _pRoot;
		stack<Node*> s1;
		stack<Node*> s2;
		Find3(pNode1, s1);
		Find3(pNode2, s2);
		while (s1.size() != s2.size()){
			if (s1.size() < s2.size()){
				s2.pop();
			}
			else{
				s1.pop();
			}
		}
		while (!s1.empty() && !s2.empty() && s1.top() != s2.top()){
			s1.pop();
			s2.pop();
		}
		if (s1.top() == s2.top())
			return s1.top();
		else if (!s1.empty()){
			return pNode1;
		}
		else{
			return pNode2;
		}
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
		size_t leftLength  = _GetMaxLength2(pRoot->_pleft, maxlength);
		size_t rightLength = _GetMaxLength2(pRoot->_pright, maxlength);

		if (leftLength + rightLength > maxlength)
			maxlength = leftLength + rightLength;
		return leftLength > rightLength ? leftLength + 1 : rightLength + 1;
	}
	//判断一棵树是不是另外一棵树的子树
	

	//求二叉树两个结点的最远距离
	unsigned int MaxNodeLen()
	{
		unsigned int MaxLen = 0;
		
		_MaxNodeLen(_pRoot, MaxLen);
	}

	unsigned int _MaxNodeLen(Node* pRoot, unsigned int& Maxlen)
	{
		if (nullptr == pRoot)
			return 0;
		//if(pRoot->_pleft)
		unsigned int leftMaxLen = _MaxNodeLen(pRoot->_pleft, Maxlen);
		//if(pRoot->_pright)
		unsigned int rightMaxLen = _MaxNodeLen(pRoot->_pright, Maxlen);

		if (leftMaxLen + rightMaxLen > Maxlen)
			Maxlen = leftMaxLen + rightMaxLen;

		return leftMaxLen > rightMaxLen ? leftMaxLen + 1 : rightMaxLen + 1;
	}

	//二叉树的最大（小）层数
	int maxdefpth()
	{
		if (_pRoot == NULL)
			return 0;
		return _maxdepth(_pRoot);
	}

	int _maxdepth(Node* pRoot)
	{
		if (pRoot == NULL)
			return 0;
		if (pRoot->_pleft == NULL && pRoot->_pright == NULL)
			return 1;
		int leftdepth = _maxdepth(pRoot->_pleft);
		int rightdepth = _maxdepth(pRoot->_pright);
		
		return leftdepth > rightdepth ? leftdepth + 1 : rightdepth + 1;
	}

	//判断另一棵二叉树是不是这棵树的子树
	bool check_is_subtree(Node* pTestRoot)
	{
		if (pTestRoot == NULL)
			return true;
		return _check_is_subtree(_pRoot, pTestRoot);
	}
	
	bool _sub_check(Node* pRoot, Node* pTestRoot)
	{
		if (pRoot->_value != pTestRoot->_value)
			return false;
		if (pRoot == NULL && pTestRoot == NULL)
			return true;
		if (pRoot == NULL || pTestRoot == NULL)
			return false;
		return _sub_check(pRoot->_pleft, pTestRoot->_pleft) || \
			_sub_check(pRoot->_pright, pRoot->_pright);
	}

	bool _check_is_subtree(Node* pRoot, Node* pTestRoot)
	{
		if (pRoot == NULL)
			return false;
		if (pRoot->_value == pTestRoot->_pright)
			return _sub_check(pRoot, pTestRoot);

		return _check_is_subtree(pRoot->_pleft, pTestRoot) || \
			_check_is_subtree(pRoot->_pright, pTestRoot);
	}

	

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

TreeNode* _ReBuildBinaryTree2(int& postindex, int inBegin, int inEnd, \
	const vector<char>& postOrder, const vector<char>& inOrder)
{
	if (inBegin > inEnd)
		return NULL;
	TreeNode* root = new TreeNode(postOrder[postindex]);
	int rootindex = inBegin;
	while (rootindex <= inEnd){
		if (root->_value == inOrder[rootindex])
			break;
		rootindex++;
	}
	assert(rootindex <= inEnd);
	if (rootindex + 1 <= inEnd)
		 root->_pright = _ReBuildBinaryTree2(--postindex, rootindex + 1, inEnd, postOrder, inOrder);
	else
    	 root->_pright = NULL;
	if (inBegin <= rootindex - 1)
		root->_pleft = _ReBuildBinaryTree2(--postindex, inBegin , rootindex - 1, postOrder, inOrder);
	else
		root->_pleft = NULL;
	return root;
}

TreeNode* ReBulidBinaryTree2(const vector<char>& postOrder, const vector<char>& inOrder)
{
	if (postOrder.size() != inOrder.size())
		return NULL;
	int postindex = postOrder.size() - 1;
	int inBegin = 0;
	int inEnd = inOrder.size() - 1;
	return _ReBuildBinaryTree2(postindex, inBegin, inEnd, postOrder, inOrder);
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

//根据有序序列构建二叉树
TreeNode* build_bst(vector<int> _v )
{
	if (_v.size() == 0)
		return NULL;
	if (_v.size() == 1)
		return new TreeNode(_v[0]);
	int mid = _v.size() / 2;
	vector<int>::const_iterator frist = _v.begin();
	vector<int>::const_iterator last = _v.begin() + mid;

	vector<int> _v2(frist, last);
	TreeNode* node = new TreeNode(_v[mid]);
	
	node->_pleft = build_bst(_v2);

	if (mid == _v.size() - 1)
		node->_pright = NULL;
	else
	{
		frist = _v.begin() + mid + 1;
		last = _v.end();
		vector<int> _v2(frist, last);
		node->_pright = build_bst(_v2);
	}
	return node;
}

//二叉树的数值最大路径
int maxPathSum(TreeNode* root, int& maxSum)
{
	if (root == NULL)
		return 0;
	int leftsum = maxPathSum(root->_pleft, maxSum);
	int rightsum = maxPathSum(root->_pright, maxSum);

	int value = root->_value;
	int retsum = leftsum > rightsum ? max(leftsum + value, value) : \
		max(rightsum + value, value);
	maxSum = max(maxSum, max(value + leftsum + rightsum, retsum));
	return retsum;
}

bool has_path_sum(TreeNode* pRoot, int sum)
{
	if (pRoot == NULL)
		return false;
	if (pRoot->_pleft == NULL && pRoot->_pright == NULL && sum == pRoot->_value)
	{
		return true;
	}
	return has_path_sum(pRoot->_pleft, sum - pRoot->_value) || \
		has_path_sum(pRoot->_pright, sum - pRoot->_value);
}

void Test()
{
	vector<char> prev;
	vector<char> in;
	vector<char> post;
 	prev.push_back('1');
	prev.push_back('2');
	prev.push_back('3');
	prev.push_back('4');
	prev.push_back('5');
	prev.push_back('6');
	in.push_back('3');
	in.push_back('2');
	in.push_back('4');
	in.push_back('1');
	in.push_back('6');
	in.push_back('5');
	post.push_back('3');
	post.push_back('4');
	post.push_back('2');
	post.push_back('6');
	post.push_back('5');
	post.push_back('1');

	TreeNode* root1 = ReBulidBinaryTree(prev, in);
	TreeNode* root2 = ReBulidBinaryTree2(post, in);
	cout << "ha"<< has_path_sum(root2, 6) << endl;
}

int main()
{
	char arr[] = { '1', '2', '3', '#', '#', '4', '#', '#', '5', '6' };

	BinaryTree<char> BiTree(arr, sizeof(arr) / sizeof(arr[0]), '#');
	BiTree.Zhi_print();
	BiTree.PrintLevel();
	BiTree.Post_Order();
	BiTree.Pre_Order();
	//cout << BiTree.GetLastCommonAncestor(BiTree.Find1('4'), BiTree.Find1('3'))->_value << endl;;
	//cout << BiTree.GetLastCommonAncestor2(BiTree.Find1('2'), BiTree.Find1('3'))->_value << endl;;
	//cout << BiTree.GetMaxLength() << endl;
	Test();
	BiTree.Mid_Order();
	BiTree.level_Order();
	cout << BiTree.IsTotalTree()<<endl;
	//if (BiTree.IsTotalTree())
	//	cout << "shi" << " ";
	//else
	//	cout << "no" << " ";
	//BiTree.Mirror();
	//BiTree.PreOrder();
	//cout << BiTree.Size() << endl;
	cout << BiTree.TreeHeight() << endl;
	cout << BiTree.k_nodes(3) << endl;
	cout << BiTree.maxdefpth() << endl;
	//int Prearr[] = { 1, 2, 3 };//前序遍历结果
	//int Inarr[] = { 2,1,3 };//中序遍历结果
	//BinaryTree<int> tree;
	//tree.ReConstruct(Prearr, Inarr,sizeof(Prearr));
	//tree.Pre_Order();
	//tree.Mid_Order();
	system("pause");
	return 0;
}

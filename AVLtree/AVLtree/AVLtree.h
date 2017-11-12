#include<iostream>
#include<stdlib.h>

using namespace std;

template<class K,class V>
struct AVLnode
{
	K _key;
	V _value;
	int _bf;
	AVLnode<K, V>* _pLeft;
	AVLnode<K, V>* _pRight;
	AVLnode<K, V>* _pParent;

	AVLnode(const K& key, const V& value)
		:_key(key)
		, _value(value)
		, _pLeft(NULL)
		, _pRight(NULL)
		, _pParent(NULL)
		, _bf(0)
	{}
};

template<class K,class V>
class AVLtree
{
	typedef AVLnode<K, V> Node;
public:
	AVLtree()
		:_root(NULL)
	{}

	bool Insert(const K& key, const V& value)
	{
		if (_root == NULL){
			_root = new Node(key, value);
			return true;
		}
		Node* cur = _root;
		Node* pParent = NULL;
		while (cur){
			if (cur->_key > key){
				pParent = cur;
				cur = cur->_pLeft;
			}
			else if (cur->_key < key){
				pParent = cur;
				cur = cur->_pRight;
			}
			else{
				return false;
			}
		}
		cur = new Node(key, value);
		if (cur->_key > pParent->_key){
			pParent->_pRight = cur;
			cur->_pParent = pParent;
		}
		else{
			pParent->_pLeft = cur;
			cur->_pParent = pParent;
		}
		while (pParent)//��ʼ����ƽ������
		{//�����ȼ���pParent��ƽ������
			if (pParent->_pLeft == cur)
				pParent->_bf -= 1;
			else
				pParent->_bf += 1;

			if (pParent->_bf == -2){
				if (pParent->_pLeft->_bf == 1){
					RotateLR(pParent);
					return true;
				}
				else if (pParent->_pLeft->_bf == -1){
					RotateR(pParent);
					return true;
				}
			}
			else if (pParent->_bf == 2){
				if (pParent->_pRight->_bf == -1){
					RotateRL(pParent);
					return true;
				}
				else if (pParent->_pRight->_bf == 1){
					RotateL(pParent);
					return true;
				}
			}
			else if (pParent->_bf == -1 || pParent->_bf == 1){
				cur = pParent;
				pParent = pParent->_pParent;
			}
			else{
				break;
			}
				
		}
		return true;
	}

	bool IsBalance()
	{
		int deepth = 0;
		return _IsBalance(_root,deepth);
		//return _IsBalance(_root);
	}

	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

	void _InOrder(Node* root)
	{
		if (NULL == root)
			return;
		_InOrder(root->_pLeft);
		cout << root->_key << ":" << root->_value << " ";
		_InOrder(root->_pRight);
	}

protected:
	bool _IsBalance(Node* root)//ʱ�临�Ӷ�Ϊ n^2;  �Ӹ���Ҷ�Ӽ��
	{
		if (root == NULL)
			return true;

		int LeftHeight = Height(root->_pLeft);
		int RightHeight = Height(root->_pRight);
		int HeightGap = LeftHeight - RightHeight;
		if (abs(HeightGap) > 1 || HeightGap != root->_bf)
		{
			cout << root->_bf << "ƽ�����ӳ�����" << endl;
			return false;
		}
		return abs(HeightGap) < 2 && _IsBalance(root->_pLeft) && _IsBalance(root->_pRight);
	}

	bool _IsBalance(Node* root, int& deepth)//ʱ�临�Ӷ�O��n�� ��Ҷ��������
	{							//ע�����ﴫ����int&
		if (root == NULL){
			deepth = 0;//���deepth����һ�㴫������Leftdeepth �� Rightdeepth
			return true;
		}
		int Leftdeepth = 0;//ÿһ��ݹ鶨�����������������һ��root��������ȡ�
		if (!_IsBalance(root->_pLeft, Leftdeepth))
			return false;

		int Rightdeepth = 0;
		if (!_IsBalance(root->_pRight, Rightdeepth))
			return false;

		if (root->_bf != Rightdeepth - Leftdeepth){
			cout << root->_key << " " << "ƽ����������" << root->_bf << endl;
			return false;
		}//���ƽ�������Ƿ���ȷ
		
		deepth = Rightdeepth > Leftdeepth ? Rightdeepth + 1 : Leftdeepth + 1; //���deepth����һ�㴫������Leftdeepth �� Rightdeepth
		return abs(Rightdeepth - Leftdeepth) < 2;
	}

	
	int Height(Node* _root)
	{
		if (_root == NULL)
		{
			return 0;
		}
		int Leftheight = Height(_root->_pLeft);
		int Rightheight = Height(_root->_pRight);

		return Leftheight > Rightheight ? Leftheight + 1 : Rightheight + 1;
	}

	void RotateLR(Node* pParent)
	{
		Node* pSubL = pParent->_pLeft;
		Node* pSubLR = pSubL->_pRight;
		int bf = pSubLR->_bf;
		RotateL(pSubL);
		RotateR(pParent);
		
		if (bf == 1){
			pSubL->_bf = -1;
			pParent->_bf = 0;
		}
		else if (bf == -1){
			pSubL->_bf = 0;
			pParent->_bf = 1;
		}
		else{
			pSubL->_bf = pParent->_bf = 0;
		}
		pSubLR->_bf = 0;
	}

	void RotateRL(Node* pParent)
	{
		Node* pSubR = pParent->_pRight;
		Node* pSubRL = pSubR->_pLeft;
		int bf = pSubRL->_bf;//ע������������ת֮ǰȡpSubRL��ƽ������
		RotateR(pSubR);
		RotateL(pParent);

		if (bf == 1){
			pParent->_bf = -1;
			pSubR->_bf = 0;
		}
		else if (bf == -1){
			pSubR->_bf = 1;
			pParent = 0;
		}
		else{
			pSubR->_bf = pParent->_bf = 0;
		}
		pSubRL->_bf = 0;
	}

	void RotateL(Node* pParent)
	{
		Node* pSubR = pParent->_pRight;
		Node* pSubRL = pSubR->_pLeft;

		pParent->_pRight = pSubRL;
		if (pSubRL)
			pSubRL->_pParent = pParent;

		Node* pGrandParent = pParent->_pParent;
		pSubR->_pLeft = pParent;
		pParent->_pParent = pSubR;

		if (pGrandParent == NULL){
			_root = pSubR;
			pSubR->_pParent = NULL;
		}
		else{
			if (pGrandParent->_pLeft == pParent){
				pGrandParent->_pLeft = pSubR;
				pSubR->_pParent = pGrandParent;
			}
			else{
				pGrandParent->_pRight = pSubR;
				pSubR->_pParent = pGrandParent;
			}
		}
		pSubR->_bf = pParent->_bf = 0;
	}

	void RotateR(Node* pParent)
	{
		Node* pSubL = pParent->_pLeft;
		Node* pSubLR = pSubL->_pRight;
		
		pParent->_pLeft = pSubLR;
		if (pSubLR)
			pSubLR->_pParent = pParent;

		Node* pGrandParent = pParent->_pParent;
		pSubL->_pRight = pParent;
		pParent->_pParent = pSubL;

		if (pGrandParent == NULL){
			_root = pSubL;
			pSubL->_pParent = NULL;
		}
		else{
			if (pGrandParent->_pLeft == pParent){
				pGrandParent->_pLeft = pSubL;
				pSubL->_pParent = pGrandParent;
			}
			else{
				pGrandParent->_pRight = pSubL;
				pSubL->_pParent = pGrandParent;
			}
		}
		pSubL->_bf = pParent->_bf = 0;
	}
private:
	Node* _root;
};
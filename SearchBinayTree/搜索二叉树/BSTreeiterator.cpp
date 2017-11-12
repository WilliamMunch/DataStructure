//#pragma once
//#include"BSTree.cpp"
//
//using namespace std;
//
//template<class K, class V, class Ref, class Ptr>
//class BSTreeIterator
//{
//	typedef BSTNode<K, V> Node;
//	typedef BSTTreeIterator<K, V, Ref, Ptr> Self;
//
//protected:
//	Node* _pNode;
//public:
//	BSTreeIterator()
//		:_pNode(NULL);
//	{}
//
//	BSTreeIterator(Node* pNode)
//		:_pNode(pNode)
//	{};
//	
//	BSTreeIterator(const Self& s)
//		: _pRoot(s._pNode);
//	{}
//
//	Ref operator * ()
//	{
//		return _pNode->key;
//	}
//		
//	Ptr operator & ()
//	{
//		return &(operator*());
//	}
//};


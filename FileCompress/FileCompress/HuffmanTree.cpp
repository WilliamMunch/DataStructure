#include"Heap.cpp"

template<class W>
struct HuffmanTreeNode
{
	W _w;
	HuffmanTreeNode<W>* _left;
	HuffmanTreeNode<W>* _right;
	HuffmanTreeNode<W>* _parent;
	HuffmanTreeNode(const W& w)
		:_w(w)
		, _left(NULL)
	    , _right(NULL)
		, _parent(NULL)
	{}
};



template<class	W>
class HuffmanTree
{
	typedef HuffmanTreeNode<W> Node;
public:
	HuffmanTree()
	{}

	HuffmanTree(W* arr, size_t n, const W& invalid)
	{
	
		struct NodeCompare{
			bool operator () (const Node* l, const Node* r)
			{
				return l->_w < r->_w;
			}
		};
		Heap<Node*,NodeCompare> minhp;
		for (size_t i = 0; i < n; ++i){
			if (arr[i] != invalid){
				minhp.Push(new Node(arr[i]));
			}
		}
		
		while (minhp.Size() > 1){
			Node* left = minhp.Top();
			minhp.Pop();
			Node* right = minhp.Top();
			minhp.Pop();
			Node* parent = new Node(left->_w + right->_w);
			left->_parent = parent;
			right->_parent = parent;
			parent->_left = left;
			parent->_right = right;
			minhp.Push(parent);
		}
		_root = minhp.Top();
	}

	Node*& GetRoot()
	{
		return _root;
	}

private:
	Node* _root;
};

//void TestHuffman()
//{
//	int arr[] = { 2, 4, 1, 3, 5, 6, 7, 3, -1 };
//	HuffmanTree<int>(arr, sizeof(arr) / sizeof(int), -1);
//}

//int main()
//{
//	TestHuffman();
//	system("pause");
//	return 0;
//}


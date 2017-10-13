#include"HuffmanTree.cpp"
#include<algorithm>
#pragma warning(disable:4996)

struct CharInfo{
	int _count = 0;
	string code = "";
	char ch;
		
	bool operator != (const CharInfo& s)
	{
		return _count != s._count;
	}

	bool operator <(const CharInfo& s)
	{
		return _count < s._count;
	}
		
	CharInfo operator + (const CharInfo& s)
	{
		CharInfo tmp;
		tmp._count = _count + s._count;
		return tmp;
	}
};

class FileCompress
{
	typedef HuffmanTreeNode<CharInfo> Node;
public:
	void Compression(char* file)
	{
		FILE* fout = fopen(file, "r");
		char ch = fgetc(fout);//从文件file中读取一个字符
		while (ch != EOF){
			_info[(unsigned char)ch]._count++;
			_info[(unsigned char)ch].ch = ch;
			ch = fgetc(fout);
		}//统计原文件中每个字符的个数 统计结束后文件指针指向文件结尾

		CharInfo invalid;
		invalid._count = 0;
		HuffmanTree<CharInfo> tree(_info, 256, invalid);
		
		_GetHuffmanCode(tree.GetRoot());
		
		fseek(fout, 0, SEEK_SET);//将fout指针位置重定义到原文件头部
		ch = fgetc(fout);
		char value = 0;
		int pos = 0;
		string compressFile = file;
		compressFile += "huffman.txt";//构建压缩文件名
		FILE* fin = fopen(compressFile.c_str(), "w");
		while (ch != EOF)
		{
			string& code = _info[(unsigned char)ch].code;
			for (size_t i = 0; i < code.size(); i++){
				if (code[i] == '0')
					value &= ~(1 << pos);
				else if(code[i] == '1')
					value |= (1 << pos);
				else
					assert(false);
				++pos;

				if (8 == pos){
					fputc(value, fin);
					value = 0;
					pos = 0;
				}
			}
			ch = fgetc(fout);
		}
		if (pos != 0){//处理原文件末尾转换的哈夫曼编码凑不够一个字符八位的情况
					  //（后几位以本来的零连同整个字符写入压缩文件）
			fputc(value, fin);
		}
		fclose(fin);
		fclose(fout);
										
	}

	void Uncompression(char* file)
	{
		//构建解压后还原文件名
		FILE* fout = fopen(file, "r");
		string uncompressFile = file;
		size_t pos = uncompressFile.rfind('h');
		uncompressFile.erase(pos, uncompressFile.size() - pos);
		uncompressFile += "unhuffman.txt";
		FILE* fin = fopen(uncompressFile.c_str(), "w");
		//重建Huffman树
		CharInfo invalid;
		invalid._count = 0;
		HuffmanTree<CharInfo> tree(_info, 256, invalid);
		//解压缩
		Node* cur = tree.GetRoot();
		char value;
		long long count = tree.GetRoot()->_w._count;
		value = fgetc(fout);
		while (value != EOF)
		{
			for (size_t pos = 0; pos <= 7; ++pos)
			{
				if (value & (1 << pos))
					cur = cur->_right;
				else
					cur = cur->_left;
				if (NULL == cur->_left && NULL == cur->_right){
					fputc(cur->_w.ch, fin);
					if (--count == 0){
						break;
					}
					cur = tree.GetRoot();
				}
			}
			value = fgetc(fout);
		}
		fclose(fin);
		fclose(fout);
	}
		
protected:
	CharInfo _info[256];
	//三岔链获取哈夫曼编码
	void _GetHuffmanCode(Node* root)
	{
		if (NULL == root)
		{
			return;
		}

		if (NULL == root->_left && NULL == root->_right)
		{
			Node* cur = root;
			Node* parent = cur->_parent;
			string& code = _info[(unsigned char)root->_w.ch].code;//巧用引用增加代码可读性和效率
			while (parent)
			{
				if (cur == parent->_left)
					code.push_back('0');
				else
					code.push_back('1');

				cur = parent;
				parent = cur->_parent;
			}
			reverse(code.begin(), code.end());
			return;
		}
		_GetHuffmanCode(root->_left);
		_GetHuffmanCode(root->_right);
		
	}

	//二岔链获取哈夫曼编码
	void _GetHuffmanCode(Node* root, string& code)
	{
		if (NULL == root)
			return;

		if (NULL == root->_left && NULL == root->_right){
			_info[(unsigned char)root->_w.ch].code = code;
			return;
		}

		_GetHuffmanCode(root->_left, code + '0');
		_GetHuffmanCode(root->_right, code + '1');
	}
};

int main()
{
	FileCompress a;
	a.Compression("file.txt");
	a.Uncompression("file.txthuffman.txt");
	system("pause");
	return 0;
}
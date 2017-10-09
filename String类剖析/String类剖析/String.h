#pragma once

#include<iostream>
#include<assert.h>
using namespace std;
//数据结构----自我管理的字符串

//1 普通String类 传统写法 老老实实开空间拷数据
namespace Tra
{
	class String
	{
	public:
		String(char* str = "")
			:_str(new char[strlen(str) + 1])
		{
			strcpy(_str, str);
		}

		String()
			:_str(new char[1])
		{
			*_str = '\0';
		}

		String(const String& s)
		{
			_str = new char[strlen(s._str) + 1];
			strcpy(_str, s._str);
		}

		/*String& operator = (const String& s)
		{
			if (this != &s){
				delete[] _str;
				_str = new char[strlen(s._str) + 1];
				strcpy(_str, s._str);
			}
		}*/

		String& operator=(const String& s)
		{
			if (this != &s)
			{
				char* tmp = new char[strlen(s._str) + 1];
				strcpy(tmp, s._str);
				delete[] _str;
				_str = tmp;
			}
			return *this;//为了支持链式访问
		}

		~String()
		{
			if (_str){
				delete[] _str;
				_str = NULL;
			}
		}

		char* GetStr()
		{
			return _str;
		}

	private:
		char* _str;
	};

	void TestString()
	{
		String s1("hello world");
		String s2("change world");

		String s3(s1);
		cout << s1.GetStr() << endl;
		cout << s3.GetStr() << endl;

		s1 = s2;

		cout << s1.GetStr() << endl;
		cout << s2.GetStr() << endl;

		s1 = s1;
		cout << s1.GetStr() << endl;
		cout << s2.GetStr() << endl;
	}
}


//现代写法 别人替我拷 拷完了一换就好了
namespace Mor{
	class String
	{
	public:
		String(char* str = "")
			:_str(new char[strlen(str) + 1])
		{
			strcpy(_str, str);
		}

		String(const String& s)
			:_str(NULL)
		{
			String tmp(s._str);
			swap(_str, tmp._str);
		}

		String& operator = (const String& s)
		{
			if (this != &s){
				String tmp(s._str);
				swap(_str, tmp._str);
			}
			return *this;
		}

		~String()
		{
			if (_str){
				delete[] _str;
				_str = NULL;
			}
		}

		char* GetChar()
		{
			return _str;
		}

	private:
		char* _str;
	};
}

namespace COW1//写时拷贝 引用计数指针
{
	class String
	{
	public:
		String(const char* str = "")
			:_refCountPtr(new int(1))
		{//引用计数指针版本的String构造函数初始化标识字符串字符数的_size 
		 //字符串空间大小的_capacity
		 //字符串_str
		 //引用计数指针_refCountPtr指向的空间 并初始化为一（同一个字符串最初只有一个对象管理）
			_size = strlen(str);
			_capacity = _size;
			_str = new char[_capacity + 1];
			strcpy(_str, str);
		}

		String(const String& s)//引用计数方式的String类的拷贝构造函数
			:_refCountPtr(s._refCountPtr)
			,_size(s._size)
			,_capacity(s._capacity)
			,_str(s._str)
		{//每次做拷贝的时候只是让新对象的字符指针和引用计数指针指向原对象空间
			//并++两对象引用计数指针指向的共同引用计数 实际上内存中的字符串只有一份
			(*_refCountPtr)++;//这样做是为了节省空间  所谓“写时拷贝 不拷就赚”
		}

		String& operator = (const String& s)
		{
			if (_str != s._str){
				Ralese();

				_refCountPtr = s._refCountPtr;
				_str = s._str;
				(*_refCountPtr)++;
			}
			return *this;
		}

		void Ralese()
		{
			if (--(*_refCountPtr) == 0){
				cout << "delete[]" << _str << endl;
				delete[] _str;
				delete _refCountPtr;
			}
		}

		void PushBack(const char& ch)
		{
			//修改字符串的时候 才真正拷贝一份新的在使用角度上已经有的新字符串
			//在该字符串上做修改  
			CopyOnWrite();
			if (_size == _capacity){

			}
			_str[_size++] = ch;
			_str[_size] = '\0';
			
		}

		void CopyOnWrite()
		{
			if (*_refCountPtr > 1){//写时拷贝发生的条件 即同一个在内存中的字符串被多个对象
									//的字符指针所引用
				char* newSize = new char[_capacity];
				strcpy(newSize,_str);

				*(_refCountPtr)--;
				_str = newSize;
				_refCountPtr = new int(1);//本函数负责修改公共引用计数 拷贝原对象所有内容
			}
		}

		char& operator[](size_t pos)
		{
			CopyOnWrite(); //非const类型的operator[]函数因为要修改_str[X]中的内容
			return _str[pos];//必须为要修改的对象的字符串重新开辟空间 否则在应用层面上将形成
							//改变了多个字符串的现象 因为在底层他们各自的char*指向同一字符串
		}

		char& operator[] (size_t pos)const
		{
			return _str[pos];
		}

		~String()
		{
			Ralese();
		}

		const char* c_str()
		{
			return _str;
		}
	private:
		char* _str;
		int* _refCountPtr;
		size_t _size;
		size_t _capacity;
	};

	// "有时候读的时候也要拷贝"
	void TestString1()
	{
		/*String s1("hello world");
		String s2(s1);
		s1 = s2;

		String s3("dadadada");
		s3 = s1;

		String s4("dadadsqwqdq");
		s1 = s4;*/

		String s1("hello world");
		String s2(s1);
		cout << s1[0] << endl;
		cout << s1.c_str() << endl;
		cout << s2.c_str() << endl;
	}
}

namespace COW2//写时拷贝 在对象空间前4个字节存放引用计数
{
	class String//在构造时初始化引用计数 涉及到拷贝时修改引用计数
	{
	public:
		String(const char* str = "")
			:_size(strlen(str))
			, _capacity(_size)
		{
			_str = new char[_capacity + 5];
			strcpy(_str + 4, str);
			_str += 4;
			GetCountRef()++;
		}

		int& GetCountRef()
		{
			return *((int*)(_str - 4));
		}

		String(const String& s)
			:_size(s._size)
			,_capacity(s._capacity)
			,_str(s._str)
		{
			GetCountRef()++;
		}

		String& operator = (const String& s)
		{
			if (_str != s._str){
				Ralese();
				_size = s._size;
				_capacity = s._capacity;
				_str = s._str;
				GetCountRef()++;
			}
		}

		void Ralese()
		{
			if (--GetCountRef() == 0){
				delete[] (_str - 4);
			}
		}

		void CopyOnwrite()
		{
			if (GetCountRef() > 1){
				char* newSize = new char[_capacity + 5];
				strcpy(newSize + 4, _str);

				GetCountRef()--;
				_str = newSize + 4;
				*((int*)(_str - 4)) = 1;
			}
		}

		char& operator[](size_t pos)
		{
			CopyOnwrite();
			return _str[pos];
		}

		char operator[](size_t pos)const
		{
			return _str[pos];
		}

		~String()
		{
			Ralese();
		}

		const char* c_str()
		{
			return _str;
		}
	private:
		char* _str;
		size_t _size;
		size_t _capacity;
	};
}

namespace DC//实现String类的增删查改
{
	class String
	{
	public:
		String(const char* str = "")
		{
			_size = strlen(str);
			_capacity = _size;
			_str = new char(_capacity + 1);
			strcpy(_str,str);
		}

		String(const String& s)
		{
			String tmp(s._str);//拷贝构造时先创造一个临时对象 让临时对象和当前
			Swap(tmp);         //对象内容交换 再因为临时对象出函数作用域要被释放 所以释放对象
							   //留下拷贝后的对象。
		}

		void Swap(String& tmp)
		{
			swap(_str, tmp._str);
			swap(_size, tmp._size);
			swap(_capacity, tmp._capacity);
		}

		String& operator = (String& s)
		{
			Swap(s);
			return *this;
		}

		size_t Size()
		{
			return _size;
		}

		size_t Capacity()
		{
			return _capacity;
		}

		char* c_str()
		{
			return _str;
		}

		void PushBack(char ch)
		{
			if (_size == _capacity){
				Expand(_capacity * 2);
			}

			_str[_size++] = ch;
			_str[_size] = '\0';
		}

		void PushBack(const char* str)
		{
			size_t len = strlen(str);
			if (_size + len > _capacity){
				Expand(_size + len);
			}

			strcpy(_str + len, str);
		}

		void Popback()
		{
			assert(_size);
			--_size;
		}

		void Insert(char ch, int pos)
		{
			if (_size > _capacity){
				Expand(_capacity * 2);
			}

			int end = _size;
			while (end >= pos){
				_str[end+ 1] = _str[end];
				--end;
			}
			_str[pos] = ch;
			++_size;
		}
		//插入方法同顺序表
		void Insert(const char* str, int pos)
		{
			if (_size + strlen(str) > _capacity){
				Expand(_size + strlen(str));
			}
			int end = _size;
			while (end >= (int)pos){
				_str[end + strlen(str)] = _str[end];
				--end;
			}
			while (*str){
				_str[pos++] = *str++;
			}
			_size += strlen(str);
		}

		void Erase(size_t pos, size_t count)
		{
			if (pos + count > _size - 1){
				_str[pos] = '\0';
				_size = pos;//pos 到 count超过整个字符串 删去pos之后字符 
			}
			else{
				strcpy(_str + pos, _str + pos + count);//将 pos 至 count 段的字符覆盖掉
				_size -= count;
			}
		}

		void Expand(size_t n)
		{
			if (n > _capacity){
				_str = (char*)realloc(_str, n + 1);
				assert(_str);
				_capacity = n;
			}
		}

		int Find(const char ch)
		{
			for (size_t i = 0; i < _size; ++i){
				if (_str[i] == ch){
					return i;
				}
				else{
					return -1;
				}
			}
		}

		int Find(const char* str)const
		{
			assert(str);
			const char* srcStr = _str;
			const char* subStr = str;
			size_t srcIndex = 0;
			size_t subIndex = 0;
			size_t sublen = strlen(str);

			while (srcIndex < _size - sublen -  1){
				size_t matchIndex = srcIndex;//这里是在一个疑似的第一个字符索引
				while (_str[matchIndex] == str[subIndex]){//该循环在疑似字串中一个个比对
					matchIndex++;                         //字符直到比到要找的字串结尾2
					subIndex++;
					if (subIndex == sublen){
						return srcIndex;
					}
				}
				subIndex = 0;//字串的索引重新置零 从下一个子串的头开始找
				srcIndex++;//找以下一个字符为首的字符串是不是字串str
			}
			return -1;
		}

		~String()
		{
			if (_str){
				delete[] _str;
				_str = NULL;
				_capacity = _size = 0;
			}
		}

		bool operator<(const String& s) const
		{
			size_t i = 0;
			for (; i < _size && i < s._size; ++i)
			{
				if (_str[i] < s._str[i])
				{
					return true;
				}
				else if (_str[i] > s._str[i])
				{
					return false;
				}
			}

			if (i == _size && i < s._size) //?
			{
				return true;
			}
			else
			{
				return false;
			}

		}

		inline bool operator<=(const String& s) const
		{
			return *this < s || *this == s;
		}
		inline bool operator>(const String& s) const
		{
			return !(*this <= s);
		}
		bool operator>=(const String& s) const;

		bool operator==(const String& s) const
		{
			size_t i = 0;
			for (; i < _size && i < s._size; ++i)
			{
				if (_str[i] != s._str[i])
				{
					return false;
				}
			}

			if (i == _size && i == s._size)
			{
				return true;
			}
			else
			{
				return false;
			}

		}
	private:
		char* _str;
		size_t _size;
		size_t _capacity;
	};
}
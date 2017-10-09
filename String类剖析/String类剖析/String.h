#pragma once

#include<iostream>
#include<assert.h>
using namespace std;
//���ݽṹ----���ҹ�����ַ���

//1 ��ͨString�� ��ͳд�� ����ʵʵ���ռ俽����
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
			return *this;//Ϊ��֧����ʽ����
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


//�ִ�д�� �������ҿ� ������һ���ͺ���
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

namespace COW1//дʱ���� ���ü���ָ��
{
	class String
	{
	public:
		String(const char* str = "")
			:_refCountPtr(new int(1))
		{//���ü���ָ��汾��String���캯����ʼ����ʶ�ַ����ַ�����_size 
		 //�ַ����ռ��С��_capacity
		 //�ַ���_str
		 //���ü���ָ��_refCountPtrָ��Ŀռ� ����ʼ��Ϊһ��ͬһ���ַ������ֻ��һ���������
			_size = strlen(str);
			_capacity = _size;
			_str = new char[_capacity + 1];
			strcpy(_str, str);
		}

		String(const String& s)//���ü�����ʽ��String��Ŀ������캯��
			:_refCountPtr(s._refCountPtr)
			,_size(s._size)
			,_capacity(s._capacity)
			,_str(s._str)
		{//ÿ����������ʱ��ֻ�����¶�����ַ�ָ������ü���ָ��ָ��ԭ����ռ�
			//��++���������ü���ָ��ָ��Ĺ�ͬ���ü��� ʵ�����ڴ��е��ַ���ֻ��һ��
			(*_refCountPtr)++;//��������Ϊ�˽�ʡ�ռ�  ��ν��дʱ���� ������׬��
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
			//�޸��ַ�����ʱ�� ����������һ���µ���ʹ�ýǶ����Ѿ��е����ַ���
			//�ڸ��ַ��������޸�  
			CopyOnWrite();
			if (_size == _capacity){

			}
			_str[_size++] = ch;
			_str[_size] = '\0';
			
		}

		void CopyOnWrite()
		{
			if (*_refCountPtr > 1){//дʱ�������������� ��ͬһ�����ڴ��е��ַ������������
									//���ַ�ָ��������
				char* newSize = new char[_capacity];
				strcpy(newSize,_str);

				*(_refCountPtr)--;
				_str = newSize;
				_refCountPtr = new int(1);//�����������޸Ĺ������ü��� ����ԭ������������
			}
		}

		char& operator[](size_t pos)
		{
			CopyOnWrite(); //��const���͵�operator[]������ΪҪ�޸�_str[X]�е�����
			return _str[pos];//����ΪҪ�޸ĵĶ�����ַ������¿��ٿռ� ������Ӧ�ò����Ͻ��γ�
							//�ı��˶���ַ��������� ��Ϊ�ڵײ����Ǹ��Ե�char*ָ��ͬһ�ַ���
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

	// "��ʱ�����ʱ��ҲҪ����"
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

namespace COW2//дʱ���� �ڶ���ռ�ǰ4���ֽڴ�����ü���
{
	class String//�ڹ���ʱ��ʼ�����ü��� �漰������ʱ�޸����ü���
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

namespace DC//ʵ��String�����ɾ���
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
			String tmp(s._str);//��������ʱ�ȴ���һ����ʱ���� ����ʱ����͵�ǰ
			Swap(tmp);         //�������ݽ��� ����Ϊ��ʱ���������������Ҫ���ͷ� �����ͷŶ���
							   //���¿�����Ķ���
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
		//���뷽��ͬ˳���
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
				_size = pos;//pos �� count���������ַ��� ɾȥpos֮���ַ� 
			}
			else{
				strcpy(_str + pos, _str + pos + count);//�� pos �� count �ε��ַ����ǵ�
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
				size_t matchIndex = srcIndex;//��������һ�����Ƶĵ�һ���ַ�����
				while (_str[matchIndex] == str[subIndex]){//��ѭ���������ִ���һ�����ȶ�
					matchIndex++;                         //�ַ�ֱ���ȵ�Ҫ�ҵ��ִ���β2
					subIndex++;
					if (subIndex == sublen){
						return srcIndex;
					}
				}
				subIndex = 0;//�ִ��������������� ����һ���Ӵ���ͷ��ʼ��
				srcIndex++;//������һ���ַ�Ϊ�׵��ַ����ǲ����ִ�str
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
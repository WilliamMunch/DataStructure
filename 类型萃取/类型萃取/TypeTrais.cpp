#include<iostream>
#include<stdlib.h>
#include<string>

using namespace std;
//
//template<class T>
//void Copy(T* dst, T* src,size_t size)
//{
//	memcpy(dst, src, sizeof(T)*size);
//}

struct _TrueType
{
	static bool Get()
	{
		return true;
	}
};

struct _FalseType
{
	static bool Get()
	{
		return false;
	}
};

template<class T>
struct TypeTraits
{
	typedef _FalseType _IsPod;
};

template<>
struct TypeTraits<int>
{
	typedef _TrueType _IsPod;
};

template<>
struct TypeTraits<char>
{
	typedef _TrueType _IsPod;
};

template<class T>
void Copy(T* dst, T* src, size_t size)
{
	if (TypeTraits<T>::_IsPod().Get())//构建一个临时对象
		memcpy(dst, src, sizeof(T)*size);
	else{
		for (size_t i = 0; i < size; ++i){
			dst[i] = src[i];
		}
	}
}

int main()
{
	
	string a[4] = { "111", "222", "333" };
	string b[4] = { "444", "555", "666" };
    int data = 9;
	int _data = 8;
	//Copy(a, b, 4);
	Copy<string> (a, b, sizeof(a) / sizeof(a[0]));
	Copy<int>(&data, &_data, 1);
	system("pause");
	return 0;
}
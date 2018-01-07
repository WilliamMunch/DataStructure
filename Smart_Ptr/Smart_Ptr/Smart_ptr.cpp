#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<stdlib.h>

using namespace std;

template<class T>
class AutoPtr
{
public:
	AutoPtr(T* ptr)
		:_ptr(ptr)
	{}

	AutoPtr(AutoPtr<T>& ap)
		:_ptr(ap._ptr)
	{
		ap._ptr = NULL;//控制权移交。
	}

	AutoPtr<T>& operator=(AutoPtr<T>& ap)
	{
		if (this != &ap){
			if (_ptr){
				delete _ptr;
			}
			_ptr = ap._ptr;
			ap._ptr = NULL;
		}
		return *this;
	}

	~AutoPtr()
	{
		if (_ptr){
			delete _ptr;
			_ptr = NULL;
		}
	}

	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return _ptr;
	}

protected:
	T* _ptr;
};

struct AA
{
	int _a;
	int _b;
};

void TestAutoPtr()
{
	AutoPtr<int> ap1(new int(10));
	cout << *ap1 << endl;
	AutoPtr<int> ap2(ap1);
	AutoPtr<int> ap3(new int(20));
	cout << *ap3 << endl;
	ap2 = ap3;
	
	cout << *ap2 << endl;
	cout << endl;
	AutoPtr<AA> ap(new AA);
	ap->_a = 10;
	ap->_b = 20;
	cout << ap->_a << endl;
	cout << ap->_b << endl;
	(*ap)._a = 30;
	cout << ap->_a << endl;

	AutoPtr<AA> ap4(new AA);
	ap4 = ap;
	cout << ap4->_a << endl;
}

template<class T>
class ScopedPtr
{
public:
	ScopedPtr(T* ptr)
		:_ptr(ptr)
	{}

	~ScopedPtr()
	{
		if (_ptr){
			delete _ptr;
			_ptr = NULL;
		}
	}

	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return _ptr;
	}
private:
	ScopedPtr<T>& operator=(const ScopedPtr<T>&);
	ScopedPtr(const ScopedPtr<T>&);
protected:
	T* _ptr;
};

void TestScopedPtr()
{
	ScopedPtr<int> sp(new int(10));
	//ScopedPtr<int> sp2(sp);
}

//定制删除器
template<class T>
struct __Del
{
	void operator()(T* ptr){
		delete ptr;
	}
};

struct Fclose
{
	void operator()(FILE* fp){
		fclose(fp);
	}
};

template<class T>
struct DelArray
{
	void operator()(T* ptr){
		delete[] ptr;
	}
};

//定制器版本shreadptr
template<class T, class Del = __Del<T>>
class SharedPtr
{
public:
	SharedPtr(T* ptr = NULL, Del del = __Del<T>())
		:_ptr(ptr)
		, _refcount(new int(1))
		, _del(del)
	{}

	SharedPtr(const SharedPtr<T, Del>& sh)
		:_ptr(sh._ptr)
		, _refcount(sh._refcount)
	{
		++(*_refcount);
	}

	//SharedPtr<T, Del>& operator=(const SharedPtr<T, Del>& shp)
	//{
	//	if (_ptr != shp._ptr){
	//		if (--(*_refcount) == 0){
	//			_del(_ptr);
	//			delete _refcount;
	//		}
	//		_ptr = shp._ptr;
	//		_refcount = shp._refcount;
	//		++(*_refcount);
	//	}
	//}

	SharedPtr<T, Del>& operator=(SharedPtr<T, Del>& sh)
	{
		swap(_ptr, sh._ptr);
		swap(_refcount, sh._refcount);
		return *this;
	}

	~SharedPtr()
	{
		if (--(*_refcount) == 0){
			cout << "delete" << endl;

			_del(_ptr);
			delete _refcount;
		}
	}

	int GetRef()
	{
		return *_refcount;
	}

	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return _ptr;
	}

	T* GetPtr() const
	{
		return _ptr;
	}
protected:
	T* _ptr;
	int* _refcount;
	Del _del;

};

void TestSharedPtr()
{
	SharedPtr<FILE, Fclose> fshp(fopen("loal.txt", "w"), Fclose());
	SharedPtr<int>   int_shp(new int(2));
	SharedPtr<string, DelArray<string>> string_shp(new string[10], DelArray<string>());
}

template<class T>
class WeakPtr
{
public:
	WeakPtr()
		:_ptr(NULL)
	{}

	WeakPtr(const SharedPtr<T>& sh)
		:_ptr(sh.GetPtr())
	{}

	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return _ptr;
	}

private:
	T* _ptr;
};

//循环引用
struct ListNode
{
	WeakPtr<ListNode> _prev;
	WeakPtr<ListNode> _next;
	
	~ListNode()
	{
		cout<<"~ListNode()"<<endl;
	}

};

void TestCycleRef()
{
	SharedPtr<ListNode> cur = new ListNode;
	SharedPtr<ListNode> next = new ListNode;

	cur->_next = next;
	next->_prev = cur;
}

int main()
{
	TestCycleRef();
	TestSharedPtr();
	TestScopedPtr();
	TestAutoPtr();
	system("pause");
	return 0;
}
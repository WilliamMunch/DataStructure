#include<iostream>
#include<stdlib.h>
#include<vector>
#include<memory.h>

using namespace std;

template <class T>
class Vector
{
public:
	typedef T value_type;
	typedef value_type* point;
	typedef value_type* iterator;
	typedef const value_type* Constiterator;
	typedef value_type& reference;
	typedef const value_type& Constreference;
	typedef size_t SizeType;
	typedef const size_t ConstSizeType;

	

	Vector()
		:start(0)
		,finish(0)
		,end_of_capacity(0)
	{}

    Vector(SizeType n ,const T& value = T())
		:start(new T[n])
		, finish(start)
		, end_of_capacity(start)
	{
		for(SizeType idx = 0;idx < n;idx++){
		   start[idx] = value;
		   finish++;
		}
		end_of_capacity = start + n - 1;
	}

	~Vector()
	{
		delete[] start;
		start = NULL;
	}

	iterator Begin()
	{
		return start;
	}

	iterator End()
	{
		return finish;
	}

	Constiterator Begin()const
	{
		return start;
	}

	Constiterator End()const
	{
		return finish;
	}


	SizeType Size()const
	{
		return (SizeType)(End() - Begin());
	}

	ConstSizeType Capacity()const
	{
		return (SizeType)(end_of_capacity - Begin());
	}

	bool empty()const
	{
		return Begin() == End();
	}

	reference front()
	{
		return *Begin();
	}

	reference back()
	{
		return *(End() - 1);
	}

	Constreference front()const
	{
		return *Begin();
	}

	Constreference back()const
	{
		return *(End() - 1);
	}

	void CheckCapacity()
	{
		if(End() == end_of_capacity){
			T* pTemp = new T[Size()*2 + 1];
			memcpy(pTemp,start,sizeof(T)*Size());
			delete[] start;
			start = pTemp;
			finish = start + Size();
			end_of_capacity = start + Size()*2 +1;
   		}
	}

	void PushBack (const T& x)
	{
		CheckCapacity();
		*finish = x;
		++finish;
	}

	void Insert(iterator pos,const T& x)
	{
		CheckCapacity();
		if (End() == pos){
			*pos = x;
			++finish;
		}
        point pCur = finish - 1; 
		point pNext = finish;
		while(pCur-- == pos){
             *pNext-- = *pCur;
		}
		++finish;
		*pos = x;
	}
	
	void erase(iterator pos)
	{
		if(End() == pos +1){
			delete pos;
			--finish;
		}
           point pCur = pos;
		   point pNext = pos +1;
		   while(pNext != finish){
			   *pCur++ = *pNext++;
		   }
		    
		   --finish;
    }

	reference operator[] (SizeType n)
	{
		return *(Begin() + n);
	}
		
protected:
	iterator start;
	iterator finish;
	iterator end_of_capacity;
};


int main()
{
	Vector<int> v1(10,5);
	v1.PushBack(3);
	v1.PushBack(4);
	v1.PushBack(6);
	//v1.Insert()
	cout << v1[9] << endl;
	cout << v1[10] << endl;
	cout << v1[11] << endl;
	cout << v1[12] << endl;
	v1.Insert(&v1[3], 7);
	cout << v1[3] << endl;
	v1.erase(&v1[3]);
	cout << v1[3] << endl;
	system("pause");
	return 0; 
}
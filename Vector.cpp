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
	typedef value_type& reference;
	typedef size_t SizeType;

	iterator start;
	iterator finish;
	iterator end_of_capacity;

	Vector()
		:start(0)
		,finish(0)
		,end_of_capacity(0)
	{}

    Vector(SizeType n ,const& T value = T())
		:start(new T[n])
	{
		for(SizeType idx = 0;idx < n;idx++){
		   start[n] = value;
		}
	}

	~Vector()
	{
		delete[] start;
	}

	iterator Begin()
	{
		return start;
	}

	iterator End()
	{
		return finish;
	}

	SizeType Size()const
	{
		return (SizeType)(End() - Begin());
	}

	SizeType Capacity()const
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
	
	iterator erase(iterator pos)
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
		   delete pCur;
		   --finish;
    }

};


int main()
{
	Vector<int> v1(5,6);
	system("pause");
	return 0;
}
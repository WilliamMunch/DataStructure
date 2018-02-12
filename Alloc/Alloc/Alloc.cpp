#pragma once
#include<iostream>

using namespace std;
//一级空间配置器
template<int inst>
class _Malloc_Alloc_Template
{
	//Oom // Out_of_memory;
private:
	static void *Oom_Malloc(size_t);
	static void *Oom_Realloc(void* p, size_t size);
	static void(*__Malloc_Alloc_Oom_Handler)();//该函数的函数指针由用户自己知道自己设置。

public:
	static void* Allocate(size_t n)
	{
		void* result = malloc(n);//一级空间配置器直接使用malloc();
		if (NULL == result) result = Oom_Malloc(n);//malloc调用失败就调用out_of_memory时继续要malloc的处理函数
		return result;
	}

	static void* Reallocate(void* p, size_t new_size)
	{
		void* result = realloc(p, new_size);//一级空间配置器的reallocate（）直接调用relloc（）
		if (NULL == result) result = Oom_Realloc(p, new_size);//同Allocate。
		return result;
	}

	static void DeAllocate(void* p)
	{
		free(p);
	}

	//用户设置自己的 set_out_of_memory handler 将自己的内存不足处理方法传给 空间配置器
	//并保留原来的内存不足处理方法保留在old函数指针中。
	static void(*Set_Malloc_Handler(void(*f)()))()
	{
		void(*old)() = __Malloc_Alloc_Oom_Handler;
		__Malloc_Alloc_Oom_Handler = f;
		return (old);
	}

};

template<int inst>
void(*_Malloc_Alloc_Template<inst>::__Malloc_Alloc_Oom_Handler) () = 0;//默认的内存不足处理方法

template<int inst>
void* _Malloc_Alloc_Template<inst>::Oom_Malloc(size_t n)
{
	void(*My_Malloc_Handler)();
	void* result;

	for (;;){
		My_Malloc_Handler = __Malloc_Alloc_Oom_Handler;//循环调用用户自定义out of memory 处理例程 
		//希望释放后能成功分配内存
		if (NULL == My_Malloc_Handler){ _THROW_BAD_ALLOC };//用户没有定义则抛异常，丢出bad_alloc异常信息 或利用exit(1)终止程序。
		(*My_Malloc_Handler)();//试图释放内存
		result = malloc(n);
		if (result) return result;//成功申请到内存则返回指向该空间的指针。
	}
}

//同上
template<int inst>
void* _Malloc_Alloc_Template<inst>::Oom_Realloc(void* p, size_t n)
{
	void(*My_Malloc_Handler)();
	void* result;

	for (;;){
		My_Malloc_Handler = __Malloc_Alloc_Oom_Handler;
		if (NULL == My_Malloc_Handler) { _THROW_BAD_ALLOC };
		(*My_Malloc_Handler)();
		result = realloc(p, n);
		if (result) return result;
	}
}

typedef _Malloc_Alloc_Template<0> malloc_alloc;

//二级空间配置器
enum { _ALIGN = 8 };//小块内存最小字节数 每一块自由链表的内存都是_ALIGN的倍数。
enum { _MAX_BYTES = 128 };//定义的小型内存区块的上限
enum { _NUMBEROFLISTS = _MAX_BYTES / _ALIGN };//维护的自由链表的数量

template<bool thread, int init>
class _Default_Alloc_Template
{
private:
	static size_t ROUND_UP(size_t bytes)
	{//将需要的bytes 上调至八的倍数
		return (((bytes)+_ALIGN - 1) &~(_ALIGN - 1));//这样的方法效率更高
	}

	union obj{//自由链表结点 类型是union 为了不为维护链表所必须的指针而额外占用内存空间
		obj* FreeListLink;//指向另一个obj结构
		char client_data[1];//指向实际内存区块
	};

	static obj* volatile FreeList[_NUMBEROFLISTS];//用指针数组保存管理二级空间配置器的各个节点大小不同的自由链表
	static size_t FreeListIndex(size_t bytes)//通过开辟空间字节数找到其对应使用的自由链表在指针数组中的索引
	{
		return (((bytes)+_ALIGN - 1) / _ALIGN - 1);//这种方式效率高
	}

	static void * Refill(size_t n);//
	static char* Chunk_Alloc(size_t size, int& nobjs);//
	static char* start_free;//表示内存池的起始位置
	static char* end_free;//表示内存池的终止位置
	static size_t heapsize;//记录空间配置器共向系统堆申请了多大的内存。

public:
	
	static void* Allocate(size_t n)
	{
		obj * volatile * my_free_list;//操作自由链表中节点指针的指针
		obj* result;//定义指向返回内存块的指针
		if ((size_t)_MAX_BYTES < n){//申请大小超过128字节 调用一级空间配置器。
			return (malloc_alloc::Allocate(n));
		}
		my_free_list = FreeList + FreeListIndex(n);//自由链表中找到需要的内存块
		result = *my_free_list;//返回
		if (result == NULL){
			void* r = Refill(ROUND_UP(n));//如果这个自由链表没有内存块了 则从内存池上取20块这条链表结点指向空间大小的内存链接到指针数组的这个元素后面
			return r;
		}
		*my_free_list = result->FreeListLink;//指向下一个内存块 相当于头删
		return result;
	}

	static void DeAllocate(void* p, size_t n)
	{
		obj * q = (obj*)p;//Q是要是要还会自由链表中的节点
		obj * volatile * my_free_list;
		if ((size_t)_MAX_BYTES < n){//释放大小超过128字节 调用一级空间配置器。
			malloc_alloc::DeAllocate(p, n);
			return;
		}
		my_free_list = FreeList + FreeListIndex(n);//自由链表中找到需要的内存块
		q->FreeListLink = *my_free_list;//将要释放的节点头插还回自由链表
		*my_free_list = q;
	}
	//本质上这里的申请和释放是将一块内存空间交给用户管理和还给空间配置器管理。

};

template<bool thread, int inst>
char* _Default_Alloc_Template<thread, inst>::start_free = 0;

template<bool thread, int inst>
char* _Default_Alloc_Template<thread, inst>::end_free = 0;

template<bool thread, int inst>
char* _Default_Alloc_Template<thread, inst>::heapsize = 0;

template<bool thread, int inst>
typename _Default_Alloc_Template<thread, inst>::obj *  volatile 
_Default_Alloc_Template<thread, inst>::FreeList[_NUMBEROFLISTS] =
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };


template<bool thread, int inst>
void* _Default_Alloc_Template<thread, inst>::Refill(size_t n) //填充一条自由链表的算法
{//参数n是指需要重新填充的链表的节点指向的空间的大小
	int nobjs = 20;//默认忘一条空链表填充20个该链表节点
	int i = 1;
	obj* volatile * my_free_list;
	obj* cur_obj, next_obj;
	obj* result;

	char* chunk = Chunk_Alloc(n, nobjs);//注意 nobjs是传引用 调用结束后nobjs表示实际上从内存池切下多少块内存块
	if (1 == nobjs) return (chuck);
	my_free_list = FreeList + FreeListIndex(n);//找到需要填充的链表的位置

	result = (obj*)chunk;//从内存池中切适当大小的内存 这里把第一块返回
	*my_free_list = next_obj = (obj*)(chunk + n);//这里把第二块先挂到指针数组对应位置下  //注意这里的n在传参数时已经调整到8的倍数
	for (i = 1;; i++){//循环进行了nobjs - 2次
		cur_obj = next_obj;
		next_obj = (obj*)((chat*)next_obj + n);//这里为什么是尾差不是头插？
		if (nobjs - 1 == i){                   //因为第一次从内存池取下的空间在物理上是连续的 尾插方便用 以后用完还回自由链表的就不是了
			cur_obj->FreeLinkList = NULL;//这里没有添加节点
			break;
		}
		else{
			cur_obj->FreeLinkList = next_obj;//nobjs - 2是最后一次添加节点
		}
	}
	return result;
}

template<bool thread, int init>
char* _Default_Alloc_Template<thread, init>::Chunk_Alloc(size_t size, int& nobjs)
{
	char* result;
	size_t TotalBytes = size * nobjs;//需要从內存池切多少字节
	char* LeftBytes = end_free - start_free;//内存池剩下多少字节
	if (TotalBytes <= LeftBytes){//内存池剩余空间够20块n个字节大小
		result = start_free;
		start_free += TotalBytes;
		return result;
	}
	else if (TotalBytes > LeftBytes){//内存池剩余空间不足
		nobjs = LeftBytes / size;//减少切下的内存块数
		TotalBytes = nobjs * size;//重新计算共从内存池切下多少字节
		result = start_free;
		start_free += TotalBytes;
		return result;
	}
	else{
		if (LeftBytes > 0){//内存池中还有不到1块内存  将剩的这不到一块内存挂到自由链表下
			obj* volatile * my_free_list = FreeList + FreeListIndex(LeftBytes);//LeftBytes 一定是8的倍数 因为之前是按照八的倍数切得内存
			(obj*)(start_free)->FreeListLink = *my_free_list;//头插
			*my_free_list = (obj*)start_free;
		}
		size_t BytesToGet = 2 * TotalBytes + ROUND_UP(heapsize >> 4);//这里通过heapsize进行负反馈调节如果之前申请过的堆空间越大 这里就多开辟些内存池
		start_free = (char*)malloc(BytesToGet);

		if (0 == start_free){//heap 空间不足,malloc()失败。
			obj* volatile *my_free_list;//在比当前需求的自由链表保存内存块大小大的自由链表中寻找一块空间作为内存池 并切下作为小自由链表的内存块
			obj* p;
			for (int i = size; i <= _MAX_BYTES; i += _ALIGN){
				my_free_list = FreeList + FreeListIndex(i);
				p = *my_free_list;
				if (0 != p){
					*my_free_list = p->FreeListLink;
					start_free = (char*)p;
					end_free = start_free + i;
					return(Chunk_Alloc(size, nobjs));
				}
			}
			end_free = 0;
			start_free = (char*)_Malloc_Alloc_Template::Allocate(BytesToGet);
			//分配失败时start_free是0 这时如果end_free不是0的话 下次end_free - start_free
			//会得到很大一块非法空间。
		}
		heapsize += BytesToGet;//记录向系统堆空间申请大小。
		end_free = start_free + BytesToGet;//标记好新的内存池的大小。
		return (Chunk_Alloc(size, nobjs));
	}
}

template<class T, class Alloc>
class simple_alloc{
	static T* allocate(size_t n)
	{
		return 0 == n ? 0 : (T*)Alloc::allocate(n * sizeof(T));
	}

	static T* allocate(void){
		return (T*)Alloc::allocate(sizeof(T));
	}

	static void deallocate(T* p, size_t n){
		if (0 != n) Alloc::deallocate(p, n * sizeof(T));
	}
	
	static void deallocate(T* p){
		Alloc::deallocate(p, sizeof(T));
	}
};

template<class T, class Alloc = alloc>
class Vector{
protected:
	typedef simple_alloc<ValueType, Alloc> data_allocator;

	void deallocate(){
		if (...)
			data_allocator::deallocate(start, end_of_storage - start);
	}
};



int main()
{
	char a[10] = { 0 };
	return 0;
}







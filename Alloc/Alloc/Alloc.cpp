#pragma once
#include<iostream>

using namespace std;
//һ���ռ�������
template<int inst>
class _Malloc_Alloc_Template
{
	//Oom // Out_of_memory;
private:
	static void *Oom_Malloc(size_t);
	static void *Oom_Realloc(void* p, size_t size);
	static void(*__Malloc_Alloc_Oom_Handler)();//�ú����ĺ���ָ�����û��Լ�֪���Լ����á�

public:
	static void* Allocate(size_t n)
	{
		void* result = malloc(n);//һ���ռ�������ֱ��ʹ��malloc();
		if (NULL == result) result = Oom_Malloc(n);//malloc����ʧ�ܾ͵���out_of_memoryʱ����Ҫmalloc�Ĵ�����
		return result;
	}

	static void* Reallocate(void* p, size_t new_size)
	{
		void* result = realloc(p, new_size);//һ���ռ���������reallocate����ֱ�ӵ���relloc����
		if (NULL == result) result = Oom_Realloc(p, new_size);//ͬAllocate��
		return result;
	}

	static void DeAllocate(void* p)
	{
		free(p);
	}

	//�û������Լ��� set_out_of_memory handler ���Լ����ڴ治�㴦�������� �ռ�������
	//������ԭ�����ڴ治�㴦����������old����ָ���С�
	static void(*Set_Malloc_Handler(void(*f)()))()
	{
		void(*old)() = __Malloc_Alloc_Oom_Handler;
		__Malloc_Alloc_Oom_Handler = f;
		return (old);
	}

};

template<int inst>
void(*_Malloc_Alloc_Template<inst>::__Malloc_Alloc_Oom_Handler) () = 0;//Ĭ�ϵ��ڴ治�㴦����

template<int inst>
void* _Malloc_Alloc_Template<inst>::Oom_Malloc(size_t n)
{
	void(*My_Malloc_Handler)();
	void* result;

	for (;;){
		My_Malloc_Handler = __Malloc_Alloc_Oom_Handler;//ѭ�������û��Զ���out of memory �������� 
		//ϣ���ͷź��ܳɹ������ڴ�
		if (NULL == My_Malloc_Handler){ _THROW_BAD_ALLOC };//�û�û�ж��������쳣������bad_alloc�쳣��Ϣ ������exit(1)��ֹ����
		(*My_Malloc_Handler)();//��ͼ�ͷ��ڴ�
		result = malloc(n);
		if (result) return result;//�ɹ����뵽�ڴ��򷵻�ָ��ÿռ��ָ�롣
	}
}

//ͬ��
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

//�����ռ�������
enum { _ALIGN = 8 };//С���ڴ���С�ֽ��� ÿһ������������ڴ涼��_ALIGN�ı�����
enum { _MAX_BYTES = 128 };//�����С���ڴ����������
enum { _NUMBEROFLISTS = _MAX_BYTES / _ALIGN };//ά�����������������

template<bool thread, int init>
class _Default_Alloc_Template
{
private:
	static size_t ROUND_UP(size_t bytes)
	{//����Ҫ��bytes �ϵ����˵ı���
		return (((bytes)+_ALIGN - 1) &~(_ALIGN - 1));//�����ķ���Ч�ʸ���
	}

	union obj{//���������� ������union Ϊ�˲�Ϊά�������������ָ�������ռ���ڴ�ռ�
		obj* FreeListLink;//ָ����һ��obj�ṹ
		char client_data[1];//ָ��ʵ���ڴ�����
	};

	static obj* volatile FreeList[_NUMBEROFLISTS];//��ָ�����鱣���������ռ��������ĸ����ڵ��С��ͬ����������
	static size_t FreeListIndex(size_t bytes)//ͨ�����ٿռ��ֽ����ҵ����Ӧʹ�õ�����������ָ�������е�����
	{
		return (((bytes)+_ALIGN - 1) / _ALIGN - 1);//���ַ�ʽЧ�ʸ�
	}

	static void * Refill(size_t n);//
	static char* Chunk_Alloc(size_t size, int& nobjs);//
	static char* start_free;//��ʾ�ڴ�ص���ʼλ��
	static char* end_free;//��ʾ�ڴ�ص���ֹλ��
	static size_t heapsize;//��¼�ռ�����������ϵͳ�������˶����ڴ档

public:
	
	static void* Allocate(size_t n)
	{
		obj * volatile * my_free_list;//�������������нڵ�ָ���ָ��
		obj* result;//����ָ�򷵻��ڴ���ָ��
		if ((size_t)_MAX_BYTES < n){//�����С����128�ֽ� ����һ���ռ���������
			return (malloc_alloc::Allocate(n));
		}
		my_free_list = FreeList + FreeListIndex(n);//�����������ҵ���Ҫ���ڴ��
		result = *my_free_list;//����
		if (result == NULL){
			void* r = Refill(ROUND_UP(n));//��������������û���ڴ���� ����ڴ����ȡ20������������ָ��ռ��С���ڴ����ӵ�ָ����������Ԫ�غ���
			return r;
		}
		*my_free_list = result->FreeListLink;//ָ����һ���ڴ�� �൱��ͷɾ
		return result;
	}

	static void DeAllocate(void* p, size_t n)
	{
		obj * q = (obj*)p;//Q��Ҫ��Ҫ�������������еĽڵ�
		obj * volatile * my_free_list;
		if ((size_t)_MAX_BYTES < n){//�ͷŴ�С����128�ֽ� ����һ���ռ���������
			malloc_alloc::DeAllocate(p, n);
			return;
		}
		my_free_list = FreeList + FreeListIndex(n);//�����������ҵ���Ҫ���ڴ��
		q->FreeListLink = *my_free_list;//��Ҫ�ͷŵĽڵ�ͷ�廹����������
		*my_free_list = q;
	}
	//�����������������ͷ��ǽ�һ���ڴ�ռ佻���û�����ͻ����ռ�����������

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
void* _Default_Alloc_Template<thread, inst>::Refill(size_t n) //���һ������������㷨
{//����n��ָ��Ҫ������������Ľڵ�ָ��Ŀռ�Ĵ�С
	int nobjs = 20;//Ĭ����һ�����������20��������ڵ�
	int i = 1;
	obj* volatile * my_free_list;
	obj* cur_obj, next_obj;
	obj* result;

	char* chunk = Chunk_Alloc(n, nobjs);//ע�� nobjs�Ǵ����� ���ý�����nobjs��ʾʵ���ϴ��ڴ�����¶��ٿ��ڴ��
	if (1 == nobjs) return (chuck);
	my_free_list = FreeList + FreeListIndex(n);//�ҵ���Ҫ���������λ��

	result = (obj*)chunk;//���ڴ�������ʵ���С���ڴ� ����ѵ�һ�鷵��
	*my_free_list = next_obj = (obj*)(chunk + n);//����ѵڶ����ȹҵ�ָ�������Ӧλ����  //ע�������n�ڴ�����ʱ�Ѿ�������8�ı���
	for (i = 1;; i++){//ѭ��������nobjs - 2��
		cur_obj = next_obj;
		next_obj = (obj*)((chat*)next_obj + n);//����Ϊʲô��β���ͷ�壿
		if (nobjs - 1 == i){                   //��Ϊ��һ�δ��ڴ��ȡ�µĿռ����������������� β�巽���� �Ժ����껹����������ľͲ�����
			cur_obj->FreeLinkList = NULL;//����û����ӽڵ�
			break;
		}
		else{
			cur_obj->FreeLinkList = next_obj;//nobjs - 2�����һ����ӽڵ�
		}
	}
	return result;
}

template<bool thread, int init>
char* _Default_Alloc_Template<thread, init>::Chunk_Alloc(size_t size, int& nobjs)
{
	char* result;
	size_t TotalBytes = size * nobjs;//��Ҫ�Ӄȴ���ж����ֽ�
	char* LeftBytes = end_free - start_free;//�ڴ��ʣ�¶����ֽ�
	if (TotalBytes <= LeftBytes){//�ڴ��ʣ��ռ乻20��n���ֽڴ�С
		result = start_free;
		start_free += TotalBytes;
		return result;
	}
	else if (TotalBytes > LeftBytes){//�ڴ��ʣ��ռ䲻��
		nobjs = LeftBytes / size;//�������µ��ڴ����
		TotalBytes = nobjs * size;//���¼��㹲���ڴ�����¶����ֽ�
		result = start_free;
		start_free += TotalBytes;
		return result;
	}
	else{
		if (LeftBytes > 0){//�ڴ���л��в���1���ڴ�  ��ʣ���ⲻ��һ���ڴ�ҵ�����������
			obj* volatile * my_free_list = FreeList + FreeListIndex(LeftBytes);//LeftBytes һ����8�ı��� ��Ϊ֮ǰ�ǰ��հ˵ı����е��ڴ�
			(obj*)(start_free)->FreeListLink = *my_free_list;//ͷ��
			*my_free_list = (obj*)start_free;
		}
		size_t BytesToGet = 2 * TotalBytes + ROUND_UP(heapsize >> 4);//����ͨ��heapsize���и������������֮ǰ������Ķѿռ�Խ�� ����Ͷ࿪��Щ�ڴ��
		start_free = (char*)malloc(BytesToGet);

		if (0 == start_free){//heap �ռ䲻��,malloc()ʧ�ܡ�
			obj* volatile *my_free_list;//�ڱȵ�ǰ����������������ڴ���С�������������Ѱ��һ��ռ���Ϊ�ڴ�� ��������ΪС����������ڴ��
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
			//����ʧ��ʱstart_free��0 ��ʱ���end_free����0�Ļ� �´�end_free - start_free
			//��õ��ܴ�һ��Ƿ��ռ䡣
		}
		heapsize += BytesToGet;//��¼��ϵͳ�ѿռ������С��
		end_free = start_free + BytesToGet;//��Ǻ��µ��ڴ�صĴ�С��
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







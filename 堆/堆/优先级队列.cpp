#include"堆.cpp"

#define N 1000
#define K 20
//优先级队列为堆的简单封装
template<class T>
class PriorityQueue
{
public:
	PriorityQueue()
	{}

	void Push(const T& data)
	{
		hp.Push(data);
	}
	
	void Pop()
	{
		hp.Pop();
	}

	const T& Top()
	{
		return hp.Top();
	}

	size_t Size()
	{
		return hp.Size();
	}

	bool Empty()
	{
		return hp.Empty();
	}
private:
	Heap<int, Greater<int>> hp;
};

void Test()
{
	int array[] = { 53, 17, 78, 9, 45, 65, 87, 23 };
	Heap<int, Greater<int> > h(array, sizeof(array) / sizeof(int));
	h.Push(80);
	h.Pop();
}

void TestPriorityQueue()
{
	int array[] = { 53, 17, 78, 9, 45, 65, 87, 23 };
	size_t len = sizeof(array) / sizeof(int);
	PriorityQueue<int> p;
	for (size_t index = 0; index < len; ++index)
	{
		p.Push(array[index]);
	}

	cout << p.Top() << endl;
	p.Pop();
	cout << p.Top() << endl;
}
//TopK问题
void TopK()
{
	int arr[N];
	int brr[K];
	for (size_t i = 0; i < N; ++i){
		arr[i] = rand() % N;
	}

	for (size_t i = 0; i < K; ++i){
		brr[i] = arr[i];
	}

	Heap<int, Less<int>> hp(brr, sizeof(brr) / sizeof(int));
	for (size_t i = K; i <= N; ++i){
		if (arr[i] > hp.Top()){
			hp.Pop();
			hp.Push(arr[i]);
		}
	}
	hp.Printheap();
}

int main()
{

	/*Test();
	TestQueue();*/
	TopK();
	system("pause");
	return 0;
}
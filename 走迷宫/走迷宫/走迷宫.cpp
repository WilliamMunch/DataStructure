#define _CRT_SECURE_NO_WARNINGS 1
#include"Stack.cpp"
#include<stack>
#include<iostream>
#include<stdlib.h>
#include<assert.h>

//#define MAX_ROW 10
//#define MAX_COL 10

using namespace std;
//
//struct Seat
//{
//	Seat(int x, int y)
//	:_x(x)
//	, _y(y)
//	{}
//	int _x;
//	int _y;
//};
//
//template<size_t N, size_t M>
//class Maze
//{
//public:
//	Maze(int** arr,FILE* fp)
//		:_maze(arr)
//		, _row(N)
//		, _col(M)
//	{
//		assert(_maze);
//		assert(fp);
//		for (size_t i = 0; i < _row; ++i){
//			for (size_t j = 0; j < _col;){
//				char ch = fgetc(fp);
//				if (ch == '0' || ch == '1'){
//					_maze[i][j] = ch - '0';
//					++j;
//				}
//			}
//		}
//		fclose(fp);
//	}
//
//	void PrintMaze()
//	{
//		for (int i = 0; i < _row; ++i){
//			for (int j = 0; j < _col; ++j){
//				cout << _maze[i][j] << " ";
//			}
//			cout << endl;
//		}
//		cout << endl;
//	}
//
//	bool IsPass(const Seat& s)
//	{
//		if (s._x < 0 || s._y < 0 || s._x > _row || s._y > _col)
//			return true; //���߳��Թ� ֱ�ӷ���
//		if (1 == _maze[s._x][s._y])
//			return true;//��·ͨ
//		return false;
//	}
//	//�ݹ�ⷨ
//	bool GetPath(Seat s)
//	{
//		if (s._x < 0 || s._y < 0 || s._x >= _row || s._y >= _col)
//			return true;//�˴�Ϊ�ݹ����
//		Seat cur = s;
//		Seat next = cur;
//		_maze[next._x][next._y] = 2;//��ͨ· ���Ϊ2
//
//		next._x -= 1;
//		if (IsPass(next)){
//			if (GetPath(next)){
//				return true;
//			}
//		}
//
//		next = cur;
//		next._y -= 1;
//		if (IsPass(next)){
//			if (GetPath(next)){//��������ͨ·�ĺ���ͨ· �������true(69��)��˵�����ҵ�����\
//				��ʱ����Ҳ����true ���շ������в㺯�� �������false(107��) �����ڱ�����\
//				��ִ�С�����������Ѱ��ͨ·��
//				return true;
//			}
//		}
//
//		next = cur;
//		next._x += 1;
//		if (IsPass(next)){
//			if (GetPath(next)){
//				return true;
//			}
//		}
//
//		next = cur;
//		next._y += 1;
//		if (IsPass(next)){
//			if (GetPath(next)){
//				return true;
//			}
//		}
//		//��һ���û�к���ͨ· �����ߵ�����
//		_maze[next._x][next._y] = 3; //����Ϊ��·�Ľ����Ϊ��
//		return false;//û��ͨ·�򷵻�flase
//	}
//	//ѭ���ⷨ
//	//bool GetPath(Seat s)
//	//{
//	//	if (s._x < 0 || s._y < 0 || s._x >= _row || s._y >= _col)
//	//		return true;
//	//	if (!IsPass(s))
//	//		return false;
//
//	//	stack<Seat> con;
//	//	con.push(s);//�Ƚ���һ��ͨ·��ջ
//
//	//	while (!con.empty()){
//	//		Seat cur = con.top();//ȡջ��Ԫ�أ�ʵ������ȥ�ոյ����ͨ·
//	//		
//	//		if (cur._x < 0 || cur._x >= _row ||
//	//			cur._y < 0 || cur._y >= _col)
//	//		{
//	//			return true;
//	//		}
//	//		_maze[cur._x][cur._y] = 2;
//	//		Seat next(cur);
//	//		
//	//		//next = cur;
//	//		next._x -= 1;
//	//		if (IsPass(next)){
//	//			con.push(next);//��ͨ·�Ļ�����ջ��
//	//			continue;
//	//		}
//	//		
//	//		next = cur;
//	//		next._y -= 1;
//	//		if (IsPass(next)){
//	//			con.push(next);
//	//			continue;
//	//		}
//
//	//		next = cur;
//	//		next._x += 1;
//	//		if (IsPass(next)){
//	//			con.push(next);
//	//			continue;
//	//		}
//
//	//		next = cur;
//	//		next._y += 1;
//	//		if (IsPass(next)){
//	//			con.push(next);
//	//			continue;
//	//		}
//	//		//��һ�������ͨ· ��������· �����ܵ�����λ����			
//	//		_maze[cur._x][cur._y] = 3;//˼·���Ϊ3.
//	//		con.pop();��֮ǰ�߹��ĺ�������·�Ľ���ջ
//	        //ѭ������ ����һ���߹��Ľ��������ͨ·
//	//	}
//	//	return false;
//	//}
//
//    
//	
//
//	~Maze()
//	{
//		for (size_t i = 0; i < _row; ++i)
//				delete[] _maze[i];
//			delete[] _maze;
//	}
//
//private:
//	int** _maze;
//	int _row;
//	int _col;
//
//};
//
//void Auto_two_dimension_arry()
//{
//	int** p = new int*[10];
//	for (size_t i = 0; i < 10; ++i){
//		p[i] = new int[10];
//	}
//	
//	//for (size_t j = 0; j < 10; ++j){
//	//	delete[] p[j];
//	//}
//
//	//delete[] p;
//}
//
//void Test()
//{
//	FILE* fp = fopen("Maze.txt", "r");
//	/*int row = 0;
//	int col = 0;
//	fscanf(fp, "%d %d", &row, &col);
//	int start_x = 0;
//	int start_y = 0;
//	fscanf(fp, "%d %d", &start_x, &start_y);*/
//	int** p = new int*[10];
//	for (size_t i = 0; i < 10; ++i){
//		p[i] = new int[10];
//	}
//
//	Maze<10,10> m(p,fp);
//	m.PrintMaze();
//	m.GetPath(Seat(9, 3));
//	m.PrintMaze();
//}
//
//int main()
//{
//	//int maparr[MAX_ROW][MAX_COL] = {
//	//	{ 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
//	//	{ 0, 0, 1, 1, 1, 1, 1, 0, 0, 0 },
//	//	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
//	//	{ 1, 1, 1, 0, 1, 0, 0, 0, 0, 0 },
//	//	{ 0, 0, 1, 0, 1, 0, 0, 0, 0, 0 },
//	//	{ 0, 0, 1, 1, 1, 0, 0, 0, 0, 0 },
//	//	{ 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
//	//	{ 0, 0, 1, 1, 0, 0, 0, 0, 0, 0 },
//	//	{ 0, 0, 0, 1, 1, 1, 1, 0, 0, 0 },
//	//	{ 0, 0, 0, 1, 0, 0, 1, 0, 0, 0 }
//	//};
//	//Maze m(maparr,MAX_ROW, MAX_COL);
//	//m.PrintMaze();
//	//m.GetPath(Seat(9,3));
//	////cout << "���·��Ϊ��" << m.GetPath(Seat(9, 3)) << endl;
//	//m.PrintMaze();
//	Test();
//	system("pause");
//	return 0;
//}

struct Seat
{
	Seat(int x, int y)
	:_x(x)
	,_y(y)
	{}
	int _x;
	int _y;
};

//���Թ������Ž�
template<size_t N, size_t M>
class Maze
{
public:
	Maze(int** arr, FILE* fp)
		:_maze(arr)
		, _row(N)
		, _col(M)
	{
		assert(arr);
		assert(fp);
		for (size_t i = 0; i < _row; ++i){
			for (size_t j = 0; j < _col;){
				char ch = fgetc(fp);
				if (ch == '0' || ch == '1'){
					_maze[i][j] = ch - '0';
					++j;
				}
			}
		}
		fclose(fp);
	}

	~Maze()
	{
		for (size_t i = 0; i < _row; ++i)
			delete[] _maze[i];
		delete[] _maze;
	}

	friend ostream& operator<<(ostream& _cout, Maze<10, 10>& m);

	void Print()
	{
		for (size_t i = 0; i < _row; ++i){
			for (size_t j = 0; j < _col; ++j){
			     cout << _maze[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}

	bool IsShortPath(Seat& s,Seat& cs)
	{
		if (s._x >= 0 && s._y >= 0 && s._y < N && s._x < M){
			if (1 == _maze[s._x][s._y] || _maze[s._x][s._y] > _maze[cs._x][cs._y])
				return true;
			 //����·������һ���ֲ�·���� ����true
			//return true;
		}
		return false;
	}

	void GetShortPath(Seat s, stack<Seat>& ShortPath, stack<Seat>& Path)
	{
		Seat cur = s;                                           
		Seat next = cur;
		Path.push(cur);
		//if(Path.enpty())
		//{
		//  _maze[cur._x][cur._y] = 2;
		//
       	//}
		//Seat prev = Path.top();
		//_maze[cur._x][cur._y] = _maze[prev._x][prev._y] + 1;
				
		if (s._x == 0 || s._y == 0 )
		{
			//Print();
			Path.pop();
			printf("����һ�����ڣ�%d, %d��\n", s._x, s._y);
			if (ShortPath.empty() || Path.size() < ShortPath.size())
			{
				ShortPath = Path;
			}
			return;
		}

 		next._x -= 1;
		if (IsShortPath(next,cur)){
			_maze[next._x][next._y] = _maze[cur._x][cur._y] + 1;
			GetShortPath(next, ShortPath, Path);
		}

		next = cur;
		next._y -= 1;
		if (IsShortPath(next, cur)){
			_maze[next._x][next._y] = _maze[cur._x][cur._y] + 1;
			GetShortPath(next, ShortPath, Path);
				
		}

		next = cur;
		next._y += 1;
		if (IsShortPath(next, cur)){
			_maze[next._x][next._y] = _maze[cur._x][cur._y] + 1;
			GetShortPath(next, ShortPath, Path);
		}

		next = cur;
		next._x += 1;
		if (IsShortPath(next, cur)){
			_maze[next._x][next._y] = _maze[cur._x][cur._y] + 1;
			GetShortPath(next, ShortPath, Path);
				
		}
		
		Path.pop();

	}
	
private:
	int** _maze;
	int _row;
	int _col;
};

ostream& operator<<(ostream& _cout, Maze<10,10>& m)
{
	for (size_t i = 0; i < m._row; ++i){
		for (size_t j = 0; j < m._col; ++j){
			_cout << m._maze[i][j] << " ";
		}
		_cout << endl;
	}
	return _cout;
}

void Test()
{
	int** p = new int*[10];
	for (size_t i = 0; i < 10; ++i){
		p[i] = new int[10];
	}
	FILE* fp = fopen("Maze.txt", "r");
	int row = 0;
	int col = 0;
	fscanf(fp, "%d %d", &row, &col);
	int start_x = 0;
	int start_y = 0;
	fscanf(fp, "%d %d", &start_x, &start_y);
	Maze<10, 10> m(p,fp);
	
	m.Print();
	stack<Seat> ShortPath, Path;
	m.GetShortPath(Seat(9, 3), ShortPath, Path);
	m.Print();
	
}

int main()
{
	
	Test();
	system("pause");
	return 0;
}


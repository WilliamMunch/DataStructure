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
//			return true; //已走出迷宫 直接返回
//		if (1 == _maze[s._x][s._y])
//			return true;//此路通
//		return false;
//	}
//	//递归解法
//	bool GetPath(Seat s)
//	{
//		if (s._x < 0 || s._y < 0 || s._x >= _row || s._y >= _col)
//			return true;//此处为递归出口
//		Seat cur = s;
//		Seat next = cur;
//		_maze[next._x][next._y] = 2;//是通路 标记为2
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
//			if (GetPath(next)){//查找这条通路的后续通路 如果返回true(69行)则说明已找到出口\
//				这时本层也返回true 最终返回所有层函数 如果返回false(107行) 继续在本层向\
//				下执行。在其他方向寻找通路。
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
//		//这一结点没有后续通路 程序走到这里
//		_maze[next._x][next._y] = 3; //后续为死路的结点标记为三
//		return false;//没有通路则返回flase
//	}
//	//循环解法
//	//bool GetPath(Seat s)
//	//{
//	//	if (s._x < 0 || s._y < 0 || s._x >= _row || s._y >= _col)
//	//		return true;
//	//	if (!IsPass(s))
//	//		return false;
//
//	//	stack<Seat> con;
//	//	con.push(s);//先将第一步通路入栈
//
//	//	while (!con.empty()){
//	//		Seat cur = con.top();//取栈顶元素，实际上是去刚刚到达的通路
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
//	//			con.push(next);//是通路的话就入栈。
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
//	//		//上一条到达的通路 后续是死路 代码跑到现在位置上			
//	//		_maze[cur._x][cur._y] = 3;//思路标记为3.
//	//		con.pop();把之前走过的后续是死路的结点出栈
//	        //循环继续 从上一条走过的结点重新找通路
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
//	////cout << "最短路径为：" << m.GetPath(Seat(9, 3)) << endl;
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

//求迷宫的最优解
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
			 //这条路径比另一条分叉路径短 返回true
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
			printf("发现一个出口（%d, %d）\n", s._x, s._y);
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


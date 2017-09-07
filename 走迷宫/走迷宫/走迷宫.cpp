#include"Stack.cpp"
#include<stack>
#include<iostream>
#include<stdlib.h>

#define MAX_ROW 10
#define MAX_COL 10

using namespace std;

struct Seat
{
	Seat(int x, int y)
	:_x(x)
	, _y(y)
	{}
	int _x;
	int _y;
};

class Maze
{
public:
	Maze(int arr[][MAX_COL],int row, int col)
	{
		for (int i = 0; i < row; ++i){
			for (int j = 0; j < col; ++j){
				maze[i][j] = arr[i][j];
			}
		}
	}

	void PrintMaze()
	{
		for (int i = 0; i < MAX_ROW; ++i){
			for (int j = 0; j < MAX_COL; ++j){
				cout << maze[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}

	bool IsPass(const Seat& s)
	{
		if (s._x < 0 || s._y < 0 || s._x > MAX_ROW || s._y > MAX_COL)
			return true;
		if (1 == maze[s._x][s._y])
			return true;
		return false;
	}

	bool GetPath(Seat s)
	{
		if (s._x < 0 || s._y < 0 || s._x >= MAX_ROW || s._y >= MAX_COL)
			return true;
		if (!IsPass(s))
			return false;

		stack<Seat> con;
		con.push(s);

		while (!con.empty()){
			Seat cur = con.top();
			
			if (cur._x < 0 || cur._x >= MAX_ROW ||
				cur._y < 0 || cur._y >= MAX_COL)
			{
				return true;
			}
			maze[cur._x][cur._y] = 2;
			Seat next(cur);
			
			//next = cur;
			next._x -= 1;
			if (IsPass(next)){
				con.push(next);
				continue;
			}
			
			next = cur;
			next._y -= 1;
			if (IsPass(next)){
				con.push(next);
				continue;
			}

			next = cur;
			next._x += 1;
			if (IsPass(next)){
				con.push(next);
				continue;
			}

			next = cur;
			next._y += 1;
			if (IsPass(next)){
				con.push(next);
				continue;
			}
						
			maze[cur._x][cur._y] = 3;
			con.pop();
		}
		return false;
	}
	/*int GetPath(Seat s){
		stack<Seat> con;
		con.push(s);
		Seat cur = con.top();
		Seat next(cur);
		return _GetPath(con,cur,next);
	}*/
	
	//int _GetPath(stack<Seat>& con,Seat cur,Seat next)
	//{
	//	int count = 0;
	//	//int ret = 0;
	//	//cur = con.push(s);
	//	cur = con.top();
	//	next = cur;
	//	
	//	if (count < _GetPath(con, cur, next))
	//		count = con.size();

	//	maze[cur._x][cur._y] = 2;
	//	
	//	next._x -= 1;
	//	if (IsPass(next)){
	//		con.push(next);
	//		_GetPath(con, cur, next);
	//	}

	//	next = cur;
	//	next._y -= 1;
	//	if (IsPass(next)){
	//		con.push(next);
	//		_GetPath(con, cur, next);
	//	}

	//	next = cur;
	//	next._y += 1;
	//	if (IsPass(next)){
	//		con.push(next);
	//		_GetPath(con, cur, next);
	//	}

	//	next = cur;
	//	next._x += 1;
	//	if (IsPass(next)){
	//		con.push(next);
	//		_GetPath(con, cur, next);
	//	}
	//	maze[cur._x][cur._y] = 3;
	//	con.pop();
	//	if (cur._x < 0 || cur._y < 0 || cur._x >= MAX_ROW || cur._y >= MAX_COL)
	//		return con.size();
	//	else
	//		return 0;
	//	return 0;

	//}

	~Maze()
	{}

private:
	int maze[MAX_ROW][MAX_COL];

};

void Auto_two_dimension_arry()
{
	int** p = new int*[10];
	for (size_t i = 0; i < 10; ++i){
		p[i] = new int[10];
	}
	for (size_t j = 0; j < 10; ++j){
		delete[] p[j];
	}

	delete[] p;
}


int main()
{
	int maparr[MAX_ROW][MAX_COL] = {
		{ 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
		{ 0, 0, 1, 1, 1, 1, 1, 0, 0, 0 },
		{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
		{ 1, 1, 1, 0, 1, 0, 0, 0, 0, 0 },
		{ 0, 0, 1, 0, 1, 0, 0, 0, 0, 0 },
		{ 0, 0, 1, 1, 1, 0, 0, 0, 0, 0 },
		{ 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 1, 1, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 1, 1, 1, 1, 0, 0, 0 },
		{ 0, 0, 0, 1, 0, 0, 1, 0, 0, 0 }
	};
	Maze m(maparr,MAX_ROW, MAX_COL);
	m.PrintMaze();
	m.GetPath(Seat(9,3));
	//cout << "×î¶ÌÂ·¾¶Îª£º" << m.GetPath(Seat(9, 3)) << endl;
	m.PrintMaze();
	system("pause");
	return 0;
}


// Sudoku.cpp
// Sudoku - PB
// 解数独程序

#include "stdafx.h"
#include <iostream>
#include "Windows.h"
using namespace std;
class Last
{
public:
	int *a;
	int length = 0;
	~Last()
	{
		delete a;
	}
	//交叉运算:求交
	Last& operator*(const Last& l) 
	{
		const Last *l2 = &l;
		Last *l1 = new Last();
		int *a1 = new int[9];
		int n = 0;
		for (int i = 0; i < this->length; i++)
		{
			for (int j = 0; j < l2->length; j++)
			{
				if (this->a[i] == l2->a[j])
				{
					a1[n] = this->a[i];
					n++;
				}
			}
		}
		l1->a = a1;
		l1->length = n;
		delete l2;
		return *l1;
	}
};
class Point
{
public:
	int x;
	int y;
};
//数独数组图
int m[9][9] =
{
	       //y
	//0 1 2 3 4 5 6 7 8
	{ 1,0,0,0,0,0,0,0,0 },//0
	{ 2,0,0,0,0,0,0,0,0 },//1
	{ 3,0,0,0,0,0,0,0,0 },//2
	{ 4,0,0,0,0,0,0,0,0 },//3
	{ 5,0,0,0,0,0,0,0,0 },//4     x     
	{ 6,0,0,0,0,0,0,0,0 },//5
	{ 7,0,0,0,0,0,0,0,0 },//6
	{ 8,0,0,0,0,0,0,0,0 },//7
	{ 9,0,0,0,0,0,0,0,0 },//8
};
/*
//备用初始化数独图
{ 0,0,0,0,0,0,0,0,0 },//0
{ 0,0,0,0,0,0,0,0,0 },//1
{ 0,0,0,0,0,0,0,0,0 },//2
{ 0,0,0,0,0,0,0,0,0 },//3
{ 0,0,0,0,0,0,0,0,0 },//4     x     
{ 0,0,0,0,0,0,0,0,0 },//5
{ 0,0,0,0,0,0,0,0,0 },//6
{ 0,0,0,0,0,0,0,0,0 },//7
{ 0,0,0,0,0,0,0,0,0 },//8
*/
Last *(*lm)[9] = new Last*[9][9];//剩余数图
	//         y
	//n  0 1 2 3 4 5 6 7 8
	//---------------------
	//0| 0 0 0 0 0 0 0 0 0
	//1| 0 0 0 0 0 0 0 0 0
//x	//2| 0 0 0 0 0 0 0 0 0
	//3| 0 0 0 0 0 0 0 0 0
	//4| 0 0 0 0 0 0 0 0 0
	//5| 0 0 0 0 0 0 0 0 0
	//6| 0 0 0 0 0 0 0 0 0
	//7| 0 0 0 0 0 0 0 0 0
	//8| 0 0 0 0 0 0 0 0 0
Last* findV(int x, int y);//找到竖排剩余数
Last* findH(int x, int y);//找到横排剩余数
Last* findG(int x, int y);//找到九宫格内剩余数
void printLast(Last l);//输出剩余数
void resetLastMap();//初始化剩余数图
void searchMap();//遍历全图找剩余数并更新至剩余数图
void printMap();//输出图
void getSimplifyMap();//获得最简剩余数图
int checkZeroNumber();//查看当前数独图剩余0的数量
void inputMap();//输入图
int checkNoSolve();//判断无解
bool isFilled();//被填满判断
void printLastLength();//输出剩余数图长度
Point* findZeroPoint();//查找剩余图长度不为0的点
void flashBack(Point p);//回溯
int numbers = 0;
int main(void)
{
	inputMap();
	getSimplifyMap();
	cout << "=================" << endl;
	if (checkNoSolve() == 1)
	{
		cout << "无解" << endl;
	}
	else
	{
		//进行回溯
		if (isFilled() == true)
		{
			printMap();
		}
		else
		{
			Point *p = findZeroPoint();
			flashBack(*p);
		}
	}
	if (numbers >= 1)
	{
		cout << "数独总拥有" << numbers << "个结果" << endl;
	}
	else
	{
		cout << "无解" << endl;
	}
	
	system("pause");
	return 0;
}
//被填满判断
bool isFilled()
{
	for (int i = 0; i <= 8; i++)
	{
		for (int j = 0; j <= 8; j++)
		{
			if (m[i][j] == 0)
			{
				return false;
			}
		}
	}
	return true;
}
//查找剩余图长度不为0的点
Point *findZeroPoint()
{
	Point *p = new Point();
	for (int i = 0; i <= 8; i++)
	{
		for (int j = 0; j <= 8; j++)
		{
			if (lm[i][j]->length != 0)
			{
				p->x = i;
				p->y = j;
				return p;
			}
		}
	}
	return NULL;
}
//回溯
void flashBack(Point p)
{
	int g[9][9] = {};
	for (int i = 0; i <= 8; i++)
	{
		for (int j = 0; j <= 8; j++)
		{
			g[i][j] = m[i][j];
		}
	}
	for (int i = 0;i < lm[p.x][p.y]->length; i++)
	{
		m[p.x][p.y] = lm[p.x][p.y]->a[i];
		getSimplifyMap();//这里有问题
		bool isfilled = isFilled();
		if (isfilled==true)
		{
			cout << "=======================第" << numbers+1 << "个解" << endl;
			printMap();
			numbers++;
		}
		if (checkNoSolve() == 0)
		{
			Point *p1 = findZeroPoint();
			if (p1 != NULL)
			{
				flashBack(*p1);
			}
		}
		for (int i1 = 0; i1 <= 8; i1++)
		{
			for (int j1 = 0; j1 <= 8; j1++)
			{
				m[i1][j1] = g[i1][j1];
			}
		}
		getSimplifyMap();
	}

}
//输出剩余数图长度
void printLastLength()
{
	for (int i = 0; i <= 8; i++)
	{
		for (int j = 0; j <= 8; j++)
		{
			cout << lm[i][j]->length << " ";
		}
		cout << endl;
	}
}
//判断无解
int checkNoSolve()
{
	//1为无解
	//0为有解
	for (int i = 0; i <= 8; i++)
	{
		for (int j = 0; j <= 8; j++)
		{
			if (lm[i][j]->length == 0&&m[i][j]==0)
			{
				return 1;
			}
		}
	}
	return 0;
}
//输入图
void inputMap()
{
	for (int i = 0; i <= 8; i++)//           用法: 0代表空白代填数不需要任何分割符号
	{                           //           例子: 第1行:032000006
		cout << "第:" << i + 1 << "行";
		char s[20];
		cin >> s;
		for (int k = 0; k <= 8; k++)
		{
			m[i][k] = (int)(s[k] - 48);
		}
	}
}
//查看当前数独图剩余0的数量
int checkZeroNumber()
{
	int n = 0;
	for (int i = 0; i <= 8; i++)
	{
		for (int j = 0; j <= 8; j++)
		{
			if (m[i][j] == 0)
			{
				n++;
			}
		}
	}
	return n;
}
//获得最简剩余数图
void getSimplifyMap()
{
	int n = 0;
	do
	{
		resetLastMap();
		searchMap();
		n = 0;
		for (int i = 0; i <= 8; i++)
		{
			for (int j = 0; j <= 8; j++)
			{
				if (lm[i][j]->length == 1)
				{
					m[i][j] = lm[i][j]->a[0];
					resetLastMap();
					searchMap();
					n++;
				}
				
			}
		}
	} while (n != 0);
}
//输出图
void printMap() {
	for (int i = 0; i <= 8; i++)
	{
		for (int j = 0; j <= 8; j++)
		{
			cout << m[i][j] << " ";
		}
		cout << endl;
	}
}
//遍历全图找剩余数并更新至剩余数图
void searchMap()
{
	for (int i = 0; i <= 8; i++)
	{
		for (int j = 0; j <= 8; j++)
		{
			if (m[i][j] == 0)
			{
				Last *l = findV(i, j);
				Last *l1 = findH(i, j);
				Last *l2 = findG(i, j);
				//交叉运算
				Last *l3 = &(*l * (*l1) * (*l2));
				lm[i][j] = l3;
			}
		}
	}
}
//初始化剩余数图
void resetLastMap()
{
	for (int i = 0; i <= 8; i++)
	{
		for(int j = 0; j <= 8; j++)
		{
			lm[i][j] = new Last();
		}
	}
}
//输出剩余数
void printLast(Last l)
{
	for (int i = 0; i < l.length; i++)
	{
		cout << l.a[i] << " ";
	}
	cout << endl;
}
//找到竖排剩余数
Last* findV(int x, int y)
{
	Last *l = new Last();
	int *a = new int[9];
	for (int i = 0; i <= 8; i++)
	{
		a[i] = 0;
	}
	int n = 0;
	for (int j = 1; j <= 9; j++)
	{

		for (int i = 0; i < 9; i++)
		{
			if (m[i][y] == j)
			{
				break;
			}
			if (m[i][y] != j && i == 8)
			{
				a[n] = j;
				n++;
			}
		}
	}
	l->a = &a[0];
	//delete[] a;
	l->length = n;
	return l;
}
//找到横排剩余数
Last* findH(int x, int y)
{
	Last *l = new Last();
	int *a = new int[9];
	for (int i = 0; i <= 8; i++)
	{
		a[i] = 0;
	}
	int n = 0;
	for (int j = 1; j <= 9; j++)
	{

		for (int i = 0; i < 9; i++)
		{
			if (m[x][i] == j)
			{
				break;
			}
			if (m[x][i] != j && i == 8)
			{
				a[n] = j;
				n++;
			}
		}
	}
	l->a = a;
	//delete[] a;
	l->length = n;
	return l;
}
//找到九宫格内剩余数
Last* findG(int x, int y)
{
	Last *l = new Last();
	int *a = new int[9];
	int n = 0;
	//所在九宫格横竖排起始点
	int xs = 0;
	int ys = 0;
	xs = floor(x / 3) * 3;
	ys = floor(y / 3) * 3;
	//cout << xs << "," << ys << endl;
	//数字遍历
	for (int i = 1; i <= 9; i++)
	{
		bool bx = 0;
		//坐标遍历
		for (int x0 = xs; x0 <= xs + 2 && bx == 0; x0++)
		{
			for (int y0 = ys; y0 <= ys + 2; y0++)
			{
				if (m[x0][y0] == i) {
					bx = 1;
					break;
				}
				if (x0 == xs + 2 && y0 == ys + 2 && m[x0][y0] != i)
				{
					a[n] = i;
					n++;
				}
			}
		}
	}
	l->a = &a[0];
	//delete[] a;
	l->length = n;
	return l;
}
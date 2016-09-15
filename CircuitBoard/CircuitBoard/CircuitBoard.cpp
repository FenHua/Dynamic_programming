/*CircuitBoard.cpp : 定义控制台应用程序的入口点。
问题描述：在一块电路板的上、下两端分别有n个接线柱。根据电路设计，要求用
导线(i,π(i)) 将上端接线柱i与下端接线柱π(i)相连，如下图。其中，π(i),1≤ i ≤n,是｛1,2,…,n｝的
一个排列。导线(I, π(i))称为该电路板上的第i条连线。对于任何1 ≤ i ≤ j ≤n,第i条连线和第j条连线相交的充要条件是π(i)> π(j).
*/

#include "stdafx.h"
#include "iostream"
using namespace std;

const int N = 10;
void MNS(int c[], int n, int **size);
void Traceback(int c[], int**size, int n, int Net[], int&m);

int main()
{
	int c[] = { 0, 8, 7, 4, 2, 5, 1, 9, 3, 10, 6 };//下标从1开始  
	int **size = new int *[N + 1];
	for (int i = 0; i <= N; i++)
	{
		size[i] = new int[N + 1];
	}
	MNS(c, N, size);
	cout << "电路布线最大不相交连线数目为：" << size[N][N] << endl;
	int Net[N], m;
	Traceback(c, size, N, Net, m);
	cout << "最大不相交连线分别为：" << endl;
	for (int i = m - 1; i >= 0; i--)
	{
		cout << "(" << Net[i] << "," << c[Net[i]] << ")";
	}
	cout << endl;
	return 0;
}

int max(int a, int b)
{
	if (a > b)
		return a;
	else
	{
		return b;
	}
}
void MNS(int c[], int n, int**size)
{
	for (int j = 0; j < c[1]; j++)
	{
		size[1][j] = 0;
	}
	for (int j = c[1]; j <= n; j++)
	{
		size[1][j] = 1;
	}
	for (int i = 2; i < n; i++)
	{
		for (int j = 0; j < c[1]; j++)
		{
			size[i][j] = size[i - 1][j];//当i<c[i]的情形
		}
		for (int j = c[i]; j <= n; j++)
		{
			size[i][j] =max(size[i - 1][j], size[i - 1][c[i] - 1] + 1);
			//当j>=c[i]时，考虑(i,c[i])是否属于MNS(i,j)的两种情况
		}
	}
	size[n][n] = max(size[n - 1][n], size[n - 1][c[n] - 1] + 1);
}
void Traceback(int c[], int**size, int n, int Net[], int&m)
{
	int j = n;
	m = 0;
	for (int i = n; i > 1; i--)
	{
		if (size[i][j] != size[i - 1][j])
		{
			//此时，(i,c[i])是最大不相交子集的一条边
			Net[m++] = i;
			j = c[i] - 1;
		}
	}
	if (j >= c[1])
		Net[m++] = 1;//处理i=1的情形
}

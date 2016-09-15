/*KnapSack.cpp : 定义控制台应用程序的入口点。
给定n种物品和一背包。物品i的重量是wi，其价值为vi，背包的容量为C。
问:应如何选择装入背包的物品，使得装入背包中物品的总价值最大?
问题具有最优性！
*/

#include "stdafx.h"
#include"iostream"
using namespace std;

const int N = 4;
void Knapsack(int v[],int w[],int c,int n,int m[][10]);
void Traceback(int m[][10], int w[], int c, int n, int x[]);


int main()
{
	int c = 8;
	int v[] = { 0, 2, 1, 4, 3 }, w[] = { 0, 1, 4, 2, 3 };//下标从1开始  
	int x[N + 1];
	int m[10][10];
	cout << "待装物品重物分别为：" << endl;
	for (int i = 1; i <= N; i++)
	{
		cout << w[i] << " ";
	}
	cout << endl;
	cout << "待装物品价值分别为：" << endl;
	for (int i = 1; i <= N; i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;
	Knapsack(v, w, c, N, m);
	cout << "背包能装的最大价值为：" << m[1][c] << endl;
	Traceback(m,w,c,N,x);
	cout << "背包装下的物品编号为：" << endl;
	for (int i = 1; i <= N; i++)
	{
		if (x[i] == 1)
		{
			cout << i << " ";
		}
	}
	cout << endl;
	return 0;
}

int min(int a, int b)
{
	if (a > b)
	{
		return b;
	}
	else
	{
		return a;
	}
}
int max(int a, int b)
{
	if (a > b)
	{
		return a;
	}
	else
	{
		return b;
	}
}
void Knapsack(int v[], int w[], int c, int n, int m[][10])
{
	int jMax = min(w[n] - 1, c);//背包剩余容量上限，范围[0~w[n]-1]
	for (int j = 0; j <= jMax; j++)
	{
		m[n][j] = 0;
	}
	for (int j = w[n]; j <= c; j++)
	{
		//限制范围[w[n]~c]
		m[n][j] = v[n];
	}
	for (int i = n - 1; i > 1; i--)
	{
		jMax = min(w[i] - 1, c);
		for (int j = 0; j < jMax; j++)
		{
			//背包不通剩余容量j<=jMax<c
			m[i][j] = m[i + 1][j];//没产生任何效应
		}
		for (int j = w[i]; j <= c; j++)
		{
			m[i][j] = max(m[i + 1][j], m[i + 1][j - w[i]] + v[i]);//效应增长vi
		}
	}
	m[1][c] = m[2][c];
	if (c >= w[1])
	{
		m[1][c] = max(m[1][c], m[2][c - w[1]] + v[1]);
	}
}
//x[]数组存储对应物品0-1向量，0不装入背包，1表示装入背包
void Traceback(int m[][10], int w[], int c, int n, int x[])
{
	for (int i = 1; i < n; i++)
	{
		if (m[i][c] == m[i + 1][c])
		{
			x[i] = 0;
		}
		else
		{
			x[i] = 1;
			c -= w[i];
		}
	}
	x[n] = (m[n][c]) ? 1 : 0;
}
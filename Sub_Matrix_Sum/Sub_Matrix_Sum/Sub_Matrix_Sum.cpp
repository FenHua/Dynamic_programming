/*Sub_Matrix_Sum.cpp : 定义控制台应用程序的入口点。
问题描述：给定一个m行n列的整数矩阵A，试求A的一个子矩阵，时期各元素之和为最大。
容易看出，这是一维情形的最大子段和问题。因此，借助最大子段和问题的动态规划算法MaxSum
*/

#include "stdafx.h"
#include"iostream"
using namespace std;

const int M = 4;
const int N = 3;
int MaxSum(int n, int *a);
int MaxSum2(int m, int n, int a[M][N]);


int main()
{
	int a[][N] = { { 4, -2, 9 }, { -1, 3, 8 }, { -6, 7, 6 }, { 0, 9, -5 } };
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j<N; j++)
		{
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	cout << "数组a的最大连续字段和为：" << MaxSum2(M, N, a) << endl;
	return 0;
}

int MaxSum(int n, int*a)
{
	int sum = 0, b = 0;
	for (int i = 1; i <= n; i++)
	{
		if (b > 0)
		{
			b += a[i];
		}
		else
		{
			b = a[i];
		}
		if (b > sum)
		{
			sum = b;
		}
	}
	return sum;
}
int MaxSum2(int m, int n, int a[M][N])
{
	int sum = 0;
	int *b = new int[n + 1];
	for (int i = 0; i < m; i++)
	{
		//枚举行
		for (int k = 0; k < n; k++)
		{
			b[k] = 0;
		}
		for (int j = i; j < m; j++)
		{
			//枚举初始行i,结束行j
			for (int k = 0; k < n; k++)
			{
				b[k] += a[j][k];//为纵向列求和
			}
			int max = MaxSum(n, b);
			if (max>sum)
			{
				sum = max;
			}
		}
	}
	return sum;
}
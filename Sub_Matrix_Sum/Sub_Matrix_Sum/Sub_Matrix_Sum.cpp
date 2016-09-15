/*Sub_Matrix_Sum.cpp : �������̨Ӧ�ó������ڵ㡣
��������������һ��m��n�е���������A������A��һ���Ӿ���ʱ�ڸ�Ԫ��֮��Ϊ���
���׿���������һά���ε�����Ӷκ����⡣��ˣ���������Ӷκ�����Ķ�̬�滮�㷨MaxSum
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
	cout << "����a����������ֶκ�Ϊ��" << MaxSum2(M, N, a) << endl;
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
		//ö����
		for (int k = 0; k < n; k++)
		{
			b[k] = 0;
		}
		for (int j = i; j < m; j++)
		{
			//ö�ٳ�ʼ��i,������j
			for (int k = 0; k < n; k++)
			{
				b[k] += a[j][k];//Ϊ���������
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
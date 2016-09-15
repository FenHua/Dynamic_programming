/*CircuitBoard.cpp : �������̨Ӧ�ó������ڵ㡣
������������һ���·����ϡ������˷ֱ���n�������������ݵ�·��ƣ�Ҫ����
����(i,��(i)) ���϶˽�����i���¶˽�������(i)����������ͼ�����У���(i),1�� i ��n,�ǣ�1,2,��,n����
һ�����С�����(I, ��(i))��Ϊ�õ�·���ϵĵ�i�����ߡ������κ�1 �� i �� j ��n,��i�����ߺ͵�j�������ཻ�ĳ�Ҫ�����Ǧ�(i)> ��(j).
*/

#include "stdafx.h"
#include "iostream"
using namespace std;

const int N = 10;
void MNS(int c[], int n, int **size);
void Traceback(int c[], int**size, int n, int Net[], int&m);

int main()
{
	int c[] = { 0, 8, 7, 4, 2, 5, 1, 9, 3, 10, 6 };//�±��1��ʼ  
	int **size = new int *[N + 1];
	for (int i = 0; i <= N; i++)
	{
		size[i] = new int[N + 1];
	}
	MNS(c, N, size);
	cout << "��·��������ཻ������ĿΪ��" << size[N][N] << endl;
	int Net[N], m;
	Traceback(c, size, N, Net, m);
	cout << "����ཻ���߷ֱ�Ϊ��" << endl;
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
			size[i][j] = size[i - 1][j];//��i<c[i]������
		}
		for (int j = c[i]; j <= n; j++)
		{
			size[i][j] =max(size[i - 1][j], size[i - 1][c[i] - 1] + 1);
			//��j>=c[i]ʱ������(i,c[i])�Ƿ�����MNS(i,j)���������
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
			//��ʱ��(i,c[i])������ཻ�Ӽ���һ����
			Net[m++] = i;
			j = c[i] - 1;
		}
	}
	if (j >= c[1])
		Net[m++] = 1;//����i=1������
}

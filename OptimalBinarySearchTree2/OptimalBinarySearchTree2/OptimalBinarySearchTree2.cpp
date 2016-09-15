/*OptimalBinarySearchTree2.cpp : �������̨Ӧ�ó������ڵ㡣
*/

#include "stdafx.h"
#include"iostream"
using namespace std;

const int N = 3;
void OptimalBinarySearchTree(double a[], double b[], int n, double **m, int**s, double**w);
void Traceback(int n, int i, int j, int**s, int f, char ch);

int main()
{
	double a[] = { 0.15, 0.1, 0.05, 0.05 };
	double b[] = { 0.00, 0.5, 0.1, 0.05 };

	cout << "���򼯵ĸ��ʷֲ�Ϊ��" << endl;
	for (int i = 0; i<N + 1; i++)
	{
		cout << "a" << i << "=" << a[i] << ",b" << i << "=" << b[i] << endl;
	}

	double **m = new double *[N + 2];
	int **s = new int *[N + 2];
	double **w = new double *[N + 2];

	for (int i = 0; i<N + 2; i++)
	{
		m[i] = new double[N + 2];
		s[i] = new int[N + 2];
		w[i] = new double[N + 2];
	}

	OptimalBinarySearchTree(a, b, N, m, s, w);
	cout << "������������Сƽ��·��Ϊ��" << m[1][N] << endl;
	cout << "��������Ŷ�����Ϊ:" << endl;
	Traceback(N, 1, N, s, 0, '0');

	for (int i = 0; i<N + 2; i++)
	{
		delete m[i];
		delete s[i];
		delete w[i];
	}
	delete[] m;
	delete[] s;
	delete[] w;
	return 0;
}

void OptimalBinarySearchTree(double a[], double b[], int n, double**m, int**s, double**w)
{
	//��ʼ���������ڲ��ڵ�����
	for (int i = 0; i <= n; i++)
	{
		w[i + 1][i] = a[i];
		m[i + 1][i] = 0;
		s[i + 1][i] = 0;
	}
	for (int r = 0; r <= n; r++)//������ֹ�±�Ĳ�
	{
		for (int i = 1; i <= n - r; i++)//iΪ��ʼԪ���±�
		{
			int j = i + r;//jΪ��ֹԪ���±�
			int i1 = s[i][j - 1] > i ? s[i][j - 1] : i;
			int j1 = s[i + 1][j] > i ? s[i + 1][j] : j;
			//����T[i][j]��дw[i][j],m[i][j],s[i][j]
			//����i��Ϊ������������Ϊ�գ�������Ϊ�ڵ�
			w[i][j] = w[i][j - 1] + a[j] + b[j];
			m[i][j] = m[i][i1 - 1] + m[i1 + 1][j];
			s[i][j] = i1;
			/*
			��ѡi��Ϊ������kΪ�������k=i+1����������j ������Ϊ�ڵ㣺i��i+1����������k-1��������Ϊ�ڵ㣺k+1,k+2.....n
			*/
			for (int k = i1 + 1; k <= j1; k++)
			{
				double t = m[i][k - 1] + m[k + 1][j];
				if (t < m[i][j])
				{
					m[i][j] = t;
					s[i][j] = k;//��¼���ڵ�
				}
			}
			m[i][j] += w[i][j];
		}
	}
}
void Traceback(int n,int i, int j,int **s, int f, char ch)
{
	int k = s[i][j];
	if (k > 0)
	{
		if (k > 0)
		{
			//root
			cout << "Root: " << k << " (i:j):(" << i << "," << j << ")" << endl;
		}
		else
		{
			//SubTree
			cout << ch << " of " << f << ":" << k << " (i:j):(" << i << "," << j << ")" << endl;
		}
		int t = k - 1;
		if (t >= i&&t <= n)
		{
			//����������
			Traceback(n, i, t, s, k, 'L');
		}
		t = k + 1;
		if (t <= j)
		{
			//����������
			Traceback(n, t, j, s, k, 'R');
		}
	}
}
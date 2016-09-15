/*M_MaxSum.cpp : �������̨Ӧ�ó������ڵ㡣
����������������n������(����Ϊ����)��ɵ�����a1,a2,a3����an,�Լ�һ��������m,Ҫ
��ȷ�������е�m�����ཻ�Ӷε��ܺʹﵽ�������Ӷκ����������m�ֶκ����⵱m=1ʱ���������Ρ�
*/

#include "stdafx.h"
#include"iostream"
using namespace std;

int MaxSum(int m, int n, int*a);

int main()
{
	int a[] = { 0, 2, 3, -7, 6, 4, -5 };//����ű��1��ʼ  
	for (int i = 1; i <= 6; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
	cout << "����a����������Ӷκ�Ϊ:" << MaxSum(3, 6, a) << endl;
	return 0;
}
/*
int MaxSum(int m, int n, int*a)
{
	if (n < m || m < 1)
		return 0;
	int**b = new int*[m + 1];
	for (int i = 0; i <= m; i++)
	{
		b[i] = new int[n + 1];
	}
	for (int i = 0; i <= m; i++)
	{
		b[i][0] = 0;
	}
	for (int j = 1; j <= n; j++)
	{
		b[0][j] = 0;
	}
	//ö���Ӷ���Ŀ����1��ʼ��������m�����Ƴ�b[i][j]��ֵ
	for (int i = 1; i <= m; i++)
	{
		//n-m+i���Ʊ���������㣬��i=mʱ,j���Ϊn���ɾݴ˵��ƹ�ʽ
		for (int j = i; j <= n - m + i; j++)
		{
			if (j > i)
			{
				b[i][j] = b[i][j - 1] + a[j];//����a[j]��a[j-1]һ�𣬶������һ���Ӷ���
				for (int k = i - 1; k < j; k++)
				{
					if (b[i][j] < (b[i - 1][k] + a[j]))
						b[i][j] = b[i - 1][k] + a[j];//�������һ���Ӷν�����a[j]
				}
			}
			else
			{
				b[i][j] = b[i - 1][j - 1] + a[j];//��i=jʱ��ÿһ��Ϊһ�Ӷ�
			}
		}
	}
	int sum = 0;
	for (int j = m; j <= n; j++)
	{
		if (sum < b[m][j])
			sum = b[m][j];
	}
	return sum;
}
*/
int MaxSum(int m, int n, int*a)
{
	int sum = 0;
	if (n < m || m < 1)
		return 0;
	int *b = new int[n + 1];
	int*c = new int[n + 1];
	b[0] = 0;//b�����¼��i�е����i�Ӷκ�
	c[1] = 0;//c�����¼��i-1�е����i-1�Ӷκ�
	for (int i = 1; i <= m; i++)
	{
		b[i] = b[i - 1] + a[i];
		c[i - 1] = b[i];
		int max = b[i];
		//n-m+i���ƣ����Ա��������㣬��i=mʱ��j���Ϊn���ɾݴ��ƶ���������
		for (int j = i + 1; j <= i + n - m; j++)
		{
			b[i] = b[i - 1] > c[j - 1] ? b[j - 1] + a[j] : c[j - 1] + a[j];
			c[j - 1] = max;//Ԥ�ȱ����j-1�е����j-1�Ӷκ�
			if (max < b[j])
				max = b[j];
		}
		c[i + n - m] = max;
	}
	for (int j = m; j <= n; j++)
	{
		if (sum < b[j])
			sum = b[j];
	}
	return sum;
}
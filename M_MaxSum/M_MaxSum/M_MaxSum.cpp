/*M_MaxSum.cpp : 定义控制台应用程序的入口点。
问题描述：给定由n个整数(可能为负数)组成的序列a1,a2,a3……an,以及一个正整数m,要
求确定此序列的m个不相交子段的总和达到最大。最大子段和问题是最大m字段和问题当m=1时的特殊情形。
*/

#include "stdafx.h"
#include"iostream"
using namespace std;

int MaxSum(int m, int n, int*a);

int main()
{
	int a[] = { 0, 2, 3, -7, 6, 4, -5 };//数组脚标从1开始  
	for (int i = 1; i <= 6; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
	cout << "数组a的最大连续子段和为:" << MaxSum(3, 6, a) << endl;
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
	//枚举子段数目，从1开始，迭代到m，递推出b[i][j]的值
	for (int i = 1; i <= m; i++)
	{
		//n-m+i限制避免多余运算，当i=m时,j最大为n，可据此递推公式
		for (int j = i; j <= n - m + i; j++)
		{
			if (j > i)
			{
				b[i][j] = b[i][j - 1] + a[j];//代表a[j]和a[j-1]一起，都在最后一个子段中
				for (int k = i - 1; k < j; k++)
				{
					if (b[i][j] < (b[i - 1][k] + a[j]))
						b[i][j] = b[i - 1][k] + a[j];//代表最后一个子段仅包含a[j]
				}
			}
			else
			{
				b[i][j] = b[i - 1][j - 1] + a[j];//当i=j时，每一项为一子段
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
	b[0] = 0;//b数组记录第i行的最大i子段和
	c[1] = 0;//c数组记录第i-1行的最大i-1子段和
	for (int i = 1; i <= m; i++)
	{
		b[i] = b[i - 1] + a[i];
		c[i - 1] = b[i];
		int max = b[i];
		//n-m+i限制，可以避免多余计算，当i=m时，j最大为n，可据此推断所有情形
		for (int j = i + 1; j <= i + n - m; j++)
		{
			b[i] = b[i - 1] > c[j - 1] ? b[j - 1] + a[j] : c[j - 1] + a[j];
			c[j - 1] = max;//预先保存第j-1行的最大j-1子段和
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
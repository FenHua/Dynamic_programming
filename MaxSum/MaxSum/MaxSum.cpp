/*MaxSum.cpp : 定义控制台应用程序的入口点。
问题定义：对于给定序列a1,a2,a3……an,寻找它的某个连续子段，使得其和最大。
如( -2,11,-4,13,-5,-2 )最大子段是{ 11,-4,13 }其和为20。
一共(n+1)*n/2个连续子段，使用枚举
*/
#include "stdafx.h"
#include<iostream>
using namespace std;

int MaxSum(int n, int*a, int&besti, int&bestj);

int main()
{
	int a[] = { -2, 11, -4, 13, -5, -2 };
	for (int i = 0; i < 6; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
	int besti, bestj;
	cout << "数组a的最大连续子段和为：a[" << besti << ":" << bestj << "]:" << MaxSum(6, a, besti, bestj) << endl;
	return 0;
}
/*
int MaxSum(int n, int*a, int&besti, int&bestj)
{
	int sum = 0;
	for (int i = 0; i < n; i++)
	{
		//控制求和起始项
		for (int j = i; j < n; j++)
		{
			//控制求和结束项
			int thissum = 0;
			for (int k=i; k<=j; k++)
			{
				//求和
				thissum += a[k];
			}
			if (thissum>sum)
			{
				sum = thissum;
				besti = i;
				bestj = j;
			}
		}
	}
	return sum;
}
*/
int MaxSum(int n, int *a, int&besti, int&bestj)
{
	int sum = 0;
	for (int i = 0; i < n; i++)
	{
		int thissum = 0;
		for (int j = i; j < n; j++)
		{
			thissum += a[j];
			if (thissum>sum)
			{
				sum = thissum;
				besti = i;
				bestj = j;
			}
		}
	}
	return sum;
}
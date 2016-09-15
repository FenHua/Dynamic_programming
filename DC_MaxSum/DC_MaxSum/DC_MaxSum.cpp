/*DC_MaxSum.cpp : 定义控制台应用程序的入口点。
最大子段和问题的分治算法
*/
#include "stdafx.h"
#include"iostream"
using namespace std;

int MaxSubSum(int *a, int left, int right);
int MaxSum(int n,int*a);

int main()
{
	int a[] = { -2, 11, -4, 13, -5, -2 };
	for (int i = 0; i<6; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
	cout << "数组a的最大连续子段和为:" << MaxSum(6, a) << endl;
	return 0;
}
/*
int MaxSubSum(int*a, int left, int right)
{
	int sum = 0;
	if (left == right)
	{
		sum = a[left] > 0 ? a[left] : 0;
	}
	else
	{
		int center = (left + right) / 2;
		int leftsum = MaxSubSum(a, left, center);
		int rightsum = MaxSubSum(a, center + 1, right);
		int s1 = 0;
		int lefts = 0;
		for (int i = center; i >= left; i--)
		{
			lefts += a[i];
			if (lefts > s1)
			{
				s1 = lefts;
			}
		}
		int s2 = 0;
		int rights = 0;
		for (int i = center + 1; i <=right; i++)
		{
			rights += a[i];
			if (rights>s2)
			{
				s2 = rights;
			}
		}
		sum = s1 + s2;
		if (sum < leftsum)
		{
			sum = leftsum;
		}
		if (sum < rightsum)
		{
			sum = rightsum;
		}
	}
	return sum;
}
int MaxSum(int n, int*a)
{
	return MaxSubSum(a, 0, n - 1);
}
*/
/*
动态规划：由b[j]的定义知，当b[j-1]>0时，b[j]=b[j-1]+a[j]，否则b[j]=a[j]。
由此可得b[j]的动态规划递推式如下： b[j]=max{b[j-1]+a[j],a[j]},1<=j<=n。
*/
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
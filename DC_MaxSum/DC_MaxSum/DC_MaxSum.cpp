/*DC_MaxSum.cpp : �������̨Ӧ�ó������ڵ㡣
����Ӷκ�����ķ����㷨
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
	cout << "����a����������Ӷκ�Ϊ:" << MaxSum(6, a) << endl;
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
��̬�滮����b[j]�Ķ���֪����b[j-1]>0ʱ��b[j]=b[j-1]+a[j]������b[j]=a[j]��
�ɴ˿ɵ�b[j]�Ķ�̬�滮����ʽ���£� b[j]=max{b[j-1]+a[j],a[j]},1<=j<=n��
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
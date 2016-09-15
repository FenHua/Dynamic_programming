/*MaxSum.cpp : �������̨Ӧ�ó������ڵ㡣
���ⶨ�壺���ڸ�������a1,a2,a3����an,Ѱ������ĳ�������ӶΣ�ʹ��������
��( -2,11,-4,13,-5,-2 )����Ӷ���{ 11,-4,13 }���Ϊ20��
һ��(n+1)*n/2�������ӶΣ�ʹ��ö��
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
	cout << "����a����������Ӷκ�Ϊ��a[" << besti << ":" << bestj << "]:" << MaxSum(6, a, besti, bestj) << endl;
	return 0;
}
/*
int MaxSum(int n, int*a, int&besti, int&bestj)
{
	int sum = 0;
	for (int i = 0; i < n; i++)
	{
		//���������ʼ��
		for (int j = i; j < n; j++)
		{
			//������ͽ�����
			int thissum = 0;
			for (int k=i; k<=j; k++)
			{
				//���
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
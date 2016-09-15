/*MemoizedMatrixChain.cpp : 定义控制台应用程序的入口点。
备忘录方法用表格保存已解决的子问题答案，在下次需要解决此子问题时，只要简
单查看该子问题的解答，而不必重新计算。备忘录方法为每一个子问题建立一个
记录项，初始化时，该记录项存入一个特殊的值，表示该子问题尚未求解。在求解的过
程中，对每个带求的子问题，首先查看其相应的记录项。若记录项中存储的是初始化时存入
的特殊值，则表示该问题是第一次遇到，此时计算出该子问题的解，并将其保存在相应的记录项
中，以备以后查看。若记录项中存储的已不是初始化时存入的特殊值，则表示该子问题已被计算过，相应的记录项中
存储的是该子问题的解答。此时从记录项中取出该子问题的解答即可，而不必重新计算。
*/
//A1 30*35 A2 35*15 A3 15*5 A4 5*10 A5 10*20 A6 20*25  
//p[0-6]={30,35,15,5,10,20,25} 
#include "stdafx.h"
#include"iostream"
using namespace std;

const int L = 7;
int LookupChain(int i, int j, int **m, int**s, int *p);
int MemoizedMatrixChain(int n, int **m, int **s, int *p);
void Traceback(int i, int j, int**s);//构造最优解

int main()
{
	int p[L] = { 30, 35, 15, 5, 10, 20, 25 };
	int**s = new int*[L];
	int**m = new int*[L];
	for (int i = 0; i < L; i++)
	{
		s[i] = new int[L];
		m[i] = new int[L];
	}
	cout << "矩阵的最少计算次数为：" << MemoizedMatrixChain(6, m, s, p) << endl;
	cout << "矩阵最优计算次序为：" << endl;
	Traceback(1, 6, s);
	return 0;
}

int MemoizedMatrixChain(int n, int**m, int **s, int*p)
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			m[i][j] = 0;
		}
	}
	return LookupChain(1, n, m, s, p);
}
int LookupChain(int i, int j, int **m, int**s, int*p)
{
	if (m[i][j] > 0)
	{
		return m[i][j];
	}
	if (i == j)
	{
		return 0;
	}
	int u = LookupChain(i, i, m, s, p) + LookupChain(i + 1, j, m, s, p) + p[i - 1] * p[i] * p[j];
	s[i][j] = i;
	for (int k = i + 1; k < j; k++)
	{
		int t = LookupChain(i, k, m, s, p) + LookupChain(k + 1, j, m, s, p) + p[i -1] * p[k] * p[j];
		if (t < u)
		{
			u = t;
			s[i][j] = k;
		}
	}
	m[i][j] = u;
	return u;
}
void Traceback(int i, int j, int**s)
{
	if (i == j)
		return;
	Traceback(i, s[i][j], s);
	Traceback(s[i][j] + 1, j, s);
	cout << "Multiply A" << i << "," <<s[i][j];
	cout << "and A" << (s[i][j] + 1) << "," << j << endl;
}

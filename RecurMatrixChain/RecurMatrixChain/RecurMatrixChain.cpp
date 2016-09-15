/*RecurMatrixChain.cpp : 定义控制台应用程序的入口点。
矩阵连乘
若将对应m[i][j]的断开位置k记为s[i][j]，在计算出最优值m[i][j]后，可
递归地由s[i][j]构造出相应的最优解。s[i][j]中的数表明，计算矩阵链A[i:j]的
最佳方式应在矩阵Ak和Ak+1之间断开，即最优的加括号方式应为(A[i:k])(A[k+1:j)。
因此，从s[1][n]记录的信息可知计算A[1:n]的最优加括号方式为(A[1:s[1][n]])(A[s[1][n]+1:n])，进
一步递推，A[1:s[1][n]]的最优加括号方式为(A[1:s[1][s[1][n]]])(A[s[1][s[1][n]]+1:s[1][s[1][n]]])。
同理可以确定A[s[1][n]+1:n]的最优加括号方式在s[s[1][n]+1][n]处断开...照此递推下去，最
终可以确定A[1:n]的最优完全加括号方式，及构造出问题的一个最优解。
*/
//A1 30*35 A2 35*15 A3 15*5 A4 5*10 A5 10*20 A6 20*25 
//p[0-6]={30,35,15,5,10,20,25}
#include "stdafx.h"
#include<iostream>
using namespace std;
const int L = 7;
int RecurMatrixChain(int i, int j, int**s, int *p);//递归求解最优解
void Traceback(int i, int j, int **s);//构造最优解



int main()
{
	int p[L] = { 30, 35, 15, 5, 10, 20, 25 };
	int**s = new int *[L];
	for (int i = 0; i < L; i++)
	{
		s[i] = new int[L];
	}
	cout << "矩阵的最少计算次数为：" << RecurMatrixChain(1, 6, s, p) << endl;
	cout << "矩阵的最优计算次序：" << endl;
	Traceback(1, 6, s);
	return 0;
}

int RecurMatrixChain(int i, int j, int **s, int *p)
{
	if (i == j)
		return 0;
	int u = RecurMatrixChain(i, i, s, p) + RecurMatrixChain(i + 1, j, s, p) + p[i - 1] * p[i] * p[j];
	s[i][j] = i;
	for (int k = i + 1; k < j; k++)
	{
		int t = RecurMatrixChain(i, k, s, p) + RecurMatrixChain(k + 1, j, s, p) + p[i - 1] * p[k] * p[j];
		if (t < u)
		{
			u = t;
			s[i][j] = k;
		}
	}
	return u;
}
void Traceback(int i, int j, int **s)
{
	if (i == j)
		return;
	Traceback(i, s[i][j], s);
	Traceback(s[i][j] + 1, j, s);
	cout << "Multiply A" << i << "," << s[i][j];
	cout << "and A" << (s[i][j] + 1) << "," << j << endl;
}
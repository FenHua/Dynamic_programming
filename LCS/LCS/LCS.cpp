/*LCS.cpp : 定义控制台应用程序的入口点。
       一个给定序列的子序列是在该序列中删去若干元素后得到的序列。
确切地说，若给定序列X= { x1, x2,…, xm}，则另一序列Z= {z1, z2,…, zk}
是X的子序列是指存在一个严格递增的下标序列 {i1, i2,…, ik}，使得对于所
有j=1,2,…,k有 Xij=Zj。例如，序列Z={B,C,D,B}是序列X={A,B,C,B,D,A,B}的
子序列，相应的递增下标序列为{2,3,5,7}。给定两个序列X和Y，当另一序列Z既是
X的子序列又是Y的子序列时，称Z是序列X和Y的公共子序列。例如，若X=
{ A, B, C, B, D, A, B}和Y= {B, D, C, A, B, A}，则序列{B,C,A}是X和Y的一个公
共子序列，序列{B,C,B,A}也是X和Y的一个公共子序列。而且，后者是X和Y的一
个最长公共子序列，因为X和Y没有长度大于4的公共子序列。给定两个序列X= {x1, x2, …, xm}
和Y= {y1, y2, … , yn}，要求找出X和Y的一个最长公共子序列。
      Xi={x1,x2……xi}，Yj={y1,y2……yj}。当i=0或j=0时，空序列是xi和yj的最长公共子序列。
此时，c[i][j]=0；当i,j>0，xi=yj时，c[i][j]=c[i-1][j-1]+1；当i,j>0，xi!=yj时，c[i][j]=max{c[i][j-1],c[i-1][j]}
*/

#include "stdafx.h"
#include"iostream"
using namespace std;

const int M = 7;
const int N = 6;

void output(char*s, int n);
void LCSLength(int m, int n, char*x, char*y, int**c, int**b);
void LCS(int i, int j, char*x, int**b);


int main()
{
	char x[] = { ' ', 'A', 'B', 'C', 'B', 'D', 'A', 'B' };
	char y[] = { ' ', 'B', 'D', 'C', 'A', 'B', 'A' };
	int **c = new int*[M + 1];
	int**b = new int*[M + 1];
	for (int i = 0; i <= M; i++)
	{
		c[i] = new int[N + 1];
		b[i] = new int[N + 1];
	}
	cout << "序列X：" << endl;
	output(x, M);
	cout << "序列Y：" << endl;
	output(y, N);
	LCSLength(M, N, x, y, c, b);
	cout << "序列X,Y最长公共序列长度为：" << c[M][N] << endl;
	cout << "序列X,Y最长公共子序列为：" << endl;
	LCS(M, N, x, b);
	cout << endl;
	return 0;
}

void output(char*s, int n)
{
	for (int i = 1; i <= n; i++)
	{
		cout << s[i] << " ";
	}
	cout << endl;
}
void LCSLength(int m, int n, char*x, char*y, int**c, int **b)
{
	int i, j;
	for (i = 1; i <= m; i++)
	{
		c[i][0] = 0;
	}
	for (i = 1; i <= n; i++)
	{
		c[0][i] = 0;
	}
	for (i = 1; i <= m; i++)
	{
		for (j = 1; j<= n; j++)
		{
			if (x[i] == y[j])
			{
				c[i][j] = c[i - 1][j - 1] + 1;
				b[i][j] = 1;
			}
			else if (c[i - 1][j] >= c[i][j - 1])
			{
				c[i][j] = c[i - 1][j];
				b[i][j] = 2;
			}
			else
			{
				c[i][j] = c[i][j - 1];
				b[i][j] = 3;
			}
		}
	}
}
void LCS(int i, int j, char*x, int**b)
{
	if (i == 0 || j == 0)
	{
		return;
	}
	if (b[i][j] == 1)
	{
		LCS(i - 1, j - 1, x, b);
		cout << x[i] << " ";
	}
	else if (b[i][j] == 2)
	{
		LCS(i - 1, j, x, b);
	}
	else
	{
		LCS(i, j - 1, x, b);
	}
}
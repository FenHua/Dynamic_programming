/*P_LCS.cpp : 定义控制台应用程序的入口点。
按照一般的算法设计策略设计出的算法，往往在算法的时间和
空间需求上还可以改进。这种改进，通常是利用具体问题的一些
特殊性。例如，在算法LCS_length和LCS中，可进一步将数组b省去。
事实上，数组元素c[i,j]的值仅由c[i-1][j-1]，c[i-1][j]和c[i][j-1]三个值之一确定，而
数组元素b[i][j]也只是用来指示c[i][j]究竟由哪个值确定。因此，在算法LCS中，我
们可以不借助于数组b而借助于数组c本身临时判断c[i][j]的值是由c[i-1][j-1]，c[i-1][j]和
c[i][j-1]中哪一个数值元素所确定，代价是Ο(1)时间。既然b对于算法LCS不是必要的，那
么算法LCS_length便不必保存它。这一来，可节省θ(mn)的空间，而LCS_length和LCS所需
要的时间分别仍然是Ο(mn)和Ο(m+n)。另外，如果只需要计算最长公共子序列的长度，则
算法的空间需求还可大大减少。事实上，在计算c[i][j]时，只用到数组c的第i行和第i-1行。
因此，只要用2行的数组空间就可以计算出最长公共子序列的长度。
更进一步的分析还可将空间需求减至min(m, n)。
*/

#include "stdafx.h"
#include"iostream"
using namespace std;

const int M = 7;
const int N = 6;

void output(char*s, int n);
void LCSLength(int m, int n, char*x, char*y, int**c);
void LCS(int i, int j, char*x, int**c);

int main()
{
	char x[] = { ' ', 'A', 'B', 'C', 'B', 'D', 'A', 'B' };
	char y[] = { ' ', 'B', 'D', 'C', 'A', 'B', 'A' };
	int**c = new int*[M + 1];
	for (int i = 0; i <= M; i++)
	{
		c[i] = new int[N + 1];
	}
	cout << "序列X为：" << endl;
	output(x, M);
	cout << "序列Y为：" << endl;
	output(y, N);
	LCSLength(M, N, x, y, c);
	cout << "序列X,Y最长公共子序列长度为：" << c[M][N] << endl;
	cout << "序列X,Y最长公共子序列为：" << endl;
	LCS(M, N, x, c);
	cout << endl;
	return 0;
}

void output(char *s, int n)
{
	for (int i = 1; i <= n; i++)
	{
		cout << s[i] << " ";
	}
	cout << endl;
}
void LCSLength(int m, int n, char*x, char*y, int**c)
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
		for (j = 1; j <= n; j++)
		{
			if (x[i] ==y[j])
			{
				c[i][j] = c[i - 1][j - 1] + 1;
			}
			else if (c[i - 1][j] >= c[i][j - 1])
			{
				c[i][j] = c[i - 1][j];
			}
			else
			{
				c[i][j] = c[i][j - 1];
			}
		}
	}
}
void LCS(int i, int j, char*x, int**c)
{
	if (i == 0 || j == 0)
	{
		return;
	}
	if (c[i][j] == c[i - 1][j - 1] + 1)
	{
		LCS(i - 1, j - 1, x, c);
		cout << x[i] << " ";
	}
	else if (c[i - 1][j] >= c[i][j - 1])
	{
		LCS(i - 1, j, x, c);
	}
	else
	{
		LCS(i, j - 1, x, c);
	}
}
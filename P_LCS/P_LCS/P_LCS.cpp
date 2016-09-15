/*P_LCS.cpp : �������̨Ӧ�ó������ڵ㡣
����һ����㷨��Ʋ�����Ƴ����㷨���������㷨��ʱ���
�ռ������ϻ����ԸĽ������ָĽ���ͨ�������þ��������һЩ
�����ԡ����磬���㷨LCS_length��LCS�У��ɽ�һ��������bʡȥ��
��ʵ�ϣ�����Ԫ��c[i,j]��ֵ����c[i-1][j-1]��c[i-1][j]��c[i][j-1]����ֵ֮һȷ������
����Ԫ��b[i][j]Ҳֻ������ָʾc[i][j]�������ĸ�ֵȷ������ˣ����㷨LCS�У���
�ǿ��Բ�����������b������������c������ʱ�ж�c[i][j]��ֵ����c[i-1][j-1]��c[i-1][j]��
c[i][j-1]����һ����ֵԪ����ȷ���������Ǧ�(1)ʱ�䡣��Ȼb�����㷨LCS���Ǳ�Ҫ�ģ���
ô�㷨LCS_length�㲻�ر���������һ�����ɽ�ʡ��(mn)�Ŀռ䣬��LCS_length��LCS����
Ҫ��ʱ��ֱ���Ȼ�Ǧ�(mn)�ͦ�(m+n)�����⣬���ֻ��Ҫ��������������еĳ��ȣ���
�㷨�Ŀռ����󻹿ɴ����١���ʵ�ϣ��ڼ���c[i][j]ʱ��ֻ�õ�����c�ĵ�i�к͵�i-1�С�
��ˣ�ֻҪ��2�е�����ռ�Ϳ��Լ��������������еĳ��ȡ�
����һ���ķ������ɽ��ռ��������min(m, n)��
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
	cout << "����XΪ��" << endl;
	output(x, M);
	cout << "����YΪ��" << endl;
	output(y, N);
	LCSLength(M, N, x, y, c);
	cout << "����X,Y����������г���Ϊ��" << c[M][N] << endl;
	cout << "����X,Y�����������Ϊ��" << endl;
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
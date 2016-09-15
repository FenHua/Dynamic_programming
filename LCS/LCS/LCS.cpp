/*LCS.cpp : �������̨Ӧ�ó������ڵ㡣
       һ���������е����������ڸ�������ɾȥ����Ԫ�غ�õ������С�
ȷ�е�˵������������X= { x1, x2,��, xm}������һ����Z= {z1, z2,��, zk}
��X����������ָ����һ���ϸ�������±����� {i1, i2,��, ik}��ʹ�ö�����
��j=1,2,��,k�� Xij=Zj�����磬����Z={B,C,D,B}������X={A,B,C,B,D,A,B}��
�����У���Ӧ�ĵ����±�����Ϊ{2,3,5,7}��������������X��Y������һ����Z����
X������������Y��������ʱ����Z������X��Y�Ĺ��������С����磬��X=
{ A, B, C, B, D, A, B}��Y= {B, D, C, A, B, A}��������{B,C,A}��X��Y��һ����
�������У�����{B,C,B,A}Ҳ��X��Y��һ�����������С����ң�������X��Y��һ
������������У���ΪX��Yû�г��ȴ���4�Ĺ��������С�������������X= {x1, x2, ��, xm}
��Y= {y1, y2, �� , yn}��Ҫ���ҳ�X��Y��һ������������С�
      Xi={x1,x2����xi}��Yj={y1,y2����yj}����i=0��j=0ʱ����������xi��yj������������С�
��ʱ��c[i][j]=0����i,j>0��xi=yjʱ��c[i][j]=c[i-1][j-1]+1����i,j>0��xi!=yjʱ��c[i][j]=max{c[i][j-1],c[i-1][j]}
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
	cout << "����X��" << endl;
	output(x, M);
	cout << "����Y��" << endl;
	output(y, N);
	LCSLength(M, N, x, y, c, b);
	cout << "����X,Y��������г���Ϊ��" << c[M][N] << endl;
	cout << "����X,Y�����������Ϊ��" << endl;
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
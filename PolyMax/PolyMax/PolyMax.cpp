/*PolyMax.cpp : 定义控制台应用程序的入口点。
给定N个顶点的多边形，每个顶点标有一个整数，每条边上标有+(加)或
是×(乘)号，并且N条边按照顺时针依次编号为1~N
游戏规则 ：(1) 首先，移走一条边。 (2) 然后进行下面的操作： 选中一条边E，该边
有两个相邻的顶点，不妨称为V1和V2。对V1和V2顶点所标的整数按照E上所标运算
符号(+或是×)进行运算，得到一个整数；用该整数标注一个新顶点，该顶点代替V1和V2 。 
持续进行此操作，直到最后没有边存在，即只剩下一个顶点。该顶点的整数称为此次游戏的得分(Score)。
*/

#include "stdafx.h"
#include"iostream"
using namespace std;
#define NMAX 100
int N, m[NMAX + 1][NMAX + 1][2], v[NMAX + 1];
char op[NMAX + 1];
void MinMax(int n, int i, int s, int j, int&minf, int&maxf);
int PloyMax(int n, int&p);

int main()
{
	int p;
	cout << "请输入多边形顶点数：" << endl;
	cin >> N;
	for (int i = 1; i <= N; i++)
	{
		cout << "请输入多边形顶点" << i << "数值：" << endl;
		cin >> v[i];
		m[i][1][0] = v[i];
		m[i][1][1] = v[i];
		cout << "请输入多边形边" << i << "运算符：" << endl;
		cin >> op[i];
	}
	cout << "多边形游戏首次删除第" << p << "条边，结果为：" << PloyMax(N, p) << endl;
	return 0;
}

void MinMax(int n, int i, int s, int j, int&minf, int&maxf)
{
	int e[5];
	int a = m[i][s][0], b = m[i][s][1];
	int r = (i + s - 1) % n + 1;//多边形的实际顶点编号
	int c = m[r][j - s][0], d = m[r][j - s][1];
	if (op[r - 1] == '+')
	{
		minf = a + c;
		maxf = b + d;
	}
	else
	{
		e[1] = a*c;
		e[2] = a*d;
		e[3] = b*c;
		e[4] = d*b;
		minf = e[1];
		maxf = e[1];
		for (int r = 2; r < N; r++)
		{
			if (minf>e[r])
				minf = e[r];
			if (maxf < e[r])
				maxf = e[r];
		}
	}
}
int PloyMax(int n, int&p)
{
	int minf, maxf;
	for (int j = 2; j <= n; j++)
	{
		//迭代链的长度
		for (int i = 1; i <= n; i++)
		{
			//迭代首次删除的第i条边
			for (int s = 1; s < j; s++)
			{
				//迭代断开的位置
				MinMax(n, i, s, j, minf, maxf);
				if (m[i][j][0]>minf)
					m[i][j][0] = minf;
				if (m[i][j][1] < maxf)
					m[i][j][1] = maxf;
			}
		}
	}
	int temp = m[1][n][1];
	p = 1;
	for (int i = 2; i <= n; i++)
	{
		if (temp < m[i][n][1])
		{
			temp = m[i][n][1];
			p = i;
		}
	}
	return temp;
}
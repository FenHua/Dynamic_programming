/*MinWeightTriangulation.cpp : 定义控制台应用程序的入口点。
凸多边形的三角剖分：将凸多边形分割成互不相交的三角形的弦的集合T。
若凸(n+1)边形P={V0,V1……Vn}的最优三角剖分T包含三角形V0VkVn,1<=k<=n，则T的权为
三个部分权之和：三角形V0VkVn的权，多边形{V0,V1……Vk}的权和多边形{Vk,Vk+1……Vn}的权之和。
可以断言，由T确定的这两个子多边形的三角剖分也是最优的。因为若有{V0,V1……Vk}和{V0,V1……Vk}更小权的三角剖
分，将导致T不是最优三角剖分的矛盾。因此，凸多边形的三角剖分问题具有最优子结构性质。
*/

#include "stdafx.h"
#include"iostream"
using namespace std;

const int N = 7;//凸多边形边数+1
int weight[][N] = { { 0, 2, 2, 3, 1, 4 }, { 2, 0, 1, 5, 2, 3 }, { 2, 1, 0, 2, 1, 4 }, { 3, 5, 2, 0, 6, 2 }, { 1, 2, 1, 6, 0, 1 }, { 4, 3, 4, 2, 1, 0 } };//凸多边形的权  
int MinWeightTriangulation(int n, int **t, int **s);
void Traceback(int i, int j, int**s);//构造最优解
int Weight(int a, int b, int c);//权函数

int main()
{
	int **s = new int *[N];
	int **t = new int *[N];
	for (int i = 0; i<N; i++)
	{
		s[i] = new int[N];
		t[i] = new int[N];
	}
	cout << "此多边形的最优三角剖分值为：" << MinWeightTriangulation(N - 1, t, s) << endl;
	cout << "最优三角剖分结构为：" << endl;
	Traceback(1, 5, s);//s[i][j]记录了vi-1和vj构成的三角形的三个顶点的位置
	return 0;
}

int MinWeightTriangulation(int n, int**t, int**s)
{
	for (int i = 1; i <= n; i++)
	{
		t[i][i] = 0;
	}
	for (int r = 2; r <= n; r++)
	{
		//r为当前计算的链长（子问题规模）
		for (int i = 0; i < n - r + 1; i++)
		{
			//n-r+1为最后一个r链的前边界
			int j = i + r - 1;//计算前边界为r，链长为r的链的后边界
			t[i][j] = t[i + 1][j] + Weight(i - 1, i, j);//将链ij划分为A(i)*(A[i+1:j])，这里实际上就是k=i
			s[i][j] = i;
			for (int k = i + 1; k < j; k++)
			{
				//将链ij划分为(A[i:k])*(A[k+1:j])
				int u = t[i][k] + t[k + 1][j] + Weight(i - 1, k, j);
				if (u < t[i][j])
				{
					t[i][j] = u;
					s[i][j] = k;
				}
			}
		}
	}
	return t[1][N - 2];
}
void Traceback(int i, int j, int**s)
{
	if (i == j)
		return;
	Traceback(i, s[i][j], s);
	Traceback(s[i][j] + 1, j, s);
	cout << "三角剖分顶点：V" << i - 1 << ",V" << j << ",V" << s[i][j] << endl;
}
int Weight(int a, int b, int c)
{
	return weight[a][b] + weight[b][c] + weight[a][c];
}
/*MinDistance.cpp : 定义控制台应用程序的入口点。
深度优先遍历解决图遍历问题
*/

#include "stdafx.h"
#include"iostream"
#include<fstream>
#include<string>
using namespace std;

ifstream fin("in.txt");
#define maxLength 20
int matrix[maxLength][maxLength];//有向图的邻接表
int minPath[maxLength];//存储每个节点到最终点的最短路径
int trace[maxLength];//记录最短路径
string Node[maxLength] = { "A", "B1", "B2", "C1", "C2", "C3", "C4", "D1", "D2", "D3", "E" };//节点标记
int v_n;//节点个数
int MinDistance(int v);

/*
int main()
{
	fin >> v_n;
	for (int i = 0; i < v_n; i++)
	{
		for (int j = 0; j < v_n; j++)
		{
			fin >> matrix[i][j];
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	memset(trace, 0, sizeof(int)*maxLength);
	int minD = MinDistance(0);
	cout << "最短路径：" << minD << endl;
	int k = 0;
	cout << Node[0] << "->";
	while (minD > 0)
	{
		cout << Node[trace[k]] << "->";
		minD = minD - matrix[k][trace[k]];
		k = trace[k];
	}
	cout << endl;
	return 0;
}

int MinDistance(int v)
{
	if (v == v_n - 1)
		return 0;//边界值
	int min = 1000, t, j;
	for (int i = v + 1; i < v_n; i++)
	{
		if (matrix[v][i]>0)
		{
			t = matrix[v][i] + MinDistance(i);
			if (min > t)
			{
				min = t;
				j = i;
			}
		}
		trace[v] = j;
		return min;
	}
}
*/
/*
每次除了已经访问过的城市外，其他城市都要访问，所以时间复杂度为O(n!)，
这是一个“指数级”的算法，那么，还有没有更好的算法呢？首先，我们来观察
一下这个算法。在求从B1到E的最短距离的时候，先求出从C2到E的最短距离；而
在求从B2到E的最短距离的时候，又求了一遍从C2到E的最短距离。也就是说，从C2到E的最
短距离我们求了两遍。同样可以发现，在求从C1、C2到E的最短距离的过程中，从D1
到E的最短距离也被求了两遍。而在整个程序中，从D1到E的最短距离被求了四遍。如果在求
解的过程中，同时将求得的最短距离"记录在案"，随时调用，就可以避免这种情况。于是，可以
改进该算法，将每次求出的从v到E的最短距离记录下来，在算法中递归地求MinDistance(v)时
先检查以前是否已经求过了MinDistance(v)，如果求过了则不用重新求一遍，只要查找以前的记录
就可以了。这样，由于所有的点有n个，
因此不同的状态数目有n个，该算法的数量级为O(n)。
*/
int main()
{
	fin >> v_n;
	for (int i = 0; i < v_n; i++)
	{
		for (int j = 0; j < v_n; j++)
		{
			fin >> matrix[i][j];
			cout << matrix[i][j]<<" ";
		}
		cout << endl;
	}
	memset(minPath, 0, sizeof(int)*maxLength);
	memset(trace, 0, sizeof(int)*maxLength);
	int minD = MinDistance(0);
	cout << "最短路径为：" <<minD<< endl;
	int k = 0;
	cout << Node[0] << "->";
	while (minD > 0)
	{
		cout << Node[trace[k]] << "->";
		minD = minD - matrix[k][trace[k]];
		k = trace[k];
	}
	cout << endl;
	return 0;
}
 
int MinDistance(int v)
{
	if (minPath[v] > 0)
		return minPath[v];
	if (v = v_n - 1)
		return 0;//边界值
	int min = 1000, t, j;
	for (int i = v + 1; i < v_n; i++)
	{
		if (matrix[v][i]>0)
		{
			t = matrix[v][i] + MinDistance(i);
			if (min > t)
			{
				min = t;
				j = i;
			}
		}
	}
	minPath[v] = min;
	trace[v] = j;
	return minPath[v];
}
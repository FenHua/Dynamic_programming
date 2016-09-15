/*MinDistance.cpp : �������̨Ӧ�ó������ڵ㡣
������ȱ������ͼ��������
*/

#include "stdafx.h"
#include"iostream"
#include<fstream>
#include<string>
using namespace std;

ifstream fin("in.txt");
#define maxLength 20
int matrix[maxLength][maxLength];//����ͼ���ڽӱ�
int minPath[maxLength];//�洢ÿ���ڵ㵽���յ�����·��
int trace[maxLength];//��¼���·��
string Node[maxLength] = { "A", "B1", "B2", "C1", "C2", "C3", "C4", "D1", "D2", "D3", "E" };//�ڵ���
int v_n;//�ڵ����
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
	cout << "���·����" << minD << endl;
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
		return 0;//�߽�ֵ
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
ÿ�γ����Ѿ����ʹ��ĳ����⣬�������ж�Ҫ���ʣ�����ʱ�临�Ӷ�ΪO(n!)��
����һ����ָ���������㷨����ô������û�и��õ��㷨�أ����ȣ��������۲�
һ������㷨�������B1��E����̾����ʱ���������C2��E����̾��룻��
�����B2��E����̾����ʱ��������һ���C2��E����̾��롣Ҳ����˵����C2��E����
�̾��������������顣ͬ�����Է��֣������C1��C2��E����̾���Ĺ����У���D1
��E����̾���Ҳ���������顣�������������У���D1��E����̾��뱻�����ı顣�������
��Ĺ����У�ͬʱ����õ���̾���"��¼�ڰ�"����ʱ���ã��Ϳ��Ա���������������ǣ�����
�Ľ����㷨����ÿ������Ĵ�v��E����̾����¼���������㷨�еݹ����MinDistance(v)ʱ
�ȼ����ǰ�Ƿ��Ѿ������MinDistance(v)��������������������һ�飬ֻҪ������ǰ�ļ�¼
�Ϳ����ˡ��������������еĵ���n����
��˲�ͬ��״̬��Ŀ��n�������㷨��������ΪO(n)��
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
	cout << "���·��Ϊ��" <<minD<< endl;
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
		return 0;//�߽�ֵ
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
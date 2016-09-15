/*RecurMatrixChain.cpp : �������̨Ӧ�ó������ڵ㡣
��������
������Ӧm[i][j]�ĶϿ�λ��k��Ϊs[i][j]���ڼ��������ֵm[i][j]�󣬿�
�ݹ����s[i][j]�������Ӧ�����Ž⡣s[i][j]�е������������������A[i:j]��
��ѷ�ʽӦ�ھ���Ak��Ak+1֮��Ͽ��������ŵļ����ŷ�ʽӦΪ(A[i:k])(A[k+1:j)��
��ˣ���s[1][n]��¼����Ϣ��֪����A[1:n]�����ż����ŷ�ʽΪ(A[1:s[1][n]])(A[s[1][n]+1:n])����
һ�����ƣ�A[1:s[1][n]]�����ż����ŷ�ʽΪ(A[1:s[1][s[1][n]]])(A[s[1][s[1][n]]+1:s[1][s[1][n]]])��
ͬ�����ȷ��A[s[1][n]+1:n]�����ż����ŷ�ʽ��s[s[1][n]+1][n]���Ͽ�...�մ˵�����ȥ����
�տ���ȷ��A[1:n]��������ȫ�����ŷ�ʽ��������������һ�����Ž⡣
*/
//A1 30*35 A2 35*15 A3 15*5 A4 5*10 A5 10*20 A6 20*25 
//p[0-6]={30,35,15,5,10,20,25}
#include "stdafx.h"
#include<iostream>
using namespace std;
const int L = 7;
int RecurMatrixChain(int i, int j, int**s, int *p);//�ݹ�������Ž�
void Traceback(int i, int j, int **s);//�������Ž�



int main()
{
	int p[L] = { 30, 35, 15, 5, 10, 20, 25 };
	int**s = new int *[L];
	for (int i = 0; i < L; i++)
	{
		s[i] = new int[L];
	}
	cout << "��������ټ������Ϊ��" << RecurMatrixChain(1, 6, s, p) << endl;
	cout << "��������ż������" << endl;
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
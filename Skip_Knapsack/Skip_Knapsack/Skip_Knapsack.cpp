/*Skip_Knapsack.cpp : �������̨Ӧ�ó������ڵ㡣
��m(i,j)�ĵݹ�ʽ����֤������һ������£���ÿһ��ȷ����i(1��i��n)������m(i,j)�ǹ��ڱ���j�Ľ���״��������������
��Ծ������һ�ຯ����������������һ������£�����m(i,j)����ȫ����Ծ��Ψһȷ����
����m(i,j)���ɺ���m(i+1,j)�뺯��m(i+1,j-wi)+vi��max����õ��ġ���ˣ�����m(i,j)��ȫ����Ծ�������
����m(i+1��j)����Ծ�㼯p[i+1]�뺯��m(i+1��j-wi)+vi����Ծ�㼯q[i+1]�Ĳ����С���֪��(s,t)��q[i+1]����
����wi<=s<=c��(s-wi,t-vi)��p[i+1]����ˣ�������p[i+1]ȷ����Ծ�㼯q[i+1]���£�
q[i+1]=p[i+1]��(wi,vi)={(j+wi,m(i,j)+vi)|(j,m(i,j))��p[i+1]}
��һ���棬��(a��b)��(c��d)��p[i+1]��q[i+1]�е�2����Ծ�㣬��c>=a��d<bʱ��(c��d)
�ܿ���(a��b)���Ӷ�(c��d)����p[i]�е���Ծ�㡣���ܿ���Ծ���⣬p[i+1]��q[i+1]�е�������Ծ���
Ϊp[i]�е���Ծ�㡣�ɴ˿ɼ����ڵݹ���ɱ�p[i+1]�����p[i]ʱ��������p[i+1]�����q[i+1]��Ȼ���
����p[i+1]�ͱ�q[i+1]����������е��ܿ���Ծ��õ���p[i]��
*/

#include "stdafx.h"
#include"iostream"
using namespace std;

const int N = 4;
template<class type>int Knapsack(int n, type c,type v[], type w[], int**p, int x[]);
template<class type>void Traceback(int n, type w[], type v[], type**p, int *head, int x[]);

int main()
{
	int c = 8;
	int v[] = { 0, 2, 1, 4, 3 }, w[] = { 0, 1, 4, 2, 3 };//�±��1��ʼ  
	int x[N + 1];

	int **p = new int *[50];
	for (int i = 0; i<50; i++)
	{
		p[i] = new int[2];
	}

	cout << "��װ��Ʒ�����ֱ�Ϊ��" << endl;
	for (int i = 1; i <= N; i++)
	{
		cout << w[i] << " ";
	}
	cout << endl;

	cout << "��װ��Ʒ��ֵ�ֱ�Ϊ��" << endl;
	for (int i = 1; i <= N; i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;

	cout << "������װ������ֵΪ��" << Knapsack(N, c, v, w, p, x) << endl;

	cout << "����װ�µ���Ʒ���Ϊ��" << endl;
	for (int i = 1; i <= N; i++)
	{
		if (x[i] == 1)
		{
			cout << i << " ";
		}
	}
	cout << endl;

	for (int i = 0; i<50; i++)
	{
		delete p[i];
	}

	delete[] p;
	return 0;
}

template<class type>int Knapsack(int n, type c, type v[], type w[], int **p, int x[])
{
	int *head = new int[n + 2];
	head[n + 1] = 0;
	p[0][0] = 0;//p[][0]�洢��Ʒ������
	p[0][1] = 0;//p[][1]�洢��Ʒ�ļ�ֵ����Ʒn����Ծ��(0,0)
	//leftָ��p[i+1]�ĵ�һ����Ծ�㣬rightָ�����һ��
	int left = 0, right = 0, next = 1;//next����һ��Ҫ��ŵ�λ��
	head[n] = 1;//head[n]ָ���n����Ʒ��һ����Ծ���λ��
	for (int i = n; i >= 1; i--)
	{
		int k = left;//kָ��p[]����Ծ�㣬�ƶ�k���ж�p[]��p[]+(w,v)�е��ܿص�
		for (int j = left; j <= right; j++)
		{
			if (p[j][0] + w[i] > c)
				break;//ʣ��ռ䲻����װ��i���˳�forѭ��
			type y = p[j][0] + w[i], m = p[j][1] + v[i];//����p[]+(w,v)
			//��p[k][0]��С��(p[k][0] p[k][1])һ�������ܿص㣬������Ϊp[i]����Ծ��洢
			while ((k <= right) && (p[k][0] < y))
			{
				p[next][0] = p[k][0];
				p[next++][1] = p[k++][1];
			}
			//���p[k][0]==y��m<p[k][1],��(y m)Ϊ�ܿص㲻��
			if (k <= right&&p[k][0] == y)
			{
				if (m < p[k][1])
				{
					//��(p[k][0] p[k][1])�����ж�
					m = p[k][1];
				}
				k++;
			}
			//��p[k][0]>=y��m>=p[k][1],�ж��ǲ��ǵ�ǰi�����һ����Ծ����ܿص�
			//��������Ϊi����Ծ��洢
			if (m>p[next - 1][1])
			{
				p[next][0] = y;
				p[next++][1] = m;
			}
			//���ǣ������һ��Ԫ�ؽ����ж�
			while (k <= right&&p[k][1] <= p[next - 1][1])
			{
				k++;
			}
		}
		while (k <= right)
		{
			p[next][0] = p[k][0];
			p[next++][1] = p[k++][1];//��i+1ʣ�µ���Ծ����Ϊi����Ծ��洢
		}
		left = right + 1;
		right = next - 1;
		//��i-1����Ʒ��һ����Ծ���λ��head[0]ָ��0����Ʒ��һ����Ծ���λ��
		head[i - 1] = next;
	}
	Traceback(n, w, v, p, head, x);
	return p[next - 1][1];
}
//x[]����洢��Ӧ��Ʒ0-1������0��װ�룬1��ʾװ�뱳��
template<class type>void Traceback(int n, type w[], type v[], type**p, int *head, int x[])
{
	//��ʼ��j��mΪ���һ����Ծ���Ӧ�ĵ�0���Լ���1��
	type j = p[head[0] - 1][0], m = p[head[0] - 1][1];
	for (int i = 1; i <= n; i++)
	{
		x[i] = 0;//��ʼ������
		for (int k = head[i + 1]; k <= head[i] - 1; k++)
		{
			//�ж���Ʒi�Ƿ�װ��
			if ((p[k][0] + w[i] == j) && (p[k][1] + v[i] == m))
			{
				x[i] = 1;//��Ʒi��װ�룬��x[i]��1
				j = p[k][0];//j��mֵ��Ϊ����if��������Ծ���Ӧ��ֵ
				m = p[k][1];
				break;//�������ж���һ����Ʒ
			}
		}
	}
}